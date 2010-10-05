#!/bin/sh
make maintainer-clean
./autogen.sh
./configure --prefix=$HOME/usr
make
