# Pokedex Project
# Overview
This project is a simple implementation of a Pokedex, a digital encyclopedia of Pokémon, using C programming language. It allows users to create and manage a list of Pokémon, each with its unique attributes.
This 'pokemon encyclopedia' (Pokedex) reads from a text file a list of pokemons and their special attributes, then creates a special Data Structure which is a Linked List of heaps.
Then a user can type in his own Pokemon with its attributes, and the system is capable of choosing the best pokemon to fight the user's Pokemon.
גdf

# Repository Structure
The repository contains the following main files in the "Assignment 2" folder:

mainFirst.c: The main file to run the program.
Pokemon.c: Contains the implementation of functions to create and print Pokémon.
Pokemon.h: Header file containing the declarations of the Pokémon structure and functions.
Pokedex.h: Header file (content not available).
# How to Run
Clone the repository to your local machine.
Navigate to the directory containing the source files.
Compile the program using a C compiler.
sh
Copy code
gcc mainFirst.c Pokemon.c -o pokedex
Run the compiled program.
sh
Copy code
./pokedex
# Features
Create Pokémon: allocate space, Allows users to create a new Pokémon with attributes such as name, type, HP, attack, defense, speed, special attack, and special defense.

Print Pokémon: Prints the details of a Pokémon to the console.

Add another Pokemon to the list of 'effective against me' current Pokemon

Delete Pokemon: Delete the Pokemon and deallocates the pokemon space.

