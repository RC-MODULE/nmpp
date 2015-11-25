#NMPP             = $(ROOT)/deps/nmpp
#NMPROFILER       = $(ROOT)/deps/nmprofiler
#http_proxy        = http://user:pass@proxy:80/       (for wget usage)

NEURO    ?= $(realpath $(ROOT))/deps/nmsdk
#VSHELL32 = $(realpath $(ROOT))/deps/vshell32
MC5103   = $(realpath $(ROOT))/deps/mc5103sdk
MC7601   = $(realpath $(ROOT))/deps/mc7601sdk
MB7707   = $(realpath $(ROOT))/deps/mb7707sdk




ifeq ($(OS),Windows_NT)
  AURA     = d:/GIT/matlab/aura
  ARM_CC   = d:/SDK/arm-module-linux-gnueabi/bin/arm-module-linux-gnueabi-gcc
  ARM_AR   = d:/SDK/arm-module-linux-gnueabi/bin/arm-module-linux-gnueabi-ar
  
  SHELL    = cmd
  OS_RM    = del /Q
  OS_RD    = rd /Q /S 
  OS_WHICH =$(windir)/system32/where
 #OS_WGET  = wget
  OS_WGET  = powershell  -ExecutionPolicy Bypass -file $(ROOT)/deps/wget.ps1 
 #OS_UNZIP = unzip 
  OS_UNZIP = powershell  -ExecutionPolicy Bypass -file $(ROOT)/seps/unzip.ps1 
  OS_TODIR = -d
  OS_TAR   = $(OS_UNZIP)
  PATH    := $(NEURO)/bin;$(MC5103)/bin;$(MB7707)/bin;$(MC7601)/bin;$(ROOT)/deps/gnuwin32/bin;$(VSHELL32)/bin;$(PATH)
  #prevents call of embedded 'find.exe' in Windows and GNU make becomes callable
  PATH:= $(subst $(SystemRoot),,$(PATH))	

  MB7707_MAC ?= 1A-2B-3C-4D-5E-6F
else
  ARM_CC   = arm-module-linux-gnueabi-gcc 
  OS_RM    = rm -f -r
  OS_RD    = rm -d -r
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

#PLATFORMS += gcc

TARGET1=mc5103
TARGET2=vs80

 