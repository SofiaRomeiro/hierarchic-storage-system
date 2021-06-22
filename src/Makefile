CC=gcc
CFLAGS= -g -Wall -Wextra -Werror -pedantic -ansi

OBJECTS1= main.o tree.o 
OBJECTS2= main.o list.o
#OBJECTS3 = main.o input.o

all: tree list #input

tree : $(OBJECTS1)
	$(LINK.c) -o $@ $(OBJECTS1)

list : $(OBJECTS2)
	$(LINK.c) -o $@ $(OBJECTS2)

#input : $(OBJECTS3)
#	$(LINK.c) -o $@ $(OBJECTS3) 



main.o: main.c tree.h list.h #input.h
tree.o: tree.c tree.h
list.o: list.c list.h
#input.o: input.c input.h

run::
	./main

