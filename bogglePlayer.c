/*

  Authors (group members):
  Email addresses of group members:
  Group name:

  Course:
  Section:

  Description of the overall algorithm and main data structures:


*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "bogglePlayer.h"
#include "word.h"
#include "hash.h"

//Struct to hold a letter's position
typedef struct pos{

	//Coordinates on map array
	int y, x;

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
void getWord(WordList* myWords, library_file* library,char* word){

	//Check if word is in dictionary
	short step = 0;
	while(library->word[step].letter!='\0'){
    word[step]=library->word[step].letter;
		step++;
	}

  //Format word string to remove excess characters
  for(short i=step;i<17;i++){
    word[i]='\0';
  }

  //Check whether word will be added to list
  short duplicate = 0;
  short word_replaced = 0;
  short index = myWords->length;
  if(checkWord(word)){
    for(short i=0;i<myWords->length;i++){
      if(!strcmp(myWords->wordlist[i].word,word))//Check that word isn't in list
        duplicate = 1;
      if(strlen(myWords->wordlist[i].word)<strlen(word)){//Check if word will score more points than another word on the list
        index = i;
        word_replaced = 1;
      }
    }

    //Add word to list if it has open positions or a shorter word
    if(duplicate==0&&myWords->length<20||word_replaced==1&&duplicate==0){
      if(word_replaced==0)//Don't update length if word was replaced
        setWordListLength(myWords,myWords->length+1);
      setWord(&myWords->wordlist[index],word);
      setPathLength(&myWords->wordlist[index],step);
      for(short i=0;i<step;i++){//Add path
        setLetterRowAndCol(&myWords->wordlist[index],i,library->word[i].position.y,library->word[i].position.x);
      }

    }
  }

	//Set first letter of word
	if(library->remaining==16){
		library->remaining--;
		for(short i=0;i<16;i++){
      //Define first letter node of word
			library->word[library->letter_pos].letter = library->letters[i];
			library->word[library->letter_pos].position.y = i/4;
			library->word[library->letter_pos].position.x = i%4;

      //Remove used char from chars available from use
			library->letters[i]='#';

      //Iterate right in word
			library->letter_pos++;

      //Recursive call with updated array of available characters
			getWord(myWords,library,word);

      //Reset values
			for(short j=library->letter_pos;j<17;j++){
				library->word[j].letter = '\0';
			}
			library->letter_pos--;
			library->letters[i] = library->word[library->letter_pos].letter;
		}
  //Return from getWord when all characters have been used as the first character in the word
	return;
	}

	//Add letters to word after first characted is set
	if(library->remaining>11){//Limit words to size 5
    //Use all remaining valid characters
    for(short i=0;i<16;i++){
			if(library->letters[i]!='#'){

        //Set values of board positions to be checked
				library->neighbor2.y = i/4;
				library->neighbor2.x = i%4;
				library->neighbor1.y = library->word[(library->letter_pos)-1].position.y;
				library->neighbor1.x = library->word[(library->letter_pos)-1].position.x;

				//If character i in letter array is a valid letter (neighbor) to follow previous, add to word and update library
				if(isNeighbor(library)==1){

          //Add character to word array with its position
					library->word[library->letter_pos].letter = library->letters[i];
					library->word[library->letter_pos].position.y = i/4;
					library->word[library->letter_pos].position.x = i%4;

          //Remove character from available char array
					library->letters[i] = '#';

          //Iterate right in word
					library->letter_pos++;

          //Update # of available chars
					library->remaining--;

          //Recursive call with updated array of available characters
					getWord(myWords,library,word);

          //Reset values
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

//Return to recursive calls
return;
}

// initialize BogglePlayer with a file of English words
void initBogglePlayer(char* word_file) {

  buildDictionary(word_file);

}

WordList* getWords(char board[4][4]) {

    WordList* myWords = getNewWordList();
    myWords->length = 0;

    //Declare library and initialize values
    library_file library;
    for(short y=0;y<4;y++){
      for(short x=0;x<4;x++){
        library.letters[(y*4)+x]=board[y][x];
      }
    }
    for(short i=0;i<17;i++){
  		library.word[i].letter = '\0';
  	}
  	library.letter_pos = 0;
  	library.remaining = 16;
  	char word[17];
    for(int i=0;i<17;i++){
      word[i]='\0';
    }

    //Get words from boggle board and add them to word list
    getWord(myWords,&library,word);

    //Return words found
    return myWords;
}
