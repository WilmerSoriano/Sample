// Copyright 2023 Wilmer Soriano 
// This file is part of the Index Sorting System and is licensed
// under the terms of the Gnu General Public License version 3 or
// any later version, see <https://www.gnu.org/licenses/>.

#include "Index.h"
#include <sstream>
#include <fstream>

int main(int argc, char* argv[])
{
   Index In; //Moved outside the loop to accumulate words from all files
   
   if(argc < 2) //If user does not use atleast 1 file, stream out an error message
   {
      std::cerr << "How to use: ./mkindex <file1> <file2> ...etc" << std::endl;
      std::cerr << "\n Exisitng program...\n" << std::endl;
      return 1;
   }

   for(int file = 1; file < argc; ++file) 
   {
      std::string filename = argv[file]; //Aquire the filename found in arguments
      std::ifstream ist(filename);
      
      if(!ist) //Open file
      {
         std::cerr << "Failed to open file: " << filename << "\n\n Exisitng program ...\n" << std::endl;
         return 1;
      }

      Word word;      //These data type must be inside the loop, for each new file it must reset to default value
      int line = 1;
      std::string read;
      
      while(std::getline(ist, read))
      {
         std::istringstream iss(read);

         while (iss >> word)  //Remove word processing logic (removing punctuation, converting to lowercase, etc.) 
         {
            //Add processed word to the index
            In.add_word(word, filename, line);
         }
         ++line;
      }
      ist.close(); //Close file
   }
   //Stream the whole index outside the loop after processing all files
   std::ostringstream oss;
   oss << In;

   std::cout << "\n\t\t= = =Index= = =" <<std::endl;
   std::cout << "Note: Please read Word carefuly when searching for Index\n" <<std::endl;
   std::cout << oss.str() << std::endl;
   std::cout << "\n\t\t= = =End of Index= = =" << std::endl;

   return 0;
}
