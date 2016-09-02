ROOT=../../../../..
include $(ROOT)/global.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
.SUFFIXES:


INC_DIRS = -I"$(NEURO)/include" -I$(ROOT)/Include 
LIB_DIRS = -L"$(NEURO)/lib"  -L$(ROOT)/Lib -L$(ROOT)/app/deps/nm_io/lib -L"$(MB7707)/lib" 
LIBS     = mb7707lib.lib  nmpp-nmc3.lib  libint_soc.lib libc05.lib nm_io_dummy.lib



#cppnew05.lib libc05.lib
#           ^- important that it goes first before libc05.lib
TARGET   = main.abs
CFG      = mb7707brd.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))


$(TARGET): lib $(SRC_CPP)  $(CFG)   Makefile
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -nmc3 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=0 -heap1=0 -heap2=0 -heap3=0
	
#	nmcc $(SRC_CPP) $(SRC_ASM) -Sc -nmc3 -g -O0 $(INC_DIRS)
#	linker main.elf -o$(TARGET) -m.main.map -d0 $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=0 -heap1=0 -heap2=0 -heap3=0

#nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -soc -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=0 -heap1=0 -heap2=0 -heap3=0
#                                                                                         [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3 
#	DEBUG=y
run: $(TARGET) 
	mb7707run -a$(MB7707_MAC) $(TARGET) -i

clean:
	-$(OS_RM) -f *.abs *.elf .*

	

