# set magic number to 0x1BADB002
.set MAGIC, 0x1BADB002

# NO flags - no additional fields needed for now
.set FLAGS, 0

# checksum must be magic+flags
.set CHECKSUM, -(MAGIC+FLAGS)

# Multiboot section
.section .multiboot

# must be u32, and long obstensibly is 4 bytes
.long MAGIC
.long FLAGS
.long CHECKSUM

# stackBottom first because since sp goes high to low
stackBottom:

# max size 4096 bytes
.skip 4096

stackTop:

#text section
.section .text

# for future linking 
.global _start

# Declares start function
.type _start, @function

# Startup functoin
_start:
	#move SP
	mov $stackTop, %esp
	call kernel_entry
	cli

# Loop forever
deadLoop:
	# Wait until interrupt
	hlt
	# Go back to deadLoop label
	jmp deadLoop

.size _start, . - _start
