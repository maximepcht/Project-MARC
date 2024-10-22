//
// Created by ADMIN on 10/22/2024.
//
#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#define NB_CHOICES 5

t_node* addNode(int val, t_node* parent){
    t_node *newNode = malloc(sizeof(t_node));
    newNode->value = val;
    newNode->depth = parent->depth+1;
    newNode->nbSons = NB_CHOICES-newNode->depth;
    newNode->sons = malloc(sizeof(t_node)*newNode->nbSons);
    for (int i = 0; i < newNode->nbSons; i++){
        newNode->sons[i] = NULL;
    }
    return  newNode;
}

n_tree* createEmptyTree(){
    n_tree* newN_Tree = malloc(sizeof(n_tree));
    newN_Tree->root = NULL;
    newN_Tree->height = 0;
    return newN_Tree;
}

void fillTree(n_tree* tree, int* listOfValues);