#define BASE_ADDRESS 0xB000
#define ARR_LENGTH 12
#define COLOR_ARRAY 16
void main(){
	
	//Relative Mem Video Address
	int RMVA = 160;
	int memVideoAddr = 0x8000;
	int x, y, i;
	char* text = "Hello World!";

	for(y=0; y < 25; y = y+1){
		for(x=0; x < RMVA; x = x+1){
			putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA),0x00);
			putInMemory(BASE_ADDRESS, memVideoAddr+(x+1)+(y*RMVA), 0x0);
		}
	}

	for(y=0; y < 25; y = y+1){
		for(x=0; x < RMVA; x = x+1){

			if((x<30 || x>125) && y<21)
				if((x%4==0) && (y%2==0)){
				putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA), 0x212);
				putInMemory(BASE_ADDRESS, memVideoAddr+(x+1)+(y*RMVA), 0x74);
				}else if((x%8==0)){
				putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA), 0x212);
				putInMemory(BASE_ADDRESS, memVideoAddr+(x+1)+(y*RMVA), 0x74);
				}
			if(y>=21)
				if((x%4==0) && (y%2==0)){
				putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA), 0x212);
				putInMemory(BASE_ADDRESS, memVideoAddr+(x+1)+(y*RMVA), 0x71);
				}else if((x%8==0)){
				putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA), 0x212);
				putInMemory(BASE_ADDRESS, memVideoAddr+(x+1)+(y*RMVA), 0x71);
				}
		}
	}

	for(x=0; x < COLOR_ARRAY; x = x+1){
		for(i=0; i < ARR_LENGTH; i = i+1){
			putInMemory(BASE_ADDRESS, memVideoAddr+70+(x*RMVA), text[i]);
			putInMemory(BASE_ADDRESS, memVideoAddr+71+(x*RMVA), i+3);
			memVideoAddr+=2;		
		}
		memVideoAddr-=(ARR_LENGTH*2);	
	}	

	
}
