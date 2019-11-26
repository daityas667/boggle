#include <stdio.h>
#include <string.h>
#include <time.h>

//Struct to hold a letter's position
typedef struct pos{

	//Coordinates on map array
	short y, x;

}map_pos;

//Struct to hold letter and its position
typedef struct letter{

	char letter;
	map_pos position;

}letter;

//Library struct, holds values used in getWord()
typedef struct library{

	map_pos neighbor1, neighbor2;
	char letters[16];
	letter word[17];
	short remaining;
	short letter_pos;

}library_file;

//Function that returns 1 if two nodes are neighbors, 0 if they are not
short isNeighbor(library_file* library){

	short neighbor_check = 0;

	//Check that x/y coords of node 1 are within 1 of the x/y coords of node 2
	if(library->neighbor1.y == (library->neighbor2.y)+1 || library->neighbor1.y == (library->neighbor2.y)-1 || library->neighbor1.y == library->neighbor2.y){
		if(library->neighbor1.x == (library->neighbor2.x)+1 || library->neighbor1.x == (library->neighbor2.x)-1 || library->neighbor1.x == library->neighbor2.x){
			neighbor_check = 1;
		}
	}

return neighbor_check;
}

//Function that generates all possible words and checks against dictionary
void getWord(library_file* library){

	//Check if word is in dictionary
	short step = 0;
	while(library->word[step].letter!='\0'){
		printf("%c",library->word[step].letter);
		step++;
	}
	printf(" %d \n",library->remaining);

	//Set first letter of word
	if(library->remaining==16){
		library->remaining--;
		for(short i=0;i<16;i++){
			library->word[library->letter_pos].letter = library->letters[i];
			library->word[library->letter_pos].position.y = i/4;
			library->word[library->letter_pos].position.x = i%4;
			library->letters[i]='#';
			library->letter_pos++;
			getWord(library);
			for(short j=library->letter_pos;j<17;j++){
				library->word[j].letter = '\0';
			}
			library->letter_pos--;
			library->letters[i] = library->word[library->letter_pos].letter;
		}
	return;
	}

	//Add letters to word after first characted is set
	if(library->remaining>0){
		for(short i=0;i<16;i++){
			if(library->letters[i]!='#'){
				library->neighbor2.y = i/4;
				library->neighbor2.x = i%4;
				library->neighbor1.y = library->word[(library->letter_pos)-1].position.y;
				library->neighbor1.x = library->word[(library->letter_pos)-1].position.x;
				//If character i in letter array is a valid letter to follow previous, add to word and update library
				if(isNeighbor(library)==1){
					library->word[library->letter_pos].letter = library->letters[i];
					library->word[library->letter_pos].position.y = i/4;
					library->word[library->letter_pos].position.x = i%4;
					library->letters[i] = '#';
					library->letter_pos++;
					library->remaining--;
					getWord(library);
					library->remaining++;
					for(short j=library->letter_pos;j<17;j++){
						library->word[j].letter = '\0';
					}
					library->letter_pos--;
					library->letters[i] = library->word[library->letter_pos].letter;
				}
			}
		}
	}

return;
}

int main(){

	time_t start, end;
  start = time(NULL);

	library_file library;

	char letter = 'a';
	for(short i=0;i<16;i++){
		library.letters[i] = letter+i;
		printf("%c",library.letters[i]);
	}
	printf("\n");

	for(int i=0;i<17;i++){
		library.word[i].letter = '\0';
	}

	library.letter_pos = 0;
	library.remaining = 16;

	getWord(&library);

	end = time(NULL);
	printf("Time taken to print sum is %.2f seconds", difftime(end, start));

return 0;
}
