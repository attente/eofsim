#!/bin/sh

set -e

if [ "$1" = "clean" ]; then
  rm -f aclocal.m4 configure missing install-sh \
        depcomp ltmain.sh config.guess config.sub \
        `find . -name Makefile.in` compile
  rm -rf autom4te.cache
  exit
fi

aclocal-1.9
automake-1.9 --add-missing --foreign
autoconf
CFLAGS=-ggdb ./configure --enable-maintainer-mode "$@"
