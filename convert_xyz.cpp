#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <getopt.h>

#include "molecule.hpp"
#include "utility.hpp"

void usages (char * name) 
{
  std::cerr << "usage: " << name << " [options] xyz" << std::endl;
  std::cerr << " -h, --help                   : display this help and exit" << std::endl;
  std::cerr << " " << std::endl;
  std::cerr << " -c, --convert-autoan         : convert a.u. coordinates to angstrom coordinates" << std::endl;
  std::cerr << " -b, --convert-antoau         : convert angstrom coordinates to a.u. coordinates" << std::endl;
 
  exit (1);
}

int main (int argc, char ** argv) 
{
  bool convertautoan = false, convertantoau = false;

  while (1) 
  {
    std::string inputs;

    int c, option_index;
    static struct option long_options[] = {
      {"help", 0, NULL, 'h'},
      {"convert-autoan", 0, NULL, 'c'},
      {"convert-antoau", 0, NULL, 'b'},
      {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "hbc", long_options, &option_index);
    
    if (c == -1)
      break;

    switch (c) {
      case 'h':
        usages (argv[0]);
        break;
      case 'c':
        convertautoan = true;
        break;
      case 'b':
        convertantoau = true;
        break;
      default:
        usages (argv[0]);
        break;
    }
  }

  if (optind >= argc) 
    usages (argv[0]);

  if (convertantoau && convertautoan)
    usages (argv[0]);

  std::string filename = argv[optind];

  berthaingen::molecule mol;

  if (mol.read_xyz_file(filename.c_str()))
  {
    // TODO

  }
  else
  {
    std::cerr << "Error in parsing " << filename << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
