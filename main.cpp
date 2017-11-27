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
  std::cerr << " " << std::endl;
  std::cerr << " -o, --out-inputfname=\"filename\"     " << std::endl;
  std::cerr << "                              : specify bertha input filename (default: input.inp" << std::endl;  
  std::cerr << " -O, --out-fittfname=\"filename\"     " << std::endl;
  std::cerr << "                              : specify bertha fitting input filename (default: fitt2.inp" << std::endl;  
 
 
  exit (1);
}

int main (int argc, char ** argv) 
{
  std::vector<std::string> basisset_fname, fitset_fname;
  std::string bertha_in = "./input.inp";
  std::string fitt_in = "./fitt2.inp";

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
      {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "hb:f:o:O:", long_options, &option_index);
    
    if (c == -1)
      break;

    switch (c) {
      case 'h':
        usages (argv[0]);
        break;
      case 'o':
        bertha_in.assign(optarg);
        break;
      case 'O':
        fitt_in.assign(optarg);
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

  if (mol.read_xyz_file(filename.c_str()))
  {
    //std::cout << mol << std::endl;
    
    std::ofstream fout(bertha_in.c_str(), 
        std::ios::out | std::ios::trunc);
    
    if (fout) 
    {
      fout << "\'TYPE OF BASIS SET; 1 FOR GEOMETRIC, 2 FOR OPTIMIZED\'" << std::endl;
      fout << "2" << std::endl;
      fout << "\'NUMBER OF CENTERS\'" << std::endl;
      fout << mol.get_atomsize() << std::endl;
      
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
        fout << "\'COORDINATES FOR CENTER " << i+1 << "\'" << std::endl;
        fout << atoms[i].get_x() << "," 
                  << atoms[i].get_y() << ","
                  << atoms[i].get_z() << std::endl;
        fout << "\'Z, N, MAXL AND CHARGE FOR CENTER " << i+1 << "\'" << std::endl;
        berthaingen::ptable::element e = atoms[i].get_element();
        if (basisset_map.find(e) != basisset_map.end())
        {
          std::vector<std::string>::iterator it = basisset_map[e].begin();
          fout << berthaingen::ptable::atomic_number(e) << ","
                    << berthaingen::ptable::atomic_weight(e) << ","
                    << *it << "," // MAXL
                    << "0" << std::endl;
          fout << "\'BASIS SET FOR CENTER " << i+1 << "\'" << std::endl;
          it++;
          for (; it != basisset_map[e].end(); ++it)
            fout << *it  << std::endl;
        }
        else
        {
          std::cerr << "Cannot find a basis set for element : " << 
            atoms[i].get_element();
          return EXIT_FAILURE;
        }
      }
      
      fout << "\'NUMBER OF CLOSED-SHELL ELECTRONS\'" << std::endl;
      fout << totelectron << ",0,0" << std::endl; 
      fout << "\'SPECIFY CLOSED AND OPEN SHELLS AND COUPLING\'" << std::endl;
      fout << "0" << std::endl;
      fout << "\'ENTER 1 FOR NEW RUN AND 0 FOR RESTART\'" << std::endl;
      fout << "1" << std::endl;
      fout << "\'LEVEL SHIFT FACTOR IN STAGE 0, 1, AND 2\'" << std::endl;
      fout << "-2.0,-2.0,-2.0" << std::endl;
      fout << "\'STARTING STAGE (0-2)\'" << std::endl;
      fout << "2" << std::endl;
      fout << "\'PRINT LEVEL FROM 1-2\'" << std::endl;
      fout << "2" << std::endl;
      fout << "\'DAMPING FACTOR AND RELATIVE TRESHOLD FOR INITIATION OF DAMPING\'" << std::endl;
      fout << "0.10D0,1.0D-2" << std::endl;
      fout << "\'ENTER NCORE, MACTVE,NACTVE\'" << std::endl;
      fout << totelectron << ",0,0" << std::endl;                                                
      fout << "\'ENTER GRID QUALITY FROM 1 (COURSE) to 5 (FINE)\'" << std::endl;
      fout << "3" << std::endl;
      fout << "\'EX-POTENTIAL available: LDA, B88P86,HCTH93\'" << std::endl;
      fout << "BLYP" << std::endl;
      fout << "\'Fitt\' USEFITT" << std::endl;
      fout << "2 1" << std::endl;
      fout << "\'scalapack\'" << std::endl;
      fout << "2 2 32 2.0" << std::endl;
      fout << "\'maxit\'" << std::endl;
      fout << "3" << std::endl;
    }

    fout.close();

    std::ofstream foutf(fitt_in.c_str(), 
        std::ios::out | std::ios::trunc);
    
    if (foutf) 
    {
      foutf << mol.get_atomsize() << std::endl;
      
      std::vector<berthaingen::atom> atoms;
      atoms = mol.get_atomlist();
      
      for (int i = 0; i < mol.get_atomsize(); ++i)
      {
        foutf << atoms[i].get_x() << " " 
                  << atoms[i].get_y() << " "
                  << atoms[i].get_z() << std::endl;
        berthaingen::ptable::element e = atoms[i].get_element();
        if (fitset_map.find(e) != fitset_map.end())
        {
          std::vector<std::string>::iterator it = fitset_map[e].begin();
          for (; it != fitset_map[e].end(); ++it)
            foutf << *it << std::endl;
        }
        else
        {
          std::cerr << "Cannot find a fitting set for element : " << 
            atoms[i].get_element();
          return EXIT_FAILURE;
        }
      }
    }

    foutf.close();
  }
  else
  {
    std::cerr << "Error in parsing " << filename << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
