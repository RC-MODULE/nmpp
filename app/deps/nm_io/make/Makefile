
../lib/nm_io_dummy.lib: dummy.elf
	libr -c ../lib/nm_io_dummy.lib dummy.elf

dummy.elf:	dummy.asm 
	asm -nmc3 dummy.asm
	
dummy.asm: dummy.c
	nmcpp -6405 -DNEURO -OPT2 -inline dummy.c -Tc

