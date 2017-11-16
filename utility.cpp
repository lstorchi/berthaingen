#include <string>
#include <sstream>

#include "utility.hpp"

bool berthaingen::is_float (const std::string & s) 
{
  std::istringstream iss(s);
  float f;
    
  iss >> std::noskipws >> f; 
                
  return iss.eof() && !iss.fail(); 
}

bool berthaingen::isInteger(const std::string & s)
{
  if(s.empty() || ((!isdigit(s[0])) && 
        (s[0] != '-') && (s[0] != '+'))) 
    return false ;

  char * p ;
  strtol(s.c_str(), &p, 10) ;

  return (*p == 0) ;
}

void berthaingen::tokenize (const std::string & str, 
    std::vector<std::string> & tokens,
    const std::string & delimiters)
{
  // Skip delimiters at beginning.
  std::string::size_type lastPos = 
    str.find_first_not_of(delimiters, 0);
  std::string::size_type pos = 
    str.find_first_of(delimiters, lastPos);
  
  while (std::string::npos != pos || 
      std::string::npos != lastPos)
  {
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delimiters, pos);
    pos = str.find_first_of(delimiters, lastPos);
  }
}
