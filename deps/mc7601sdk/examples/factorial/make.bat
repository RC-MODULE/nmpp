@call cleanup.bat > nul

nmcpp -6405 nm_part.cpp -I"..\..\include" -I"%NEURO%\include"
asm -soc nm_part.asm
linker nm_part.elf mc7601_ll_nm.lib libc05.lib -l"..\..\lib" -l"%NEURO%\lib" ^
-cmc7601brd.cfg -m

setlocal
call "%VS80COMNTOOLS%..\..\vc\vcvarsall.bat"
cl host.cpp mc7601_ll_pc.lib /I"..\..\include" /I"%NEURO%\libload" /MT /EHsc ^
/link /libpath:"..\..\lib" /libpath:"%NEURO%\libload"
endlocal
