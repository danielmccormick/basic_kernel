/* Declare entry point for kernel */
ENTRY(_start)

SECTIONS 
{
	/* Grab 2 MB Space
	   This requests starting at address 2M */
	. = 2M;
	.heap BLOCK(4K) : ALIGN(4K)
	{
		_HEAP_START_ = .;
		*(.heap)
		_HEAP_END_ = .;
		
	}
	. = 4M;
	/* Text Block */
	.text BLOCK(4K) : ALIGN (4K)
	{ 
		*(.multiboot)
		*(.text) 
	}	

	/* Read Only Data */
	.rodata BLOCK(4K) : ALIGN (4K)
	{ 
		*(.rodata)
	}

	/* Not Read Only Data */
	.data BLOCK(4K) : ALIGN (4K) 
	{
		*(.data)
	}

	/* Binary Segment */
	.bss BLOCK(4K) : ALIGN (4K)
	{
		*(COMMON)
		*(.bss)
	}
}
