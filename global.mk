
NMPP      = $(ROOT)
#http_proxy        = http://user:pass@proxy:80/       (for wget usage)

DEVPACK	 ?= $(realpath $(ROOT)/deps/dev-pack)

export NEURO    ?= $(DEVPACK)/nmsdk
export VSHELL32 ?= $(DEVPACK)/vshell32
MC5103    = $(DEVPACK)/mc5103sdk
MC7601    = $(DEVPACK)/mc7601sdk
MB7707    = $(DEVPACK)/mb7707sdk
GNUWIN32  = $(DEVPACK)/gnuwin32/bin

$(info $(DEVPACK))
$(info $(NEURO))


ifeq ($(OS),Windows_NT)
   ROOTFS  = $(DEVPACK)/rootfs
   EASYNMC = $(DEVPACK)/nmc-utils-0.1.1/libeasynmc-nmc

   ARM_CC   = arm-linux-gnueabihf-gcc.exe
   ARM_AR   = arm-linux-gnueabihf-ar.exe
   ARM_LD   = arm-linux-gnueabihf-ld.exe

   CROSS_COMPILE=arm-linux-gnueabihf-
   
   SHELL    = cmd
   OS_FIND  = $(call BACKSLASH,$(GNUWIN32)/find)
   OS_DIFF  = $(call BACKSLASH,$(GNUWIN32)/diff)
   OS_SCP   = $(call BACKSLASH,$(GNUWIN32)/pscp)
   OS_CAT   = $(call BACKSLASH,$(GNUWIN32)/cat)
   OS_MV    = rename
   OS_RM    = del /Q
#  OS_RM    = rm -f -r
   OS_RD    = rd /Q /S 
   OS_CP    = $(call BACKSLASH,$(GNUWIN32)/cp)
   OS_WHICH =$(windir)/system32/where
#  OS_WGET  = wget
   OS_WGET  = powershell  -ExecutionPolicy Bypass -file $(NMPP)\deps\wget.ps1 
#  OS_UNZIP = unzip 
   OS_UNZIP = powershell  -ExecutionPolicy Bypass -file $(NMPP)\deps\unzip.ps1 
   OS_TODIR = -d
   OS_UNPACK= $(OS_UNZIP)
   PATH_DEP = 	$(realpath $(GNUWIN32));\
				$(realpath $(NEURO)/bin);\
				$(realpath $(MC5103)/bin);\
				$(realpath $(MB7707)/bin);\
				$(realpath $(MC7601)/bin);\
				$(realpath $(VSHELL32)/bin);\
  
  export PATH    := $(realpath $(ROOT)/deps/gnumake/bin);$(PATH);C:/SysGCC/Raspberry/bin;$(DEVPACK)/Raspberry/bin);$(PATH_DEP)
  
  #$(info $(PATH))
  # NOTE: 'Raspberry\bin' shuld be first in PATH then $(GNUWIN32), because of 'libiconv-2.dll' version conflict.
  # But 'make.exe' ver-3.81 must be found first in then PATH then 'make.exe' ver-3.82 located in Raspberry\bin because of their non-compatibility 
  
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
  OS_RD    = rm -d -r
  OS_WHICH = which
  OS_WGET  = wget  
  OS_UNZIP = unzip
  OS_UNPACK= tar xvzf 
  OS_TODIR = -C
  PATH    := $(NEURO)/bin:$(MC5103)/bin:$(MB7707)/bin:$(PATH)
  LD_LIBRARY_PATH = $(MC5103)/bin:$(MB7707)/bin
  MB7707_MAC = eth0
endif

PLATFORMS:=emu6405
ifdef MB7707
PLATFORMS += mb7707_libload
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
PLATFORMS = vs80 mc5103 emu6405 mc7601

TARGET1=mc5103
TARGET2=vs80

define newline


endef	

 