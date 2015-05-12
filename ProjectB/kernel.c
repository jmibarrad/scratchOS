#define BASE_ADDRESS 0xB000
#define RMVA 160
#define memVideoAddr 0x8000
void printString(char* text);
void cleanScreen();
void main(){
	int i;
	char* text = "Hello";
	char* charac;
	//cleanScreen();
	
	for(i=0; i<8; i=i+1){
		charac[i] = readChar();
		printChar(charac[i]);
	}
	printString(text);	
	
}

void printString(char* str){
	int i;	
	for(i=0; i<80; i++){
		if(str[i]!='\0')
			printChar(str[i]);	
	}
	
	printChar('\n');
}

void cleanScreen(){

	int x,y;
	for(y=0; y < 25; y = y+1){
		for(x=0; x < RMVA; x = x+1){
			putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA),0x0);
			putInMemory(BASE_ADDRESS, memVideoAddr+(x+1)+(y*RMVA), 0x3);
		}
	}

}

