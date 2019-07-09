#include <iostream>
#include <fstream>
#include <list>
#include <ctype.h>
#include <stdlib.h>
#include <stdexcept>
#include <vector>

using namespace std;

class hash_calculation
{
   public:
   //This method is used to calculate the hash for the vector by single character.
   unsigned short getHash(const vector<char> &charList) 
   { 
      unsigned short shift, hash = 0; 
      vector<char>::const_iterator itr; 
      for (itr = charList.begin(); itr != charList.end(); itr++) 
      { 
         hash ^= *itr; 
         shift = (hash & 15); 
         hash = (hash << shift) | (hash >> (16 - shift)); 
      }
      return hash;
   } 
};

class replace_process
{
   public:
   //This method for switching capital letter of fixed vector based on the original content.
   char swap(char orignial, char replaced)
   {
      if (isupper(orignial))
      {
         return toupper(replaced);
      }
      else
      {
         return replaced;
      }
   }
};
