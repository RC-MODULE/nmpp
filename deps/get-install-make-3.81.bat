powershell  -ExecutionPolicy Bypass -file wget.ps1  http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81.exe
powershell  -ExecutionPolicy Bypass -file wget.ps1  http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81-bin.zip http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81-dep.zip
mkdir make
powershell  -ExecutionPolicy Bypass -file unzip.ps1 make-3.81-bin.zip -d make
powershell  -ExecutionPolicy Bypass -file unzip.ps1 make-3.81-dep.zip -d make

@echo 
@echo GNU make-3.81 have installed to make
@echo Add %~dp0\make\bin to PATH environment variable!
rem @choice 
rem setx path "%~dp0\make\bin;%path%;" /M
