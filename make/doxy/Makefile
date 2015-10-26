include ../../setenv.mk
SHELL := cmd

all: pdf

chm:
	taskkill /FI "windowtitle eq nmpp"
	doxygen
	copy html\*.chm .


pdf: chm
	cd latex &&	call make.bat
	copy .\latex\refman.pdf .\nmpp.pdf

clean: 
	-rm -f -r -v html latex nmpp.chm nmpp.pdf 
	
open:
	www.bat
	
	#http://rc-module.github.io/nmpp
	
github: clean chm pdf
	cp ./latex/refman.pdf ./html/nmpp.pdf
	cd html &&\
	git init . && git checkout --orphan gh-pages &&\
	git add * &&\
	git commit -m "documentation-for-gh-pages" &&\
	git remote add origin https://github.com/RC-MODULE/nmpp.git  &&\
	git push -u -f origin gh-pages	
