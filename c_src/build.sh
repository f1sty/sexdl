#!/usr/bin/env bash
gcc -fPIC -shared sdl_nif.c -o sdl_nif.so -I/usr/include/SDL2 -I/usr/lib/erlang/usr/include -I$HOME/.asdf/installs/erlang/26.0.1/usr/include/ -D_REENTRANT -L/usr/lib -lSDL2 -lSDL2_image
