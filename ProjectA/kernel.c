#define BASE_ADDRESS 0xB000
void main(){
	
	int i, j;
	for(i=0; i < 160; i = i+1){
		for(j=0; j < i; j = j+1){
	   		putInMemory(BASE_ADDRESS, 0x8140, 'X');
		}
	}

	putInMemory(BASE_ADDRESS, 0x8140, 'F');
	putInMemory(BASE_ADDRESS, 0x8141, 0x7);
	putInMemory(BASE_ADDRESS, 0x8142, 'M');
	putInMemory(BASE_ADDRESS, 0x8143, 0x7);
	putInMemory(BASE_ADDRESS, 0x8144, 'M');
	putInMemory(BASE_ADDRESS, 0x8145, 0x7);
}
