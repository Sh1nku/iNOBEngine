
# iNOB Engine
![Tests](https://github.com/Sh1nku/iNOBEngine/actions/workflows/tests.yml/badge.svg)
![](https://inobstudios.com/LOCCounterBadge/iNOBEngine/responses/pybadges) <br>
A c++17 based engine, using an entity-component-system structure. Capable of displaying 2d sprites in a 3d environment with either orthographic, or perspective projections.
## Features
 - Entities can have components, and can be manipulated by systems
 - Scripting system using Lua with the help of [Sol2](https://github.com/ThePhD/sol2)
 - Collision using [Box2d](https://box2d.org/)
 - Animation system for sprites
 - Event-Subscriber model for having different gameobjects react to events
 - Writing UIs with HTML by embedding [Cef](https://bitbucket.org/chromiumembedded) 
## Demonstration
An asteroid avoidance game, written entirely using the Lua scripting system
![AsteroidAvoidanceGame](https://user-images.githubusercontent.com/42642351/126903753-08e08fb9-1dca-488d-bad0-fb42808e22f5.gif)


## Build
You will need the [conan](https://conan.io/) (Note: 2x not supported yet use 1.60.0) package manager and the remote repository for bincrafters
- Note: If on linux using GCC you should run this to use the new GCC abi `conan profile update settings.compiler.libcxx=libstdc++11 default`
this requires the profile `default` to already exist, if not use `conan profile new default --detect`
```
conan config set general.revisions_enabled=1
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan remote add inobstudios https://conan.inobstudios.com
mkdir build
cd build
conan install .. --build=missing
cmake ..
```
