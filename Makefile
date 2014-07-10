#   FILE: Makefile
# AUTHOR: Jon Gherardini (jsg)
#   DATE: Wed Jul 10 12:24:54 EDT 2014
#  DESCR: Hacky Makefile for compiling the Mber C++ SDK under Linux
#

#CC=/usr/bin/gcc
RM=/bin/rm -f

CFLAGS = -fPIC -g -w -fmax-errors=1 -Wfatal-errors #-Wall -Wextra -O2 
CXXFLAGS+= -std=gnu++0x -fPIC -g -w
LDFLAGS = -shared 
TARGET_LIB = libMber.so 
INCLUDES= -I. -Icpp/generated/include -Icpp/src -Icpp/poco-1.5.3-all/Foundation/include -Icpp/poco-1.5.3-all/Net/include -Icpp/poco-1.5.3-all/JSON/include -Icpp/poco-1.5.3-all/NetSSL_OpenSSL/include -Icpp/poco-1.5.3-all/Crypto/include -Icpp/poco-1.5.3-all/Util/include
CPPFLAGS+=$(INCLUDES) 
LIBS= 

SRCS = $(wildcard cpp/generated/src/*.cpp) $(wildcard cpp/src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(LINK.cpp) $(INCLUDES) ${LDFLAGS} $^ $(LIBS) $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.cpp=.d)

