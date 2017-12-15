@rm -f .utf2win
@for %%i in (latex\*.tex) do (
	@rm -f temp.txt
	iconv -f utf-8 -t cp1251 %%i >  temp.txt
	cp temp.txt %%i
	@if ERRORLEVEL 1 goto WTF 
)

@for %%i in (latex\*.sty) do (
	@rm -f temp.txt
	iconv -f utf-8 -t cp1251 %%i >  temp.txt
	cp temp.txt %%i
	@if ERRORLEVEL 1 goto WTF 
)

@for %%i in (latex\*.eps) do (
	@rm -f temp.txt
	iconv -f utf-8 -t cp1251 %%i >  temp.txt
	cp temp.txt %%i
	@if ERRORLEVEL 1 goto WTF 
)


sed -e "s/usepackage\[utf8\]/usepackage[cp1251]/g" latex/refman.tex -i

@echo  "utf-8 to windows-1251 converted" > .cp-win1251.tex
@exit 0
:WTF 
@exit 1
