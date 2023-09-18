CC = g++
CPPFLAGS = -O2 -Wall -std=c++17
WITH_TEST = 1

PROGRAMS = package-info
SUBDIRS  = 

ifeq ($(WITH_TEST), 1)
	SUBDIRS += test
endif

.PHONY : all clean all-clean distclean $(SUBDIRS)

all : $(PROGRAMS) $(SUBDIRS)
package-info : main.o package.o explorer.o program.o collector.o
	$(CC) -o $@ $+

$(SUBDIRS):
	make -C $@ $(MAKECMDGOALS)

clean : $(SUBDIRS)
	rm -f *.o
all-clean : clean
	rm -f *~
	rm -f $(PROGRAMS)
distclean : all-clean

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@
%.cpp : %.hpp
