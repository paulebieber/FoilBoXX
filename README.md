# FoilBoXX
__A design tool for (wortman-)flapped airfoils with a fresh user-interface, uses a class-shape parametrization with bernstein polynomials as shape functions__

__Download & Use (only Linux for now):__

1) Go to releases, choose th latest one, open assets and download the AppImage\
    -> https://github.com/paulebieber/FoilBoXX/releases
2) Open a terminal, and run chmod +x on the AppImage to make it executable, then run it\
    alternative: open Filebrowser, rightclick the AppImage, under Properties/Accessablitiy activate run as executable\
    
__External Libraries:__
- xfoil-cpp-master (https://github.com/kamino410/xfoil-cpp), GPL-v3
- GPL-v3 licenced version of Qt5.9.9 (https://www.qt.io/download-open-source)
- Qwt Plot (https://qwt.sourceforge.io/), LGPL
- dlib (http://dlib.net/), Boost software licence
- armadillo (http://arma.sourceforge.net/), Apache 2.0
- openBlas (https://www.openblas.net/), BSD

__For compiling from source:__
- install Qt5.9.9 (best via https://www.qt.io/offline-installers)
- install openBlas (on arch linux only https://aur.archlinux.org/packages/openblas-lapack worked for use with dlib)
- install mesa-common-dev (packagename for apt)
- after cloning do a git submodule update --init
- For ubuntu use snap to get the latest cmake version
- Check for right CMAKE_PREFIX_PATH for including the Qt cmake folder in the CMakeLists.txt
- Information: Temporary fix for xfoil-cpp ("Memset not declared"): Modified XFoil.h: added "#include \<cstring\>" to headers

__Roadmap:__\
In further Developement, the following functionality is planned:
- draw Blueprints to the PressurePlot for every FoilMode, for reference
- add geometric Optimization for minimization of gap between blueprint and pressure-Distribution
- More refined analysis, like H parameter, delta*, theta and friction coefficient

__Contributing to the source code:__\
If you want to help me on the developement of the FoilBoXX, please contact me:
paulbieberstein@gmail.com
