#!/usr/bin/env bash
gcc -o test main.c -I/usr/include/SDL2 -D_REENTRANT -L/usr/lib -lSDL2 -lSDL2_image
