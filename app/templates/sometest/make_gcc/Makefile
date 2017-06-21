ROOT=../../../../../..
include $(ROOT)/global.mk

# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file

.SUFFIXES:

#NMPP?=
ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 

	
#ifndef CROSS_COMPILE
#  $(warning *** WARNING: 'CROSS_COMPILE' environment variable is not defined! GCC (mingw32) might not have installed correctly. )
#  .DEFAULT_GOAL := skip
#endif


.PHONY : run clean

INC_DIRS = -I"$(NMPP)/include"
LIB_DIRS = -L"$(NMPP)/lib"  
LIBS     =nmpp-x64
ifeq ($(OS),Windows_NT)
TARGET   = main.exe
else 
TARGET   = main
endif
SRC_CPP  = $(wildcard $(addsuffix /*.cpp,..))


VPATH    = $(subst -L,,$(LIB_DIRS)) $(NEURO)/lib

$(TARGET): $(SRC_CPP)  Makefile $(NMPP)/lib/libnmpp-x64.a
	@echo $(CURDIR)>> $(ROOT)/app/test/build-gcc.txt
	g++ -o $(TARGET) $(SRC_CPP) $(INC_DIRS) $(LIB_DIRS) -l$(LIBS)
	@echo -OK>> $(ROOT)/app/test/build-gcc.txt

run:	$(TARGET)
	$(TARGET)

test: .exitcode
	
	
ifeq ($(OS),Windows_NT)	
.exitcode: $(TARGET) .test.bat
	.test.bat 
	
.test.bat: 
	@echo $(TARGET) >.test.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.test.bat
else 
.exitcode: $(TARGET)
	./$(TARGET) ; echo $$? > .exitcode
endif

	
#-----------------------------------------------------
	
clean:
	-rm -f $(TARGET) *.abs *.elf .*

skip:
	@echo Compilation is skipped!
	
