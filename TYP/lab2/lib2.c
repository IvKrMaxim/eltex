#include "lib2.h"

void showtree(struct treenode *root, int i) {
    int j = 0;
    if (root->left != NULL)
	showtree(root->left, i + 1);
    for (j = 0; j < i; j++)
	printf("\t");
    printf("%s\n", root->key);
    if (root->right != NULL)
	showtree(root->right, i + 1);
}

void addtree(struct treenode *root, char *key1, char *key2) {
    struct treenode *node;
    for (node = root; node->left != NULL; node = node->left);
    node->left = createnode(key1, NULL, NULL);
    for (node = root; node->right != NULL; node = node->right);
    node->right = createnode(key2, NULL, NULL);
}

struct treenode *createnode(char *key, struct treenode *left, struct treenode *right) {
    struct treenode *node = malloc(sizeof(struct treenode));
    if (node == NULL)
	return NULL;
    node->key = strdup(key);
    node->left = left;
    node->right = right;
    return node;
}
