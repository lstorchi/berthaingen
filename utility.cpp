#include <string>
#include <sstream>

#include "utility.hpp"

using namespace berthaingen;

bool is_float (const std::string & s) 
{
  std::istringstream iss(s);
  float f;
    
  iss >> std::noskipws >> f; 
                
  return iss.eof() && !iss.fail(); 
}

bool isInteger(const std::string & s)
{
  if(s.empty() || ((!isdigit(s[0])) && 
        (s[0] != '-') && (s[0] != '+'))) 
    return false ;

  char * p ;
  strtol(s.c_str(), &p, 10) ;

  return (*p == 0) ;
}
