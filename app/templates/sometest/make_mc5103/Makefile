include $(ROOT)/global.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:

NMPP?=

ifndef MC5103
$(warning*** WARNING: 'MC5103' environment variable is not defined! Board SDK might not have installed correctly. )
endif 

ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 

INC_DIRS = -I"$(NMPP)/include" -I"$(MC5103)/include"
LIB_DIRS = -L"$(NMPP)/lib"  -L"$(MC5103)/lib" -L$(NMPP)/deps/nm_io/lib
LIBS     = nm_io.lib mc5103lib.lib nmpp-nmc3d.lib libint05.lib  
TARGET   = main.abs
CFG      = mc5103brd.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))


VPATH    = $(subst -L,,$(LIB_DIRS)) $(NEURO)/lib

$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile $(NMPP)/lib/nmpp-nmc3d.lib
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -6405 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=6384 -heap1=16384 -heap2=16384 -heap3=16384
#                                                                                                                  [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3 DEBUG=y
	
run: $(TARGET)
	mc5103run $(TARGET)

test: .exitcode
	
ifeq ($(OS),Windows_NT)	
.exitcode: $(TARGET) .test.bat
	.test.bat 
	
.test.bat: 
	@echo "$(MC5103)/bin/mc5103run" $(TARGET) >.test.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.test.bat
else 
.exitcode: $(TARGET)
	mc5103run ./$(TARGET) ; echo $$? > .exitcode
endif

clean:
	-$(OS_RM) *.abs *.elf .*


	

