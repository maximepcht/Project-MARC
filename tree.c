#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
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

t_node* createNode(int val, int nb_sons, int depth, int* avails) {
    t_node *newNode = (t_node*) malloc(sizeof(t_node));
    newNode->value = val;
    newNode->nbSons = 0;
    newNode->depth = depth;
    newNode->sons = NULL;
    newNode->avails = avails;

    if (depth <= MAX_DEPTH) {
        newNode->sons = (t_node**) malloc(nb_sons * sizeof(t_node*));
        for (int i = 0; i < nb_sons; i++) {
            int* new_avails = removeFromArray(avails, nb_sons, i);
            newNode->sons[i] = createNode(avails[i], nb_sons - 1, depth + 1, new_avails);
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
    tree->root = createNode(-1, numValues, 0, avails);
}
