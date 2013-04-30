#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "hashTable.h"
extern qsortASM(char** array, int left, int right);
#define MAX_WORD_SIZE  256
/* Casey Gilray
  Final ASsignment
   5/2/13
*/

char* getNextWord(FILE* fd){
 char word[MAX_WORD_SIZE];
 int wordlen = 0;
 char c;
 while ((c=fgetc(fd))!=EOF){
   // printf("%c",c);
   //if the word is at max length, return it with an appending null character
   //while we have not reached the end of file yet, if the character is a space, append a \0 to the current spot in the file and return
   if (isspace(c)){
     if (wordlen >0){
     word[wordlen]='\0';
     return (char*)strdup(word);
     }
   }
   if(isalnum(c)&&(wordlen<=((MAX_WORD_SIZE)-1))){
     //if it is alphanumeric, put it into the word and incriment the "wordlen".
     
     word[wordlen]= tolower(c);
     wordlen++;
   }
 }
 //returns null when EOF is hit
 return NULL;
}



void applyPrint(node* node, int x){
	//defines an apply function to iterate over the hashtable with
	//int x is unused in this function, but can be added later.
	printf("Key: %16s || Value: %8d\n",node->key,(int)node->value);
}

int nodeComp(const void* aNode,const void* bNode){
	//provides qsort with a node comparator, returns <0 if a is less than b, returns 0 if a = b,returns >0 if a > b
	//cast sequence void* > node** => node* -> int* value -> derefrence
	node** nodeA = (node**)aNode;
	node** nodeB = (node**)bNode;
	node* parseNodeA = *nodeA;
	node* parseNodeB = *nodeB;
	char*  a = (char *)parseNodeA->key;
	char*  b = (char *)parseNodeB->key;
	int strResult = strcmp(a,b);
	if (strResult>0){return 1;}
	if (strResult==0){return 0;}
	return -1;
}	

int main(int argc, char* argv[]){
	if (argc < 2){
		printf("Usage: %s, arguments\n", argv[0]);
		return(1);
	}
	

	clock_t t;
  FILE* filename; //used to hold the current filename
  char* sword;
	hashtable* table = construct(101);
	filename = fopen(argv[1],"r");
    if (filename==NULL){return 1;}
  	while ((sword = getNextWord(filename)) != NULL){
		//insert, ignoring duplicates
		insert(table,sword);
	}
  
	//applysfunction to the hashtable to fill the searchresult array with node pointers
	//and sorts using the given function and qsort		
	node** sortList;	
	sortList = makeArray(table);
	char* sortListASM[table->entries];
	for (int i = 0;i<table->entries;i++){
		sortListASM[i] = sortList[i]->key;
	}
	t = clock();
	qsort(sortList,(table->entries-1),sizeof(node*),nodeComp);
	clock_t qsortT = clock() - t;
	float qsortTinSeconds = (float)qsortT/(float)CLOCKS_PER_SEC;
	printf("Attempting to sort via asm\n");
	t=clock();
	qsortASM(sortListASM,0, getEntries(table));
	clock_t asmClockT = clock() -t;
	float qsortASMTinSeconds = (float)asmClockT/CLOCKS_PER_SEC;
  	//for (int p = 0;p<250;p++){
	//node* node = sortList[p];	
	//printf("Key: %16s \n",node->key);
	//}
	for (int p = 0;p<getEntries(table);p++){
		//prints all values in the sortlistASM table
		printf("Key: %16s \n", sortListASM[p]);	
	}
		printf("C qsort took %f seconds.\n",qsortTinSeconds);
	printf("ASM qsort took %f seconds.\n", qsortASMTinSeconds);
	printf("done printing, closing file\n");
  fclose(filename);
return 0;
  }

