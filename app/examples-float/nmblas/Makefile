ROOT=../../..

ifeq ($(OS),Windows_NT)
	PYTHON = python
else
	PYTHON = python3
endif

configure:
	$(PYTHON) $(ROOT)/app/nmcmake.py configure 

build:
	$(PYTHON) $(ROOT)/app/nmcmake.py make 
	
kill:
	$(PYTHON) $(ROOT)/app/nmcmake.py kill
	
run :
	$(PYTHON) $(ROOT)/app/nmcmake.py make run

clean :
	$(PYTHON) $(ROOT)/app/nmcmake.py make clean
