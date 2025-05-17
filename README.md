# project name

This project is just a skeleton for new C application.

## Getting started

The project uses only Makefile{s}. The GNU standard variables and rules are allowed:
 - *prefix=<path>* to change the installation prefix and other pathes
 - *DESTDIR=<path>* to prefix the path during installation
 - *NDEBUF=[y|n]* to enable/disable debug options
 - *DEBUG=[y|n]* the same as previous but converse the meaning
 - *BUILDDIR=<path>* to create a build directory and generates files inside it
 - *defconfig* to generate configuration files
 - *oldconfig* to re-generate configuration files with new options
 - *install* to install the project into \*NIX files tree

Standard usage:
```shell
$ make prefix=/usr sysconfdir=/etc BUILDDIR=build defconfig
$ cd build
$ make
$ make DESTDIR=$PWD/package install
$ tar -C package -czf package.tar.gz *
```

## Usage


