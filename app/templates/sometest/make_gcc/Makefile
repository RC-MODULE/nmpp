include $(ROOT)/global.mk
# BUILD AND RUN MAKEFILE
# This makefile builds simple nmc-application containing single cpp-file  
# Rule 'run' executes the application on MC5103 board and stores return code in ".exitcode"  file

.SUFFIXES:

#NMPP?=
ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 

	
ifndef CROSS_COMPILE
  $(warning *** WARNING: 'CROSS_COMPILE' environment variable is not defined! GCC (mingw32) might not have installed correctly. )
  .DEFAULT_GOAL := skip
endif


.PHONY : run clean

INC_DIRS = -I"$(NMPP)/include"
LIB_DIRS = -L"$(NMPP)/lib"  
LIBS     =gcc
ifeq ($(OS),Windows_NT)
TARGET   = main.exe
else 
TARGET   = main
endif
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))


VPATH    = $(subst -L,,$(LIB_DIRS)) $(NEURO)/lib

$(TARGET): $(SRC_CPP)  Makefile $(NMPP)/lib/gcc.a
	@echo $(CURDIR)>> $(ROOT)/app/test/build-gcc.txt
	g++ -o $(TARGET) $(SRC_CPP) $(INC_DIRS) $(LIB_DIRS) -l$(LIBS)
	@echo -OK>> $(ROOT)/app/test/build-gcc.txt


run: .exitcode
	
	
ifeq ($(OS),Windows_NT)	
.exitcode: $(TARGET) .exitrun.bat
	.exitrun.bat 
	
.exitrun.bat: 
	@echo $(TARGET) >.exitrun.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.exitrun.bat
else 
.exitcode: $(TARGET)
	./$(TARGET) ; echo $$? > .exitcode
endif

	
#-----------------------------------------------------
	
clean:
	-rm -f $(TARGET) *.abs *.elf .*

skip:
	@echo Compilation is skipped!
	
