.extern _main

begin:
	call _main
	infinite_loop:
	jmp infinite_loop ;locks main func
	
	