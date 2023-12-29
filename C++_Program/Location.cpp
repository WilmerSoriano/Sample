#include "Location.h"
 
   Location::Location(std::string filename, int line) //Part of the Map array in Index.cpp
   :_filename{filename}, _line{line}{}
   
   std::ostream& operator<<(std::ostream& ost , const Location& location)  //Prints the name of the file and what number line is located
   {
      ost << location._filename << " line " << location._line <<'\n';
      return ost;
   }
   
   int Location::compare(const Location& location)const //Part of H_file 
   {                                                    //Design to use a class with operators in main
      if(_filename < location._filename)return -1;
      if(_filename > location._filename)return -1;
      if(_line < location._line)return -1;
      if(_line > location._line)return -1;
      return 0;
   }   