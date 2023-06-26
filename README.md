OpenScop Library 0.9.7
======================

Installation
------------

Arch Linux users can install the library via the AUR:

```.bash
$ yay -S osl
```

Dependencies
------------

Recommended packages:

```.bash
# For Ubuntu
$ apt install build-essential autoconf automake autotools-dev libtool libgmp-dev autoconf-archive ccache doxygen
# For Fedora
$ dnf install @c-development @development-tools libtool gmp-devel autoconf-archive ccache
# For Arch Linux
$ pacman -S base-devel posix-c-development autoconf-archive gmp ccache
```

Build + installation via autotools
----------------------------------

```.bash
$ autoreconf -fi
$ mkdir build
$ cd build
$ ../configure CC="ccache cc"
$ make -j$(nproc)
$ make install
```


Alternative: build and install with CMake (experimental, may not work!)
-----------------------------------------------------------------------

```.bash
$ mkdir build
$ cd build
$ cmake .. # -DCMAKE_INSTALL_PREFIX="/your/install/directory"
$ make
$ make test
$ # make install # sudo make install # su -c "make install"
$ make doc
```


Support
-------

Please contact:
openscop-development@googlegroups.com
