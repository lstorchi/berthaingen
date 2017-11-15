#!gmake
##################################################
#
# Makefile for berthaingen
#
# $Id$
#
###################################################

include ./config.mk

PROG_NAME = berthaingen

OBJ = main.o \
      molecule.o \
      utility.o

CFLAGS+= $(BASINC) 
LIB+= 

all: $(PROG_NAME) 

$(PROG_NAME): $(OBJ)
	$(CXX) -o $(@) $(OBJ) $(LIB) 

clean:
	rm -rf $(OBJ) $(PROG_NAME)


main.o: molecule.hpp utility.hpp
molecule.o: molecule.hpp utility.hpp
utility.o: utility.hpp
