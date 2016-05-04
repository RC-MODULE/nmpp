@call cleanup.bat > nul

@rem NM

nmcpp -6405 nm_part.cpp -I"..\..\..\include" -I"%NEURO%\include"
asm -soc nm_part.asm
linker nm_part.elf mb7707lib.lib libc05.lib -l"..\..\..\lib" -l"%NEURO%\lib" ^
-cmb7707brd.cfg -m

@rem Host

setlocal
call "%VS80COMNTOOLS%..\..\vc\vcvarsall.bat"
cl host.cpp mb7707load.lib /I"..\..\..\libload" /I"%NEURO%\libload" /MT /EHsc ^
/link /libpath:"..\..\..\libload" /libpath:"%NEURO%\libload"
endlocal
