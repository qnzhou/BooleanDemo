###About###

This repository contains minimalistic demos of various mesh boolean libraries.

It is created for the purpose of comparing robustness and performance of various
boolean libraries.  It is spun off from the
[boolean module of PyMesh](https://github.com/qnzhou/PyMesh/tree/master/tools/Boolean).

The libraries supported are:

* CGAL - Nef Polyhedron
* libigl

###Build###

    mkdir build
    cd build
    cmake ..
    make

###Useage###

All demos have the same command line interface:

    ./[library]_boolean [op] mesh1.off mesh2.off result.off

where `[library]` is either `libigl` or `cgal`,  and `[op]` could be any of
`union`, `intersection`, `difference` or `xor`.

Qingnan (James) Zhou<br>
New York University
