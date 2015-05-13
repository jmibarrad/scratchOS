#define BASE_ADDRESS 0xB000
#define RMVA 160
#define memVideoAddr 0x8000
#define strLength 80

void printString(char str[]);
void cleanScreen();
void readString(char str[]);
void nextLine();

void main(){

	/*char str[strLength];
	char buffer[512];
	char* str2 = "Enter your name: ";
	
	cleanScreen();
	printString(str2);
	readString(str);
	
	readSector(buffer, 30);
	printString(buffer);

	printString("Program Finished");
*/
	cleanScreen();
	setCursor();
	makeInterrupt21();
	loadProgram();
	
}

void printString(char str[]){
	int i;	
	for(i=0; str[i]!='\0'; i++){
		printChar(str[i]);
	}
	//nextLine();
}

void readString(char str[]){
	int i;
	char current = 0;
	for(i=0; i<strLength; i++)
		str[i] = 0x0;	
	i=0;
	while( current != 0xD ){
		current = readChar();

		if(current == 0x8 && i > 0){
			printChar(current);
			printChar(0x0);
			printChar(current);
			i--;	
		}else if(i <= strLength && current != 0x8 && current != 0xD){
			str[i] = current;
			printChar(str[i]);
			i++;
		}
	}
	nextLine();
	str[strLength] = 0;
}

void nextLine(){
	printChar('\r');
	printChar('\n');
}

void cleanScreen(){

	int x, y;
	for(y=0; y < 25; y++){
		for(x=0; x < RMVA; x++){
			putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA), ' ');
			putInMemory(BASE_ADDRESS, memVideoAddr+(x+1)+(y*RMVA), 0x2);
		}
	}

}
