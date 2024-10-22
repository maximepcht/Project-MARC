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
}t_node;

t_node* addNode(int, t_node*);

typedef struct s_tree{
    t_node *root;
    int height;
}n_tree;

n_tree* createEmptyTree();

void fillEmptyTree(n_tree*, int*);

#endif //UNTITLED1_TREE_H
