CC = g++
CPPFLAGS = -O -Wall -g

PROGRAMS += package-object package-list
CPPFLAGS += -I..

.PHONY : all clean all-clean distclean 

all : $(PROGRAMS)
package-object : package-object.o ../package.cpp
package-list : package-list.o ../package.cpp

clean :
	rm -f *.o
all-clean : clean
	rm -f *~
	rm -f $(PROGRAMS)
distclean : all-clean
