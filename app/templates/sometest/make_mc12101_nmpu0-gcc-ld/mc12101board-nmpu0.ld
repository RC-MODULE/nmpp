MEMORY
{
  C0_IMU0 : ORIGIN = 0x00000800, LENGTH = 0x0001F800
  C0_IMU1 : ORIGIN = 0x00020000, LENGTH = 0x00020000
  C0_IMU2 : ORIGIN = 0x00040000, LENGTH = 0x00020000
  C0_IMU3 : ORIGIN = 0x00060000, LENGTH = 0x00020000
  C0_IMU4 : ORIGIN = 0x00080000, LENGTH = 0x00020000
  C0_IMU5 : ORIGIN = 0x000A0000, LENGTH = 0x00020000
  C0_IMU6 : ORIGIN = 0x000C0000, LENGTH = 0x00020000
  C0_IMU7 : ORIGIN = 0x000E0000, LENGTH = 0x00020000
/*SHMEM0 : ORIGIN = 0x00280000, LENGTH = 0x00020000 bytes reserved for by system loader*/
  SHMEM0 : ORIGIN = 0x002A0000, LENGTH = 0x00020000
  SHMEM1 : ORIGIN = 0x002C0000, LENGTH = 0x00040000
  EMI : ORIGIN = 0x80000000, LENGTH = 0x20000000
}

SECTIONS
{
  .text : ALIGN(0x8)
  {
    *(.text);
  } > EMI
  .init : ALIGN(0x8)
  {
    *(.init);
  } > C0_IMU5
  .fini : ALIGN(0x8)
  {
    *(.fini);
  } > C0_IMU5
  .mem_bank0 : ALIGN(0x8)
  {
    *(.mem_bank0);
  } > C0_IMU0
  .mem_bank1 : ALIGN(0x8)
  {
    *(.mem_bank1);
  } > C0_IMU1
  .mem_bank2 : ALIGN(0x8)
  {
    *(.mem_bank2);
  } > C0_IMU2
  .mem_bank3 : ALIGN(0x8)
  {
    *(.mem_bank3);
  } > C0_IMU3
  .mem_bank4 : ALIGN(0x8)
  {
    *(.mem_bank4);
  } > C0_IMU4
  .mem_bank5 : ALIGN(0x8)
  {
    *(.mem_bank5);
  } > C0_IMU5
  .mem_bank6 : ALIGN(0x8)
  {
    *(.mem_bank6);
  } > C0_IMU6
  .mem_bank7 : ALIGN(0x8)
  {
    *(.mem_bank7);
  } > C0_IMU7
  .data_DDR : ALIGN(0x8)
  {
    *(.data_DDR);
  } > EMI
  .mem_bank0.bss : ALIGN(0x8)
  {
    *(.mem_bank0.bss);
  } > C0_IMU0
  .mem_bank1.bss : ALIGN(0x8)
  {
    *(.mem_bank1.bss);
  } > C0_IMU1
  .mem_bank2.bss : ALIGN(0x8)
  {
    *(.mem_bank2.bss);
  } > C0_IMU2
  .mem_bank3.bss : ALIGN(0x8)
  {
    *(.mem_bank3.bss);
  } > C0_IMU3
  .mem_bank4.bss : ALIGN(0x8)
  {
    *(.mem_bank4.bss);
  } > C0_IMU4
  .mem_bank5.bss : ALIGN(0x8)
  {
    *(.mem_bank5.bss);
  } > C0_IMU5
  .mem_bank6.bss : ALIGN(0x8)
  {
    *(.mem_bank6.bss);
  } > C0_IMU6
  .mem_bank7.bss : ALIGN(0x8)
  {
    *(.mem_bank7.bss);
  } > C0_IMU7
  .data_DDR.bss : ALIGN(0x8)
  {
    *(.data_DDR.bss);
  } > EMI
  .data : ALIGN(0x8)
  {
    *(.data);
  } > C0_IMU6
  .bss : ALIGN(0x8)
  {
    *(.bss);
  } > C0_IMU6
  .stack : ALIGN(0x8)
  {
    *(.stack);
  } > C0_IMU7
  
  
  .rpc_services.bss : ALIGN(0x8)
  {
    *(.rpc_services.bss);
  } > EMI
  .rpc_services : ALIGN(0x8)
  {
    *(.rpc_services);
  } > EMI
  
  .heap : ALIGN(0x8)
  {
    *(.heap);
	. = ORIGIN(C0_IMU0) + LENGTH(C0_IMU0);
    __HEAP_0_END = .;
  } > C0_IMU0

  .heap1 : ALIGN(0x8)
  {
    *(.heap1);
	. = ORIGIN(C0_IMU1) + LENGTH(C0_IMU1);
    __HEAP_1_END = .;
  } > C0_IMU1

  .heap2 : ALIGN(0x8)
  {
    *(.heap2);
	. = ORIGIN(C0_IMU2) + LENGTH(C0_IMU2);
    __HEAP_2_END = .;
  } > C0_IMU2

  .heap3 : ALIGN(0x8)
  {
    *(.heap3);
	. = ORIGIN(C0_IMU3) + LENGTH(C0_IMU3);
    __HEAP_3_END = .;
  } > C0_IMU3
  
  
}