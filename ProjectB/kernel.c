#define BASE_ADDRESS 0xB000
#define RMVA 160

void printString(char* text);
void cleanScreen();
void main(){
	cleanScreen();
		
	
}

void printString(char* text){
	int i;	
	for(i=0; i<80; i++){
		printChar(text[i]);	
	}
	
	printChar('\n');
}

void cleanScreen(){
	
	for(y=0; y < 25; y = y+1){
		for(x=0; x < RMVA; x = x+1){
			putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA),0x0);
			putInMemory(BASE_ADDRESS, memVideoAddr+(x+1)+(y*RMVA), 0x0);
		}
	}

}

