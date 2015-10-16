
all: pdf

chm:
	taskkill /FI "windowtitle eq nmpp"
	doxygen
	copy html\*.chm .


pdf: chm
	cd latex &&	call make.bat
	copy .\latex\refman.pdf .\nmpp.pdf

clean: 
	rm -f -r html latex *.chm *.pdf 
