#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "loc.h"
#include "robot.h"
#include "time.h"


int main() {
    clock_t  start, end;
    double timeTaken;
    start = clock();
    t_map map = createMapFromFile("..\\maps\\example2.map");
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
    t_localisation startLoc = loc_init(10,10,NORTH);
    findBaseStation(&startLoc,map);
    end = clock();
    timeTaken = ((double ) end -start) / CLOCKS_PER_SEC;
    printf("Time taken to reach base station : %f seconds\n",timeTaken);
    return 0;
}
