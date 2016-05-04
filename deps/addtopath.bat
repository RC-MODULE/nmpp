rem Script adds full path from %1 argument to %PATH% system environment variable
@echo off
set Key=HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment

set FolderToAdd=%1

For /f "tokens=2*" %%a In ('Reg.exe query "%key%" /v Path^|Find "Path"') do set CurPath=%%~b
reg.exe add "%Key%" /v Path /t REG_EXPAND_SZ /d "%CurPath%;%FolderToAdd%" /f
@echo Restart Windows