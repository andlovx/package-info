PROGRAMS = package-info

.PHONY : all clean all-clean distclean

all : $(PROGRAMS)
package-info : main.o package.o explorer.o program.o collector.o format.o
	$(CC) -o $@ $+

clean :
	rm -f *.o
all-clean : clean
	rm -f *~
	rm -f $(PROGRAMS)
distclean : all-clean

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@
%.cpp : %.hpp
