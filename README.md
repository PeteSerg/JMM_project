# JMM_project
CS3560 Team Project

Pete Sergakis -
GH: PeteSerg
OU Email: ps769417@ohio.edu </br>

This is a prototype. Renders an animation, and allows the player to enter text at the top of the screen.</br>
All you can do is 1. exit with escape, 2. exit by entering "exit", or 3. stop animation by entering "stop"

# Build
libsfml will need to be installed before building
```
$ g++ -c main.cpp game.cpp && g++ main.o game.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app
```
To generate .exe for windows (statically linked):
```
$ x86_64-w64-mingw32-g++ -c main.cpp game.cpp -I/path/to/windows/sfml/binary/include/
$ x86_64-w64-mingw32-g++ -DSFML_STATIC -I/path/to/windows/sfml/include -L/path/to/windows/binary/lib main.cpp game.cpp -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static-libgcc -static-libstdc++
```
Pete Sergakis: GH - PeteSerg
Gabe Havas: GH - ghavas444
Eric Nelson: GH - xnely
Owen Rutter: GH - OR0611

# Project

Our group is making a text based adventure game. Our goal is to make a game with
multiple paths for the player to explore. We're hoping to include simple visuals
and graphics with each stage. 
