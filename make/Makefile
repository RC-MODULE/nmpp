ROOT = ..
include $(ROOT)/global.mk
#==================== Handle OS Specifics ==========================
ifeq ($(OS),Windows_NT)
  SHELL   = cmd
  OS_WHICH= where
  OS_RM   = del /Q /A:A
  OS_RD   = rd /Q /S
  OS_SET_ENV = setx  /m 
else
  OS_WHICH= which
  OS_RM   = rm -f -r
  OS_RD   = rm -f -r
  OS_SET_ENV = export 
endif

.PHONY : all nmpp-nmc3 nmpp-nmc4 nmpp-nmc4f nmpp-nmc3-legacy nmpp-nmc4-legacy nmpp-nmc4f-legacy nmpp-x86-x64


all: nmpp-nmc3 nmpp-nmc4 nmpp-nmc4f nmpp-nmc3-legacy nmpp-nmc4-legacy nmpp-nmc4f-legacy nmpp-x86-x64
	

nmpp-nmc3:
	$(MAKE) -C ./nmpp-nmc3

nmpp-nmc4:
	$(MAKE) -C ./nmpp-nmc4

nmpp-nmc4f:
	$(MAKE) -C ./nmpp-nmc4f
	
nmpp-nmc3-legacy:
	$(MAKE) -C ./nmpp-nmc3 legacy

nmpp-nmc4-legacy:
	$(MAKE) -C ./nmpp-nmc4 legacy
	
nmpp-nmc4f-legacy:
	$(MAKE) -C ./nmpp-nmc4f legacy
	
nmpp-x86-x64:
	$(MAKE) -C ./nmpp-x86-x64

	
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
	$(MAKE) -C ./nmpp-nmc4 clean
	$(MAKE) -C ./nmpp-nmc4f clean
	
	
	$(MAKE) -C ./nmpp-nmc3-rpc clean
	$(MAKE) -C ./nmpp-arm-rpc clean
	$(MAKE) -C ./nmpp-arm clean
	$(MAKE) -C ./doxy  clean 
	#-rm -f -r *.suo *.ncb
	#-rm -f -r lib
	

install: all setenv 
	
	
setenv:
	$(OS_SET_ENV) NMPP "$(realpath ..)"
	
#	setenv -ua NMPP "$(realpath ..)"


		
#	$(OS_SET_ENV)

	