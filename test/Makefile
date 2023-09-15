CC = g++
CPPFLAGS = -O -Wall -g -std=c++17

CPPFLAGS += -I..
PROGRAMS += \
	package-object \
	package-list \
	explore-filter \
	explore-all \
	explore-name \
	explore-regex \
	explore-func \
	explore-files \
	explore-exclude \
	collector 

.PHONY : all clean all-clean distclean 

all : $(PROGRAMS)

package-object : package-object.o ../package.o
package-list : package-list.o ../package.o
explore-filter : explore-filter.o ../explorer.o
explore-all : explore-all.o ../explorer.o
explore-name : explore-name.o ../explorer.o
explore-regex : explore-regex.o ../explorer.o
explore-func : explore-func.o ../explorer.o
explore-files : explore-files.o ../explorer.o
explore-exclude : explore-exclude.o ../explorer.o
collector : collector.o ../collector.o ../explorer.o

clean :
	rm -f *.o
all-clean : clean
	rm -f *~
	rm -f $(PROGRAMS)
distclean : all-clean
