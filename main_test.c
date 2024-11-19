//
// Created by PC on 11/12/2024.
//
#include <stdio.h>
#include <time.h>
#include "tree.h"

int main() {
    clock_t start = clock();
    int avails[9] = {30,4,10,10000,6,45,1,32,0};
    int sizeAvails = sizeof(avails)/sizeof(avails[0]);
    n_tree* myTree = createNTree();
    fillNTree(myTree, avails, sizeAvails);
    t_node** MinArray = NULL;
    int sizeOfMinArray = 0;
    int sizeOfPathArray;
    int min = 0;
    findMinLeaf(myTree->root, &MinArray, &sizeOfMinArray, &min);
    t_stack* pathArray = findPathToMin(MinArray, sizeOfMinArray, &sizeOfPathArray);
    displayPathToMin(pathArray, sizeOfPathArray);
//    displayTree(myTree->root, 5);
    clock_t end = clock();
    double elapsed_time = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);
    return 0;
}