#include <stdio.h>
#include <string.h>

struct treenode {
    char *key;
    struct treenode *left;
    struct treenode *right;
};

void showtree(struct treenode*, int i);
void addtree(struct treenode*, char*, char*);
struct treenode *createnode(char*, struct treenode*, struct treenode*);