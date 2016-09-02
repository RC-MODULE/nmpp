ROOT=../../../../..
include $(ROOT)/global.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:


INC_DIRS = -I"$(NMPP)/include" -I"$(NEURO)/include"
LIB_DIRS = -L"$(NMPP)/lib" -L"$(NEURO)/lib"  -L$(ROOT)/app/deps/nm_io/lib 
LIBS     = nm_io_dummy.lib nmpp-nmc3d.lib libint05.lib  
TARGET   = main.abs
CFG      = emu6405.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))


VPATH    = $(subst -L,,$(LIB_DIRS)) $(NEURO)/lib

$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile $(NMPP)/lib/nmpp-nmc3d.lib
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -6405 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
#                                                                                                                  [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

run: $(TARGET) 
	nm6405emurun ./$(TARGET) 


clean:
	-rm -f *.abs *.elf .*


	

