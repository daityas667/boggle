/*

  Authors (group members): Brendan Shupp, Christopher Tinkler, John Dewey
  Email addresses of group members: bshupp2018@my.fit.edu, ctinkler2018@my.fit.edu, jdewey2018@my.fit.edu
  Group name: Hairy Hooligans

  Course: CSE 2010
  Section: 03

  Description of the overall algorithm and main data structures:


*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "bogglePlayer.h"
#include "word.h"

char *table[128710]; //Hash Table

void printTable(void){
    for(int i = 0; i < 128710; i++){
        if(table[i] != NULL)
            printf("%d: %s\n", i, table[i]);
    }
}

int getHash(char *word, int length){
    int value = 0;
    for(int i = 0; i < length; i++)
        value += (int)word[i];
    
    value *= 2027;
    while(value > 128710)
        value /= 47;
    
    return value;
}

void insert(char *word){
    int index = getHash(word, strlen(word)), spotVisited = 1;
    if(table[index] != NULL){
        for(int i = 0; table[index] != NULL; i++){
            if(spotVisited == 128710)
                return;
            index += i;
            if(index > 128710)
                index %= 128710;
            spotVisited++;
        }
    }
    table[index] = (char*)malloc(30 * sizeof(char));
    strcpy(table[index], word);
}

int checkWord(char *word){
    int index = getHash(word, strlen(word));
    if(table[index] == NULL)
        return 0;
    
    if(strcmp(word, table[index])){
        for(int i = 1; strcmp(table[index], word) != 0; i++){
            index += 1;
            if(index > 128710)
                index %= 128710;
            if(table[index] == NULL)
                return 0;
        }
    }
    if(strcmp(table[index], word))
        return 1;
    else
        return 0;
}

// initialize BogglePlayer with a file of English words
void initBogglePlayer(char* word_file) {
    int numWords = 0;
    char str[31];
    FILE *inp = fopen(word_file, "r");
    while(!feof(inp)){
        fgets(str, 30, inp);
        int size = strlen(str) - 2;
        str[size] = '\0';
        for(int i = 0; i < size; i++){
            str[i] = toupper(str[i]);
        }
        if(size > 3 && size < 9){
            numWords++;
            insert(str);
        }
    }/*
    printTable();
    printf("Num of Words: %d\n", numWords);
    char checkStr[30];
    printf("Enter a word to check: ");
    scanf("%s", checkStr);
    if(checkWord(checkStr))
        printf("Word Found!\n");
    else
        printf("Word Not Found!\n");*/
}



void      sampleWordList(WordList* myWords);   // a sample function to populate a word list

// based on the board, find valid words
//
// board: 4x4 board, each element is a letter, 'Q' represents "QU",
//    first dimension is row, second dimension is column
//    ie, board[row][col]
//
// Return at most 20 valid words in UPPERCASE and
//    their paths of locations on the board in myWords
//
// See word.h for details of the struct for Word, WordList, Location, and access functions
/*
WordList* getWords(char board[4][4]) {

    WordList* myWords = getNewWordList(); 

    sampleWordList(myWords);
    
    return myWords;
}*/

void acquireWord(libary_file* library){
    short step = 0;
    while(library->word[step].letter != '\0')
        step++;
}

WordList* getWords(char board[4][4]) {

    WordList* myWords = getNewWordList(); 

    sampleWordList(myWords);
    
    return myWords;
}



// a sample list of one word
void sampleWordList(WordList* myWords)  {
    setWordListLength(myWords, 1);      // number of words on the list 
    Word *word = getWordFromWordList(myWords, 0);   // first word

    setWord(word, "cat");               // word string

    setPathLength(word, 3);             // word path
    setLetterRowAndCol(word, 0, 1, 2);  // letter 0 is at row 1 and column 2
    setLetterRowAndCol(word, 1, 1, 3);
    setLetterRowAndCol(word, 2, 2, 3);
}