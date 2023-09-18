export CC = g++
export CPPFLAGS = -Wall -std=c++17 $(INCLUDES)

INCLUDES = -I../source

WITH_DEBUG = 0
WITH_TEST  = 0
SUBDIRS    = source

ifeq ($(WITH_TEST), 1)
	SUBDIRS += test
endif

ifeq ($(WITH_DEBUG), 1)
	CPPFLAGS += -O -g
else
	CPPFLAGS += -O2
endif

.PHONY : all clean all-clean distclean $(SUBDIRS)

all : $(SUBDIRS)
clean : $(SUBDIRS)
distclean : clean $(SUBDIRS)
all-clean : distclean

$(SUBDIRS):
	make -C $@ $(MAKECMDGOALS)
