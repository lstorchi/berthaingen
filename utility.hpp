#include <string>
#include <vector>

namespace berthaingen
{
  void tokenize (const std::string &, std::vector<std::string> &,
      const std::string & delimiters = " ");
  
  bool is_float (const std::string &);
  
  bool is_integer(const std::string &);
}
