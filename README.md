## Getting Started

This is my COMP 2150 Assignment 2 submission. This `README` file is written specifically to show how to compile and run the program

## Folder Structure

Inside this zip file (folder once uncompressed) contains 16 C++ headers and their implementations, a main.cpp file to run, a header file that contains enums, this README file and a Makefile. The main.cpp file contains the main method, so this is where you want to run the program.

## How to run 

In order to compile to run the program on Aviary, you can use either of these two options:

1) Compile and run directly:
    - On your Aviary terminal, you can use the following commands to compile the files and run the executable file:
        g++ -Wall -g *.cpp -o main -std=c++11
        ./main [your_file_here.txt] [your_runways_here]

2) Compile and run using Makefile:
    - On your Aviary terminal, you can use the following commands to compile and run the Java files:
        make main
        ./main [your_file_here.txt] [your_runways_here]

Both requires you to pass an input file via command line argument, otherwise the program might throw an error and terminates.
