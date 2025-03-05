#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_NAME 256
#define TABLE_SIZE 11
#define DELETED_NODE (person *) (0xFFFFFFFFFFFFFUL)

typedef struct {
	char name[MAX_NAME];
	int age;
} person;

person *hash_table[TABLE_SIZE];

void init_hash_table() {
	for (int i = 0; i < TABLE_SIZE; i++)
		hash_table[i] = NULL;
}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
#define BASE (256)
#define MULTIPLIER (37)

#if 0
unsigned int hash_key(const char* key)
{
    u_int64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (u_int64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
	printf("hash = %lu for key = %s\n", hash, key);
    return hash & (TABLE_SIZE - 1);
}
#endif

#if 0
unsigned int hash_key(const char *key)
{
	unsigned int h;
	unsigned const char *s;

	s = (unsigned const char *)key;
	h = 0;
	while (*s != '\0') {
		h = (h * BASE + *s) % TABLE_SIZE;
		s++;
	}

	return h;
}
#endif

#if 0
unsigned int hash_key(const char *s)
{
	unsigned int h;
	unsigned const char *us;

	us = (unsigned const char *)s;
	h = 0;
	while (*us != '\0') {
		h = h * MULTIPLIER + *us;
		us++;
	}

	return h % TABLE_SIZE;
}
#endif

unsigned int hash_key(const char *key)
{
	return (unsigned int)key % TABLE_SIZE;
}

unsigned int hash(char *name) {
	int length = strnlen(name, MAX_NAME);

	unsigned int hash_value = 0;
	for (int i = 0; i < length; i++) {
		hash_value += name[i];
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
	}

	return hash_value;
}

void print_table()
{
	printf("Start\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash_table[i] == NULL)
			printf("\t%i\t----------\n", i);
		else if (hash_table[i] == DELETED_NODE)
			printf("\t%i\t--DELETED--\n", i);
		else
			printf("\t%i\t%s\n", i, hash_table[i]->name);
	}
	printf("End\n");
}

bool hash_table_insert(person *p)
{
	if (p == NULL)
		return false;
	
	//int index = hash(p->name);
	int index = hash_key(p->name);
	printf("index = %d for %s\n", index, p->name);
	// open addressing
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (i + index) % TABLE_SIZE;
		if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
			hash_table[try] = p;
			return true;
		}
	}
#if 0
	if (hash_table[index] != NULL) {  // collision
		printf("Collision at index %i for %s\n", index, p->name);
		return false;
	}

	hash_table[index] = p;
	return true;
#endif
	return false;
}

person *hash_table_lookup(char *name)
{
	//int index = hash(name);
	int index = hash_key(name);

	// open addressing
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (i + index) % TABLE_SIZE;
		if (hash_table[try] == NULL)
			return false;
		if (hash_table[try] == DELETED_NODE)
			continue;

		if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0)
			return hash_table[try];

#if 0
		if (hash_table[try] != NULL && 
			strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0)
			return hash_table[try];
#endif
	}
	
	return NULL;
#if 0
	if (hash_table[index] != NULL && 
		strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0)
		return hash_table[index];
	else
		return NULL;
#endif
}

person *hash_table_delete(char *name)
{
	//int index = hash(name);
	int index = hash_key(name) % TABLE_SIZE;

	// open addressing
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (i + index) % TABLE_SIZE;
		if (hash_table[try] == NULL)
			return NULL;
		if (hash_table[try] == DELETED_NODE)
			continue;

		//printf("index = %d of %s to delete\n", index % TABLE_SIZE, name);
		if (strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0) {
			person *tmp = hash_table[try];
			hash_table[try] = DELETED_NODE;
			return tmp;
		}
			
#if 0
		if (hash_table[try] != NULL &&
			strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0) {
			person *tmp = hash_table[try];
			hash_table[try] = NULL;
			return tmp;
		}
#endif
	}

	return NULL;
#if 0
	if (hash_table[index] != NULL &&
		strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0) {
		person *tmp = hash_table[index];
		hash_table[index] = NULL;
		return tmp;
	} else
		return NULL;
#endif
}

int
main(void)
{
	init_hash_table();
	print_table();

	person jacob = {.name = "jacob"};
	person kate = {.name = "Kate"};
	person mpho = {.name = "Mpho"};
	person sarah = {.name = "Sarah"};
	person edna = {.name = "Edna"};
	person maren = {.name = "Maren"};
	person eliza = {.name = "Eliza"};
	person robert = {.name = "Robert"};
	person jane = {.name = "Jane"};

	printf("jacob(hash_key) = %d\n", hash_key("jacob"));
	printf("jacob(hash) = %d\n", hash("jacob"));
	printf("kate(hash_key) = %d\n", hash_key("kate"));
	printf("kate(hash) = %d\n", hash("kate"));
	hash_table_insert(&jacob);
	hash_table_insert(&kate);
	hash_table_insert(&mpho);
	hash_table_insert(&sarah);
	hash_table_insert(&edna);
	hash_table_insert(&maren);
	hash_table_insert(&eliza);
	hash_table_insert(&robert);
	hash_table_insert(&jane);
	print_table();

	person *tmp = hash_table_lookup("Mpho");
	if (tmp == NULL)
		printf("%s: Not found\n", "Mpho");
	else
		printf("Found: %s\n", tmp->name);

	tmp = hash_table_lookup("George");
	if (tmp == NULL)
		printf("%s: Not found\n", "George");
	else
		printf("Found: %s\n", tmp->name);
	

	tmp = hash_table_delete("Mpho");
	if (tmp == NULL)
		printf("%s: Not in the table to delete\n", "Mpho");
	else
		printf("%s: Found and deleted\n", "Mpho");

	print_table();
#if 0
	printf("Jacob => %u\n", hash("Jacob"));
	printf("Natalie => %u\n", hash("Natalie"));
	printf("Sara => %u\n", hash("Sara"));
	printf("Mpho => %u\n", hash("Mpho"));
	printf("Tebogo => %u\n", hash("Tebogo"));
	printf("Ron => %u\n", hash("Ron"));
	printf("Jane => %u\n", hash("Jane"));
	printf("Maren => %u\n", hash("Maren"));
	printf("Bill => %u\n", hash("Bill"));
#endif
	
	return 0;
}
