/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    James Harris, Jerrald Nelson, Alexander Farrell
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       // for MAP
//#include <map>
#include <sstream>         // String Stream
#include <fstream>         // File
#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include "wordCount.h" // for wordCount() prototype
using namespace custom;

bool debug;

/**********************************************************************
 * ReadFile
 * The function which reads the file/puts them into a map
 ***********************************************************************/
void ReadFile(map <std::string, int> & words, const std::string & fileName)
{

   std::ifstream fin(fileName);

   //Checking to see if opening file failed
   if (fin.fail())
   {
      std::cout << "File not found or failed to open.";
      return;
   }

   std::string line;

   //The Value
   std::string c="";

   //Getting one line from file at a time
   while (std::getline(fin, line))
   {
      //Declaring Variable
      std::stringstream ss(line);


      //looping through string items and inserting them into map
      for (int i = 0; ss >> c; i++)
      {
         //Debug code
         if (debug == true)
            std::cout << "Words  #: " << c << std::endl;

         if (c != "")
         {
            //Find
            if (words.find(c) != words.end())
            {
               words[c] = words[c] + 1;
            }
            else { words[c] = 1; }
         }
      }

   }

   //close file
   fin.close();
}

/**********************************************************************
 * fileName
 * The function which gets the file name
 ***********************************************************************/
std::string getFileName()
{
   // get the fileName
   std::string fileName;
   std::cout << "What is the filename to be counted? ";
   std::cin >> fileName;
   return fileName;
}

/**********************************************************************
 * displays the results
 * The function which reads the word count
 ***********************************************************************/
void displayResults(map <std::string, int> & words)
{
   // get the word
   std::string word;
   std::cout << "What word whose frequency is to be found. Type ! when done\n";

   std::cout << "> ";
   std::cin >> word;

   // loop for different words until done.
   while (word != "!")
   {
      int i = words[word];
      std::cout << "\t" << word << " : " << i << std::endl;
      std::cout << "> ";
      std::cin >> word;
   }
}

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   //Debug flag
   debug = false;

   //Create map 
   map<std::string,int> words;

   //Reading from file and filling map
   ReadFile(words, getFileName());

   //Display the word counts
   displayResults(words);
}
