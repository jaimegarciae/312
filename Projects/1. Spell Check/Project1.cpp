/*
 * Project1.cpp
 * 
 * Name: Jaime Eugenio Garcia
 * EE312 Spring 2017
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

/*
	isLetter: checks if the character it receives is a letter
	input: pointer to a character
	output: 1 if character is a letter, 0 if it is not
*/
int isLetter(char *p){
	return (*p >= 'a' && *p <= 'z');
}

/*
	wordFinder: looks through article until it finds a word
	input: pointer to current location on article search
	output: pointer to the first letter of a word or end of article
*/
char * wordFinder(char *p){
	while(*p != 0){
		if((isLetter(p)) && (isLetter((p+1)))){
			return p;
		} else{
			p++;
		}
	}
	return p;
}

/*
	lowerCase: switches upper-case letters to lower-case letters
	input: pointer to null terminated string
	output: none
*/
void lowerCase(char *p){
	while(*p != 0){
		if(*p >= 'A' && *p <= 'Z'){
			*p = *p + 32;
		}
		p++;
	}
}

/*
	updatePointer: moves article pointer to end of current word
	input: pointer to the start of the current word
	output: none
*/
char * updatePointer(char *p){
	while(isLetter(p)){
		p++;
	}
	return p;
}

/*
	nextWord: updates dictionary pointer to next word
	input: pointer to current word in dictionary
	output: pointer to next word in dictionary
*/
char * nextWord(char *dictionary){
	while(dictionary != 0){
		if(*dictionary == '\n'){
			dictionary++;
			return dictionary;
		}
        dictionary++;
	}
	return dictionary;
}

/*
	wordEnd: updates article pointer to end of current word
	input: pointer to current word in article
	output: pointer to end of current word in article
*/
char * wordEnd(char *article){
	while(article != 0){
		article++;
		if(!isLetter(article)){
			return article;
		}
	}
	return article;
}

/*
	checkDictionary: looks through dictionary to find the word
	input: pointer to start of word, pointer to dictionary
	output: 1 if word is found, 0 if word is not found
*/
int checkDictionary(char *word, char *dictionary){
	char *temp = word;
	while(*dictionary != 0){
		while(*temp == *dictionary && isLetter(temp)){
			temp++;
			dictionary++;
		}
		if(!isLetter(temp) && (*dictionary == '\n')){
			return 1;
		}
		else{
			dictionary = nextWord(dictionary);
		}
		temp = word;
	}
	return 0;
}

/*
	printWord: prints words in the article not found in the dictionary
	input: pointer to misspelled word
	output: none
*/
void printWord(char *p){
	while(isLetter(p)){
		printf("%c", *p);
		p++;
	}
	printf("\n");
}

/*
	spellCheck: checks if words contained in the article are in the dictionary, if not the words are printed to the console
	input: pointer to article and pointer to dictionary
	output: none
*/
void spellCheck(char article[], char dictionary[]) {
	char *articlePointer = &(article[0]);
	char *dictionaryPointer = &(dictionary[0]);

	lowerCase(articlePointer);
	lowerCase(dictionaryPointer);

	while(*articlePointer != 0){
		articlePointer = wordFinder(articlePointer);
		if(*articlePointer != 0){
            if(!(checkDictionary(articlePointer, dictionary))){
			    printWord(articlePointer);
            }
		}
		articlePointer = wordEnd(articlePointer);
	}
}