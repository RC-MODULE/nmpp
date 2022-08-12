ROOT=../..

ifeq ($(OS),Windows_NT)
	PYTHON = python
else
	PYTHON = python3
endif


default: kill configure build run match 

configure:
	autotest configure 

build:
	autotest make 
	
kill:
	autotest kill

run :
	autotest make run

match:
	autotest match .exitcode

qemu:
	autotest make qemu

clean :
	autotest make clean
