/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    James Harris, Jerrald Nelson, Alexander Farrell
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

//#include "map.h"       // for MAP
#include <map>
#include <sstream>         // String Stream
#include <fstream>         // File
#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include "wordCount.h" // for wordCount() prototype
using namespace std;

bool debug;

/**********************************************************************
 * ReadFile
 * The function which reads the file/puts them into a map
 ***********************************************************************/
void ReadFile(map <string, int> & words, const string & fileName)
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
   string c="";

   //Getting one line from file at a time
   while (std::getline(fin, line))
   {
      //Declaring Variable
      std::stringstream ss(line);

      //inserting into variables
      //ss >> c;

      //looping through string items and inserting them into set
      for (int i = 0; ss >> c; i++)
      {
         //Debug code
         if (debug == true)
            cout << "Words  #: " << c << endl;

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
string getFileName()
{
   // get the fileName
   string fileName;
   cout << "What is the filename to be counted? ";
   cin >> fileName;
   return fileName;
}

/**********************************************************************
 * displays the results
 * The function which reads the word count
 ***********************************************************************/
void displayResults(map <string, int> & words)
{
   // get the word
   string word;
   cout << "What word whose frequency is to be found. Type ! when done";
   //cout << "Enter \"quit\" when done.\n";

   cout << "> ";
   cin >> word;

   while (word != "!")
   {
      int i = words[word];
      //cout << "> " << word << endl;
      cout << "        " << word << " : " << i << endl;
      cout << "> ";
      cin >> word;
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
   map<string,int> words;

   //Reading from file and filling vector
   ReadFile(words, getFileName());

   //Display the word counts
   displayResults(words);
}
