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




ifndef VS120COMNTOOLS
$(warning *** WARNING: 'VS120COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 13  might not have installed correctly. )
.DEFAULT_GOAL := skip
endif 

ifeq ($(OS),Windows_NT)
  SHELL = cmd
endif

#--------------  target & input dirs -------------------
ROOT             = ../../..
include $(ROOT)/global.mk
include $(ROOT)/make/src.mk
SRC_DIRS        := $(subst /nm ,/pc ,$(SRC_DIRS))
PROJECT          = nmpp-vs13
OUT_DIR          = $(ROOT)/lib
TARGET           = $(OUT_DIR)/$(PROJECT).lib
TARGETD          = $(OUT_DIR)/$(PROJECT)d.lib
INC_DIRS         = -I$(ROOT)/include -I$(ROOT)/include/nmpls


					

LIB_DIRS         =
TMP_DIR          = Release
LIBS             = 
#--------------  RELEASE/ALL config -------------------
CROSS_COMPILE   ?=
LIBS             =

AS               =
AS_FLAGS         =
AS_FLAGS_C2ASM   =

CC               =
CC_FLAGS         =

BUILDER          =
BUILDER_FLAGS    =




#--------------  DEBUG config -------------------------
ifdef DEBUG      
TMP_DIR          =Debug
endif 
#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      =$(ROOT)/source $(ROOT)/include $(ROOT)/include/nmplv $(ROOT)/include/nmpli $(ROOT)/include/nmpls $(ROOT)/include/nmplm $(ROOT)/include/nmplc
RESOURCES        =Makefile 

#=================== SOURCE & OBJECTS COLLECTION ===========================

#-include colorizer.mk
-include $(TMP_DIR)/*.dep
.SUFFIXES:




# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_ASM =$(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
ALL_H   =$(wildcard $(addsuffix /*.h,$(HEADER_DIRS)))


VPATH    = $(SRC_DIRS)



#======================== BUILD RULES ====================================
.PHONY: $(TARGET) $(TARGETD) all clean cleanall kill vs13 vs8stdout skip $(PROJECT).vcxproj

.DEFAULT_GOAL=all
	
all :  $(TARGET) $(TARGETD)



	
#$(TMP_DIR):
#	-mkdir "$(@)"

$(TARGETD): $(PROJECT).vcxproj
	"$(VS120COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj
	
$(TARGET): $(PROJECT).vcxproj 	
	"$(VS120COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj /p:Configuration=Release
 

clean:
	-$(OS_RM) *.exe *.o *.ncb *.ilk  *.dep *.ac *.map *.suo *.user *.ncb .toolchecked.mk null
	-$(OS_RD) Debug Release
 
.toolchecked.mk:
	$(MAKE) -f checktools.mk	
#========================== Visual Studio 8 support ===================
export HEADER_DIRS
export INC_DIRS LIB_DIRS
export LIBS LIBSD
export ALL_CPP ALL_ASM ALL_C ALL_H
export TARGET TARGETD

vs13: $(PROJECT).vcxproj

$(PROJECT).vcxproj: Makefile
	make --file=$(ROOT)/deps/projector/vs13.mk vc-lib --silent >$(@)	

skip:
	@echo SDK missing. Compilation is skipped!
	
