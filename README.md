# FoilBoXX
__A design tool for (wortman-)flapped airfoils with a fresh user-interface, uses a class-shape parametrization with bernstein polynomials as shape functions__

__External Libraries:__
- xfoil-cpp-master (https://github.com/kamino410/xfoil-cpp), GPL-v3
- GPL-v3 licenced version of Qt5 (https://www.qt.io/download-open-source)
- Qwt Plot (https://qwt.sourceforge.io/), LGPL
- dlib (http://dlib.net/), Boost software licence
- armadillo (http://arma.sourceforge.net/), Apache 2.0
- openBlas (https://www.openblas.net/), BSD

__For compiling from source install on your system:__
- openBlas (on arch linux only https://aur.archlinux.org/packages/openblas-lapack worked for use with dlib)
- qt5 (packages qt5-default and on apt also: qtbase5-dev)
- Temporary fix for xfoil-cpp ("Memset not declared"): Modify XFoil.h: add "#include <cstring>" to headers

__Roadmap:__\
In further Developement, the following functionality is planned:
- draw Blueprints to the PressurePlot for every FoilMode, for reference
- add geometric Optimization for minimization of gap between blueprint and pressure-Distribution
- same on Polars
- More refined analysis, like H parameter, delta*, theta and friction coefficient

__Contributing to the source code:__\
If you want to help me on the developement of the FoilBoXX, please contact me:
paulbieberstein@gmail.com
