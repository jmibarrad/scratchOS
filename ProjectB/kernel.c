#define BASE_ADDRESS 0xB000
#define RMVA 160
#define memVideoAddr 0x8000
#define strLength 80

void printString(char str[]);
void readString(char str[]);
void nextLine();
void drawBar();


void main(){
	
	
	int hr;
	int min;
	int sec;
	getTime(&hr, &min, &sec);
	
	clrScreen();
	drawBar();
	makeInterrupt21();
	loadProgram();

}

void printString(char str[]){
	int i;	
	for(i=0; str[i] != '\0'; i++){
		printChar(str[i]);
	}
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
		}else if(i < strLength-1 && current != 0x8 && current != 0xD){
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

void drawBar(){
	int x, y;
	for(y=0; y < 25; y++){
		for(x=0; x < RMVA; x++){
			if(y<2){
				putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA), 0x33);
			}
			if(x==RMVA-1 && y>=2){
				putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA), 0x77);
			}
			if(y>23){
				putInMemory(BASE_ADDRESS, memVideoAddr+(x)+(y*RMVA), 0x77);
			}
		}
	}
}
