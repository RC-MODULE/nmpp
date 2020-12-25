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
    *(text);
  } > NMMB0
 
  .text_ddr : ALIGN(0x8)
  {
    *(.text.*);
  } > EMI_CPU
  
  .init : ALIGN(0x8)
  {
    *(.init);
  } > NMMB0
  
  .fini : ALIGN(0x8)
  {
    *(.fini);
  } > NMMB0
  
  .data_imu0 : ALIGN(0x8)
  {
    *(.data_imu0);
    *(.data_imu0.bss);
  } > NMMB1
  
  .data_imu1 : ALIGN(0x8)
  {
    *(.data_imu1);
    *(.data_imu1.bss);
  } > NMMB1
  
  .data_imu2 : ALIGN(0x8)
  {
    *(.data_imu2);
    *(.data_imu2.bss);
  } > NMMB2
  
  .data_imu3 : ALIGN(0x8)
  {
    *(.data_imu3);
    *(.data_imu3.bss);
  } > NMMB3
  
  .data_imu4 : ALIGN(0x8)
  {
    *(.data_imu4);
    *(.data_imu4.bss);
  } > NMMB4
  
  .data_imu5 : ALIGN(0x8)
  {
    *(.data_imu5);
    *(.data_imu5.bss);
  } > NMMB5
  
  .data_imu6 : ALIGN(0x8)
  {
    *(.data_imu6);
    *(.data_imu6.bss);
  } > NMMB6
  
  .data_imu7 : ALIGN(0x8)
  {
    *(.data_imu7);
    *(.data_imu7.bss);
  } > NMMB7
  
  .data_ddr : ALIGN(0x8)
  {
    *(.data_ddr);
    *(.data_ddr.bss);
  } > EMI_CPU
  
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

  .heap4 : ALIGN(0x8)
  {
    *(.heap4);
	. = ORIGIN(NMMB4) + LENGTH(NMMB4);
    __HEAP_4_END = .;
  } > NMMB4
  .heap5 : ALIGN(0x8)
  {
    *(.heap5);
	. = ORIGIN(NMMB5) + LENGTH(NMMB5);
    __HEAP_5_END = .;
  } > NMMB5
  .heap6 : ALIGN(0x8)
  {
    *(.heap6);
	. = ORIGIN(NMMB6) + LENGTH(NMMB6);
    __HEAP_6_END = .;
  } > NMMB6
  .heap7 : ALIGN(0x8)
  {
    *(.heap7);
	. = ORIGIN(NMMB7) + LENGTH(NMMB7);
    __HEAP_7_END = .;
  } > NMMB7
 
}