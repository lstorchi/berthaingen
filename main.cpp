#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <getopt.h>

namespace 
{
   void tokenize (const std::string & str, std::vector<std::string> & tokens,
       const std::string & delimiters = " ")
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
}


void usages (char * name) 
{
  std::cerr << "usage: " << name << " [option] xyz" << std::endl;
  std::cerr << " -h, --help                   : display this help and exit" << std::endl;
  std::cerr << " -b, --basis-set=[filename1;...;filename2]   " << std::endl;
  std::cerr << "                              : specify basisset filenames " << std::endl; 
  std::cerr << " -f, --fit-set=[filename1;...;filename2]     " << std::endl;
  std::cerr << "                              : specify fitset filenames " << std::endl;  
 
  exit (1);
}

int main (int argc, char ** argv) 
{
  std::vector<std::string> basisset_fname, fitset_fname;

  while (1) 
  {
    std::string inputs;

    int c, option_index;
    static struct option long_options[] = {
      {"help", 0, NULL, 'h'},
      {"basis-set", 0, NULL, 'b'},
      {"fit-set", 0, NULL, 's'},
      {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "hb:f:", long_options, &option_index);
    
    if (c == -1)
      break;

    switch (c) {
      case 'h':
        usages (argv[0]);
        break;
      case 'b':
        inputs.assign(optarg);
        tokenize (inputs, basisset_fname, ";");
        break;
      case 'f':
        inputs.assign(optarg);
        tokenize (inputs, fitset_fname, ";");
        break;
      default:
	usages (argv[0]);
        break;
    }
  }

  if (optind >= argc) 
    usages (argv[0]);

  return 0;
}
