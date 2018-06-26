include $(ROOT)/global.mk
-include ../local.mk
HEAP ?= -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:

#NMPP?=

ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 


INC_DIRS = -I"$(NMPP)/include" -I"$(MC7601)/include" -I$(HAL)/include
LIB_DIRS = -L"$(NMPP)/lib"  -L"$(MC7601)/lib" -L$(HAL)/lib
LIBS     = hal-mc7601.lib mc7601_ll_nm.lib nmpp-nmc3.lib libint_soc.lib  
TARGET   = main.abs
CFG      = mc7601brd.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))


$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile $(NMPP)/lib/nmpp-nmc3.lib
	@echo $(CURDIR)>> $(ROOT)/app/test/build-mc7601.txt
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM)  -soc -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
	@echo -OK>> $(ROOT)/app/test/build-mc7601.txt
#                                                                                         [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

PATH:=$(MC7601)/bin;$(PATH)

$(NMPP)/lib/nmpp-nmc3.lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3
	
run: $(TARGET)
	mc7601run $(TARGET)

test: .exitcode
	
ifeq ($(OS),Windows_NT)	
.exitcode: $(TARGET) .test.bat
	.test.bat 
	
.test.bat: 
	@echo mc7601run $(TARGET) >.test.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.test.bat
else 
.exitcode: $(TARGET)
	mc7601run ./$(TARGET) ; echo $$? > .exitcode
endif

-include $(NMPP)/local.mk
include $(ROOT)/clean.mk	

	

