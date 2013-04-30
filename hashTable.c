/* Casey Gilray
Assignment 5
HashTable/Fequency Count
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct hashtable{
	int size;
	int entries;
	struct node** table;
	float maxLoad;
} hashtable;

typedef struct node{
	char* key;
	struct node* next;
} node;

struct hashtable* construct(int num){
	//returns a barebones hashtable
	if (num <1){return NULL;}
	hashtable* temp;
 	if ((temp = malloc(sizeof(hashtable))) == NULL) {
		return NULL;
	}
	if ((temp->table = malloc(sizeof(node*)*num))==NULL){
		return NULL;
	}
	for (int i =0; i<num;i++){
		temp->table[i]=NULL;
	}	
	temp -> entries = 0;
	temp->size = num;
	temp->maxLoad = 0.65;
	return temp;
}

int hash(char* key){
	//impliments a hash function and returns the hash value
	int hashvalue = 0;
	char *p = key;
	for (int i = 0;i<strlen(key);i++){
		hashvalue = (33 * hashvalue)+p[i]; 
			
	}
	if (hashvalue < 0){return -hashvalue;}
	return hashvalue;
	
}
/*
void rehashInsert(node** table, node* node, int size){
	char* key = node->key;
	int hashVal = hash(key);
	int place = hashVal % size;
	struct node* listNode = table[place];
	//linked list is empty, put new entry in the first spot.
	if (listNode==NULL){
				node->next = listNode;
				table[place] = node;
				return;
	}
	else 
	{
		//first node is not null, if not matched key go to next node
		//if next node is null, make new node in its place
		//if node is found, value of current "node" place is updated to current
		while (strcmp(listNode->key,key)!= 0){
			listNode = listNode->next;
			if (listNode==NULL){				
				node->next = table[place];
				table[place] = node;
				return;
			}
		}
	}
	return;
	//hashes the key and finds the best place to insert it into the hashtable
	//if the key already exists, update the value based on the users defined
}

	
void rehash(hashtable* table){
	//makes a pointer to a temperary list
	int newsize = ((table->size * 2)+1);
	node** old= table->table;
	node** tempList = malloc(sizeof(node*)*newsize);	
	printf("Starting rehashLoop, inserting keys into new table");
	for (int i = 0;i<table->size;i++){
		node* current=table->table[i];
		while (current != NULL){
			rehashInsert(tempList,current,newsize);
			current = current->next;
		}
	}
	table->table = tempList;
	free(old);
	return;
}
*/


void rehash(hashtable* table){
	//makes a pointer to a temperary list
	//old node, and old table needs to be freed
	int newsize = ((table->size * 2)+1);
	node** oldTable = table->table;
	hashtable* new = construct(newsize);
	node* prev;
	for (int i = 0;i<table->size;i++){
		node* current=table->table[i];
		while (current != NULL){
			insert(new,current->key);
			prev = current;
			current = current->next;
			free(prev);
		}
	}
	table->table = new->table;
	table->size = newsize;
	free(oldTable);
	free(new);
	return;
}



void hashCheck(hashtable* table){
	float ratio = (float)(table->entries) / (float)(table->size);
	if (ratio > (table->maxLoad)){
		rehash(table);
	}
	return ; 
}


int insert(hashtable* table,char* key){
	int hashVal = hash(key);
	int place = hashVal % table->size;
	node* listNode = table->table[place];
	//linked list is empty, put new entry in the first spot.
	if (listNode==NULL){node* newNode = (node*)malloc(sizeof(node));
				newNode->key =key;
				newNode->next = listNode;
				table->table[place] = newNode;
				table->entries++;
				hashCheck(table);
				return 0;
	}
	else 
	{
		//first node is not null, if not matched key go to next node
		//if next node is null, make new node in its place
		//if node is found, value of current "node" place is updated to current
		while (strcmp(listNode->key,key)!= 0){
			listNode = listNode->next;
			if (listNode==NULL){
				node* newNode = (node*)malloc(sizeof(node));
				newNode->key =key;
				newNode->next = table->table[place];
				table->table[place] = newNode;
				table->entries++;
				hashCheck(table);
				return 0;
			}
		}
	}
	return 0;
	
}

/*void* search(hashtable* table,char* key){
	//searches for the key in the hash table and returns the void* assosciated with it
	//this returned value can be used in the insert in order to change the value
	//based on what the usedr wants to do with it
	int hashVal = hash(key);
	int place = hashVal % table->size;
	node* listNode =  table->table[place];
	//linked list is empty, node does not exist, return null
	if (listNode==NULL){
				return NULL;
	}
	else 
	{
		//first node is not null, if not matched key go to next node
		//if next node is null, node does not exist, return null
		//if node is found, value of current "node" place is updated to current
		while (strcmp(listNode->key,key)!= 0){
			listNode = listNode->next;
			if (listNode==NULL){
				return NULL;
			}
		}


		return listNode->value;;
	}
	return NULL;
}*/

void apply(hashtable* table, void(*func)(node*, int)){
	int x = 0;
	for (int i = 0;i<table->size;i++){
		node* current=table->table[i];
		while (current != NULL){
			func(current,x++);
			current = current->next;
		}
	}
}

int getsize(struct hashtable* table){
	return table->size;
}

int getEntries(struct hashtable* table){
	return table->entries;
}
/*void* getVal(struct node* node){
	return node->value;
}*/

node** makeArray(hashtable* table){
	int x = 0;
	node** temp = malloc(sizeof(node*)*(table->entries));
	for (int k = 0;k<table->entries;k++){
	temp[k] = NULL;
	}
	for (int i = 0;i<table->size;i++){
		node* current=table->table[i];
		while (current != NULL){
			temp[x] = current;
			x++;
			current = current->next;
		}
	}	
	return temp;
}
