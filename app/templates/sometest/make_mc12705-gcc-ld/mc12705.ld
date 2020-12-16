MEMORY
{
  NMMB0 : ORIGIN = 0x00000800, LENGTH = 0x0000F800
  NMMB1 : ORIGIN = 0x00010000, LENGTH = 0x00010000
  NMMB2 : ORIGIN = 0x00020000, LENGTH = 0x00010000
  NMMB3 : ORIGIN = 0x00030000, LENGTH = 0x00010000
  NMMB4 : ORIGIN = 0x00040000, LENGTH = 0x00010000
  NMMB5 : ORIGIN = 0x00050000, LENGTH = 0x00010000
  NMMB6 : ORIGIN = 0x00060000, LENGTH = 0x00010000
  NMMB7 : ORIGIN = 0x00070000, LENGTH = 0x00010000
  EMI_CPU : ORIGIN = 0x00340000, LENGTH = 0x1FCC0000
}

SECTIONS
{
  .text : ALIGN(0x8)
  {
    *(.text);
  } > EMI_CPU
  .init : ALIGN(0x8)
  {
    *(.init);
  } > NMMB7
  .fini : ALIGN(0x8)
  {
    *(.fini);
  } > NMMB7
  .mem_bank0 : ALIGN(0x8)
  {
    *(.mem_bank0);
  } > NMMB0
  .mem_bank1 : ALIGN(0x8)
  {
    *(.mem_bank1);
  } > NMMB1
  .mem_bank2 : ALIGN(0x8)
  {
    *(.mem_bank2);
  } > NMMB2
  .mem_bank3 : ALIGN(0x8)
  {
    *(.mem_bank3);
  } > NMMB3
  .mem_bank4 : ALIGN(0x8)
  {
    *(.mem_bank4);
  } > NMMB4
  .mem_bank5 : ALIGN(0x8)
  {
    *(.mem_bank5);
  } > NMMB5
  .mem_bank6 : ALIGN(0x8)
  {
    *(.mem_bank6);
  } > NMMB6
  .mem_bank7 : ALIGN(0x8)
  {
    *(.mem_bank7);
  } > NMMB7
  .data_ddr : ALIGN(0x8)
  {
    *(.data_ddr);
  } > EMI_CPU
  .bss.mem_bank0 : ALIGN(0x8)
  {
    *(.bss.mem_bank0);
  } > NMMB0
  .bss.mem_bank1 : ALIGN(0x8)
  {
    *(.bss.mem_bank1);
  } > NMMB1
  .bss.mem_bank2 : ALIGN(0x8)
  {
    *(.bss.mem_bank2);
  } > NMMB2
  .bss.mem_bank3 : ALIGN(0x8)
  {
    *(.bss.mem_bank3);
  } > NMMB3
  .bss.mem_bank4 : ALIGN(0x8)
  {
    *(.bss.mem_bank4);
  } > NMMB4
  .bss.mem_bank5 : ALIGN(0x8)
  {
    *(.bss.mem_bank5);
  } > NMMB5
  .bss.mem_bank6 : ALIGN(0x8)
  {
    *(.bss.mem_bank6);
  } > NMMB6
  .bss.mem_bank7 : ALIGN(0x8)
  {
    *(.bss.mem_bank7);
  } > NMMB7
  .bss.data_ddr : ALIGN(0x8)
  {
    *(.bss.data_ddr);
  } > EMI_CPU

  .heap : ALIGN(0x8)
  {
    *(.heap);
	. = ORIGIN(NMMB0) + LENGTH(NMMB0);
    __HEAP_0_END = .;
  } > NMMB0
  .heap1 : ALIGN(0x8)
  {
    *(.heap1);
	. = ORIGIN(NMMB1) + LENGTH(NMMB1);
    __HEAP_1_END = .;
  } > NMMB1
  .heap2 : ALIGN(0x8)
  {
    *(.heap2);
	. = ORIGIN(NMMB2) + LENGTH(NMMB2);
    __HEAP_2_END = .;
  } > NMMB2
  .heap4 : ALIGN(0x8)
  {
    *(.heap3);
	. = ORIGIN(NMMB3) + LENGTH(NMMB3);
    __HEAP_3_END = .;
  } > NMMB3
  .data : ALIGN(0x8)
  {
    *(.data);
  } > NMMB7
  .bss : ALIGN(0x8)
  {
    *(.bss);
  } > NMMB7
  .stack : ALIGN(0x8)
  {
    *(.stack);
  } > NMMB7
}