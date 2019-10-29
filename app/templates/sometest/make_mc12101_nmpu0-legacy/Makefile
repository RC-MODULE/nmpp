
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC12101 board 

-include $(ROOT)/clean.mk
NMPP?=$(ROOT)
.SUFFIXES:


ifndef MC12101
$(warning *** WARNING: 'MC12101' environment variable is not defined! Board SDK might not have installed correctly. )
endif 

PROJECT  = main
TARGET   = $(PROJECT)

CC       = nmcc
AS       = asm
CXXFLAGS = -nmc4_float -O2 -nm2ms 
ASMFLAGS = -nmc4 -nm2ms -split_sir
LIBS     = mc12101lib_nm_legacy.lib libc4f.lib nmpp-nmc4f.lib hal-mc12101.lib cppnew4.lib libint_6407.lib
MAP      = $(PROJECT).map
CFG      = mc12101brd-nmpu0.cfg
HEAPS 	 = -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
LDFLAGS  = -m$(MAP) -c$(CFG) $(HEAPS)

INC_DIRS = -I"$(NEURO)/include" -I"$(NMPP)/include" -I"$(MC12101)/include" -I"$(HAL)/include"
LIB_DIRS = -L"$(NEURO)/lib"     -L"$(NMPP)/lib"     -L"$(MC12101)/lib"     -L"$(HAL)/lib"
SRC_DIRS = ..
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))
SRC_C    = $(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
SRC_ALL  = $(SRC_CPP) $(SRC_ASM) $(SRC_C)

.DEFAULT_GOAL := $(TARGET)

$(TARGET): $(SRC_ALL) Makefile
	$(CC) -o$(TARGET) $(CXXFLAGS) $(LDFLAGS) $(SRC_ALL) $(INC_DIRS) $(LIB_DIRS) $(LIBS)

PATH:=$(MC12101)/bin;$(PATH)

run: 	$(TARGET)
	mc12101run $(TARGET)

reset:
	mc12101reset

vs2015:
	premake5 vs2015
	
vs2008:
	premake5 vs2008		