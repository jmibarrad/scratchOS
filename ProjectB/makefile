all: floppya.img userprog/syscall_test.bin
run: all
	- bochs -f opsys.bxrc -q
kernel.bin: start.o kernel.o kernel_asm.o
	ld86 -o $@ -d $^
kernel.o: kernel.c
	bcc -ansi -c -o $@ $<
kernel_asm.o: kernel.asm
	as86 $< -o $@
start.o: start.asm
	as86 $< -o $@
userprog/syscall_test.bin: userprog/start.o userprog/Test.o userprog/os_api.o
	ld86 -o $@ -d $^
userprog/Test.o: userprog/Test.c
	bcc -ansi -c -o $@ $<
userprog/os_api.o: userprog/os_api.asm
	as86 $< -o $@
bootload.bin: bootload.asm
	nasm $< -f bin -o $@
floppya.img: bootload.bin kernel.bin
	dd if=/dev/zero of=floppya.img bs=512 count=2880
	dd if=bootload.bin of=floppya.img bs=512 count=1 conv=notrunc
	dd if=kernel.bin of=floppya.img bs=512 seek=3 conv=notrunc
	dd if=userprog/syscall_test.bin of=floppya.img bs=512 count=1 seek=11 conv=notrunc
	dd if=message.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc
clean :
	rm -f *.o
	rm -f *.bin