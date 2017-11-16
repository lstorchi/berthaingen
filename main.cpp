#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <getopt.h>

#include "molecule.hpp"
#include "utility.hpp"

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
        berthaingen::tokenize (inputs, basisset_fname, ";");
        break;
      case 'f':
        inputs.assign(optarg);
        berthaingen::tokenize (inputs, fitset_fname, ";");
        break;
      default:
	usages (argv[0]);
        break;
    }
  }

  if (optind >= argc) 
    usages (argv[0]);

  std::string filename = argv[optind];

  berthaingen::molecule mol;

  if (mol.read_xyz_file(filename.c_str()))
  {
    std::cout << "Atoms: " << mol.get_atomsize() << std::endl;
  }
  else
  {
    std::cerr << "Error in parsing " << filename << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
