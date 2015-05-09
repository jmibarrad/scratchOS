_loadProgram:
	mov ax, #0x2000
	mov ds, ax
	mov ss, ax
	mov es, ax
	;let's have the stack start at 0x2000:fff0
	mov ax, #0xfff0
	mov sp, ax
	mov bp, ax
	; Read the program from the floppy
	mov
	cl, #12
	;cl holds sector number
	mov
	dh, #0
	;dh holds head number - 0
	mov
	ch, #0
	;ch holds track number - 0
	mov
	ah, #2
	;absolute disk read
	mov
	al, #1
	;read 1 sector
	mov
	dl, #0
	;read from floppy disk A
	mov
	bx, #0
	;read into offset 0 (in the segment)
	int
	#0x13
	;call BIOS disk read function
	; Switch to program
	jmp #0x2000:#0