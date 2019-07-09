#include <iostream>
#include <fstream>
#include <list>
#include <stdlib.h>
#include <ctype.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "replacement.h"
using namespace std;
/*This is a program that converts English into "Euro-English" by C++,
  which is part of the Data Structure and Algorithm's assignment.
  Also, this program gets the name of the file containing the English to be converted as a command line argument.
  It will then read the file and build uo the English message, character by character, in a linked list.
  Each node in the list will contain a single character.
*/
int main (int argc, char *argv[])
{
   hash_calculation hc;
   replace_process rp;
   vector<char> storedVectors, newVectors;

   int index = 0;
   if (argc == 2)
   {
      ifstream fin;
      char c;
      fin.open(argv[1]);

      //Read the file from arugement, open and store it as vector.
      try
      {
         if(!fin) 
		 {
		    throw exception();
		 }
		 
         while (!fin.eof())
         {
            c = fin.get();
            if (fin.good())
            storedVectors.push_back(c);
         }
		 
		 for(index = 0; index < storedVectors.size(); index++)
         {
           cout << storedVectors[index];
		   char currentValue = storedVectors[index];
		   //Replace all instances of 'w' with 'v'.
		   if(tolower(currentValue) == 'w')
		   {
			   char replaceVector = rp.swap(currentValue, 'v');
			   newVectors.push_back(replaceVector);
		   }
		   //Replace all double characters with a single instance of the character.
		   else if (tolower(currentValue) == tolower(storedVectors[index - 1]))
		   {
			   newVectors.push_back(currentValue);
			   if(newVectors.back() == newVectors.end()[-2] && isalpha(newVectors.back()))
			   {
				   newVectors.pop_back();
			   }
			   
		   }
		   //Replace all instances of "ph" with 'f'.
		   else if (tolower(currentValue) == 'h' && tolower(storedVectors[index - 1]) == 'p')
		   {
			   char replaceVector = rp.swap(newVectors.back(), 'f');
			   newVectors.pop_back();
			   newVectors.push_back(replaceVector);
		   }
		   //Replace all instances of "th" with 'z'.
		   else if (tolower(currentValue) == 'h' && tolower(storedVectors[index - 1]) == 't')
		   {
			   char replaceVector = rp.swap(newVectors.back(), 'z');
			   newVectors.pop_back();
			   newVectors.push_back(replaceVector);
		   }
		   //Replace all instances of "ou" with 'u'.
		   else if (tolower(currentValue) == 'u' && tolower(storedVectors[index - 1]) == 'o')
		   {
			   char replaceVector = rp.swap(newVectors.back(), 'u');
			   newVectors.pop_back();
			   newVectors.push_back(replaceVector);
		   }
		   //Replace all instances of "ea" with 'e'.
		   else if (tolower(currentValue) == 'a' && tolower(storedVectors[index - 1]) == 'e')
		   {
			   char replaceVector = rp.swap(newVectors.back(), 'e');
			   newVectors.pop_back();
			   newVectors.push_back(replaceVector);
		   }
		   //Replace all instances 'c' with 'k'.
		   else if (tolower(storedVectors[index - 1]) == 'c')
		   {
			   char replaceVector = rp.swap(newVectors.back(), 'k');
			   //If followed by the characters 'e', 'i'or 'y', replace with 's'.
			   if(tolower(currentValue) == 'e' || tolower(currentValue) == 'i' || tolower(currentValue) == 'y')
			   {
				    replaceVector = rp.swap(newVectors.back(), 's');
			   } 

			   newVectors.push_back(currentValue); //Add the followed letter.
			   newVectors.end()[-2] = replaceVector; //Replace the changed in the letter 'c' position.
			   if(newVectors.back() == newVectors.end()[-2])
			   {
				  newVectors.pop_back(); //Remove the last letter if it same as previous letter.
			   }
			   
			   //After this function, removed the ending with an 'e' if this word is more than 3 characters long.
			   	int i = 0; //Use to count the length of characters.
				int j = -1; //Use to point the position of the fixed vector.
				while(isalpha(newVectors.end()[j]))
				{
					j--;
					i++;
				}
				//Remove the last letter 'e' if the word count is more than 3.
				if(i > 3 && newVectors.back() == 'e' && !isalpha(storedVectors[index + 1]))
				{
					newVectors.pop_back();
				}
			   
		   }
		   //If a word is more than 3 characters long and ends with an 'e' then it can be removed.
		   else if (currentValue == 'e' && !isalpha(storedVectors[index + 1]))
		   {
				newVectors.push_back(currentValue);
				int i = 0;
				int j = -1; 
				while(isalpha(newVectors.end()[j]))
				{
					j--;
					i++;
				}
				if(i > 3)
				{
					newVectors.pop_back();
				}
		   }
		   //If a word ends with "ed" then replace it with 'd'.
		   else if (currentValue == 'd' && !isalpha(storedVectors[index + 1]))
		   {
			   if(newVectors.back() == 'e')
			   {
				   newVectors.pop_back();
			   }
			   	newVectors.push_back(currentValue);
		   }
		   //The original vector will be stored in the new vector if it didn't apply previous rule.
		   else
		   {
			   newVectors.push_back(currentValue);
		   }
		   
		   
		 }
         cout << "\n" << "hash = " << hc.getHash(storedVectors) << "\n"; //Print the hash value of the original file content.
		 
		 //Print the fixed vector again which contains the modification from previous function.
		 for(index = 0; index < newVectors.size(); index++)
		 {
		    //Eliminate the 'e' again if the word is more than 3 characters long and ends with it. 
			if(newVectors[index] == 'e' && !isalpha(newVectors[index + 1]))
			{
				int i = 0;
				int j = 1;
				while(isalpha(newVectors[index - i]))
				{
					j--;
					i++;
				}
			    if(i > 3)
				{
					newVectors.erase(newVectors.begin() + index);
				}
			}
			else
			{
			  cout << newVectors[index];
			}
		 }
		 cout << "\n" << "hash = " << hc.getHash(newVectors) << "\n"; //Print the hash value of the fixed content.
      }
      catch (const exception& e)
      {
         cerr << "Unable to open file \n"; //Message if the file is failed to open.
         exit(1);
      }
      fin.close();
   }
   else
   {
      cout << "Syntax: ./euro file \n"; //Message if the syntax is not correct.
   }  

   return 0;
};
