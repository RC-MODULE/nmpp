
-include $(ROOT)/clean.mk
NMPP?=$(ROOT)
.SUFFIXES:

BOARD = mc12101
BSP = $(MC12101)
ifndef MC12101
$(warning *** WARNING: 'MC12101' environment variable is not defined! Board SDK might not have installed correctly. )
endif 

PROJECT  = main
TARGET   = $(PROJECT)

CC       = nmcc
AS       = asm
ASMFLAGS = -nmc4 -nm2ms -split_sir
CXXFLAGS = -nmc4_float -O2 -nm2ms 
LIBS     = nmpp-nmc4f.lib hal-$(BOARD).lib 
LIBS    += $(BOARD)lib_nm_legacy.lib libc4f.lib cppnew4.lib libint_6407.lib
CFG      = $(BOARD)-nmpu0.cfg
MAP      = $(PROJECT).map

HEAPS 	 = -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
LDFLAGS  = -m$(MAP) -c$(CFG) $(HEAPS)

INC_DIRS = -I"$(BSP)/include"  -I"$(NMPP)/include"  -I"$(HAL)/include" -I"$(NEURO)/include"
LIB_DIRS = -L"$(BSP)/lib"      -L"$(NMPP)/lib"      -L"$(HAL)/lib"     -L"$(NEURO)/lib"
SRC_DIRS = ..
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))
SRC_C    = $(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
SRC_ALL  = $(SRC_CPP) $(SRC_ASM) $(SRC_C)

.DEFAULT_GOAL := $(TARGET)

$(TARGET): $(SRC_ALL) Makefile
	$(CC) -o$(TARGET) $(CXXFLAGS) $(LDFLAGS) $(SRC_ALL) $(INC_DIRS) $(LIB_DIRS) $(LIBS)

PATH:=$(BSP)/bin;$(PATH)

run: 	$(TARGET)
	$(BOARD)run $(TARGET)


vs2015:
	premake5 vs2015
	
vs2008:
	premake5 vs2008		