#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "moves.h"
#include "loc.h"
#include "tree.h"
#include "moves.h"
#define NB_CHOICES 9
#define NB_MOVES 5
int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    t_localisation startLoc = loc_init(5,6,NORTH);
    t_move* moves = getRandomMoves(NB_CHOICES);
    n_tree* choiceTree = createNTree();
    fillNTree(choiceTree,moves,NB_CHOICES,startLoc,map);
    for (int i = 0; i < NB_CHOICES; i++) {
        printf("%s\t", getMoveAsString(moves[i]));
    }
    printf("\n");
    t_node** MinArray = NULL;
    int sizeOfMinArray = 0;
    int min = 0;
    findMinLeaf(choiceTree->root, &MinArray, &sizeOfMinArray, &min);
    int sizePathArray;
    t_stack* arrayOfPaths = findPathToMin(MinArray, sizeOfMinArray, &sizePathArray);
    displayPathToMin(arrayOfPaths, sizePathArray);
    return 0;
}
