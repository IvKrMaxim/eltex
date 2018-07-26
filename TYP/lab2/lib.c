#include "lib.h"

long long hash(char *key) {
    long long h = 0;
    char *p;
    for (p = key; *p != '\0'; p++)
        h = (h * HASH_MUL + (long long)*p) % HASH_SIZE;
    return h;
}

void hashtab_init(struct listnode **hashtab) {
    int i;
    for (i = 0; i < HASH_SIZE; i++)
		hashtab[i] = NULL;
}

void push_hash(struct listnode **hashtab, char *key, int value) {
    struct listnode *node;
    struct listnode *search;
    int index = hash (key);
    search = lookup_hash(hashtab, key);
    if (search != NULL)
        return;
    node = malloc(sizeof(struct listnode));
    if (node == NULL) {
	    return;
    }
    strcpy(node->key, key);
    node->value = value;
	node->next = hashtab[index];
	hashtab[index] = node;
}

void print_hash(struct listnode **hashtab) {
    int i;
    struct listnode *node;
    for (i = 0; i < HASH_SIZE; i++) {
		for (node = hashtab[i]; node != NULL; node = node->next) {
	    	printf ("%s ", node->key);
	    	if (node->next == NULL)
				printf ("\n");
		}
    }
}

struct listnode *lookup_hash(struct listnode **hashtab, char *key) {
    struct listnode *node;
    int index = hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
        if (strcmp(key, node->key) == 0)
            return node;
     return NULL;
}