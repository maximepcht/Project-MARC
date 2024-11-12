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
    //displayTree(myTree->root,3);
    t_node* min_node = findMinLeaf(myTree->root);
    printf("Minimum value of the tree is : %d\n", min_node->value);
    printf("Minimum node pointer %p\n", min_node);
    t_stack path = findPathToMin(min_node);
    displayPathToMin(path);
    return 0;
}