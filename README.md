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

# Tools
1. 1. We will use the programming language C++ as our main base for the project, and 
possibly use SFML to implement graphics for the game

2. We will use VScode as our editor

3. For version control we are going to be using Github so that we can easily make changes
and be able to keep track of them, given that this is the version control manager we
are all most comfortable with

Team Roles-
Owen Rutter- lead writer

Eric Nelson- top down researcher

Pete Sergakis - Team organizer + programming

Gabe Havas - Programming

4. We are using SFML (Simple and Fast Multimedia Library) to handle graphics
5. We are using VSCode's IntelliSense to easily reference documentation elsewhere in our code. We are using no tools to generate documentation at this time.
6. There should be a build system. We will probably use make, and we may use premake.