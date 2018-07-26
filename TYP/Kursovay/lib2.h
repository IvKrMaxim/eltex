#include <stdio.h>
#include <string.h>
#include "lib.h"

typedef enum { typeCon, typeId, typeOpr, typeDef, typeErr } nodeEnum;

struct treenode {
    char *key;
    nodeEnum type;
    struct treenode *p1;
    struct treenode *p2;
    struct treenode *p3;
    struct treenode *p4;
    struct treenode *p5;
};

void dfs(struct treenode*);
void excep(struct treenode*, int);
struct treenode *add_atr(struct treenode*, struct treenode*);
struct treenode *create_node(char*, nodeEnum, struct treenode*, struct treenode*, struct treenode*, struct treenode*, struct treenode*);