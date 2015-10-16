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

.PHONY : all nmc3 gcc vs80 vs13 clean 


all: gcc vs80 nmc3

nmc3:
	$(MAKE) -C ./nmc3
	$(MAKE) -C ./nmc3 DEBUG=y
	
gcc:	
	$(MAKE) -C ./pc/gcc
	
vs80:	
	$(MAKE) -C ./pc/vs80

vs13:	
	$(MAKE) -C ./pc/vs13
	
dist: 
	$(MAKE) -C ./distrib
	
doc: 	
	$(MAKE) -C ./doc
	
clean:
	rm -f -r *.suo *.ncb
	$(MAKE) -C ./nmc3 clean
	$(MAKE) -C ./pc/gcc  clean
	$(MAKE) -C ./pc/vs80 clean
	$(MAKE) -C ./pc/vs13 clean
	$(MAKE) -C ./doc  clean 
	rm -f -r lib
	

install:
	$(OS_SET_ENV)

	