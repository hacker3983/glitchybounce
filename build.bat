@echo off
echo Building glitchy bounce...
gcc main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o glitchybounce
echo Running glitchy bounce...
glitchybounce.exe