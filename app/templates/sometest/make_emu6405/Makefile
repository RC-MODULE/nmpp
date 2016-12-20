include $(ROOT)/global.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:

#NMPP?=
ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 


INC_DIRS = -I"$(NMPP)/include"
LIB_DIRS = -L"$(NMPP)/lib"  -L$(ROOT)/app/deps/nm_io/lib
LIBS     = nm_io_dummy.lib nmpp-nmc3d.lib libint05.lib  
TARGET   = main.abs
CFG      = emu6405.cfg
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))
SRC_ASM  = $(wildcard $(addsuffix /*.asm,..))


VPATH    = $(subst -L,,$(LIB_DIRS)) $(NEURO)/lib

$(TARGET): $(SRC_CPP) $(SRC_ASM) $(CFG) Makefile $(NMPP)/lib/nmpp-nmc3d.lib
	@echo $(CURDIR)>> $(ROOT)/app/test/build-emu6405.txt
	nmcc -o$(TARGET) -m.main.map $(SRC_CPP) $(SRC_ASM) $(NEURO)/crt/clock.asm -6405 -g -O0 $(INC_DIRS) $(LIB_DIRS) $(LIBS) -c$(CFG) -heap=16384 -heap1=16384 -heap2=16384 -heap3=16384
	@echo -OK>> $(ROOT)/app/test/build-emu6405.txt

run: $(TARGET) 
	nm6405emurun ./$(TARGET) 

test: .exitcode 
	
ifeq ($(OS),Windows_NT)	
.exitcode: $(TARGET) .test.bat
	.test.bat 
	
.test.bat: 
	@echo nm6405emurun $(TARGET) >.test.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.test.bat
else 
.exitcode: $(TARGET)
	nm6405emurun ./$(TARGET) ; echo $$? > .exitcode
endif


clean:
	-rm -f *.abs *.elf .*


	

