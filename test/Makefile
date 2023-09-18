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
	package-json1 \
	package-json2 \
	package-path \
	package-lock \
	collector \
	format

.PHONY : all clean all-clean distclean 

all : $(PROGRAMS)

package-object : package-object.o ../source/package.o
package-list : package-list.o ../source/package.o
explore-filter : explore-filter.o ../source/explorer.o
explore-all : explore-all.o ../source/explorer.o
explore-name : explore-name.o ../source/explorer.o
explore-regex : explore-regex.o ../source/explorer.o
explore-func : explore-func.o ../source/explorer.o
explore-files : explore-files.o ../source/explorer.o
explore-exclude : explore-exclude.o ../source/explorer.o
package-json1 : package-json1.o 
package-json2 : package-json2.o 
package-path : package-path.o ../source/package.o 
package-lock : package-lock.o ../source/package.o ../source/explorer.o
collector : collector.o ../source/collector.o ../source/explorer.o ../source/package.o
format : format.o ../source/format.o ../source/package.o

clean :
	rm -f *.o
all-clean : clean
	rm -f *~
	rm -f $(PROGRAMS)
distclean : all-clean
