@call cleanup.bat > nul

nmcpp -6405 simple.cpp -OPT0 -debug
asm -6405 simple.asm -I"%NEURO%\include"
linker simple.elf -l"%NEURO%\lib" mc5103lib.lib libc05.lib -cmc5103brd.cfg -m -d0
