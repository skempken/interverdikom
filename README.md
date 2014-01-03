InterVerdiKom
=============

What is this?
-------------
The stuff PHD thesises are made of. ;-)

See http://skempken.github.io/interverdikom for details (German).

Build Instructions
------------------

On Ubuntu 12.04 Precise, install the following packages, for instance, via _apt-get_:
- build-essential
- libqt4-dev
- libqwt5-qt4-dev
- liblapack-dev
- libfftw3-dev
- gfortran

C-XSC:
This is a 3rd party dependency that needs to be compiled and installed as well, the source is provided in the _/vendor_
directory. Use the provided script *install_cxsc*.

InterVerdiKom:
Use the _configure_ script, followed by the _build_ script, provided in the main directory.
