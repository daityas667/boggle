/*
	This File contains functions for storing words into a hash table.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char *table[128710]; //hash table

/* Table Functions */

void printTable(void){
	for (int i = 0; i < 128710; i++){
		if (table[i] != NULL){
			printf("%d: %s\n", i, table[i]);
		}
	}
}

int getHash(char *word, short length){
	int value = 0;
	for (short i = 0; i < length; i++){
		value += (int)word[i];
	}
	value *= 2027;
	while (value > 128710){
		value /= 47;
	}
	return value;
}

void insert(char *word){
	int index = getHash(word, strlen(word)), spotsVisited = 1;
	if (table[index] != NULL){
		for (short i = 1; table[index] != NULL; i++){
			if (spotsVisited == 128710){
				return;
			}
			index += i;
			if (index > 128710){
				index %= 128710;
			}
			spotsVisited++;
		}
	}
	table[index] = (char *)malloc(30 * sizeof(char));
	strcpy(table[index], word);
}

void buildDictionary(char *fileName){
	char str[31];
	FILE *inp = fopen("words.txt", "r");
	while (!feof(inp)){
		fgets(str, 30, inp);
		short size = strlen(str) - 2;
		for (short i = 0; i < size; i++){
			str[i] = toupper(str[i]);
		}
		str[size] = '\0';
		if (size > 3 && size < 9){
			insert(str);
		}
	}
}

int checkWord(char *word){
	int index = getHash(word, strlen(word));
	if (table[index] == NULL){
		return 0;
	}
	if (strcmp(word, table[index])){
		for (short i = 1; strcmp(table[index], word) != 0; i++){
			index += i;
			if (index > 128710){
				index %= 128710;
			}
			if (table[index] == NULL){
				return 0;
			}
		}
	}
	if (!strcmp(table[index], word)){
		return 1;
	} else {
		return 0;
	}
}
