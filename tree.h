//
// Created by ADMIN on 10/22/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "stack.h"
typedef struct s_node{
    int value;
    int depth;
    struct s_node **sons;
    int nbSons;
    int *avails;
    struct s_node* parent;
}t_node;

int *removeFromArray(int*, int, int);

t_node* createNode(int, int, int, int*, t_node*);

t_node* createRootNode(int*);

typedef struct s_tree{
    t_node *root;
    int height;
}n_tree;

n_tree* createNTree();

void fillNTree(n_tree*, int*, int);

void displayTree(t_node*, int);

void findMinLeaf(t_node*, t_node***, int*, int*);

t_stack* findPathToMin(t_node**, int, int*);

void displayPathToMin(t_stack*, int);

#endif //UNTITLED1_TREE_H
