ROOT=../../../../..
include $(ROOT)/global.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
.SUFFIXES:


INC_DIRS = -I"$(NEURO)/include" -I$(ROOT)/Include 
LIB_DIRS = -L"$(NEURO)/lib"  -L$(ROOT)/Lib -L$(DEVPACK)/nm_io/lib
LIBS     = mc7601_LL_NM.lib   nmpp-nmc3.lib  libint_soc.lib libc05.lib nm_io_dummy.lib



#cppnew05.lib libc05.lib
#           ^- important that it goes first before libc05.lib
TARGET   = main.abs
CFG      = mc7601brd.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))


$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile $(NMPP)/lib/nmpp-nmc3d.lib
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -soc -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=0 -heap1=0 -heap2=0 -heap3=0
#                                                                                         [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3 
#	DEBUG=y
run: $(TARGET)
	mc7601run" $(TARGET) 


clean:
	-$(OS_RM) -f *.abs *.elf .*

	

