include $(ROOT)/global.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:

#NMPP?=

ifndef MC12101
$(warning *** WARNING: 'MC12101' environment variable is not defined! Board SDK might not have installed correctly. )
endif 

ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 


INC_DIRS = -I"$(NMPP)/include" -I"$(MC12101)/include" -I"$(NEURO)/include" -I"$(HAL)/include"
LIB_DIRS = -L"$(NMPP)/lib"     -L"$(MC12101)/lib" -L$(HAL)/lib -L"$(NEURO)/lib"
LIBS     = mc12101lib_nm.lib libc4f.lib libc4.lib nmpp-nmc4.lib hal-mc12101.lib
TARGET   = main.abs
CFG      = mc12101brd-nmc1.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))


$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile $(NMPP)/lib/nmpp-nmc4.lib
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) clock.asm -nmc4 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=0 -heap1=6384 -heap2=16384 -heap3=16384
#                                                                                         [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB


PATH:=$(MC12101)/bin;$(PATH)

	
run: $(TARGET)
	mc12101run $(TARGET) -p

test: .exitcode
	
ifeq ($(OS),Windows_NT)	
.exitcode: $(TARGET) .exitrun.bat
	.exitrun.bat 
	
.exitrun.bat: 
	@echo "$(MC12101)/bin/mc12101run" $(TARGET) >.exitrun.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.exitrun.bat
else 
.exitcode: $(TARGET)
	mc12101run ./$(TARGET) ; echo $$? > .exitcode
endif

clean:
	-rm -f *.abs *.elf .*

skip:
	@echo SDK missing. Compilation is skipped!
	
reset:
	reset12101	

