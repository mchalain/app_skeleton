#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "log.h"
#include "daemonize.h"

#define MODE_DAEMONIZE 0x01
#define MODE_KILLDAEMON 0x02

void help(void)
{
	fprintf(stderr, "Usage: $s [OPTION]...\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  -h          display this message\n");
	fprintf(stderr, "  -W <path>   change working directory\n");
	fprintf(stderr, "  -D          daemonize the process\n");
	fprintf(stderr, "  -P <file>   set the daemonized pid into file\n");
	fprintf(stderr, "  -U <user>   set the owner of the daemonized process\n");
	fprintf(stderr, "  -C <file>   set the configuration file\n");
}

int main(int argc, char *const argv[])
{
	const char *logfile = "-";
	const char *rootfs = NULL;
	const char *pidfile= NULL;
	const char *owner= NULL;
	const char *configfile = NULL;
	int mode = 0;

	int opt;
	do
	{
		opt = getopt(argc, argv, "hL:W:DKP:U:C:");
		switch (opt)
		{
			case 'h':
				help();
				exit(-1);
			break;
			case 'D':
				mode |= MODE_DAEMONIZE;
			break;
			case 'K':
				mode |= MODE_KILLDAEMON;
			break;
			case 'P':
				pidfile = optarg;
			break;
			case 'U':
				owner = optarg;
			break;
			case 'L':
				logfile = optarg;
			break;
			case 'W':
				rootfs = optarg;
			break;
			case 'C':
				configfile = optarg;
			break;
		}
	} while(opt != -1);

	if (mode & MODE_KILLDAEMON)
	{
		killdaemon(pidfile);
		exit(0);
	}

	if (strcmp(logfile,"-"))
	{
		int logfd = open(logfile, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		if (logfd > 0)
		{
			dup2(logfd, 1);
			dup2(logfd, 2);
			close(logfd);
		}
		else
			err("log file error %m");
	}

	daemonize((mode & MODE_DAEMONIZE) == MODE_DAEMONIZE, pidfile, owner, rootfs);

	while (isrunning()) pause();

	killdaemon(pidfile);
	dbg("process died");
	return 0;
}
