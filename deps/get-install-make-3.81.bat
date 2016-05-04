powershell  -ExecutionPolicy Bypass -file wget.ps1  http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81.exe
powershell  -ExecutionPolicy Bypass -file wget.ps1  http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81-bin.zip http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81-dep.zip
mkdir gnumake
powershell  -ExecutionPolicy Bypass -file unzip.ps1 make-3.81-bin.zip -d gnumake
powershell  -ExecutionPolicy Bypass -file unzip.ps1 make-3.81-dep.zip -d gnumake

@echo off
@echo GNU make-3.81 have installed to %~dp0\gnumake\bin
@echo Your current PATH is 
@echo %PATH%
@echo ##################################################
@echo Do you wish to add "%~dp0\gnumake\bin" folder to the PATH environment variable?
@choice 
@if ERRORLEVEL 1 call addtopath %~dp0\gnumake\bin
@pause

rem setx path "%~dp0\gnumake\bin;%path%;" /M
