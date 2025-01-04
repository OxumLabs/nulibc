#!/bin/bash

# Script to build a fully static library from nulibc.c and nulibc.h, and package them into a zip file

# Clean previous builds
rm -rf ./libnulibc.a ./nulibc.o ./nulibc.zip

# Ensure nulibc.c and nulibc.h exist
if [[ ! -f "nulibc.c" || ! -f "nulibc.h" ]]; then
    echo "Error: nulibc.c and/or nulibc.h not found."
    exit 1
fi

# Compile nulibc.c into an object file with musl-gcc for static linking
echo "Compiling nulibc.c into nulibc.o (static)..."
musl-gcc -static -c nulibc.c -o nulibc.o

# Create a static library (libnulibc.a) from the object file
echo "Creating static library libnulibc.a..."
ar rcs libnulibc.a nulibc.o

# Verify the static library
echo "Verifying libnulibc.a..."
ar -t libnulibc.a

# Package the static library, .c, and .h files into a zip
echo "Packaging libnulibc.a, nulibc.c, and nulibc.h into nulibc.zip..."
zip nulibc.zip libnulibc.a nulibc.c nulibc.h

# Clean up intermediate files
rm -rf ./nulibc.o

echo "Build and packaging completed: nulibc.zip contains libnulibc.a, nulibc.c, and nulibc.h."
