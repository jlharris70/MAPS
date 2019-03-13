###############################################################
# Program:
#     Assignment 09, Binary Search Tree
#     Brother Kirby, CS235
# Author:
#    Jerrald Nelson
#    Alexander Farrell
#    James Harris
# Summary:
#    This program demonstrates the use of a custom bnode 
#    class through various tests. It also displays its use
#    in the Huffman application which handles the code
#	 generation.
# Time:
#     Collaboration: 1 Hour
#     Alex: 2 Hours
#     Jerrald: 3.5 Hours
#     James
# The most difficult part: 
#     Jerrald: The Classes implimentation of its private and 
#			   public interfaces and how it interacts with
#			   the assignment class.
#     Alex:    Having to redesign program requests midway to 
#              support modifcations of the more advanced test.
#     James:   Coding the bnode class
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment09.o
	g++ -o a.out assignment09.o -g -std=c++11
	tar -cf assignment09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment09.o     : the driver program
##############################################################
assignment09.o: bst.h assignment09.cpp
	g++ -c assignment09.cpp -g -std=c++11

