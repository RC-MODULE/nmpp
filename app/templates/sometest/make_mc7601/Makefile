include $(ROOT)/global.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:

#NMPP?=

ifndef MC7601
$(warning *** WARNING: 'MC7601' environment variable is not defined! Board SDK might not have installed correctly. )
endif 

ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 


INC_DIRS = -I"$(NMPP)/include" -I"$(MC7601)/include"
LIB_DIRS = -L"$(NMPP)/lib"  -L"$(MC7601)/lib" -L$(DEVPACK)/nm_io/lib
LIBS     = nm_io_dummy.lib mc7601_LL_NM.lib nmpp-nmc3d.lib libint_soc.lib  
TARGET   = main.abs
CFG      = mc7601brd.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))


$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile $(NMPP)/lib/nmpp-nmc3d.lib
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -soc -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
#                                                                                         [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

run: .exitcode
	
ifeq ($(OS),Windows_NT)	
.exitcode: $(TARGET) .exitrun.bat
	.exitrun.bat 
	
.exitrun.bat: 
	@echo "$(MC7601)/bin/mc7601run" $(TARGET) >.exitrun.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.exitrun.bat
else 
.exitcode: $(TARGET)
	"$(MC7601)/bin/mc7601run" ./$(TARGET) ; echo $$? > .exitcode
endif

clean:
	-rm -f *.abs *.elf .*

skip:
	@echo SDK missing. Compilation is skipped!
	

