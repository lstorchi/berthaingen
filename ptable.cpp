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
  };

  static const edata elements[ptable::NO_ELEMENT + 1] = {
    {1   , 1.008   , "Hydrogen",      "H" },
    {2   , 4.003   , "Helium",        "He"},
    {3   , 6.941   , "Lithium",       "Li"},   
    {4   , 9.012   , "Beryllium",     "Be"},   
    {5   , 10.811  , "Boron",         "B" },   
    {6   , 12.011  , "Carbon",        "C" },   
    {7   , 14.007  , "Nitrogen",      "N" },   
    {8   , 15.999  , "Oxygen",        "O" },   
    {9   , 18.998  , "Fluorine",      "F" },   
    {10  , 20.180  , "Neon",          "Ne"},   
    {11  , 22.990  , "Sodium",        "Na"},   
    {12  , 24.305  , "Magnesium",     "Mg"},   
    {13  , 26.982  , "Aluminum",      "Al"},   
    {14  , 28.086  , "Silicon",       "Si"},   
    {15  , 30.974  , "Phosphorus",    "P" },   
    {16  , 32.065  , "Sulfur",        "S" },   
    {17  , 35.453  , "Chlorine",      "Cl"},   
    {18  , 39.948  , "Argon",         "Ar"},   
    {19  , 39.098  , "Potassium",     "K" },   
    {20  , 40.078  , "Calcium",       "Ca"},   
    {21  , 44.956  , "Scandium",      "Sc"},   
    {22  , 47.867  , "Titanium",      "Ti"},   
    {23  , 50.942  , "Vanadium",      "V" },   
    {24  , 51.996  , "Chromium",      "Cr"},   
    {25  , 54.938  , "Manganese",     "Mn"},   
    {26  , 55.845  , "Iron",          "Fe"},   
    {27  , 58.933  , "Cobalt",        "Co"},   
    {28  , 58.693  , "Nickel",        "Ni"},   
    {29  , 63.546  , "Copper",        "Cu"},   
    {30  , 65.390  , "Zinc",          "Zn"},   
    {31  , 69.723  , "Gallium",       "Ga"}, 
    {32  , 72.640  , "Germanium",     "Ge"}, 
    {33  , 74.922  , "Arsenic",       "As"}, 
    {34  , 78.960  , "Selenium",      "Se"}, 
    {35  , 79.904  , "Bromine",       "Br"}, 
    {36  , 83.800  , "Krypton ",      "Kr"}, 
    {37  , 85.468  , "Rubidium",      "Rb"},   
    {38  , 87.620  , "Strontium",     "Sr"},   
    {39  , 88.906  , "Yttrium",       "Y" },   
    {40  , 91.224  , "Zirconium",     "Zr"},   
    {41  , 92.906  , "Niobium",       "Nb"},   
    {42  , 95.940  , "Molybdenum",    "Mo"},   
    {43  , 98.000  , "Technetium",    "Tc"},   
    {44  , 101.070 , "Ruthenium",     "Ru"},   
    {45  , 102.906 , "Rhodium",       "Rh"},   
    {46  , 106.420 , "Palladium",     "Pd"},   
    {47  , 107.868 , "Silver",        "Ag"},   
    {48  , 112.411 , "Cadmium",       "Cd"},   
    {49  , 114.818 , "Indium",        "In"}, 
    {50  , 118.710 , "Tin",           "Sn"}, 
    {51  , 121.760 , "Antimony",      "Sb"}, 
    {52  , 127.600 , "Tellurium",     "Te"}, 
    {53  , 126.905 , "Iodine",        "I" }, 
    {54  , 131.293 , "Xenon",         "Xe"}, 
    {55  , 132.906 , "Cesium",        "Cs"},   
    {56  , 137.327 , "Barium",        "Ba"},   
    {57  , 138.906 , "Lanthanum",     "La"},   
    {58  , 140.116 , "Cerium",        "Ce"},
    {59  , 140.908 , "Praseodymium",  "Pr"},   
    {60  , 144.240 , "Neodymium",     "Nd"},   
    {61  , 145.000 , "Promethium",    "Pm"},   
    {62  , 150.360 , "Samarium",      "Sm"},   
    {63  , 151.964 , "Europium",      "Eu"},   
    {64  , 157.250 , "Gadolinium",    "Gd"},
    {65  , 158.925 , "Terbium",       "Tb"},   
    {66  , 162.500 , "Dysprosium",    "Dy"},   
    {67  , 164.930 , "Holmium",       "Ho"},   
    {68  , 167.259 , "Erbium",        "Er"},   
    {69  , 168.934 , "Thulium",       "Tm"},   
    {70  , 173.040 , "Ytterbium",     "Yb"},   
    {71  , 174.967 , "Lutetium",      "Lu"},
    {72  , 178.490 , "Hafnium",       "Hf"},
    {73  , 180.948 , "Tantalum",      "Ta"},
    {74  , 183.840 , "Tungsten",      "W" },
    {75  , 186.207 , "Rhenium",       "Re"},
    {76  , 190.230 , "Osmium",        "Os"},
    {77  , 192.217 , "Iridium",       "Ir"},
    {78  , 195.078 , "Platinum",      "Pt"},
    {79  , 196.967 , "Gold",          "Au"},
    {80  , 200.590 , "Mercury",       "Hg"},
    {81  , 204.383 , "Thallium",      "Tl"},
    {82  , 207.200 , "Lead",          "Pb"},
    {83  , 208.980 , "Bismuth",       "Bi"},
    {84  , 209.000 , "Polonium",      "Po"},
    {85  , 210.000 , "Astatine",      "At"},
    {86  , 222.000 , "Radon",         "Rn"},
    {87  , 223.000 , "Francium",      "Fr"},
    {88  , 226.000 , "Radium",        "Ra"},
    {89  , 227.000 , "Actinium",      "Ac"},
    {90  , 232.038 , "Thorium",       "Th"},      
    {91  , 231.036 , "Protactinium",  "Pa"},
    {92  , 238.029 , "Uranium",       "U" },
    {93  , 237.000 , "Neptunium",     "Np"},
    {94  , 244.000 , "Plutonium",     "Pu"},
    {95  , 243.000 , "Americium",     "Am"}, 
    {96  , 247.000 , "Curium",        "Cm"},
    {97  , 247.000 , "Berkelium",     "Bk"},
    {98  , 251.000 , "Californium",   "Cf"},
    {99  , 252.000 , "Einsteinium",   "Es"},
    {100 , 257.000 , "Fermium",       "Fm"},
    {101 , 258.000 , "Mendelevium",   "Md"},
    {102 , 259.000 , "Nobelium",      "No"},
    {103 , 262.000 , "Lawrencium",    "Lr"},
    {104 , 261.000 , "Rutherfordium", "Rf"},
    {105 , 262.000 , "Dubnium",       "Db"},
    {106 , 266.000 , "Seaborgium",    "Sg"},
    {107 , 264.000 , "Bohrium",       "Bh"},
    {108 , 277.000 , "Hassium",       "Hs"},
    {109 , 268.000 , "Meitnerium",    "Mt"},
    {110 , 0.00000 , "Darmstadtium",  "Ds"},
    {111 , 0.00000 , "Roentgenium",   "Rg"},
    {112 , 0.00000 , "Copernicium",   "Cn"},
    {113 , 0.00000 , "Nihonium",      "Nb"},
    {114 , 0.00000 , "Flerovium",     "Fl"},
    {115 , 0.00000 , "Moscovium",     "Mc"},
    {116 , 0.00000 , "Livermorium",   "Lv"},
    {117 , 0.00000 , "Tennessine",    "Ts"},
    {118 , 0.00000 , "Oganesson",     "Og"},  
    { -1 , 0.00000 , "noelement",     "--"}
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

ptable::element ptable::symbol_to_element (const char * s)
{
  for (int i = ptable::H; i < ptable::NO_ELEMENT; ++i)
    if ( strcasecmp(s, elements[i].symbol) == 0 ) 
      return ptable::element(i);
      
  return ptable::NO_ELEMENT;
}
