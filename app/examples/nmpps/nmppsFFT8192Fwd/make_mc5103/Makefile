ROOT=../../../../..
include $(ROOT)/global.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on board 

.SUFFIXES:

INC_DIRS = -I"$(NEURO)/include" -I$(ROOT)/Include 
LIB_DIRS = -L"$(NEURO)/lib"  -L$(ROOT)/Lib -L$(DEVPACK)/nm_io/lib
#LIBS     = nm_io.lib mc5103lib.lib nmpp-nmc3d.lib libint05.lib  
LIBS     = nm_io.lib mc5103lib.lib nmpp-nmc3.lib libint05.lib  
#cppnew05.lib libc05.lib
#           ^- important that it goes first before libc05.lib
TARGET   = main.abs
#CFG      = 1.cfg
CFG      =mc5103brd.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))




$(TARGET): lib $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile 
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -6405 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=0 -heap1=0 -heap2=0 -heap3=0
#	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -6405 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=28384 -heap1=30768 -heap2=32768 -heap3=32768
#                                                                                                                  [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3 
	
#	DEBUG=y
	
run: $(TARGET)
	mc5103run $(TARGET)


clean:
	-$(OS_RM) -f *.abs *.elf .*


	

