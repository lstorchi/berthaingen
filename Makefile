#!gmake
##################################################
#
# Makefile for berthaingen
#
# $Id$
#
###################################################

include ./config.mk

PROG_NAME1 = berthaingen

OBJ1 = berthaingen.o \
      molecule.o \
      utility.o \
      ptable.o

CFLAGS+= $(BASINC) 
LIB+= #-lboost_regex

all: $(PROG_NAME1) 

$(PROG_NAME1): $(OBJ1)
	$(CXX) -o $(@) $(OBJ1) $(LIB) 

clean:
	rm -rf $(OBJ1) $(PROG_NAME1)


berthaingen.o: molecule.hpp utility.hpp ptable.hpp
molecule.o: molecule.hpp utility.hpp ptable.hpp
utility.o: utility.hpp
ptables.o: ptable.hpp
