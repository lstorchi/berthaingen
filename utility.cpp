#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

//#include <boost/regex.hpp>

#include "utility.hpp"

namespace 
{
  bool both_are_spaces (char lhs, char rhs) 
  { 
    return (lhs == rhs) && (lhs == ' '); 
  }
}

bool berthaingen::is_float (const std::string & s) 
{
  std::istringstream iss(s);
  float f;
    
  iss >> std::noskipws >> f; 
                
  return iss.eof() && !iss.fail(); 
}

bool berthaingen::is_integer(const std::string & s)
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

void berthaingen::multispace_to_single (std::string & str)
{
  std::string::iterator new_end = 
    std::unique(str.begin(), str.end(), both_are_spaces);
  str.erase(new_end, str.end());   

  //boost::regex_replace(str, boost::regex("[' ']{2,}"), " ");
}

bool berthaingen::split_atom_and_basis (
    const std::vector<std::string> & setfname,
    std::map<berthaingen::ptable::element, std::vector<std::string> > & 
    set_map, std::stringstream & errmsg)
{
  std::vector<std::string>::const_iterator iter = setfname.begin();
  for (; iter != setfname.end(); ++iter)
  {
    std::vector<std::string> vctstring;
    berthaingen::tokenize (*iter, vctstring, ":");
    if (vctstring.size() == 2)
    {
      berthaingen::ptable::element e = 
        berthaingen::ptable::symbol_to_element(vctstring[0].c_str());

      if (e == berthaingen::ptable::NO_ELEMENT)
      {
        errmsg << "Error in element: " << vctstring[0];
        return false;
      }

      std::vector<std::string> lines;
      std::ifstream fp;
      fp.open(vctstring[1].c_str());
      if (fp.is_open()) 
      {
        while (!fp.eof()) 
        {
          std::string line;
          std::getline (fp, line);
          if (line.find_first_not_of("\t\n ") != std::string::npos)
            lines.push_back(line);
        }
      }
      fp.close();

      if (set_map.find(e) == set_map.end())
      {
        set_map[e] = lines;
      }
      else
      {
        errmsg << "Element " << vctstring[0] << " many times present ";
        return false;
      }
    }
    else
    {
      errmsg << "Error in set: " << *iter;
      return false;
    }
  }

  return true;
}
