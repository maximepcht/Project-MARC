//
// Created by PC on 11/12/2024.
//
#include <stdio.h>
#include "tree.h"

int main() {
    int avails[5] = {1,2,3,4,5,};
    int sizeAvails = 5;
    n_tree* myTree = createNTree();
    fillNTree(myTree, avails, sizeAvails);
    for (int i = 0; i < 5; i++){
        printf("Value of Son %d : %d\n",i, myTree->root->sons[i]->value);
    }
    for (int i = 0; i < 4; i++){
        printf("Son 1->Son %d : %d\n",i, myTree->root->sons[1]->sons[i]->value);
    }
    t_node** MinArray = NULL;
    int size = 0;
    int min = 0;
    findMinLeaf(myTree->root, &MinArray, &size, &min);
    t_stack* pathArray = findPathToMin(MinArray, size);
    for (int i = 0; i < size; i++){
        printf("Path %d : ", i);
        displayPathToMin(pathArray[i]);
        printf("\n");
    }
//    displayTree(myTree->root, 5);
    return 0;
}