# Autoversion makefile
# (C) 2015, Ruben Carlo Benante

#Usage:
# * From linux prompt:
#    - Normal C program (ex1.c)
#        $ make ex1.x
#    - Aspipo program (ex1.c)
#        $ make ex1.x obj=libaspipo-ux64.o
# * From vim command:
#    - Normal C program (ex1.c)
#        :make
#    - Aspipo program (ex1.c)
#        :make obj=libaspipo-ux64.o

.PHONY: clean
.PRECIOUS: %.o
SHELL=/bin/bash -o pipefail

MAJOR = 0
MINOR = 1
BUILD = $(shell date +"%g%m%d.%H%M%S")
DEFSYM = $(subst .,_,$(BUILD))
VERSION = "\"$(MAJOR).$(MINOR).$(BUILD)\""
CC = gcc
CFLAGS = -Wall -Wextra -g -O0 
#-pedantic-errors
#-ansi
CPPFLAGS = -DVERSION=$(VERSION) -DBUILD="\"$(BUILD)\""
LDLIBS = -Wl,--defsym,BUILD_$(DEFSYM)=0, -lpthread

%.x : %.c $(obj)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) $^ -o $@ 2>&1 | tee errors.err

clean:
	rm -f *.x errors.err

