#!/bin/bash

set -e
OUTPUT="system"

echo "compiling system.cpp..."
clang++ -std=c++17 -Wall -o $OUTPUT system.cpp
echo "compliation of system.cpp successful!"

if [ "$1" = "run" ]; then
    echo "Running program..."
    ./"$OUTPUT"
fi
