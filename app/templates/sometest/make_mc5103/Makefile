include $(ROOT)/global.mk
-include ../local.mk
HEAP ?= -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:

NMPP?=


ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 

INC_DIRS = -I"$(NMPP)/include" -I"$(MC5103)/include"
LIB_DIRS = -L"$(NMPP)/lib"  -L"$(MC5103)/lib" -L$(HAL)/lib
LIBS     = hal-mc5103.lib mc5103lib.lib nmpp-nmc3.lib libint05.lib  
TARGET   = main.abs
CFG      = mc5103brd.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))


VPATH    = $(subst -L,,$(LIB_DIRS)) $(NEURO)/lib

$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile $(NMPP)/lib/nmpp-nmc3.lib
	@echo $(CURDIR)>> $(ROOT)/app/test/build-mc5103.txt
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) $(NEURO)/crt/clock.asm -6405 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) $(HEAP)
	@echo -OK>> $(ROOT)/app/test/build-mc5103.txt
#                                                                                                                  [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

PATH:=$(MC5103)/bin;$(PATH)

$(NMPP)/lib/nmpp-nmc3.lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3
	
run: $(TARGET)
	mc5103run $(TARGET)

test: .exitcode
	
ifeq ($(OS),Windows_NT)	
.exitcode: $(TARGET) .test.bat
	.test.bat 
	
.test.bat: 
	@echo mc5103run $(TARGET) >.test.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.test.bat
else 
.exitcode: $(TARGET)
	mc5103run ./$(TARGET) ; echo $$? > .exitcode
endif

-include $(NMPP)/local.mk
-include $(NMPP)/clean.mk


	

