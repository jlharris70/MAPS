###############################################################
# Program:
#     Assignment 10, Map
#     Brother Kirby, CS235
# Author:
#    Jerrald Nelson
#    Alexander Farrell
#    James Harris
# Summary:
#    This program demonstrates the use of a custom map 
#    class through various tests. It also displays its use
#    in the word count application which handles the map
#	 class to count words.
# Time:
#     Collaboration: 1 Hour
#     Alex: 2 Hours
#     Jerrald: 3.5 Hours
#     James
# The most difficult part: 
#     Jerrald: The reading in of the words and putting them 
#			   into the map class.
#     Alex:    Having to redesign program requests midway to 
#              support modifcations of the more advanced test.
#     James:   Coding the bnode class
#			   the assignment class.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment10.o wordCount.o
	g++ -o a.out assignment10.o wordCount.o -g -std=c++11
	tar -cf assignment10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment10.o : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
assignment10.o: pair.h map.h bst.h assignment10.cpp
	g++ -c assignment10.cpp -g -std=c++11

wordCount.o: map.h bst.h wordCount.h wordCount.cpp 
	g++ -c wordCount.cpp -g  -std=c++11
