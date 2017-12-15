#include ../../setenv.mk
SHELL := cmd
.PHONY: chm pdf html

all: pdf

	
.cp-utf8:
	rm -f .cp-win1251
	doxygen
	echo "utf8 (without BOM)"> .cp-utf8

.cp-win1251: .cp-utf8
	rm -f .cp-utf8
	utf2win.bat

chm: 
	doxygen
	utf2win.bat
	taskkill /FI "windowtitle eq nmpp"
	-cd html && hhc index.hhp
	copy html\*.chm .

html:
	doxygen
	
pdf: 
	doxygen
	utf2win.tex.bat
	cd latex &&	call make.bat	
	copy .\latex\refman.pdf .\nmpp.pdf
	

clean: 
	-rm -f -r -v html xml latex nmpp.chm nmpp.pdf *.html .* 
	
open:
	www.bat
	
	#http://rc-module.github.io/nmpp
	
	#pdf
	#cp ./latex/refman.pdf ./html/nmpp.pdf
	#copy nmpp.pdf  html\nmpp.pdf	
	#nmpp.html ipp-nmpp.html 
	#copy ipp-nmpp.html html\ipp-nmpp.html
	#copy nmpp.html html\nmpp.html
	
github: chm pdf 
	doxygen
	copy nmpp.chm html\nmpp.chm /Y
	copy nmpp.pdf html\nmpp.pdf	/Y
	cd html &&\
	git init . && git checkout --orphan gh-pages &&\
	git add * &&\
	git commit -m "documentation-for-gh-pages" &&\
	git remote add origin https://github.com/RC-MODULE/nmpp.git  &&\
	git push -u -f origin gh-pages	


ipp:
	doxygen DoxyIPP
	
ipp-nmpp.html: 
	lua ipp-nmpp.lua
	xsltproc -o ipp-nmpp.html ipp-nmpp.xsl ipp-nmpp.xml
	
nmpp.html:	
	lua summary.lua
	xsltproc -o nmpp.html nmpp.xsl nmpp.xml
	
git-summary: nmpp.html ipp-nmpp.html 
	copy ipp-nmpp.html html\ipp-nmpp.html
	copy nmpp.html html\nmpp.html
	cd html &&\
	git add * &&\
	git commit -m "documentation-for-gh-pages" &&\
	git push -u -f origin gh-pages	
	
	