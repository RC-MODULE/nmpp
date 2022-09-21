@rm -f .utf2win
@for %%i in (html\*.html) do (
	@rm -f temp.txt 
	iconv -f utf-8 -t cp1251 %%i >temp.txt && sed -e "s/charset=UTF-8/charset=windows-1251/g" temp.txt > %%i
	@if ERRORLEVEL 1 goto WTF 
)
:@for %%i in (html\*.js) do (
:	@rm -f temp.txt 
:	iconv -f utf-8 -t cp1251 %%i >temp.txt && sed -e "s/charset=UTF-8/charset=windows-1251/g" temp.txt > %%i
:	@if ERRORLEVEL 1 goto WTF 
:)

@echo  "utf-8 to windows-1251 converted" > .cp-win1251
@exit 0
:WTF 
@exit 1
