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
  std::cerr << " -b, --basis-set=\"asymbol1:filename1;...;asymbolN:filenameN\"    " << std::endl;
  std::cerr << "                              : mandatory specify basisset filenames and atoms" << std::endl; 
  std::cerr << " -f, --fit-set=\"asymbol1:filename1;...;asymbolN:filenameN\"     " << std::endl;
  std::cerr << "                              : mandatory specify fitset filenames and atoms" << std::endl;  
  std::cerr << " -a, --set-values=\"atom1:atom2:dmin:dmax:dr\"     " << std::endl;
  std::cerr << "                              : set atoms and distances to use" << std::endl;  
  std::cerr << " " << std::endl;
  std::cerr << " -o, --out-inputfname=\"filename\"     " << std::endl;
  std::cerr << "                              : specify bertha input filename (default: input.inp" << std::endl;  
  std::cerr << " -O, --out-fittfname=\"filename\"     " << std::endl;
  std::cerr << "                              : specify bertha fitting input filename (default: fitt2.inp" << std::endl;  
  std::cerr << " -c, --convert-antoau         : convert angstrom coordinate to a.u." << std::endl;
  std::cerr << " -r, --restart-on             : set restart mode on" << std::endl;
  std::cerr << " -t, --usefitt-off            : set usefitt mode off " << std::endl;
 
  exit (1);
}

int main (int argc, char ** argv) 
{
  std::vector<std::string> basisset_fname, fitset_fname,
    values;
  bool convert = false;

  struct berthaingen::bertha_options berthaopt;

  berthaopt.bertha_in = "./input.inp";
  berthaopt.fitt_in = "./fitt2.inp";
  berthaopt.restarton = 1;
  berthaopt.usefitt = 1;

  while (1) 
  {
    std::string inputs;

    int c, option_index;
    static struct option long_options[] = {
      {"help", 0, NULL, 'h'},
      {"basis-set", 1, NULL, 'b'},
      {"fit-set", 1, NULL, 'f'},
      {"out-inputfname", 1, NULL, 'o'},
      {"out-fittfname", 1, NULL, 'O'},
      {"convert-antoau", 0, NULL, 'c'},
      {"restart-on", 0, NULL, 'r'},
      {"usefitt-off", 0, NULL, 't'},
      {"set-values", 1, NULL, 'a'},
      {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "htrcb:f:o:O:a:", long_options, &option_index);
    
    if (c == -1)
      break;

    switch (c) {
      case 'h':
        usages (argv[0]);
        break;
      case 'a':
        inputs.assign(optarg);
        berthaingen::tokenize (inputs, values, ":");
        break;
      case 't':
        berthaopt.usefitt = 0;
        break;
      case 'r':
        berthaopt.restarton = 0;
        break;
      case 'c':
        convert = true;
        break;
      case 'o':
        berthaopt.bertha_in.assign(optarg);
        break;
      case 'O':
        berthaopt.fitt_in.assign(optarg);
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

  int atom1, atom2, nstep;
  double dmin, dmax, dr;

  if (values.size() == 5)
  {
    if ((! berthaingen::is_integer (values[0])) &&
        (! berthaingen::is_integer (values[1])) &&
        (! berthaingen::is_float (values[2])) &&
        (! berthaingen::is_float (values[3])) &&
        (! berthaingen::is_float (values[4])))
    {
      std::cerr << "set-values option error in data type" << std::endl;
      return false;
    }

    atom1 = std::stoi(values[0]);
    atom2 = std::stoi(values[1]);

    dmin = std::stod(values[2]);
    dmax = std::stod(values[3]);
    dr = std::stod(values[4]);

    nstep = (int) ((dmax-dmin)/dr) + 1;
  }
  else
  {
    std::cerr << "set-values option error" << std::endl;
    return EXIT_FAILURE;
  }

  if (basisset_fname.size() == 0)
  {
    std::cerr << "Need to specify the basis set " << std::endl;
    return EXIT_FAILURE; 
  }

  if (fitset_fname.size() == 0)
  {
    std::cerr << "Need to specify the fitting set " << std::endl;
    return EXIT_FAILURE;
  }

  std::map<berthaingen::ptable::element, std::vector<std::string> > 
    basisset_map;
  std::stringstream errmsg;
  if (! split_atom_and_basis (basisset_fname, basisset_map, errmsg))
  {
    std::cerr << errmsg.str() << std::endl;
    return EXIT_FAILURE;
  }

  std::map<berthaingen::ptable::element, std::vector<std::string> > 
    fitset_map;
  if (! split_atom_and_basis (fitset_fname, fitset_map, errmsg))
  {
    std::cerr << errmsg.str() << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[optind];

  berthaingen::molecule mol;

  if (mol.read_xyz_file(filename.c_str(), convert))
  {
    std::stringstream errmsg;

    for (int i = 0; i<nstep; ++i)
      std::cout <<  dmin + i * dr << std::endl;


  }
  else
  {
    std::cerr << "Error in parsing " << filename << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
