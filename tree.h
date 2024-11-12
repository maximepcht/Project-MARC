//
// Created by ADMIN on 10/22/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

typedef struct s_node{
    int value;
    int depth;
    struct s_node **sons;
    int nbSons;
    int *avails;
}t_node;

int *removeFromArray(int*, int, int);

t_node* createNode(int, int, int, int*);

t_node* createRootNode(int*);

typedef struct s_tree{
    t_node *root;
    int height;
}n_tree;

n_tree* createNTree();

void fillNTree(n_tree*, int*, int);

#endif //UNTITLED1_TREE_H
