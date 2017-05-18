ROOT = ..
include $(ROOT)/global.mk
#==================== Handle OS Specifics ==========================
ifeq ($(OS),Windows_NT)
  SHELL   = cmd
  OS_WHICH= where
  OS_RM   = del /Q /A:A
  OS_RD   = rd /Q /S
  OS_SET_ENV = setx NMPP $(realpath ..) /m
else
  OS_WHICH= which
  OS_RM   = rm -f -r
  OS_RD   = rm -f -r
  OS_SET_ENV = export NMPP=$(realpath ..)
endif

.PHONY : all nmpp-nmc3 gcc vs8 vs13 clean 


all: gcc vs8 nmpp-nmc3

nmpp-nmc3:
	$(MAKE) -C ./nmpp-nmc3
	$(MAKE) -C ./nmpp-nmc3 DEBUG=y
	
gcc:	
	$(MAKE) -C ./pc/gcc
	
vs8:	
	$(MAKE) -C ./pc/vs8

vs13:	
	$(MAKE) -C ./pc/vs13
	
dist: 
	$(MAKE) -C ./distrib
	
doc: 	
	$(MAKE) -C ./doc

rpc:
	$(MAKE) -C ./nmpp-arm-rpc
	$(MAKE) -C ./nmpp-nmc3-rpc
	$(MAKE) -C ./nmpp-nmc3
	$(MAKE) -C ./nmpp-arm
	
clean:
	$(MAKE) -C ./nmpp-nmc3 clean
	$(MAKE) -C ./nmpp-nmc3-rpc clean
	$(MAKE) -C ./nmpp-arm-rpc clean
	$(MAKE) -C ./nmpp-arm clean
	$(MAKE) -C ./pc/gcc  clean
	$(MAKE) -C ./pc/vs8 clean
	$(MAKE) -C ./pc/vs13 clean
	$(MAKE) -C ./doc  clean 
	-rm -f -r *.suo *.ncb
	-rm -f -r lib
	

install:
	$(OS_SET_ENV)

	