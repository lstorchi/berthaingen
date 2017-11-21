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
    //std::cout << mol << std::endl;
    std::cout << "\'TYPE OF BASIS SET; 1 FOR GEOMETRIC, 2 FOR OPTIMIZED\'" << std::endl;
    std::cout << "2" << std::endl;
    std::cout << "\'NUMBER OF CENTRES\'" << std::endl;
    std::cout << mol.get_atomsize() << std::endl;

    std::vector<berthaingen::atom> atoms;
    atoms = mol.get_atomlist();
    
    unsigned int totelectron = 0;
    std::vector<berthaingen::atom>::iterator it = atoms.begin();
    for (; it != atoms.end(); ++it)
    {
      berthaingen::ptable::element e = it->get_element();
      totelectron += berthaingen::ptable::atomic_number(e);
    }

    for (int i = 0; i < mol.get_atomsize(); ++i)
    {
      std::cout << "\'COORDINATES FOR CENTER " << i+1 << "\'" << std::endl;
      std::cout << atoms[i].get_x() << "," 
                << atoms[i].get_y() << ","
                << atoms[i].get_z() << std::endl;
      std::cout << "\'Z, N, MAXL AND CHARGE FOR CENTER " << i+1 << "\'" << std::endl;
      berthaingen::ptable::element e = atoms[i].get_element();
      std::cout << berthaingen::ptable::atomic_number(e) << ","
                << berthaingen::ptable::atomic_weight(e) << ","
                << berthaingen::ptable::maxl(e) << "," 
                << "0" << std::endl;
      std::cout << "\'BASIS SET FOR CENTRE " << i+1 << "\'" << std::endl;
      std::cout << "=== base ===" << std::endl;
    }

    std::cout << "\'NUMBER OF CLOSED-SHELL ELECTRONS\'" << std::endl;
    std::cout << totelectron << ",0,0" << std::endl; 
    std::cout << "\'SPECIFY CLOSED AND OPEN SHELLS AND COUPLING\'" << std::endl;
    std::cout << "0" << std::endl;
    std::cout << "\'ENTER 1 FOR NEW RUN AND 0 FOR RESTART\'" << std::endl;
    std::cout << "1" << std::endl;
    std::cout << "\'LEVEL SHIFT FACTOR IN STAGE 0, 1, AND 2\'" << std::endl;
    std::cout << "-2.0,-2.0,-2.0" << std::endl;
    std::cout << "\'STARTING STAGE (0-2)\'" << std::endl;
    std::cout << "2" << std::endl;
    std::cout << "\'PRINT LEVEL FROM 1-2\'" << std::endl;
    std::cout << "2" << std::endl;
    std::cout << "\'DAMPING FACTOR AND RELATIVE TRESHOLD FOR INITIATION OF DAMPING\'" << std::endl;
    std::cout << "0.10D0,1.0D-2" << std::endl;
    std::cout << "\'ENTER NCORE, MACTVE,NACTVE\'" << std::endl;
    std::cout << totelectron << ",0,0" << std::endl;                                                
    std::cout << "\'ENTER GRID QUALITY FROM 1 (COURSE) to 5 (FINE)\'" << std::endl;
    std::cout << "3" << std::endl;
    std::cout << "\'EX-POTENTIAL available: LDA, B88P86,HCTH93\'" << std::endl;
    std::cout << "BLYP" << std::endl;
    std::cout << "\'Fitt\'" << std::endl;
    std::cout << "2" << std::endl;
    std::cout << "\'scalapack\'" << std::endl;
    std::cout << "2 2 32 2.0" << std::endl;
    std::cout << "\'maxit\'" << std::endl;
    std::cout << "3" << std::endl;
  }
  else
  {
    std::cerr << "Error in parsing " << filename << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
