#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "stack.h"
#define NB_CHOICES 5
#define MAX_DEPTH 5

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

t_stack* findPathToMin(t_node** minArray, int sizeOfMinArray, int* sizeOfPathArray) {
    if (minArray == NULL || sizeOfMinArray <= 0) {
        *sizeOfPathArray = 0;
        return NULL;
    }

    t_stack* pathArray = (t_stack*) malloc(sizeof(t_stack) * sizeOfMinArray);
    if (pathArray == NULL) {
        perror("Failed to allocate memory for pathArray");
        *sizeOfPathArray = 0;
        return NULL;
    }

    *sizeOfPathArray = 0; // Initialize the count of valid paths
    int validPathIndex = 0;

    for (int i = 0; i < sizeOfMinArray; i++) {
        t_node* curr = minArray[i];
        int contains10000 = 0;

        // Check if the current path contains the value 10000
        while (curr != NULL) {
            if (curr->value == 10000) {
                contains10000 = 1;
                break;
            }
            curr = curr->parent;
        }

        // If the path contains 10000, skip it
        if (contains10000) {
            continue;
        }

        // Reinitialize the traversal to build the path
        curr = minArray[i];
        pathArray[validPathIndex] = createStack(MAX_DEPTH + 1);

        while (curr != NULL) {
            push(&pathArray[validPathIndex], curr->value);
            curr = curr->parent;
        }

        validPathIndex++;
        (*sizeOfPathArray)++;
    }

    // Shrink the array to valid paths only
    t_stack* validPathArray = realloc(pathArray, sizeof(t_stack) * validPathIndex);
    if (validPathArray == NULL) {
        perror("Failed to reallocate memory for validPathArray");
        free(pathArray); // Free original allocation
        *sizeOfPathArray = 0;
        return NULL;
    }
    return validPathArray;
}


void displayPathToMin(t_stack* pathArray, int sizeOfPathArray) {
    if (pathArray == NULL || sizeOfPathArray <= 0) {
        printf("No paths to display.\n");
        return;
    }

    for (int i = 0; i < sizeOfPathArray; i++) {
        if (pathArray[i].nbElts == 0) {  // Check if the stack is empty
            printf("Path %d is empty.\n", i + 1);
            continue;
        }

        printf("Path %d to the minimum leaf: ", i + 1);
        for (int j = pathArray[i].nbElts - 1; j >= 0; j--) {  // Print stack elements
            printf("%d | ", pathArray[i].values[j]);
        }
        printf("\n");
    }
}



