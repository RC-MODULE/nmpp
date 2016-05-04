@call cleanup.bat > nul

nmcpp -6405 nm_part.cpp -I"%NEURO%\include"
asm -6405 nm_part.asm
linker nm_part.elf -l"%NEURO%\lib" mc5103lib.lib libc05.lib -cmc5103brd.cfg -m

@call "%VS80COMNTOOLS%..\..\vc\vcvarsall.bat"
@rem @call "%VS110COMNTOOLS%..\..\vc\vcvarsall.bat"
cl host.cpp "%NEURO%\libload\mc5103load.lib" -I"%NEURO%\libload" /MT /EHsc
