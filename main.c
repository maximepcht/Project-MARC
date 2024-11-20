#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "moves.h"
#include "loc.h"
#include "tree.h"
#include "moves.h"
#define NB_CHOICES 5
#define NB_MOVES 3
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
    t_localisation startLoc = loc_init(6,5,NORTH);
    t_move* moves = getRandomMoves(NB_CHOICES);
    n_tree* choiceTree = createNTree();
    fillNTree(choiceTree,moves,NB_MOVES,startLoc,map);
    displayTree(choiceTree->root, NB_MOVES);
//    t_node** MinArray = NULL;
//    int size = 0;
//    int min = 0;
//    findMinLeaf(choiceTree->root,&MinArray,&size,&min);
//    int sizePathArray;
//    t_stack* arrayOfPaths = findPathToMin(MinArray, size, &sizePathArray);
//    displayPathToMin(arrayOfPaths, sizePathArray);
    return 0;
}
