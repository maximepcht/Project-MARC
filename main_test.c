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
        printf("Son 0->Son %d : %d\n",i, myTree->root->sons[0]->sons[i]->value);
    }
    return 0;
}