ROOT=../../../../../..
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC12101 board 

#include $(NMC_GCC_TOOLPATH)/nmc4-ide/include/nmc4vars_win.mk
#NMCGCC = $(NMC_GCC_TOOLPATH)/nmc4-ide
-include nmc4vars_win.mk


.SUFFIXES:

#NMPP?=

ifndef MC12101
$(warning *** WARNING: 'MC12101' environment variable is not defined! Board SDK might not have installed correctly. )
endif 

CC       = nmc-g++
AS       = nmc-gcc
CC_FLAGS = -std=c++11 -O2 -Wall -mnmc4
ROOT     = ..
PROJECT  = main
TARGET   =$(PROJECT)
INC_DIRS = -I"$(NMPP)/include"
LIB_DIRS = -L"$(NMCGCC)/lib" -L"$(NMCGCC)/nmc/lib/nmc4" -L"$(NMPP)/lib"
LIBS     = -lnmpp-nmc4
CFG      =  "-Wl,-cmc12101brd-nmpu1.cfg"
SRC_CPP  = $(wildcard $(ROOT)/*.cpp)

$(TARGET): $(SRC_CPP) Makefile
	$(CC) $(CC_FLAGS) $(SRC_CPP) $(INC_DIRS) $(LIB_DIRS) $(LIBS) -lc $(CFG) -Wl,--whole-archive -lmc12101 -Wl,--no-whole-archive -o $(TARGET)

PATH:=$(MC12101)/bin;$(PATH)

run: $(TARGET)
	mc12101run $(TARGET) -p

clean:
	-rm -f *.abs *.elf .*  *.o

skip:
	@echo SDK missing. Compilation is skipped!

reset:
	reset12101
	
nmc4vars_win.mk:
	copy "$(NMC_GCC_TOOLPATH)\nmc4-ide\include\nmc4vars_win.mk" nmc4vars_win.mk
	