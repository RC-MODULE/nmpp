#
# This is a  Makefile for NeuroMatrix projects (application or library) 
# with automatic recursive search of source files , compiling and linking.
# Makefile is processed by GNU make and may be used both in Linux and Windows OS
#
# USAGE:
#   For release build                    run 'make'
#   For debug   build                    run 'make DEBUG=y'
#   For debug & release  build           run 'make all'
#   For full  rebuild                    run 'make -B'
#   Multithread build (speed up)         run 'make -j4'
#   To clean                             run 'make clean'
#   To clean DEBUG & RELEASE             run 'make cleanall'
#   To create VisualStudio 2005 project  run 'make vs2005'
#   To create VisualStudio 2015 project  run 'make vs2015'
#   For verbose build (no colorizing)    run 'make VERBOSE=y'
#
# WARNING:
#   Makefile is sensitive to leading or trailing spaces and backslashes in the pathes
#
# DEFENITIONS:
#   PROJECT         - project name     
#   TARGET_LIB          - output TARGET_LIB (.lib or .abs) file with path
#   INC_DIRS        - set of search pathes for the macro libraries and includes (with -I flag separated)
#   SRC_DIRS        - set of explicit  search pathes of all (.c .cpp .asm) source files (with space separated)
#   LIB_DIRS        - set of search library pathes (with -l flag separated)
#   TMP_DIR         - temporary build-folder (Debug/Release)
#   
#   CFLAGS          - C compiler
#   CXXFLAGS        - C++ compiler flags   
#   AS              - assembler
#   ASMFLAGS        - assembler flags for compiling of pure .asm files 
#   AR              - librarian
#   ARFLAGS         - librarian flags of (libr/linker)
#

ROOT             = ../..
ifeq ($(OS),Windows_NT)
nmc4vars_win.mk:
	-copy "$(NMC_GCC_TOOLPATH)\nmc4-ide\include\nmc4vars_win.mk" nmc4vars_win.mk

-include 		 nmc4vars_win.mk
SHELL 			 = cmd
endif






ARCH             = nmc4
#--------------  target & input dirs -------------------
PROJECT          = libnmpp-$(ARCH)
TMP_DIR          = Release
OUT_DIR          = $(ROOT)/lib
TARGET_LIB       = $(OUT_DIR)/$(PROJECT).a
INC_DIRS         = -I$(ROOT)/include
SRC_DIRS         =

#------------------------------------------------
CC               = nmc-g++
LD               = nmc-ld
AR               = nmc-ar
AS               = nmc-gcc
ASM              = asm

CXXFLAGS         = -m$(ARCH) $(INC_DIRS)  -std=c++11 -c -O2
ARFLAGS          = rcs $(TARGET_LIB)
ASFLAGS          = -m$(ARCH) -mgas -c $(INC_DIRS) -g
ASMFLAGS         =-$(ARCH) -nmc4_fixed -nm2ms  -split_sir -W-111 -W-109 $(INC_DIRS) 

ifdef DEBUG      
TARGET_LIB       = $(OUT_DIR)/$(PROJECT)d.a
CXXFLAGS         = -m$(ARCH) $(INC_DIRS)  -std=c++11 -c -O0 -g
TMP_DIR          =Debug
endif 



#=================== SOURCE & OBJECTS COLLECTION ===========================
.SUFFIXES:

DIRS        =
include          $(ROOT)/make/src-nmc-fixed.mk
include          $(ROOT)/make/src-nmc-risc.mk

SRC_DIRS = $(DIRS)+ $(addsuffix /nm,$(DIRS)) + $(addsuffix /common,$(DIRS))


# regular search of *.c *.cpp,*.asm,*.s *.S sources in all $(SRC_DIRS)
ALL_CPP =$(notdir $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS))))
ALL_ASM =$(notdir $(wildcard $(addsuffix /*.asm,$(SRC_DIRS))))
ALL_C   =$(notdir $(wildcard $(addsuffix /*.c,$(SRC_DIRS))))
ALL_s   =$(patsubst %.S,,$(notdir $(wildcard $(addsuffix /*.s,$(SRC_DIRS)))))
ALL_S   =$(patsubst %.s,,$(notdir $(wildcard $(addsuffix /*.S,$(SRC_DIRS)))))


VPATH    = $(SRC_DIRS)

# collecting of objects
OBJECTS_CPP = $(patsubst %.cpp,%.o,$(ALL_CPP))
OBJECTS_ASM = $(patsubst %.asm,%.o,$(ALL_ASM))
OBJECTS_C   = $(patsubst %.c,%.o,$(ALL_C))
OBJECTS_s   = $(patsubst %.s,%.o,$(ALL_s))
OBJECTS_S   = $(patsubst %.S,%.o,$(ALL_S))


export OBJECTS     = $(addprefix $(TMP_DIR)/,$(OBJECTS_C) $(OBJECTS_CPP)  $(OBJECTS_ASM) $(OBJECTS_S) $(OBJECTS_s))

#$(info ----- $(ALL_s))
#$(info ----- $(ALL_S))
#$(info ----- $(OBJECTS_s))
#$(info ----- $(OBJECTS_S))
#$(info ----- )

#======================== BUILD RULES ====================================
.DEFAULT_GOAL=default

default: 
	$(MAKE) $(TARGET_LIB) -j4 
	
logo:
	$(info *******************************************************************************)
	$(info **                                                                           **)
	$(info **                       Neuro Matrix <$(CONFIGURATION)> compiling...          )
	$(info **                                                                           **)
	$(info *******************************************************************************)


$(TARGET_LIB): logo $(TMP_DIR) $(OUT_DIR) $(OBJECTS) 
	$(info "[Linking...]")
	echo rcs $(TARGET_LIB) > .objects 
	$(MAKE) -s --no-print-directory -f printobj.mk >> .objects
	$(AR) @.objects $(ERRECHO)
	@echo *******************************************************************************
	@echo **                                                                           **
	@echo **                                   Build OK!                               **
	@echo **                                                                           **
	@echo *******************************************************************************

legacy:
	$(MAKE) -f legacy.mk
	

$(TMP_DIR):
	-mkdir "$(@)"
	
$(OUT_DIR): 
	-mkdir "$(@)"
	
$(TMP_DIR)/%.o: %.c
	$(CC) $(CXXFLAGS) $(<) -o$(@) $(INC_DIRS) $(ERRECHO)

$(TMP_DIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) $(<) -o$(@) $(INC_DIRS) $(ERRECHO)
	
$(TMP_DIR)/%.o: %.asm 
	$(ASM) $(ASMFLAGS) $(<) -o$(@) $(ERRECHO)

$(TMP_DIR)/%.o: %.S
	$(AS) $(ASFLAGS) $(<) -o$(@) $(ERRECHO)

$(TMP_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) $(<) -o$(@) $(ERRECHO)



	

	
#========================== Visual Studio support ===================
HEADER_DIRS      =$(ROOT)/include $(ROOT)/include/nmplv $(ROOT)/include/nmpli $(ROOT)/include/nmpls $(ROOT)/include/nmplm $(ROOT)/include/nmplc
RESOURCES        =Makefile


#vs2005: Makefile
#	$(MAKE) -f $(ROOT)/deps/projector/vs8.mk nmc-app MAK=$(realpath .)/Makefile --silent >$(PROJECT).vcproj 

#vs2015 : Makefile
#	$(MAKE) -f $(ROOT)/deps/projector/vs13.mk nmc-app MAK=$(realpath .)/Makefile --silent >$(PROJECT).vcxproj

#========================== cleanup ===================
include $(ROOT)/clean.mk
