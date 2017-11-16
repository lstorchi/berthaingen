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

  infile >> buf;
 
  if (! is_integer (buf))
    return false;

  std::cout << buf;

  infile >> molname;
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
