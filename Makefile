NAME = LCSS
SRCDIR = src
#YOU SHOULD SET INI_DIR IF NOT FOUND
INI_DIR = $(shell php --ini | grep -m 1 'additional .ini' | awk '{print $$NF}') 
EXTENSION_DIR = $(shell php-config --extension-dir)
EXTENSION = ${NAME}.so
INI = ${NAME}.ini
COMPILER = g++
LINKER = g++
COMPILER_FLAGS = -Wall -c -g -std=c++11 -fpic -Wno-unused-private-field -o 
LINKER_FLAGS = -shared
LINKER_DEPENDENCIES = -lphpcpp
RM = rm -f
CP = cp -f
MKDIR = mkdir -p
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

all:					${OBJECTS} ${EXTENSION}

${EXTENSION}:			${OBJECTS}
						${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
						${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

install:		
						${CP} ${EXTENSION} ${EXTENSION_DIR}
						${CP} ${INI} ${INI_DIR}
				
clean:
						${RM} ${EXTENSION} ${OBJECTS}

everything:
						make && sudo make install;
