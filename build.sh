#!/bin/bash

# Script to build a static library from nulibc.c and nulibc.h, and package them into a zip file

# Clean previous builds
rm -rf ./nulibc.a ./nulibc.o ./nulibc.zip

# Ensure nulibc.c and nulibc.h exist
if [[ ! -f "nulibc.c" || ! -f "nulibc.h" ]]; then
    echo "Error: nulibc.c and/or nulibc.h not found."
    exit 1
fi

# Compile nulibc.c into an object file with musl-gcc
echo "Compiling nulibc.c into nulibc.o..."
musl-gcc -c nulibc.c -o nulibc.o -static

# Create a static library (nulibc.a) from the object file
echo "Creating static library nulibc.a..."
ar rcs nulibc.a nulibc.o

# Verify the static library
echo "Verifying nulibc.a..."
ar -t nulibc.a

# Package the static library, .c, and .h files into a zip
echo "Packaging nulibc.a, nulibc.c, and nulibc.h into nulibc.zip..."
zip nulibc.zip nulibc.a nulibc.c nulibc.h

# Clean up intermediate files
rm -rf ./nulibc.o

echo "Build and packaging completed: nulibc.zip contains nulibc.a, nulibc.c, and nulibc.h."
