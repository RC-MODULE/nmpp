include $(ROOT)/setenv.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MB7707 board and stores return code in ".exitcode"  file

.SUFFIXES:

#NMPP?=

ifndef MB7707
$(warning*** WARNING: 'MB7707' environment variable is not defined! Board SDK might not have installed correctly. )
endif 

ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 

ifeq ($(wildcard ./config.mk),)
ifeq ($(wildcard ./../config.mk),)
ifeq ($(wildcard ./../../config.mk),)
ifeq ($(wildcard ./../../../config.mk),)
include  ../../../../config.mk
else 
include  ../../../config.mk
endif
else 
include  ../../config.mk	
endif
else
include ../config.mk
endif
else 
include ./config.mk	
endif

INC_DIRS = -I"$(NMPP)/include" -I"$(MB7707)/nm/include"
LIB_DIRS = -L"$(NMPP)/lib"  -L"$(MB7707)/nm/lib" 
LIBS     = nmpp-nmc3d.lib libint_soc.lib libc05.lib cppnew05.lib 
TARGET   = main.abs
CFG      = mb7707brd.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))

VPATH    = $(subst -L,,$(LIB_DIRS)) $(NEURO)/lib

$(TARGET): $(SRC_CPP)  $(CFG)   Makefile $(NMPP)/lib/nmpp-nmc3d.lib
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) -soc -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
#                                                                                         [L00]:64kB   [L01]:64kB  [G00]:64kB   [G01]:64kB

run: .exitcode

ifeq ($(OS),Windows_NT)	
.exitcode: $(TARGET) .exitrun.bat
	.exitrun.bat 
	
.exitrun.bat: 
	@echo edcltool -f ./run.edcl -i $(MB7707_ETH) >.exitrun.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.exitrun.bat
else 
.exitcode: $(TARGET)
	edcltool -f ./run.edcl -i $(MB7707_ETH) ; echo $$? > .exitcode
endif

		
clean:
	-rm -f *.abs *.elf .*

skip:
	@echo Compilation is skipped!
	

