#ifndef _BERTHAINGEN_UTILITY_INC_
#define _BERTHAINGEN_UTILITY_INC_

#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "ptable.hpp"

namespace berthaingen
{
  void tokenize (const std::string &, std::vector<std::string> &,
      const std::string & delimiters = " ");
  
  bool is_float (const std::string &);
  
  bool is_integer(const std::string &);

  void multispace_to_single (std::string &);
  
  void rtrim(std::string &, const std::string & delimiters = " \f\n\r\t\v");

  void ltrim(std::string &, const std::string & delimiters = " \f\n\r\t\v");
  
  bool split_atom_and_basis (const std::vector<std::string> &,
      std::map<berthaingen::ptable::element, std::vector<std::string> > &,
      std::stringstream & errmsg);
}
#endif
