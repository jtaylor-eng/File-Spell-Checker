# File-Spell-Checker

This project is meant to check a given input file for words not found in a given dictionary. 
It utilizes a linked list hash table to quickly hash your given dictionary then look up each
word scanned from the input text. Any words not existing in the hash table are then output as incorrect.
clocks are introduced in the program to also output the time of the given hash functions.

See dictionary.c for these implementations.

Usage: ./speller [DICTIONARY] [TEXT]

where DICTIONARY is a dictionary you want to use to spell check TEXT.

A dictionary is already supplied in /dictionaries under large. Others could be added however.

Many texts have been imported into /keys. Add more for files you want to check against a dictionary.

