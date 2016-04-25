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

#ifdef NEURO
#  .DEFAULT_GOAL := default
#else 
#  $(error *** ERROR: 'NEURO' environment variable is not defined! NMSDK might not have installed correctly. )
#  .DEFAULT_GOAL := skip
#endif

ROOT = ../..
include $(ROOT)/global.mk

CC =$(ARM_CC)
LD =$(ARM_CC)
AR =$(ARM_AR)
OBJCOPY = $(ARM_CC)-objcopy
OBJDUMP = $(ARM_CC)-objdump


define OS_PATH
$(eval $(subst /,\,$(1)))
endef

#--------------  target & input dirs -------------------
ROOT             = ../..
PROJECT          = libnmpp-arm-rpc
OUT_DIR          = ../../lib
ifeq ($(OS),Windows_NT)
TARGET           = $(subst /,\,$(OUT_DIR)/$(PROJECT).a)
else 
TARGET           = $(OUT_DIR)/$(PROJECT).a
endif
#INC_DIRS         = -I../../include -I../../include/nmpls
INC_DIRS         = \
-I$(ROOTFS)/usr/include/arm-linux-gnueabi/aura-0.1.2/ \
-I$(ROOTFS)/usr/include/ \
-I$(ROOTFS)/usr/include/arm-linux-gnueabi/ \
-I$(NMPP)/include \
-I$(NMPP)/include/rpc

#-I../../include -I$(AURA)/include -I$(AURA)/nmc-utils/include 
#-I../../include/nmpls
SRC_DIRS         =  ../../src/nmplv/Arithmetics/rpc-arm \
					../../src/nmplv/Bitwise/rpc-arm \
					../../src/nmplv/Select/rpc-arm \
					../../src/nmpls/FFT/FFT0256/rpc-arm \
					../../src/nmpls/FFT/FFT0512/rpc-arm \
					../../src/nmpls/FFT/FFT1024/rpc-arm \
					../../src/nmpls/FFT/FFT2048/rpc-arm \
					../../src/nmplm/MatrixVector/pc
					
					
TMP_DIR          = Release
#------------------------------------------------
AS_FLAGS         = $(INC_DIRS)
#CC_FLAGS 		 = -g -Wall -fPIC $(INC_DIRS) -DRPC=y -std=c99
CC_FLAGS = -DRPC=y -D_GNU_SOURCE -std=c99 -marm -march=armv4t -mfloat-abi=soft \
-marm -march=armv4t -mfloat-abi=soft \
--sysroot=$(ROOTFS) 


#-std=c99 -fno-exceptions -Wall -O0 -mcpu=arm1176jzf-s -DGPIO_LEG=6 -fno-zero-initialized-in-bss $(ING_DIRS) 

BUILDER          = $(AR)
BUILDER_FLAGS    = rcs $(TARGET)


#--------------  Header dependence parsing -------------------------
ifdef HAVE_gcc
PREPROCESS_ASM_DEP = $(ARM_CC)gcc -E -MM -xassembler-with-cpp -MT$(@) $(<) -o$(@).dep $(INC_DIRS) 
PREPROCESS_CPP_DEP = $(ARM_CC)gcc -E -MM -MT$(@) $(<) -o$(@).dep $(INC_DIRS)
endif

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

# collecting of objects
OBJECTS_CPP = $(notdir $(patsubst %.cpp,%.o,$(ALL_CPP)))
OBJECTS_ASM = $(notdir $(patsubst %.asm,%.o,$(ALL_ASM)))
OBJECTS_C   = $(notdir $(patsubst %.c,%.o,$(ALL_C)))
OBJECTS     = $(addprefix $(TMP_DIR)/,$(OBJECTS_C) $(OBJECTS_CPP)  $(OBJECTS_ASM))


#======================== BUILD RULES ====================================
.PHONY:all  clean cleanall vs8  skip

#.DEFAULT_GOAL=default
default: $(TMP_DIR) $(OUT_DIR)  $(TARGET)

all: 
	$(MAKE) -j4

	
$(TMP_DIR):
	-mkdir "$(@)"

$(TARGET): $(TMP_DIR) $(OBJECTS) 
	-$(OS_RM) $(TARGET)
	$(BUILDER) $(BUILDER_FLAGS) $(OBJECTS) 

$(OUT_DIR): 
	-mkdir "$(@)"
	
$(TMP_DIR)/%.o: %.c 
	$(PREPROCESS_ASM_DEP)
	$(CC) $(CC_FLAGS) -c $(<) -o$(@) $(INC_DIRS) 

$(TMP_DIR)/%.o: %.cpp
	$(PREPROCESS_ASM_DEP)
	$(CC) $(CC_FLAGS) -c $(<) -o$(@) $(INC_DIRS) 
	
clean:
	-$(OS_RM) $(TARGET) *.abs *.o *.ncb *.ilk  *.dep *.ac *.map *.suo *.user *.ncb .toolchecked.mk 
	-$(OS_RD) Debug Release
 
cleanall:
	$(MAKE) clean
	
