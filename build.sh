#!/usr/bin/bash

# arquivo de compilação
g++ src/*.cpp -g -Wall -I include -I ~/raylib/src -m64 -lraylib -lGL -lpthread -lm -lrt -ldl -lX11 -o bin/main && bin/main