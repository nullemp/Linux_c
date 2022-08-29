ENTRY(nomain)
SECTIONS
{
	. = 0x00000000004000e8 + SIZEOF_HEADERS;
	tinytext : { *(.text) *(.data) *(.rodata)}
	/DISCARD/ : {*(.comment)}

}
