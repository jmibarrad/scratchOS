#define BASE_ADDRESS 0xB000
#define ARR_LENGTH 12
#define COLOR_ARRAY 16
void main(){
	
	//Relative Mem Video Address
	int RMVA = 160;
	int memVideoAddr = 0x8000;
	int x, y, i;
	char* text = "Hello World!";

	for(x=0; x < 30; x = x+1){
		for(y=0; y < RMVA; y = y+1){
			putInMemory(BASE_ADDRESS, memVideoAddr+(y)+(x*RMVA),0x00);
			putInMemory(BASE_ADDRESS, memVideoAddr+(y+1)+(x*RMVA), 0x0);
		}
	}

	for(x=0; x < 30; x = x+1){
		for(y=0; y < RMVA; y = y+1){
			if(y==0 || y==40 || y==80 || y==120 || y == 158){
			putInMemory(BASE_ADDRESS, memVideoAddr+(y)+(x*RMVA), 0x221);
			putInMemory(BASE_ADDRESS, memVideoAddr+(y+1)+(x*RMVA), 0x34);
			}		
		}
	}

	for(x=0; x < COLOR_ARRAY; x = x+1){
		for(i=0; i < ARR_LENGTH; i = i+1){
			putInMemory(BASE_ADDRESS, memVideoAddr+10+(x*RMVA), text[i]);
			putInMemory(BASE_ADDRESS, memVideoAddr+11+(x*RMVA), i+1);
			memVideoAddr+=2;		
		}
		memVideoAddr-=(ARR_LENGTH*2);	
	}	

	
}
