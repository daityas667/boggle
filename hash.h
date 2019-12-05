/*
	This File contains functions for storing words into a hash table.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char *table[350000]; //hash table - size is set to 350000 to make the load factor .67

/* Table Functions */

/*
	getHash gets a hash value for a given word
	Input Parameters:
		char *word - word to hash
		short length - length of word
	Return Value:
		int value - hash of word
*/
int getHash(char *word, short length){
	int value = 0;
	for (short i = 0; i < length; i++){ //store the sum of each all the string's characters in value
		value += (int)word[i];
	}
	value *= 2027; //compression by multiplying by a really big prime number then dividing by a smaller prime until in range
	while (value > 350000){
		value /= 47;
	}
	return value;
}

/*
	insert inserts a word into the hash table using linear probing
	Input Parameters:
		char *word - word to insert
*/
void insert(char *word){
	int index = getHash(word, strlen(word)), spotsVisited = 1; //get initial hash
	if (table[index] != NULL){ //if there is already a word in the original hash's place, do a linear prove until an empty space is found
		for (short i = 1; table[index] != NULL; i++){
			if (spotsVisited == 350000){
				return;
			}
			index += i;
			if (index > 350000){
				index %= 350000;
			}
			spotsVisited++;
		}
	}
	table[index] = (char *)malloc(30 * sizeof(char)); //make space for word in table then add word
	strcpy(table[index], word);
}

/*
	buildDictionary adds each word in the file of words into the hash table
	Input Parameters:
		char *fileName - name of file containing words
*/
void buildDictionary(char *fileName){
	char str[31];
	FILE *inp = fopen(fileName, "r");
	while (!feof(inp)){ //while there are words left to add, scan in the strings and store them
		fgets(str, 30, inp);
		short size = strlen(str) - 2;
		for (short i = 0; i < size; i++){ //make strings all uppercase
			str[i] = toupper(str[i]);
		}
		str[size] = '\0';
		if (size > 3 && size < 6){ //insert only if string is in a certain size range reduce unnecessary processes
			insert(str);
		}
	}
}

/*
	checkWord checks if a word is in the hash table or not
	Input Parameters:
		char *word - word to check
	Return Value:
		true or false value - 1 for true, 0 for false
*/
int checkWord(char *word){
	int index = getHash(word, strlen(word)); //get word's hash
	if (table[index] == NULL){ //if spot is empty, the word is not in the list
		return 0;
	}
	if (strcmp(word, table[index])){ //if the word in the space of the hash, then do a linear probe to find the word
		for (short i = 1; strcmp(table[index], word) != 0; i++){
			index += i;
			if (index > 350000){
				index %= 350000;
			}
			if (table[index] == NULL){ //if an empty space if encountered the word is not in the list
				return 0;
			}
		}
	}
	if (!strcmp(table[index], word)){ //return true if word was found
		return 1;
	} else {
		return 0;
	}
}
