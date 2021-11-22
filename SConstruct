env = Environment();
env.Append(LIBS = ["sfml-graphics","sfml-window","sfml-system"]);

env.Program('bin/makeistrassh',       # Output executable
        ['main.cpp','scene/default.cpp', 'game.cpp'],
        CPPPATH=['#'])