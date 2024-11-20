//
// Created by ADMIN on 10/22/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "stack.h"
#include "moves.h"
#include "map.h"
#include "loc.h"
#include "moves.h"

typedef struct s_node{
    int value;
    int depth;
    struct s_node **sons;
    int nbSons;
    t_move* avails;
    struct s_node* parent;
}t_node;

t_move *removeFromArray(t_move*, int, int);

t_node* createNode(int, int, int, t_move*, t_node*, t_map, t_localisation);

t_node* createRootNode(int*);

typedef struct s_tree{
    t_node *root;
    int height;
}n_tree;

n_tree* createNTree();

void fillNTree(n_tree*, t_move*, int, t_localisation, t_map);

void displayTree(t_node*, int);

void findMinLeaf(t_node*, t_node***, int*, int*);

t_stack* findPathToMin(t_node**, int, int*);

void displayPathToMin(t_stack*, int);

#endif //UNTITLED1_TREE_H
