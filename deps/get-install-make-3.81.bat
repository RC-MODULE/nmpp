powershell  -ExecutionPolicy Bypass -file wget.ps1  http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81.exe http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81-bin.zip http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81-dep.zip
mkdir gnumake
powershell  -ExecutionPolicy Bypass -file unzip.ps1 make-3.81-bin.zip -d gnumake
powershell  -ExecutionPolicy Bypass -file unzip.ps1 make-3.81-dep.zip -d gnumake

@pause
@echo off
@echo GNU make-3.81 have installed to %~dp0\gnumake\bin
@echo.
@echo Your current PATH is 
@path
@echo.
@set /P x=Do you want to add "%~dp0\gnumake\bin" folder to the PATH environment variable? (y/n)?
@set x=%x:~0,1%
@if (%x%)==(y) call addtopath %~dp0\gnumake\bin
@if (%x%)==(Y) call addtopath %~dp0\gnumake\bin
@pause

rem setx path "%~dp0\gnumake\bin;%path%;" /M
