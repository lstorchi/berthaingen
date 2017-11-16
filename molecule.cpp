#include <fstream>
#include <sstream>
#include <iostream>

#include "molecule.hpp"
#include "utility.hpp"

using namespace berthaingen;

///////////////////////////////////////////////////////////////////////////////
//   atom public
///////////////////////////////////////////////////////////////////////////////

atom::atom(float x, float y, float z, const char * s)
{
  this->set_x(x);
  this->set_y(y);
  this->set_y(y);

  this->set_symbol(s);
}

///////////////////////////////////////////////////////////////////////////////
//   bond public
///////////////////////////////////////////////////////////////////////////////

bond::bond (int a1, int a2, bond_type t)
{
  set_type(t);
  set_a1(a1);
  set_a2(a2);
}

void bond::set_type(int in)
{
  switch (in)
  {
    case 0:
      type_ = bond_type::NOBOND;
      break;
    case 1:
      type_ = bond_type::SINGLE;
      break;
    case 2:
      type_ = bond_type::DOUBLE;
      break;
    case 3:
      type_ = bond_type::TRIPLE;
      break;
    default:
      type_ = bond_type::NOBOND;
      break;
  }
}

int bond::get_type() const
{
  switch (type_)
  {
    case bond_type::NOBOND:
      return 0;
    case bond_type::SINGLE:
      return 1;
    case bond_type::DOUBLE:
      return 2;
    case bond_type::TRIPLE:
      return 3;
    default:
      return 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
//   molecule public
///////////////////////////////////////////////////////////////////////////////

molecule::molecule(const molecule & molec)
{
  reset_ ();

  if (this != &molec) 
    copy_ (molec);
  
  return;
}

molecule & molecule::operator= (const molecule & molec) 
{
  if (this != &molec) 
  {
    reset_();
    copy_ (molec);
  }

  return *this;
}

bool molecule::read_xyz_file (const char * filename)
{
  std::ifstream infile(filename);

  unsigned int num_of_atom;
  std::string molname, buf;

  getline (infile, buf);
 
  if (! is_integer (buf))
    return false;

  getline (infile, molname);

  int dim = std::stoi (buf);

  for (int i = 0; i<dim; ++i)
  {
    std::vector<std::string> tokens;

    getline (infile, buf);

    multispace_to_single(buf);

    berthaingen::tokenize (buf, tokens, " ");

    if (tokens.size() == 4)
    {
      if (is_float(tokens[1]) && 
          is_float(tokens[2]) &&
          is_float(tokens[3]))
      {
        atom a(std::stof(tokens[1]), 
            std::stof(tokens[2]), 
            std::stof(tokens[3]),
            tokens[0].c_str());

        add_atom(a);
      }
      else
        return false;
    }
    else
      return false;
  }

}

/////////////////////////////////////////////////////////////////////////////////
//   molecule private
///////////////////////////////////////////////////////////////////////////////

void molecule::copy_ (const molecule & molec) 
{ 
  reset_();

  atoms_ = molec.atoms_;
  bonds_ = molec.bonds_;

  name_ = molec.name_;

  return;
} 
