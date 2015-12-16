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
# Define DEBUG:
#   $ make ex1.x DBG=1
#   -B force update

.PHONY: clean
.PRECIOUS: %.o
SHELL=/bin/bash -o pipefail

DBG ?= 0
IT_MAX ?= 1000
FAZ_GIF ?= 0
MAJOR = 0
MINOR = 1
BUILD = $(shell date +"%g%m%d.%H%M%S")
DEFSYM = $(subst .,_,$(BUILD))
VERSION = "\"$(MAJOR).$(MINOR).$(BUILD)\""
CC = gcc
CFLAGS = "listao.c" -Wall -Wextra -g -O0
#-pedantic-errors
#-ansi
CPPFLAGS = -DVERSION=$(VERSION) -DBUILD="\"$(BUILD)\"" -DDEBUG=$(DBG) -DITER=$(IT_MAX) -DGIF=$(FAZ_GIF)
LDLIBS = -Wl,--defsym,BUILD_$(DEFSYM)=0 -lpthread -lm -lgmp `allegro-config --cflags --libs`

%.x : %.c $(obj)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) $^ -o $@ 2>&1 | tee errors.err

%.bfx : %.bf
	    bf $^ -o $@ -i on -p both -r on -w on

clean:
	rm -f *.x errors.err
