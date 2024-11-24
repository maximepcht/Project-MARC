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

/**
 * @brief Structure for a node
 */
typedef struct s_node{
    int value;
    int depth;
    struct s_node **sons;
    int nbSons;
    t_move* avails;
    struct s_node* parent;
    t_move moveUsed;
}t_node;

/**
 * @brief Creates a node and all of its sons recursively
 * @param val : The cost of the tile represented by the node
 * @param nbSons : The number of sons the created node will contain
 * @param depth : The depth of the created node
 * @param avails : An array of t_move representing the moves available at this node
 * @param parent : The parent of the node
 * @param map : The map
 * @param loc : The localisation of the robot at this node
 * @param moveUsed : The move used to go to this node
 * @param maxDepth : The maximum depth allowed for a node
 * @return a pointer to the created node
 */
t_node* createNode(int, int, int, t_move*, t_node*, t_map, t_localisation, t_move, int);

/**
 * @brief Structure for a tree
 */
typedef struct s_tree{
    t_node *root;
}n_tree;

/**
 * @brief Creates an empty tree
 * @return a pointer to the empty tree
 */
n_tree* createNTree();

/**
 * @brief Fills a tree passed in as parameter
 * @param tree : The tree to be filled
 * @param avails : An array of t_move representing the moves available at the root of the tree
 * @param numChoices : Number of moves available
 * @param curr_loc : Current location of the robot
 * @param map : The map
 * @param maxDepth : Maximum depth possible for a node
 */
void fillNTree(n_tree*, t_move*, int, t_localisation, t_map, int);

void displayTree(t_node*, int);

/**
 * @brief Finds the minimum leaf/leaves of a tree and adds it/them to an array of pointers of t_node
 * @param root : The root of the tree
 * @param minArray : An array of pointers containing pointers to the minimum leaf/leaves
 * @param size : Pointer to the size of minArray
 * @param minValue : Pointer to the minimum value among the leaves of the tree
 */
void findMinLeaf(t_node*, t_node***, int*, int*);

/**
 * @brief Finds all the possible path to the minimum leaves. Does not include the paths containing a node with value >= 10000. Note : This function will prioritize the shortest paths.
 * @param minArray : The array containing the minimum nodes
 * @param sizeOfMinArray : The size of minArray
 * @param sizeOfPathArray : Pointer to the size of the path array
 * @return An array of stacks representing each possible path.
 */
t_stack* findPathToMin(t_node**, int, int*);

void displayPathToMin(t_stack*, int);

/**
 * @brief Frees the memory allocated for the tree
 * @param root : Pointer to the root of the tree
 */
void freeTree(t_node**);

/**
 * @brief Frees the array containing all possible paths to the minimum value
 * @param pathArray : The array of paths
 * @param sizeOfPathArray : The size of the pathArray
 */
void freeArrayOfPaths(t_stack*, int);

#endif //UNTITLED1_TREE_H
