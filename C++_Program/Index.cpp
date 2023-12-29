#include "Index.h"
#include "Location.h"

void Index::add_word(Word word, std::string filename, int line)
{
   Location highlighted = Location(filename, line);

   if(_index.count(word) == 0)//If equal, create a new set of locations
   {
      std::set<Location> locations;
      locations.insert(highlighted);    
      _index[word] = locations;   //Assign the set of locations to the word in the index
   
   }
   else//If not...
   {
      _index[word].insert(highlighted); //Insert the location into the existing set for the word
   }
}


std::ostream& operator<<(std::ostream& ost, const Index& index)
{
   for(const auto& word : index._index)
   {
      ost << "\n" << word.first << ": ";       //Print the keyword as the subtitle for location

      for(const Location& it : word.second)  //Prints the location (based on Location.cpp) this key
      {                                     //word has been founded and iterrate for each one
         ost << it << " ";
      }
      ost << "================";
   }
   return ost;
}
