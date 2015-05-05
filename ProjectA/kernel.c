#define BASE_ADDRESS 0xB000
void main(){
	
	int addrVideoMem = 160;
	int i, j;
	int x = 0x8000;

	for(i=0; i < 30; i = i+1){
		for(j=0; j < addrVideoMem; j = j+1){
			putInMemory(BASE_ADDRESS, x+(j)+(i*addrVideoMem), 0x0);
			putInMemory(BASE_ADDRESS, x+(j+1)+(i*addrVideoMem), 0x1);
		}
	}

	putInMemory(BASE_ADDRESS, 0x8140, 'R');
	putInMemory(BASE_ADDRESS, 0x8141, 0x7);
	putInMemory(BASE_ADDRESS, 0x8142, 'M');
	putInMemory(BASE_ADDRESS, 0x8143, 0x7);
	putInMemory(BASE_ADDRESS, 0x8144, 'M');
	putInMemory(BASE_ADDRESS, 0x8145, 0x7);
}
