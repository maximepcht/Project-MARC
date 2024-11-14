#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "stack.h"
#define NB_CHOICES 5
#define MAX_DEPTH 3

// Node functions

int* removeFromArray(int* arr, int size, int index) {
    if (index < 0 || index >= size) {
        printf("Index out of bounds.\n");
        return NULL;
    }
    int newSize = size - 1;
    int* newArr = (int*)malloc(newSize * sizeof(int));

    if (newArr == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    for (int i = 0; i < index; i++) {
        newArr[i] = arr[i];
    }

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


void findMinLeaf(t_node* root, t_node*** minArray, int* size, int* minValue) {
    if (root == NULL) {
        return;
    }

    // Check if the current node is a leaf node
    if (root->nbSons == 0) {
        // If this is the first leaf, initialize minValue
        if (*size == 0) {
            *minValue = root->value;
            *minArray = (t_node**) malloc(sizeof(t_node*));
            (*minArray)[0] = root;
            *size = 1;
        } else if (root->value < *minValue) {
            // Found a new minimum leaf value, reset MinArray
            *minValue = root->value;
            *minArray = (t_node**) realloc(*minArray, sizeof(t_node*));
            (*minArray)[0] = root;
            *size = 1;
        } else if (root->value == *minValue) {
            // Leaf value matches current minimum, add to MinArray
            *minArray = (t_node**) realloc(*minArray, (*size + 1) * sizeof(t_node*));
            (*minArray)[*size] = root;
            (*size)++;
        }
    }

    // Recursively check all children
    for (int i = 0; i < root->nbSons; i++) {
        findMinLeaf(root->sons[i], minArray, size, minValue);
    }
}

t_stack* findPathToMin(t_node** minArray, int sizeOfMinArray){
    t_stack* pathArray = (t_stack*) malloc(sizeof(t_stack)*sizeOfMinArray);
    for (int i = 0; i < sizeOfMinArray; i++){
        pathArray[i] = createStack(MAX_DEPTH+1);
        t_node* curr = minArray[i];
        while (curr != NULL){
            push(&pathArray[i], curr->value);
            curr = curr->parent;
        }
    }
    return pathArray;
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
