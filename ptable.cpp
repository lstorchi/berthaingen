#include "ptable.hpp"

#include <strings.h>

using namespace berthaingen;

namespace 
{
  struct edata {
    int anumber;
    double weight;
    char name[15];
    char symbol[4];
    int maxl;
  };

  static const edata elements[ptable::NO_ELEMENT + 1] = {
    {1   , 1.008   , "Hydrogen",      "H" , 0},
    {2   , 4.003   , "Helium",        "He", 0},
    {3   , 6.941   , "Lithium",       "Li", 0},   
    {4   , 9.012   , "Beryllium",     "Be", 0},   
    {5   , 10.811  , "Boron",         "B" , 1},   
    {6   , 12.011  , "Carbon",        "C" , 1},   
    {7   , 14.007  , "Nitrogen",      "N" , 1},   
    {8   , 15.999  , "Oxygen",        "O" , 1},   
    {9   , 18.998  , "Fluorine",      "F" , 1},   
    {10  , 20.180  , "Neon",          "Ne", 1},   
    {11  , 22.990  , "Sodium",        "Na", 0},   
    {12  , 24.305  , "Magnesium",     "Mg", 0},   
    {13  , 26.982  , "Aluminum",      "Al", 1},   
    {14  , 28.086  , "Silicon",       "Si", 1},   
    {15  , 30.974  , "Phosphorus",    "P" , 1},   
    {16  , 32.065  , "Sulfur",        "S" , 1},   
    {17  , 35.453  , "Chlorine",      "Cl", 1},   
    {18  , 39.948  , "Argon",         "Ar", 1},   
    {19  , 39.098  , "Potassium",     "K" , 0},   
    {20  , 40.078  , "Calcium",       "Ca", 0},   
    {21  , 44.956  , "Scandium",      "Sc", 3},   
    {22  , 47.867  , "Titanium",      "Ti", 3},   
    {23  , 50.942  , "Vanadium",      "V" , 3},   
    {24  , 51.996  , "Chromium",      "Cr", 3},   
    {25  , 54.938  , "Manganese",     "Mn", 3},   
    {26  , 55.845  , "Iron",          "Fe", 3},   
    {27  , 58.933  , "Cobalt",        "Co", 3},   
    {28  , 58.693  , "Nickel",        "Ni", 3},   
    {29  , 63.546  , "Copper",        "Cu", 3},   
    {30  , 65.390  , "Zinc",          "Zn", 3},   
    {31  , 69.723  , "Gallium",       "Ga", 1}, 
    {32  , 72.640  , "Germanium",     "Ge", 1}, 
    {33  , 74.922  , "Arsenic",       "As", 1}, 
    {34  , 78.960  , "Selenium",      "Se", 1}, 
    {35  , 79.904  , "Bromine",       "Br", 1}, 
    {36  , 83.800  , "Krypton ",      "Kr", 1}, 
    {37  , 85.468  , "Rubidium",      "Rb", 0},   
    {38  , 87.620  , "Strontium",     "Sr", 0},   
    {39  , 88.906  , "Yttrium",       "Y" , 3},   
    {40  , 91.224  , "Zirconium",     "Zr", 3},   
    {41  , 92.906  , "Niobium",       "Nb", 3},   
    {42  , 95.940  , "Molybdenum",    "Mo", 3},   
    {43  , 98.000  , "Technetium",    "Tc", 3},   
    {44  , 101.070 , "Ruthenium",     "Ru", 3},   
    {45  , 102.906 , "Rhodium",       "Rh", 3},   
    {46  , 106.420 , "Palladium",     "Pd", 3},   
    {47  , 107.868 , "Silver",        "Ag", 3},   
    {48  , 112.411 , "Cadmium",       "Cd", 3},   
    {49  , 114.818 , "Indium",        "In", 1}, 
    {50  , 118.710 , "Tin",           "Sn", 1}, 
    {51  , 121.760 , "Antimony",      "Sb", 1}, 
    {52  , 127.600 , "Tellurium",     "Te", 1}, 
    {53  , 126.905 , "Iodine",        "I" , 1}, 
    {54  , 131.293 , "Xenon",         "Xe", 1}, 
    {55  , 132.906 , "Cesium",        "Cs", 0},   
    {56  , 137.327 , "Barium",        "Ba", 0},   
    {57  , 138.906 , "Lanthanum",     "La", 4},   
    {58  , 140.116 , "Cerium",        "Ce", 4},
    {59  , 140.908 , "Praseodymium",  "Pr", 4},   
    {60  , 144.240 , "Neodymium",     "Nd", 4},   
    {61  , 145.000 , "Promethium",    "Pm", 4},   
    {62  , 150.360 , "Samarium",      "Sm", 4},   
    {63  , 151.964 , "Europium",      "Eu", 4},   
    {64  , 157.250 , "Gadolinium",    "Gd", 4},
    {65  , 158.925 , "Terbium",       "Tb", 4},   
    {66  , 162.500 , "Dysprosium",    "Dy", 4},   
    {67  , 164.930 , "Holmium",       "Ho", 4},   
    {68  , 167.259 , "Erbium",        "Er", 4},   
    {69  , 168.934 , "Thulium",       "Tm", 4},   
    {70  , 173.040 , "Ytterbium",     "Yb", 4},   
    {71  , 174.967 , "Lutetium",      "Lu", 3},
    {72  , 178.490 , "Hafnium",       "Hf", 3},
    {73  , 180.948 , "Tantalum",      "Ta", 3},
    {74  , 183.840 , "Tungsten",      "W" , 3},
    {75  , 186.207 , "Rhenium",       "Re", 3},
    {76  , 190.230 , "Osmium",        "Os", 3},
    {77  , 192.217 , "Iridium",       "Ir", 3},
    {78  , 195.078 , "Platinum",      "Pt", 3},
    {79  , 196.967 , "Gold",          "Au", 3},
    {80  , 200.590 , "Mercury",       "Hg", 3},
    {81  , 204.383 , "Thallium",      "Tl", 1},
    {82  , 207.200 , "Lead",          "Pb", 1},
    {83  , 208.980 , "Bismuth",       "Bi", 1},
    {84  , 209.000 , "Polonium",      "Po", 1},
    {85  , 210.000 , "Astatine",      "At", 1},
    {86  , 222.000 , "Radon",         "Rn", 1},
    {87  , 223.000 , "Francium",      "Fr", 0},
    {88  , 226.000 , "Radium",        "Ra", 0},
    {89  , 227.000 , "Actinium",      "Ac", 4},
    {90  , 232.038 , "Thorium",       "Th", 4},      
    {91  , 231.036 , "Protactinium",  "Pa", 4},
    {92  , 238.029 , "Uranium",       "U" , 4},
    {93  , 237.000 , "Neptunium",     "Np", 4},
    {94  , 244.000 , "Plutonium",     "Pu", 4},
    {95  , 243.000 , "Americium",     "Am", 4}, 
    {96  , 247.000 , "Curium",        "Cm", 4},
    {97  , 247.000 , "Berkelium",     "Bk", 4},
    {98  , 251.000 , "Californium",   "Cf", 4},
    {99  , 252.000 , "Einsteinium",   "Es", 4},
    {100 , 257.000 , "Fermium",       "Fm", 4},
    {101 , 258.000 , "Mendelevium",   "Md", 4},
    {102 , 259.000 , "Nobelium",      "No", 4},
    {103 , 262.000 , "Lawrencium",    "Lr", 3},
    {104 , 261.000 , "Rutherfordium", "Rf", 3},
    {105 , 262.000 , "Dubnium",       "Db", 3},
    {106 , 266.000 , "Seaborgium",    "Sg", 3},
    {107 , 264.000 , "Bohrium",       "Bh", 3},
    {108 , 277.000 , "Hassium",       "Hs", 3},
    {109 , 268.000 , "Meitnerium",    "Mt", 3},
    {110 , 0.00000 , "Darmstadtium",  "Ds", 3},
    {111 , 0.00000 , "Roentgenium",   "Rg", 3},
    {112 , 0.00000 , "Copernicium",   "Cn", 3},
    {113 , 0.00000 , "Nihonium",      "Nb", 1},
    {114 , 0.00000 , "Flerovium",     "Fl", 1},
    {115 , 0.00000 , "Moscovium",     "Mc", 1},
    {116 , 0.00000 , "Livermorium",   "Lv", 1},
    {117 , 0.00000 , "Tennessine",    "Ts", 1},
    {118 , 0.00000 , "Oganesson",     "Og", 1},  
    { -1 , 0.00000 , "noelement",     "--",-1}
  };
}

int ptable::atomic_number(ptable::element e)
{
  return elements[e].anumber;
}

double ptable::atomic_weight(ptable::element e)
{
  return elements[e].weight;
}

const char * ptable::atomic_symbol(ptable::element e)
{
  return elements[e].symbol;
}

const char * ptable::element_name(ptable::element e)
{
  return elements[e].name;
}

int ptable::maxl (ptable::element e)
{
  return elements[e].maxl;
}

ptable::element ptable::symbol_to_element (const char * s)
{
  for (int i = ptable::H; i < ptable::NO_ELEMENT; ++i)
    if ( strcasecmp(s, elements[i].symbol) == 0 ) 
      return ptable::element(i);
      
  return ptable::NO_ELEMENT;
}
