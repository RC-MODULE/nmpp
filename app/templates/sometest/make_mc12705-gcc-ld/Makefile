
NMPP?=$(ROOT)

ifeq ($(OS),Windows_NT)
include nmc4vars_win.mk
SHELL   =cmd
OS_RM   =cmd /c del /Q
NMC4VARS=nmc4vars_win.mk
LIBLOAD =mc12705load_nmc
export PATH:=$(realpath $(MC12705)/bin);$(PATH)
else 
OS_RM   =rm -f -r
LIBLOAD =nm6408load_nmc
export PATH:=$(realpath $(MC12705)/bin):$(PATH)
endif


INC_DIRS = -I"$(NMPP)/include" -I"$(MC12705)/include" -I"$(HAL)/include" -I$(ROOT)/include
LIB_DIRS = -L"$(NMPP)/lib"     -L"$(MC12705)/lib"     -L"$(HAL)/lib" 
LIBS     = -lnmpp-nmc4  -lnmpp-nmc4f -Wl,--whole-archive -l$(LIBLOAD) -Wl,--no-whole-archive
TARGET   = main.abs
CFG      = mc12705board.ld
SRC_DIRS = .. 
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))

$(TARGET): $(NMC4VARS) $(SRC_CPP) $(SRC_ASM)
	nmc-g++ -o $(TARGET) $(SRC_CPP) $(SRC_ASM) $(INC_DIRS) $(LIB_DIRS) $(LIBS)  -Wl,-T$(CFG) -mmas

nmc4vars_win.mk:
	copy "$(NMC_GCC_TOOLPATH)\nmc4-ide\include\nmc4vars_win.mk" nmc4vars_win.mk


run: $(TARGET)
	mc12705run $(TARGET) -c0 -n0
	
clean:
	$(OS_RM) nmc4vars_win.mk $(TARGET))
	$(OS_RM) *.elf *.map *.abs *.dll *.exe
	