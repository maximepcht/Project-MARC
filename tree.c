#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "stack.h"
#include "loc.h"
#include "moves.h"
#include "map.h"

//Local functions
/**
 * @brief Gets the cost of a tile if the move m were to be used
 * @param map : The map
 * @param curr_loc : Current localisation of the rover
 * @param m : The move to be used
 * @return the cost of the tile if the move m were to be used
 */
int getCostFromMove(t_map, t_localisation, t_move);

/**
 * @brief Removes the move at a specific index
 * @param arr : Array of moves
 * @param size : Size of arr
 * @param index : Index of the move to be removed
 * @return the new array of size (size-1) without the move at the specified index.
 *         Returns NULL if the index is out of bounds or memory allocation fails
 */
t_move* removeFromArray(t_move*, int, int);

/**
 * @brief Frees the node and all of the sons recursively
 * @param node : The node from which the freeing process will start
 */
void freeNode(t_node*);


//Definitions of local functions
int getCostFromMove(t_map map, t_localisation curr_loc, t_move m){
   t_localisation newLoc = move(curr_loc, m);
    return map.costs[newLoc.pos.y][newLoc.pos.x];
}

t_move* removeFromArray(t_move* arr, int size, int index) {
    //Check if the index is valid
    if (index < 0 || index >= size) {
        printf("Index out of bounds.\n");
        return NULL;
    }

    //Calculate the new size of the array
    int newSize = size - 1;

    //Allocate memory for the new array
    t_move* newArr = (t_move*)malloc(newSize * sizeof(t_move));

    //Check if memory allocation was successful
    if (newArr == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    for (int i = 0; i < index; i++) {
        newArr[i] = arr[i]; //Copy elements before the specified index
    }

    for (int i = index + 1; i < size; i++) {
        newArr[i - 1] = arr[i]; //Copy elements after the specified index
    }

    // Return the new array with the element removed
    return newArr;
}

void freeNode(t_node* node) {
    if (node == NULL) {
        return;
    }

    // Free all dynamically allocated memory inside the node
    if (node->sons != NULL) {
        for (int i = 0; i < node->nbSons; i++) {
            freeNode(node->sons[i]);  // Recursively free children (if any)
        }
        free(node->sons);  // Free the array of sons
    }

    if (node->avails != NULL) {
        free(node->avails);  // Free the dynamically allocated 'avails' array (if any)
    }


    //free the node itself
    free(node);
}

//Definitions of exported functions
//Node functions
t_node* createNode(int val, int nb_sons, int depth, t_move* avails, t_node* parent, t_map map, t_localisation loc, t_move moveUsed, int maxDepth) {
    // Allocate memory for the new node
    t_node *newNode = (t_node*) malloc(sizeof(t_node));

    //Initialize the parameters for the node
    newNode->value = val;
    newNode->nbSons = 0;
    newNode->depth = depth;
    newNode->sons = NULL;
    newNode->avails = avails;
    newNode->parent = parent;
    newNode->moveUsed = moveUsed;

    // If the node's value is 0 or >= 10000, do not create children or maxDepth has been reached
    if ((val == 0 || val >= 10000) || depth >= maxDepth) {
        return newNode;
    }

    // Allocate memory for children
    newNode->sons = (t_node**) malloc(nb_sons * sizeof(t_node*));
    for (int i = 0; i < nb_sons; i++) {
        int valueOfSon;
        t_localisation newLoc = move(loc, avails[i]); //Get the new localisation from a move
        t_move* new_avails = removeFromArray(avails, nb_sons, i); //Remove the move used to go to this node

        // Determine the value of the child node
        if (isValidLocalisation(newLoc.pos, map.x_max, map.y_max)) { //Check if after using the move the rover will be at a valid localisation

            valueOfSon = getCostFromMove(map, loc, avails[i]); //cost of the tile if the move were to be used if valid localisation
        } else {
            valueOfSon = 10000; //10000 if not a valid localisation
        }

        // Create child nodes recursively
        newNode->sons[newNode->nbSons] = createNode(valueOfSon, nb_sons - 1, depth + 1, new_avails, newNode, map, newLoc, avails[i], maxDepth);
        newNode->nbSons++;
    }

    return newNode;
}

//Tree functions
n_tree* createNTree() {
    n_tree* tree = (n_tree*) malloc(sizeof(n_tree));
    tree->root = NULL;
    return tree;
}

void fillNTree(n_tree* tree, t_move* avails, int numChoices, t_localisation curr_loc, t_map map, int maxDepth) {
    t_position curr_pos = curr_loc.pos;
    tree->root = createNode(map.costs[curr_pos.y][curr_pos.x], numChoices, 0, avails,NULL, map, curr_loc, NONE, maxDepth);
}

//Functions to find the optimal path
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
            //If a new minimum leaf value, reset MinArray
            *minValue = root->value;
            *minArray = (t_node**) realloc(*minArray, sizeof(t_node*));
            (*minArray)[0] = root;
            *size = 1;
        } else if (root->value == *minValue) {
            //If the leaf value matches the current minimum, add it to MinArray
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

    t_stack* pathArray = NULL;
    int minDepth = INT_MAX; //Set the depth to the maximum integer possible

    // Find the minimum depth
    for (int i = 0; i < sizeOfMinArray; i++) {
        t_node* curr = minArray[i];
        int contains10000 = 0;

        // Check if the current path contains the value 10000
        while (curr != NULL) {
            if (curr->value >= 10000) {
                contains10000 = 1;
                break;
            }
            curr = curr->parent;
        }

        // Skip paths containing 10000
        if (contains10000) {
            continue;
        }

        // Update minimum depth
        if (minArray[i]->depth < minDepth) {
            minDepth = minArray[i]->depth;
        }
    }

    // Collect all nodes within minArray with the minimum depth
    *sizeOfPathArray = 0;
    pathArray = (t_stack*) malloc(sizeof(t_stack) * sizeOfMinArray); // Over-allocate initially

    for (int i = 0; i < sizeOfMinArray; i++) {
        t_node* curr = minArray[i];
        int contains10000 = 0;

        // Check if the current path contains the value 10000
        while (curr != NULL) {
            if (curr->value >= 10000) {
                contains10000 = 1;
                break;
            }
            curr = curr->parent;
        }

        // Skip paths containing 10000
        if (contains10000) {
            continue;
        }

        // Add paths with the minimum depth to the pathArray
        if (minArray[i]->depth == minDepth) {
            curr = minArray[i];
            pathArray[*sizeOfPathArray] = createStack(minDepth + 1);

            //Backtrack to the root to find the moves associated with the path
            while (curr != NULL) {
                push(&pathArray[*sizeOfPathArray], curr->moveUsed);
                curr = curr->parent;
            }

            (*sizeOfPathArray)++;
        }
    }

    // Shrink the array to fit the valid paths
    t_stack* validPathArray = realloc(pathArray, sizeof(t_stack) * (*sizeOfPathArray));
    if (validPathArray == NULL) {
        perror("Failed to reallocate memory for validPathArray");
        free(pathArray);
        *sizeOfPathArray = 0;
        return NULL;
    }

    return validPathArray;
}

//Display functions (used to check if it is the correct path, not used in main())
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

        printf("Path %d to the minimum leaf: START ", i + 1);
        for (int j = pathArray[i].nbElts - 1; j >= 0; j--) {  // Print stack elements
            printf("%s -->  ", getMoveAsString(pathArray[i].values[j]));
        }
        printf("END\n");
    }
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
    printf("%d\n", node->value);

    // Recursively print each child
    for (int i = 0; i < node->nbSons; i++) {
        displayTree(node->sons[i], depth + 1);
    }
}

//Memory management functions
void freeTree(t_node** root) {
    if (root == NULL || *root == NULL) {
        return;  // Nothing to free
    }

    freeNode(*root);  // Free the tree starting from the root
    *root = NULL;     // Set the original pointer to NULL
}

void freeArrayOfPaths(t_stack* pathArray, int sizeOfPathArray) {
    if (pathArray == NULL) {
        return;
    }

    // Iterate through each stack in the array
    for (int i = 0; i < sizeOfPathArray; i++) {
        // Free the dynamically allocated array of t_move inside each stack
        if (pathArray[i].values != NULL) {
            free(pathArray[i].values);
        }
    }

    // Free the array of stacks itself
    free(pathArray);
}




