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
.skip 1024

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
	# call kernel main
	call kernel_entry
	cli

# Loop forever
gameLoop:
	# Wait until interrupt
	call game_of_life
	# Go back to deadLoop label
	jmp gameLoop

.size _start, . - _start
