#! /bin/sh

aclocal -I autoconf
glibtoolize --force --copy
autoreconf -vfi
