;kernel.asm
;Michael Black, 2007

;kernel.asm contains assembly functions that you can use in your kernel

	.global _putInMemory
	.global _makeInterrupt21
	.global _loadProgram
	.global _readChar
	.global _printChar
	;	.extern _handleInterrupt21

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
	mov si, sp
	mov al, [si+2]  
	mov ah, #0x0e
	int #0x10
	ret

_readChar:
	push bp
	mov ah, #0
	int #0x16
	pop bp
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
	
;this is called when interrupt 21 happens
;it will call your function:
;void handleInterrupt21 (int AX, int BX, int CX, int DX)
_interrupt21ServiceRoutine:
;	push dx
;	push cx
;	push bx
;	push ax
;	call _handleInterrupt21
;	pop ax
;	pop bx
;	pop cx
;	pop dx

;	iret
