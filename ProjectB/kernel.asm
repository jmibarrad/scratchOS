;kernel.asm
;Michael Black, 2007

;kernel.asm contains assembly functions that you can use in your kernel

	.global _putInMemory
	.global _makeInterrupt21
	.global _loadProgram
	.global _readChar
	.global _printChar
	.global _readSector
	.global _end
	.global _ps
	.global _rs
	.global _interrupt21ServiceRoutine
	.extern _printString
	.extern _readString
	.global _setCursor
	
;void putInMemory (int segment, int address, char character)
_putInMemory:
	push bp
	mov bp,sp
	push ds
	mov ax,[bp+4]
	mov si,[bp+6]
	mov cl,[bp+8]
	mov ds,ax
	mov [si],cl
	pop ds
	pop bp
	ret

_printChar: 
	push bp
	mov bp, sp
	mov al, [bp+4]  
	mov ah, #0x0e	
	mov bh, #1 		;current page
	int #0x10
	pop bp
	ret

_readChar:
	mov ah, #0
	int #0x16
	ret

_loadProgram:
	mov ax, #0x2000
	mov ds, ax
	mov ss, ax
	mov es, ax 
	mov ax, #0xfff0 	;let's have the stack start at 0x2000:fff0
	mov sp, ax
	mov bp, ax		; Read the program from the floppy
	mov	cl, #12		;cl holds sector number
	mov	dh, #0		;dh holds head number - 0
	mov	ch, #0		;ch holds track number - 0
	mov	ah, #2		;absolute disk read
	mov	al, #1		;read 1 sector
	mov	dl, #0		;read from floppy disk A
	mov	bx, #0		;read into offset 0 (in the segment)
	int #0x13 		;call BIOS disk read function
	jmp #0x2000:#0 	; Switch to program

;_readSector(char *buffer, int sector)
_readSector:
	push bp
	mov bp, sp
	sub sp, #6
	mov bx, [bp+4]
	mov ax, [bp+6]
	mov cl, #36
	div cl
	xor ah, ah
	mov [bp-2], ax
	mov ax, [bp+6]
	mov cl, #18
	div cl
	and al, #0x1
	xor dx, dx
	mov dl, al
	mov [bp-4], dx
	inc ah
	xor dx, dx
	mov dl, ah
	mov [bp-6], dx
	mov ah, #0x2 	;Read Sector
	mov al, #0x1
	mov ch, [bp-2]
	mov cl, [bp-6]
	mov dh, [bp-4]
	mov dl, #0 		;End Read Sector
	int #0x13
	add sp, #6
	pop bp
	ret

_setCursor:
	mov ah, #2		;Set cursor position
	mov bh, #1		;Page Number
	mov dh, #0		;Row
	mov dl, #0		;Column
	int #0x10
	mov ah, #5		;Set active display page
	mov al, #1		;Page Number
	int #0x10
	mov ah, #0xB		;Set background/border Color
	mov bh, #0		
	mov bl, #0xC		;Set color
	int #0x10
	ret

;void makeInterrupt21()
;this sets up the interrupt 0x21 vector
;when an interrupt 0x21 is called in the future, 
;_interrupt21ServiceRoutine will run

_makeInterrupt21:
	;get the address of the service routine
	mov dx,#_interrupt21ServiceRoutine
	push ds
	mov ax, #0	;interrupts are in lowest memory
	mov ds,ax
	mov si,#0x84	;interrupt 0x21 vector (21 * 4 = 84)
	mov ax,cs	;have interrupt go to the current segment
	mov [si+2],ax
	mov [si],dx	;set up our vector
	pop ds
	ret

_ps:
	push bx
	call _printString
	add sp, #2
	jmp _end

_rs:
	push bx
	call _readString
	add sp, #2
	jmp _end

_rsec:
	push cx
	push bx
	call _readSector
	add sp, #4
	jmp _end

;this is called when interrupt 21 happens
;it will call your function:
;void handleInterrupt21 (int AX, int BX, int CX, int DX)
_interrupt21ServiceRoutine:
	cmp ax, #0
	je _ps
	
	cmp ax, #1
	je _rs
	
	cmp ax, #2
	je _rsec
	
	jmp _end
	
_end:
	iret
