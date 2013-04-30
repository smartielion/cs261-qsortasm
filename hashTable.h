#ifndef HASHTABLE_H
#define HASHTABLE_H
typedef struct hashtable{
	int size ;
	int entries;
	struct node** table;
} hashtable;

typedef struct node{
	char* key;
	void* value;
	struct node* next;
} node;

hashtable* construct(int num);
int hash(char* key);
int insert(hashtable* table,char* key);
//void* search(hashtable* table,char* key);
void apply(hashtable* table, void(*func)(struct node*,int));
//int getVal(struct node* node);
int getSize(struct hashtable* table);
int getEntries(struct hashtable* table);
node** makeArray(hashtable* table);
#endif
