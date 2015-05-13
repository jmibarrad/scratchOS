#define BASE_ADDRESS 0xB000
#define RMVA 160
#define memVideoAddr 0x8000

void printString(char* str);
void cleanScreen();
void readString(char str[]);

void main(){

	char str[80], buffer[512];
	char* str2 = "Enter your name: ";
	cleanScreen();
	
	printString(str2);
	readString(str);	
	printString("Hola");	
}

void printString(char* str){
	int i;	
	for(i=0; str[i]!='\0'; i++){
		printChar(str[i]);
	}
}

void readString(char str[]){
	int i;
	for(i=0; i<8; i=i+1){
		char current = readChar();
		if(current == 0xD){	
			i=8;			
		}else if(current == 0x8){
			/*i--;
			printChar(' ');
			i--;*/
		}else{
			str[i] = current;
			printChar(str[i]);
		}
	}
	str[8] = 0;
}

void cleanScreen(){

	int x, y;
	for(y=0; y < 25; y = y+1){
		for(x=0; x < RMVA; x = x+1){
			putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA),0x07);
			//putInMemory(BASE_ADDRESS, memVideoAddr+(x+1)+(y*RMVA), 0x07);
		}
	}

}
