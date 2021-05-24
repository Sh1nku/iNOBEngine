# iNOB Engine
![](https://img.shields.io/endpoint?url=https://inobstudios.com/LOCCounterBadge/iNOBEngine/responses/shields_v1) <br>
A c++17 based engine, using an entity-component-system structure. Capable of displaying 2d sprites in a 3d environment with either orthographic, or perspective projections.
## Features
 - Entities can have components, and can be manipulated by systems
 - Scripting system using Lua with the help of [Sol2](https://github.com/ThePhD/sol2)
 - Collision using [Box2d](https://box2d.org/)
 - Animation system for sprites
 - Event-Subscriber model for having different gameobjects react to events
 - UI using [Dear Imgui](https://github.com/ocornut/imgui) with support for text and buttons.
## Demonstration
An asteroid avoidance game, written entirely using the Lua scripting system
![AsteroidAvoidanceGame](https://i.imgur.com/8yT1eZm.gif)
