#
# This is a universal Makefile for NeuroMatrix projects (application or library) [EDITION 20]
# with automatic recursive search of source files , compiling and linking.
# Makefile is processed by GNU make and may be used both in Linux and Windows OS
#
# To compile it you need: 
# * Latest NMSDK installed with utilities in your $PATH
# * NEURO environment variable pointing to NMSDK directory
# * Host GCC (Since nmcpp doesn't support generating header dependences, we use gcc for that) 
#
# Under OS Windows you need:
# * GNU Make           http://gnuwin32.sourceforge.net/packages/make.htm
# * GNU UNIX utilities http://sourceforge.net/projects/unxutils/
# * PATH enviroment variable pointing to GnuWin32 gcc
# * PATH enviroment variable pointing to GNU make
# * PATH enviroment variable pointing to GNU Utilities  (rm,find..)
#
# NOTE: You can use all-in-one package for Windows (Mingw32 + GNU make + GNU UNIX Utilities) 
#   available at \\dragon\distrib\ext_soft\gcc_make\mingw32_plus_gnumake.zip 
#   set PATH enviroment variable pointing to \mingw32\bin only
#
# USAGE:
#   For release build                    run 'make'
#   For debug   build                    run 'make DEBUG=y'
#   For debug & release  build           run 'make all'
#   For full  rebuild                    run 'make -B'
#   Multithread build (speed up)         run 'make -j4'
#   To clean                             run 'make clean'
#   To clean DEBUG & RELEASE             run 'make cleanall'
#   To create VisualStudio 2005 project  run 'make vs8'
#   For verbose build (no colorizing)    run 'make VERBOSE=y'
#   Execute target                       run 'make run'
#   Execute debug target                 run 'make rund'
#
# WARNING:
#   Makefile is sensitive to leading or trailing spaces and backslashes in the pathes
#
# DEFENITIONS:
#   PROJECT         - project name     
#   TARGET          - output target (.lib or .abs) file with path
#   INC_DIRS        - set of search pathes for the macro libraries and includes (with -I flag separated)
#   SRC_DIRS        - set of explicit  search pathes of all (.c .cpp .asm) source files (with space separated)
#   #SRC_DIR_RECURSE - set of recursive search pathes of all (.c .cpp .asm) source files (with space separated)
#   LIB_DIRS        - set of search library pathes (with -l flag separated)
#   TMP_DIR         - temporary build-folder (Debug/Release)
#   LIBS            - set of (.lib) libraries to be linked (with space separated)
#   
#   CROSS_COMPILE   - prefix before gcc in crosscompiler full name (for example: i686-w64-mingw32-) needed for generation of header dependences
#   CC              - C/C++ compiler(nmcpp/nmcc)
#   CC_FLAGS        - C/C++ compiler(nmcpp/nmcc) flags   
#   AS				- assembler(asm/nmcc)
#   AS_FLAGS        - assembler(asm/nmcc) flags for compiling of pure .asm files 
#   AS_FLAGS_C2ASM  - assembler(asm/nmcc) flags for compiling of .asm files compiled from .c/.cpp sources
#   BUILDER         - builder  (libr/linker) 			
#   BUILDER_FLAGS   - build flags of (libr/linker)
#   RUN_COMMAND     - command line to run target    
#
#   HEADER_DIRS     - set of pathes for .h   files to be included into Visual Studio project (with space separated)
#   RESOURCES       - set of any additionals files to be included into Visual Studio project
#
#============== PROJECT & BUILD CONFIGURATION ==========
#
#include .toolchecked.mk
#
#ifndef HAVE_gcc
#$(waring *** ERROR : $(CROSS_COMPILE)gcc compiler not found GCC (mingw32) might not have installed correctly. )
#.DEFAULT_GOAL := skip
#endif








#--------------  target & input dirs -------------------
ROOT             = ../../..
PROJECT          = nmpp_gcc
OUT_DIR          = $(ROOT)/lib
TARGET           = $(OUT_DIR)/lib$(PROJECT).a
INC_DIRS         = -I"$(NEURO)/include" -I$(ROOT)/include -I$(ROOT)/include/nmpls
SRC_DIRS         =  \
				../../../src/nmplc/arithmetic/common \
				../../../src/nmplc/fixpoint32/pc \
				../../../src/nmplc/fixpoint64/pc \
				../../../src/nmplc/init/common \
				../../../src/nmplc/integer/pc \
				../../../src/nmpli/Arithmetics/pc \
				../../../src/nmpli/Convert/common \
				../../../src/nmpli/Convert/pc \
				../../../src/nmpli/Filtration/common \
				../../../src/nmpli/Filtration/pc \
				../../../src/nmpli/Floodfill/common \
				../../../src/nmpli/Floodfill/pc \
				../../../src/nmpli/Init/common \
				../../../src/nmpli/Reodering/pc \
				../../../src/nmpli/Resample/common \
				../../../src/nmpli/Resample/pc \
				../../../src/nmpli/Select/pc \
				../../../src/nmpli/Support/common \
				../../../src/nmplm/Core/pc \
				../../../src/nmplm/Init/pc \
				../../../src/nmplm/Inverse/common \
				../../../src/nmplm/MatrixVector/pc \
				../../../src/nmplm/Support/common \
				../../../src/nmplm/Support/pc \
				../../../src/nmpls/Correlation/pc \
				../../../src/nmpls/FFT/FFT0256/pc \
				../../../src/nmpls/FFT/FFT0512/pc \
				../../../src/nmpls/FFT/FFT1024/pc \
				../../../src/nmpls/FFT/FFT2048/pc \
				../../../src/nmpls/FFT/FFT4096/pc \
				../../../src/nmpls/FFT/FFT8192/pc \
				../../../src/nmpls/FFT/IFFT0256/pc \
				../../../src/nmpls/FFT/IFFT0512/pc \
				../../../src/nmpls/FFT/IFFT1024/pc \
				../../../src/nmpls/FFT/IFFT2048/pc \
				../../../src/nmpls/FFT/IFFT4096/pc \
				../../../src/nmpls/FFT/IFFT8192/pc \
				../../../src/nmpls/Filter/common \
				../../../src/nmpls/Filtration/pc \
				../../../src/nmpls/Resample/common \
				../../../src/nmpls/Resample/pc \
				../../../src/nmplv/Arithmetics/common \
				../../../src/nmplv/Arithmetics/pc \
				../../../src/nmplv/Bitwise/pc \
				../../../src/nmplv/Init/common \
				../../../src/nmplv/Init/pc \
				../../../src/nmplv/nmtl_spec/pc \
				../../../src/nmplv/Select/common \
				../../../src/nmplv/Stat/common \
				../../../src/nmplv/Select/pc \
				../../../src/nmplv/Stat/pc \
				../../../src/nmplv/Support/pc \
				../../../src/nmplv/Support/common \
				../../../src/nmplv/Transform/common \
				../../../src/nmplv/Transform/pc

					

LIB_DIRS         = 
TMP_DIR          =Release
LIBS             = 
#--------------  RELEASE/ALL config -------------------
CROSS_COMPILE   ?=
AS               =
AS_FLAGS         =
AS_FLAGS_C2ASM   =
LIBS             =
CC               =gcc
CC_FLAGS         =-std=c99 -c
BUILDER          =ar
BUILDER_FLAGS    =rcs $(TARGET)
#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      =$(ROOT)/include $(ROOT)/source
RESOURCES        =Makefile



#--------------  Header dependence parsing -------------------------
PREPROCESS_ASM_DEP = $(CROSS_COMPILE)gcc -E -MM -xassembler-with-cpp -MT$(@) $(<) -o$(@).dep $(INC_DIRS) 
PREPROCESS_CPP_DEP = $(CROSS_COMPILE)gcc -E -MM -MT$(@) $(<) -o$(@).dep $(INC_DIRS)

#==================== Handle OS Specifics ==========================
ifeq ($(OS),Windows_NT)
  OS_WHICH= where
  OS_RM   = del /Q
  OS_RD   = rd /Q /S
  SHELL   = cmd
else
  OS_WHICH= which
  OS_RM   = rm -f -r
  OS_RD   = rm -f -r
endif


#=================== SOURCE & OBJECTS COLLECTION ===========================

#-include colorizer.mk
-include $(TMP_DIR)/*.dep
.SUFFIXES:




# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_ASM =$(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))


VPATH    = $(SRC_DIRS)

# collecting of objects
OBJECTS_CPP = $(notdir $(patsubst %.cpp,%.o,$(ALL_CPP)))
OBJECTS_ASM = $(notdir $(patsubst %.asm,%.o,$(ALL_ASM)))
OBJECTS_C   = $(notdir $(patsubst %.c,%.o,$(ALL_C)))
OBJECTS     = $(addprefix $(TMP_DIR)/,$(OBJECTS_C) $(OBJECTS_CPP)  $(OBJECTS_ASM))



#======================== BUILD RULES ====================================
.PHONY:all clean cleanall kill vs8 vs8stdout skip

#.DEFAULT_GOAL=default
default: $(TMP_DIR) $(OUT_DIR)  $(TARGET)

all: 
	$(MAKE) -j4

	
$(TMP_DIR):
	-mkdir "$(@)"

$(TARGET): $(TMP_DIR) $(OBJECTS) 
	$(BUILDER) $(BUILDER_FLAGS) $(OBJECTS) 

$(OUT_DIR): 
	-mkdir "$(@)"
	
$(TMP_DIR)/%.o: %.cpp 
#$(PREPROCESS_CPP_DEP)
	$(CC) $(CC_FLAGS) $(<) -o $(@) $(INC_DIRS) 

$(TMP_DIR)/%.o: %.c
#$(PREPROCESS_CPP_DEP)
	$(CC) $(CC_FLAGS) $(<) -o $(@) $(INC_DIRS) 

clean:
	-rm -f -r *.o *.ncb *.ilk  *.dep *.ac *.map *.suo *.user *.ncb 
	-rm -f -r Release Debug
 
cleanall:
	$(MAKE) clean
	$(MAKE) clean DEBUG=y
	
.toolchecked.mk:
	$(MAKE) -f checktools.mk
	
#========================== Visual Studio 8 support ===================
export ALL_CPP ALL_ASM ALL_C ALL_H

vs8: $(PROJECT).vcproj

$(PROJECT).vcproj: Makefile
	make --file=$(ROOT)/deps/projector/vs8.mk nmc-app --silent >$(@)

vs13: $(PROJECT).vcxproj

$(PROJECT).vcxproj: Makefile
	make --file=$(ROOT)/deps/projector/vs13.mk nmc-app --silent >$(@)

skip:
	@echo SDK missing. Compilation is skipped!
	
