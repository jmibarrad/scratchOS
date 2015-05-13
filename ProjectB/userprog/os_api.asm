	;.global _syscall_printString
	.global _syscall_readString
	;.extern _syscall_readSector
	
_syscall_readString:
	push bx
	pop bx
	ret
