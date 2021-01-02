# Hashing-in-C

Tested on gcc version 4.4.3 (GCC)

Commands to execute:

#Compiles the  C code

gcc -o hashing Hashing.c

#Executes the C code

./hashing file.txt

Sample input file is provided named as file.txt
The input file contains two columns of which column 1 is the command and column 2 is the parameter to be passed.
Command 10 is Insert, Command 11 is Deletion, Command 12 is Search, Command 13 is Print, Command 14 is Create, Command 15
is Comment: the rest of the line marked by a 15 is ignored.
Command 14 for create has an argument which is the value of N. Each one of 10, 11, and 12 has an argument which is a string.
