#!/bin/bash

# Clear terminal
clear

# Compile the C file
gcc Exer8.c

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the compiled program
    ./a.out
else
    echo "Compilation failed."
fi