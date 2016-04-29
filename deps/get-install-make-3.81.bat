powershell  -ExecutionPolicy Bypass -file wget.ps1  http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81.exe
powershell  -ExecutionPolicy Bypass -file wget.ps1  http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81-bin.zip http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81-dep.zip
mkdir gnumake
powershell  -ExecutionPolicy Bypass -file unzip.ps1 make-3.81-bin.zip -d gnumake
powershell  -ExecutionPolicy Bypass -file unzip.ps1 make-3.81-dep.zip -d gnumake

@echo 
@echo GNU make-3.81 have installed to make
@echo Insert "%~dp0\gnumake\bin" at the beginning of PATH environment variable!
rem @choice 
rem setx path "%~dp0\gnumake\bin;%path%;" /M
