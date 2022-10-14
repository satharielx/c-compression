//total_hours_wasted_here = 37

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>

#define atoa(x) #x

#define GetCurrentDir _getcwd
#define MAX_SYMBOLS 30 //za duma
#define MAX_WORDS_PER_DICT 413 //kolko dumi da ima
#define MAX_BUFF 200
#define CAPACITY_MAX 10000000 

typedef char Word[MAX_SYMBOLS + 1];

typedef struct {
	int Length;
	int Capacity;
	Word* list;
}WordList;


WordList* initializeAndReturn() {
	WordList* wl = (WordList*)malloc(sizeof(Word));
	//WordList wl[MAX_WORDS_PER_DICT];
	wl->Length = 0;
	wl->Capacity = MAX_WORDS_PER_DICT * 2;
	printf("%d\n", wl->Capacity);
	wl->list = (Word*)malloc(sizeof(wl->Capacity * sizeof(Word)));
	strcpy(wl->list[wl->Length], "hahah");
	printf("%s\n", wl->list[wl->Length]);
	return wl;
}

WordList* retrieveWordListFromFile(const char* filename) {
	WordList* wl = (WordList*)malloc(sizeof(Word));
	wl->Capacity = 1;
	wl->Length = 0;
	wl->list = (Word*)malloc(sizeof(wl->Capacity * sizeof(Word)));
	FILE* f;
	if ((f = fopen(filename, "r")) == NULL) {
		printf("%s", filename);
		perror("Error!");
		exit(EXIT_FAILURE);
	}
	char nextWord[MAX_SYMBOLS + 1];
	int lenght;
	int count = 0;
	while (fscanf(f, "%d", &lenght) == 1) {
		char chBetweenIdxNword = fgetc(f);
		if (lenght > MAX_SYMBOLS) {
			fprintf(stderr, "A word is larger than the assigned limits", lenght);
			exit(EXIT_FAILURE);
		}
		if (count > MAX_WORDS_PER_DICT) {
			fprintf(stderr, "Word count overload!", count);
			exit(EXIT_FAILURE);
		}
		int i = 0;
		while (i < lenght) {
			chBetweenIdxNword = fgetc(f);
			nextWord[i] = chBetweenIdxNword;
			i++;
		}
		nextWord[lenght] = '\0';
		count++;
		if (wl->Length < wl->Capacity) {
			strcpy(wl->list[wl->Length], nextWord);
		}
		else {
			wl->Capacity = wl->Capacity * 2;
			wl->list = (Word*)realloc(wl->list, wl->Capacity * sizeof(Word));
			strcpy(wl->list[wl->Length], nextWord);
		}
		//printf("%s\n", wl->list[wl->Length]);
		wl->Length++;
	}
	for (char i = '!'; i <= '~'; i++) {
		strcpy(nextWord, &i);
		nextWord[1] = '\0';
		if (wl->Length < wl->Capacity) {
			strcpy(wl->list[wl->Length], nextWord);
		}
		else {
			wl->Capacity = wl->Capacity * 2;
			wl->list = (Word*)realloc(wl->list, wl->Capacity * sizeof(Word));
			strcpy(wl->list[wl->Length], nextWord);
		}
		count++;
	}
	strcpy(nextWord, "\t");
	if (wl->Length < wl->Capacity) {
		strcpy(wl->list[wl->Length], nextWord);
	}
	else {
		wl->Capacity = wl->Capacity * 2;
		wl->list = (Word*)realloc(wl->list, wl->Capacity * sizeof(Word));
		strcpy(wl->list[wl->Length], nextWord);
	}
	strcpy(nextWord, "\n");
	if (wl->Length < wl->Capacity) {
		strcpy(wl->list[wl->Length], nextWord);
	}
	else {
		wl->Capacity = wl->Capacity * 2;
		wl->list = (Word*)realloc(wl->list, wl->Capacity * sizeof(Word));
		strcpy(wl->list[wl->Length], nextWord);
	}
	strcpy(nextWord, "\r");
	if (wl->Length < wl->Capacity) {
		strcpy(wl->list[wl->Length], nextWord);
	}
	else {
		wl->Capacity = wl->Capacity * 2;
		wl->list = (Word*)realloc(wl->list, wl->Capacity * sizeof(Word));
		strcpy(wl->list[wl->Length], nextWord);
	}
	strcpy(nextWord, " ");
	if (wl->Length < wl->Capacity) {
		strcpy(wl->list[wl->Length], nextWord);
	}
	else {
		wl->Capacity = wl->Capacity * 2;
		wl->list = (Word*)realloc(wl->list, wl->Capacity * sizeof(Word));
		strcpy(wl->list[wl->Length], nextWord);
	}
	fclose(f);
	return wl;
}



bool validChar(char ch) {
	if ((ch >= 0x20 && ch <= 0x7E) ||
		ch == 0x09 ||
		ch == 0x0A ||
		ch == 0x0D) {
		return true;
	}
	else {
		fprintf(stderr, "Invalid character code: %hhx\n", ch);
		exit(EXIT_FAILURE);
		return false;
	}
}

char* readSrcFile(FILE* f) {
	int capacity = 10;
	char *str = malloc(capacity);
	int len = 0;
	char ch;
	while ((ch = fgetc(f)) != EOF) {
		validChar(ch);
		if (len < capacity - 1) {
			str[len] = ch;
		}
		else if(capacity < CAPACITY_MAX) {
			capacity *= 10;
			str = (char*)realloc(str, capacity * sizeof(char));
			str[len] = ch;
		}
		else {
			perror("File too long!");
			exit(EXIT_FAILURE);
		}
		len++;
	}
	str[len++] = '\0';
	return str;
}



int wordToNumber(WordList* wl, Word w) {
	int code = -1;
	if (!wl && !w) {
		for (int i = 0; i < wl->Length; i++) {
			if (strcmp(wl->list[i], w) == 0) {
				code = i;
			}
		}
	}
	return code;
}

char* numberToWord(WordList* wl, int num) {
	char* word = malloc(sizeof(Word));
	if (!wl && num > -1) {
		for (int i = 0; i < wl->Length; i++) {
			if (i == num) strcpy(word, wl->list[i]);
		}
	}
	word[MAX_SYMBOLS] = '\0';
	return word;
}

char* replace(
	char const* const original,
	char const* const pattern,
	char const* const replacement
) {
	size_t const replen = strlen(replacement);
	size_t const patlen = strlen(pattern);
	size_t const orilen = strlen(original);

	size_t patcnt = 0;
	const char* oriptr;
	const char* patloc;

	// find how many times the pattern occurs in the original string
	for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen)
	{
		patcnt++;
	}

	{
		// allocate memory for the new string
		size_t const retlen = orilen + patcnt * (replen - patlen);
		char* const returned = (char*)malloc(sizeof(char) * (retlen + 1));

		if (returned != NULL)
		{
			// copy the original string, 
			// replacing all the instances of the pattern
			char* retptr = returned;
			for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen)
			{
				size_t const skplen = patloc - oriptr;
				// copy the section until the occurence of the pattern
				strncpy(retptr, oriptr, skplen);
				retptr += skplen;
				// copy the replacement 
				strncpy(retptr, replacement, replen);
				retptr += replen;
			}
			// copy the rest of the string.
			strcpy(retptr, oriptr);
		}
		return returned;
	}
}

void compressString(WordList* wl, char* content) {
	for (int i = 0; i < wl->Length; i++) {
		char numbertoi[6];
		sprintf(numbertoi, "%d", i);
		const char* newstr = replace(content, wl->list[i], numbertoi);
		strcpy(content, newstr);
	}
}

void decompressString(WordList* wl, char* content) {
	for (int i = 0; i < wl->Length; i++) {
		char numbertoi[6];
		sprintf(numbertoi, "%d", i);
		const char* newstr = replace(content, numbertoi, wl->list[i]);
		strcpy(content, newstr);
	}
}

int main() {
	char path[MAX_BUFF];
	GetCurrentDir(path, MAX_BUFF);
	int choice = -1;
	//printf("%s", strcat(path, "\\text.txt"));
	//initializeAndReturn();
	WordList* wl = retrieveWordListFromFile(strcat(path, "\\wordlist.txt"));

	GetCurrentDir(path, MAX_BUFF);
	printf("---- word list -----\n");
	for (int i = 0; i < wl->Length; i++)
		printf("%d == %s\n", i, wl->list[i]);
	printf("--------------------\n");
	printf("Word List has been successfully read!\n");
	printf("TYPE a number to select an action!\n");
	printf("(1) Compress text file! File should be with name text.txt\n");
	printf("(2) Decompress text file! File should be with name text.dat\n");
	printf("Choice: ");
	scanf("%d", &choice);
	
	if (choice == 1) {
		FILE* f;
		char* filename = strcat(path, "\\text.txt");
		if ((f = fopen(filename, "r")) == NULL) {
			printf("%s", filename);
			perror("Error!");
			exit(EXIT_FAILURE);
		}
		char* fileContent = readSrcFile(f);
		compressString(wl, fileContent);
		GetCurrentDir(path, MAX_BUFF);
		char* outfile = strcat(path, "\\text.dat");
		FILE* output;
		if ((output = fopen(outfile, "w")) == NULL) {
			printf("%s", outfile);
			perror("Error!");
			exit(EXIT_FAILURE);
		}
		int res = fputs(fileContent, output);
		if (res == EOF) {
			perror("Error!");
			exit(EXIT_FAILURE);
		}
		fclose(output);
		fclose(f);
		printf("Compression complete!");
	}
	else {
		FILE* f;
		char* filename = strcat(path, "\\text.dat");
		if ((f = fopen(filename, "r")) == NULL) {
			printf("%s", filename);
			perror("Error!");
			exit(EXIT_FAILURE);
		}
		char* fileContent = readSrcFile(f);
		decompressString(wl, fileContent);
		GetCurrentDir(path, MAX_BUFF);
		char* outfile = strcat(path, "\\text.txt");
		FILE* output;
		if ((output = fopen(outfile, "w")) == NULL) {
			printf("%s", outfile);
			perror("Error!");
			exit(EXIT_FAILURE);
		}
		int res = fputs(fileContent, output);
		if (res == EOF) {
			perror("Error!");
			exit(EXIT_FAILURE);
		}
		fclose(output);
		fclose(f);
		printf("Decompression complete!");
	
	}
	_getch();
	return 0;
}


