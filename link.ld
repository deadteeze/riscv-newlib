OUTPUT_FORMAT("elf64-littleriscv")
OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
  RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 64M
}

SECTIONS
{
  .text : {
    *(.text.init)
    *(.text)
  } > RAM

  .rodata : {
    *(.rodata)
  } > RAM

  .data : {
    *(.data)
  } > RAM

  .bss : {
    _bss_start = .;  
    *(.bss)
    *(COMMON)
    . = ALIGN(8);
    _bss_end = .;  
  } > RAM

  . = ALIGN(8);
  _end = .; 
  
  _stack_size = 64K;
  _stack_top = ORIGIN(RAM) + LENGTH(RAM);
  _stack_bottom = _stack_top - _stack_size;
  
  ASSERT(_end <= _stack_bottom, "Error: Heap collides with stack")
}
