# Sources
SOURCES             =	source
INCLUDES            =	include

TARGET              = 	$(notdir $(CURDIR))
CFILES		        =	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
CPPFILES	        =	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.cpp))
SFILES		        =	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.s))

# Compiler Settings
OUTPUT = ACNL-ItemList
CFLAGS = -O2 -flto -Wall -Wno-unused-variable $(INCLUDE) -std=c11
CXXFLAGS = $(CFLAGS) -std=c++11
CC = gcc
CXX = g++
LIBS	= 

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	= 

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C

ifeq ($(strip $(CPPFILES)),)
	export LD	= gcc

else
	export LD	= g++
endif
#---------------------------------------------------------------------------------

ifeq ($(OS),Windows_NT)
    #Windows Build CFG
    CFLAGS += -Wno-unused-but-set-variable
    LIBS += -static-libgcc
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        # OS X
        CFLAGS +=
        LIBS += -liconv
    else
        # Linux
        CFLAGS += -Wno-unused-but-set-variable
        LIBS +=
    endif
endif

OFILES	=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

INCLUDE	=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
            $(foreach dir,$(LIBDIRS),-I$(dir)/include)

LIBPATHS	=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)


main: $(OFILES)
	$(LD) -s -o $(OUTPUT) $(LIBS) $(OFILES)

clean:
	rm -rf $(OUTPUT) $(OUTPUT).exe $(OFILES)
