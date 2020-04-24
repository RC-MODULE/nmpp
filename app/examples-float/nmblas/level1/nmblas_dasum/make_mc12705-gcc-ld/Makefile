ROOT=../../../../../..

ifeq ($(OS),Windows_NT)
SHELL   = cmd
OS_RM   = cmd /c del /Q
NMC4VARS= nmc4vars_win.mk
include nmc4vars_win.mk
else 
OS_RM    = rm -f -r
endif

export PATH:=$(realpath $(MC12705)/bin);$(PATH);
define BACKSLASH
	$(subst /,\,$(1))
endef




INC_DIRS = -I"$(NMPP)/include" -I"$(MC12705)/include" -I"$(HAL)/include" -I$(ROOT)/include
LIB_DIRS = -L"$(NMPP)/lib"     -L"$(MC12705)/lib" -L$(HAL)/lib 
LIBS     =  -lnmpp-nmc4  -lnmpp-nmc4f
TARGET   = main.abs
CFG      = mc12705board.ld
SRC_DIRS = .. $(ROOT)/src_nmc
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))


#: $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile 
#	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -nmc4 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) $(HEAPS)
#                                                                                         [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

$(TARGET): $(NMC4VARS) $(SRC_CPP) $(SRC_ASM)
	nmc-g++ -o $(TARGET) $(SRC_CPP) $(SRC_ASM) $(INC_DIRS) -Wl,--whole-archive -lmc12705load_nmc -Wl,--no-whole-archive $(LIB_DIRS) $(LIBS) -L "$(NMC_GCC_TOOLPATH)/nmc4-ide/lib" -Wl,-T$(CFG) -mmas


nmc4vars_win.mk:
	copy "$(NMC_GCC_TOOLPATH)\nmc4-ide\include\nmc4vars_win.mk" nmc4vars_win.mk


run: $(TARGET)
	mc12705run $(TARGET) -c0 -n0
	
clean:
	$(OS_RM) simple.asm nmc4vars_win.mk
	$(OS_RM) *.elf *.map *.abs *.dll *.exe
	