#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "stack.h"
#define NB_CHOICES 5
#define MAX_DEPTH 3

// Node functions

int* removeFromArray(int* arr, int size, int index) {
    // Check if the index is valid
    if (index < 0 || index >= size) {
        printf("Index out of bounds.\n");
        return NULL;
    }

    // Allocate memory for the new array
    int newSize = size - 1;
    int* newArr = (int*)malloc(newSize * sizeof(int));

    if (newArr == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // Copy elements before the index to the new array
    for (int i = 0; i < index; i++) {
        newArr[i] = arr[i];
    }

    // Copy elements after the index to the new array
    for (int i = index + 1; i < size; i++) {
        newArr[i - 1] = arr[i];
    }

    return newArr;
}

t_node* createNode(int val, int nb_sons, int depth, int* avails, t_node* parent) {
    t_node *newNode = (t_node*) malloc(sizeof(t_node));
    newNode->value = val;
    newNode->nbSons = 0;
    newNode->depth = depth;
    newNode->sons = NULL;
    newNode->avails = avails;
    newNode->parent = parent;

    if (depth < MAX_DEPTH) {
        newNode->sons = (t_node**) malloc(nb_sons * sizeof(t_node*));
        for (int i = 0; i < nb_sons; i++) {
            int* new_avails = removeFromArray(avails, nb_sons, i);
            newNode->sons[i] = createNode(avails[i], nb_sons - 1, depth + 1, new_avails,newNode);
            newNode->nbSons++;
        }
    }

    return newNode;
}

// Tree functions

n_tree* createNTree() {
    n_tree* tree = (n_tree*) malloc(sizeof(n_tree));
    tree->root = NULL;
    tree->height = 0;
    return tree;
}

void fillNTree(n_tree* tree, int* avails, int numValues) {
    tree->root = createNode(-1, numValues, 0, avails,NULL);
}

void displayTree(t_node* node, int depth) {
    if (node == NULL) {
        return;
    }

    // Print indentation based on depth
    for (int i = 0; i < depth; i++) {
        printf("  ");  // Indentation for each level
    }

    // Print the current node's value
    printf("%d\t %p\n", node->value,node);

    // Recursively print each child
    for (int i = 0; i < node->nbSons; i++) {
        displayTree(node->sons[i], depth + 1);
    }
}

t_node* findMinLeaf(t_node* node){
    if (node->nbSons == 0){
        return node;
    }

    t_node* minLeafNode = NULL;
    for (int i = 0; i < node->nbSons; i++){
        t_node* childMinLeaf = findMinLeaf(node->sons[i]);
        if (childMinLeaf != NULL){
            if (minLeafNode == NULL || childMinLeaf->value < minLeafNode->value){
                minLeafNode = childMinLeaf;
            }
        }
    }
    return minLeafNode;
}

t_stack findPathToMin(t_node* targetNode){
    t_stack path = createStack(MAX_DEPTH+1);
    t_node* curr = targetNode;
    while (curr != NULL){
        push(&path, curr->value);
        curr = curr->parent;
    }
    return path;
}

void displayPathToMin(t_stack path){
    if (path.size == 0){
        printf("The path is empty\n");
        return;
    }
    printf("Path to the minimum leaf : ");
    for (int i = path.nbElts-1; i >= 0 ; i--){
        printf("%d | ", path.values[i]);
    }
}
