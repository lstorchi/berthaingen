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
    {1   , 1.00811       , "Hydrogen",      "H" , 0},
    {2   , 4.002602      , "Helium",        "He", 0},
    {3   , 6.997         , "Lithium",       "Li", 0},   
    {4   , 9.0121831     , "Beryllium",     "Be", 0},   
    {5   , 10.821        , "Boron",         "B" , 1},   
    {6   , 12.0116       , "Carbon",        "C" , 1},   
    {7   , 14.00728      , "Nitrogen",      "N" , 1},   
    {8   , 15.99977      , "Oxygen",        "O" , 1},   
    {9   , 18.998403163  , "Fluorine",      "F" , 1},   
    {10  , 20.1797       , "Neon",          "Ne", 1},   
    {11  , 22.98976928   , "Sodium",        "Na", 0},   
    {12  , 24.307        , "Magnesium",     "Mg", 0},   
    {13  , 26.9815385    , "Aluminum",      "Al", 1},   
    {14  , 28.086        , "Silicon",       "Si", 1},   
    {15  , 30.973761998  , "Phosphorus",    "P" , 1},   
    {16  , 32.076        , "Sulfur",        "S" , 1},   
    {17  , 35.457        , "Chlorine",      "Cl", 1},   
    {18  , 39.948        , "Argon",         "Ar", 1},   
    {19  , 39.0983       , "Potassium",     "K" , 0},   
    {20  , 40.078        , "Calcium",       "Ca", 0},   
    {21  , 44.955908     , "Scandium",      "Sc", 3},   
    {22  , 47.867        , "Titanium",      "Ti", 3},   
    {23  , 50.9415       , "Vanadium",      "V" , 3},   
    {24  , 51.9961       , "Chromium",      "Cr", 3},   
    {25  , 54.938044     , "Manganese",     "Mn", 3},   
    {26  , 55.845        , "Iron",          "Fe", 3},   
    {27  , 58.933194     , "Cobalt",        "Co", 3},   
    {28  , 58.6934       , "Nickel",        "Ni", 3},   
    {29  , 63.546        , "Copper",        "Cu", 3},   
    {30  , 65.38         , "Zinc",          "Zn", 3},   
    {31  , 69.723        , "Gallium",       "Ga", 1}, 
    {32  , 72.630        , "Germanium",     "Ge", 1}, 
    {33  , 74.921595     , "Arsenic",       "As", 1}, 
    {34  , 78.971        , "Selenium",      "Se", 1}, 
    {35  , 79.907        , "Bromine",       "Br", 1}, 
    {36  , 83.798        , "Krypton ",      "Kr", 1}, 
    {37  , 85.4678       , "Rubidium",      "Rb", 0},   
    {38  , 87.62         , "Strontium",     "Sr", 0},   
    {39  , 88.90584      , "Yttrium",       "Y" , 3},   
    {40  , 91.224        , "Zirconium",     "Zr", 3},   
    {41  , 92.90637      , "Niobium",       "Nb", 3},   
    {42  , 95.95         , "Molybdenum",    "Mo", 3},   
    {43  , 98.0          , "Technetium",    "Tc", 3},   
    {44  , 101.07        , "Ruthenium",     "Ru", 3},   
    {45  , 102.90550     , "Rhodium",       "Rh", 3},   
    {46  , 106.42        , "Palladium",     "Pd", 3},   
    {47  , 107.8682      , "Silver",        "Ag", 3},   
    {48  , 112.414       , "Cadmium",       "Cd", 3},   
    {49  , 114.818       , "Indium",        "In", 1}, 
    {50  , 118.710       , "Tin",           "Sn", 1}, 
    {51  , 121.760       , "Antimony",      "Sb", 1}, 
    {52  , 127.60        , "Tellurium",     "Te", 1}, 
    {53  , 126.90447     , "Iodine",        "I" , 1}, 
    {54  , 131.293       , "Xenon",         "Xe", 1}, 
    {55  , 132.90545196  , "Cesium",        "Cs", 0},   
    {56  , 137.327       , "Barium",        "Ba", 0},   
    {57  , 138.90547     , "Lanthanum",     "La", 4},   
    {58  , 140.116       , "Cerium",        "Ce", 4},
    {59  , 140.90766     , "Praseodymium",  "Pr", 4},   
    {60  , 144.242       , "Neodymium",     "Nd", 4},   
    {61  , 145.0         , "Promethium",    "Pm", 4},   
    {62  , 150.36        , "Samarium",      "Sm", 4},   
    {63  , 151.964       , "Europium",      "Eu", 4},   
    {64  , 157.25        , "Gadolinium",    "Gd", 4},
    {65  , 158.92535     , "Terbium",       "Tb", 4},   
    {66  , 162.500       , "Dysprosium",    "Dy", 4},   
    {67  , 164.93033     , "Holmium",       "Ho", 4},   
    {68  , 167.259       , "Erbium",        "Er", 4},   
    {69  , 168.93422     , "Thulium",       "Tm", 4},   
    {70  , 173.054       , "Ytterbium",     "Yb", 4},   
    {71  , 174.9668      , "Lutetium",      "Lu", 3},
    {72  , 178.49        , "Hafnium",       "Hf", 3},
    {73  , 180.94788     , "Tantalum",      "Ta", 3},
    {74  , 183.84        , "Tungsten",      "W" , 3},
    {75  , 186.207       , "Rhenium",       "Re", 3},
    {76  , 190.23        , "Osmium",        "Os", 3},
    {77  , 192.217       , "Iridium",       "Ir", 3},
    {78  , 195.084       , "Platinum",      "Pt", 3},
    {79  , 196.966569    , "Gold",          "Au", 3},
    {80  , 200.592       , "Mercury",       "Hg", 3},
    {81  , 204.385       , "Thallium",      "Tl", 1},
    {82  , 207.2         , "Lead",          "Pb", 1},
    {83  , 208.98040     , "Bismuth",       "Bi", 1},
    {84  , 209.0         , "Polonium",      "Po", 1},
    {85  , 210.0         , "Astatine",      "At", 1},
    {86  , 222.0         , "Radon",         "Rn", 1},
    {87  , 223.0         , "Francium",      "Fr", 0},
    {88  , 226.0         , "Radium",        "Ra", 0},
    {89  , 227.0         , "Actinium",      "Ac", 4},
    {90  , 232.0377      , "Thorium",       "Th", 4},      
    {91  , 231.03588     , "Protactinium",  "Pa", 4},
    {92  , 238.02891     , "Uranium",       "U" , 4},
    {93  , 237.0         , "Neptunium",     "Np", 4},
    {94  , 244.0         , "Plutonium",     "Pu", 4},
    {95  , 241.0568293   , "Americium",     "Am", 4}, 
    {96  , 243.0613893   , "Curium",        "Cm", 4},
    {97  , 247.0703073   , "Berkelium",     "Bk", 4},
    {98  , 249.0748539   , "Californium",   "Cf", 4},
    {99  , 252.082980    , "Einsteinium",   "Es", 4},
    {100 , 257.0951061   , "Fermium",       "Fm", 4},
    {101 , 258.0984315   , "Mendelevium",   "Md", 4},
    {102 , 259.10103     , "Nobelium",      "No", 4},
    {103 , 262.10961     , "Lawrencium",    "Lr", 3},
    {104 , 267.12179     , "Rutherfordium", "Rf", 3},
    {105 , 268.12567     , "Dubnium",       "Db", 3},
    {106 , 271.13393     , "Seaborgium",    "Sg", 3},
    {107 , 272.13826     , "Bohrium",       "Bh", 3},
    {108 , 270.13429     , "Hassium",       "Hs", 3},
    {109 , 276.15159     , "Meitnerium",    "Mt", 3},
    {110 , 281.16451     , "Darmstadtium",  "Ds", 3},
    {111 , 280.16514     , "Roentgenium",   "Rg", 3},
    {112 , 285.17712     , "Copernicium",   "Cn", 3},
    {113 , 284.17873     , "Nihonium",      "Nb", 1},
    {114 , 289.19042     , "Flerovium",     "Fl", 1},
    {115 , 288.19274     , "Moscovium",     "Mc", 1},
    {116 , 293.20449     , "Livermorium",   "Lv", 1},
    {117 , 292.20746     , "Tennessine",    "Ts", 1},
    {118 , 294.21392     , "Oganesson",     "Og", 1},  
    { -1 , 0.0           , "Noelement",     "--",-1}
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

