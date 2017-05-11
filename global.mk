#export  http_proxy       = http://user:pass@proxy:80/       (for wget usage)
#export https_proxy       = $(http_proxy)

export  NMPP       = $(ROOT)
export  DEVKIT    ?= d:/GIT/dev-kit
export  ARMTOOLCH ?=$(DEVKIT)/arm-rcm-linux-gnueabihf
export  NEURO     ?=$(DEVKIT)/nmsdk
export  VSHELL32  ?=$(DEVKIT)/vshell32
EASYNMC   ?=$(DEVKIT)/nmc-utils-0.1.1/libeasynmc-nmc

GNUWIN32          ?=c:/gnuwin32-lite/bin
MC5103            ?=(DEVKIT)/mc12101sdk
MC7601            ?=(DEVKIT)/mc7601sdk
MB7707            ?=(DEVKIT)/mb7707sdk


ifeq ($(OS),Windows_NT)
SHELL       = cmd
export PATH:=$(GNUWIN32);\
$(NEURO)/bin;\
$(MC5103)/bin;\
$(MB7707)/bin;\
$(MC7601)/bin;\
$(VSHELL32)/bin;\
$(ARMTOOLCH)/bin;\
$(PATH);
  
   CROSS_COMPILE=arm-rcm-linux-gnueabihf-
   ARM_CC       =arm-rcm-linux-gnueabihf-gcc.exe
   ARM_AR       =arm-rcm-linux-gnueabihf-ar.exe
   ARM_LD       =arm-rcm-linux-gnueabihf-ld.exe

#  OS_FIND  = $(call BACKSLASH,$(GNUWIN32)/find)
#  OS_DIFF  = $(call BACKSLASH,$(GNUWIN32)/diff)
#  OS_SCP   = $(call BACKSLASH,$(GNUWIN32)/pscp)
#  OS_CAT   = $(call BACKSLASH,$(GNUWIN32)/cat)
   OS_FIND  = gfind
   OS_DIFF  = diff
   OS_SCP   = pscp
   OS_CAT   = cat

   
#  OS_MV    = rename
   OS_RM    = del /Q
   RM       = rm -f -r
   OS_RD    = rd /Q /S 
#  OS_CP    = $(call BACKSLASH,$(GNUWIN32)/cp)
   OS_CP    = cp
   OS_WHICH =$(windir)/system32/where
#  OS_UNZIP = unzip 
   OS_UNZIP = powershell  -ExecutionPolicy Bypass -file $(NMPP)\deps\unzip.ps1 
   GNU_WGET = wget -nc --no-check-certificate --content-disposition 
   PS_WGET  = powershell  -ExecutionPolicy Bypass -file $(ROOT)\deps\wget.ps1 
   PS_UNZIP = powershell  -ExecutionPolicy Bypass -file unzip.ps1 
   OS_UNZIP = $(PS_UNZIP)
  
  define BACKSLASH
	$(subst /,\,$(1))
  endef

  MB7707_MAC ?= 1A-2B-3C-4D-5E-6F
else
  ARM_CC   = arm-module-linux-gnueabi-gcc 
  define OS_PATH
	$(1)
  endef 
  OS_DIFF  = diff   
  OS_SCP   = scp
  OS_RM    = rm -f -r
  RM       = rm -f -r
  OS_RD    = rm -d -r
  OS_FIND  = find
  OS_CAT   = cat
  OS_CP    = cp  
  OS_WHICH = which
  OS_WGET  = wget  
  OS_UNZIP = unzip
  OS_TAR   = tar xvzf 
  OS_TODIR = -C
  PATH    := $(NEURO)/bin:$(MC5103)/bin:$(MB7707)/bin:$(PATH)
  LD_LIBRARY_PATH = $(MC5103)/bin:$(MB7707)/bin
  MB7707_MAC = eth0
endif


PLATFORMS:=emu6405
ifdef MB7707
PLATFORMS += mb7707
ifndef MB7707_MAC
$(error MB7707_MAC is not defiened) 
endif
endif
 
#ifdef HAVE_edcltool
#PLATFORMS += mb7707_edcltool
#ifndef MB7707_ETH
#$(error MB7707_ETH is not defiened) 
#endif
#endif 

PLATFORMS  += mc5103

ifdef MC7601
PLATFORMS += mc7601
endif 

ifdef VS80COMNTOOLS
PLATFORMS += vs80
endif 

ifdef VS120COMNTOOLS
PLATFORMS += vs13
endif

#gcc
#mc7601
#PLATFORMS = vs80 mc5103 emu6405  mb7707 mc12101
PLATFORMS = vs80 mc12101_float

TARGET1=mc12101_float
TARGET2=vs80

define newline


endef	

 