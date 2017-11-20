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
      utility.o \
      ptable.o

CFLAGS+= $(BASINC) 
LIB+= #-lboost_regex

all: $(PROG_NAME) 

$(PROG_NAME): $(OBJ)
	$(CXX) -o $(@) $(OBJ) $(LIB) 

clean:
	rm -rf $(OBJ) $(PROG_NAME)


main.o: molecule.hpp utility.hpp ptable.hpp
molecule.o: molecule.hpp utility.hpp ptable.hpp
utility.o: utility.hpp
ptables.o: ptable.hpp
