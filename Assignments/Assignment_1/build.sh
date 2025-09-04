#!/bin/bash

# Exit immediately if a command fails
set -e

# The input file for the parser is the first argument to the script
INPUT_FILE=$1

# Check if an input file was provided
if [ -z "$INPUT_FILE" ]; then
    echo "Error: Please provide an input file."
    echo "Usage: ./build.sh <filename>"
    exit 1
fi

echo "Step 1: Running Bison on P1.y..."
bison -dy P1.y

echo "Step 2: Running Flex on P1.l..."
flex P1.l

echo "Step 3: Compiling with g++..."
g++ y.tab.c lex.yy.c -o parser

echo "Step 4: Running parser on $INPUT_FILE..."
./parser < "$INPUT_FILE" > test.java

echo "Done."