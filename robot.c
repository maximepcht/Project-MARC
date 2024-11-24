//
// Created by ADMIN on 11/19/2024.
//
#include <stdlib.h>
#include "stdio.h"
#include "robot.h"
#include "time.h"

//Local functions
/**
 * @brief Starts the process of one move phase
 * @param curr_loc : Current location of the rover
 * @param path : The path chosen by the robot
 */
void movePhase(t_stack, t_localisation*);

//Definition of local functions
void movePhase(t_stack path, t_localisation* curr_loc){
    if (path.nbElts == 0){
        printf("The path chosen is empty");
    }
    pop(&path); //Remove the move associated with the root (i.e. NONE)
    printf("Starting position (%d , %d)\n",curr_loc->pos.x, curr_loc->pos.y);

    //Move the rover
    while (path.nbElts != 0){
        printf("Doing move : %s\n", getMoveAsString(top(path)));
        updateLocalisation(curr_loc, pop(&path));
        printf("Current position (%d , %d)\n", curr_loc->pos.x, curr_loc->pos.y);
    }
}


//Definition of exported functions
void findBaseStation(t_localisation* curr_loc, t_map map){
    int nbChoices = 12;
    int phaseNb = 1;
    while (map.soils[curr_loc->pos.y][curr_loc->pos.x] != BASE_STATION){ //Check if the rover has reached the base station
        printf("PHASE %d\n", phaseNb);
        int nbMoves = 7;
        if (map.soils[curr_loc->pos.y][curr_loc->pos.x] == REG){ //Lower the number of moves if the rover starts the move phase on an REG tile
            nbMoves--;
        }
        t_move* moves = getRandomMoves(nbChoices); //Get the random movements
        if (map.soils[curr_loc->pos.y][curr_loc->pos.x] == ERG){ //Lower the distance of the movements if the rover starts on an ERG tile
            for (int i = 0; i < nbChoices; i++){
                switch (moves[i]) {

                    case F_20:
                        moves[i] = F_10;
                        break;
                    case F_30:
                        moves[i] = F_20;
                        break;
                    case U_TURN: //For U-Turns the rover will randomly choose between turn right and turn left
                        srand(time(NULL));
                        int choice = rand()% 2;
                        if (choice == 0){
                            moves[i] = T_LEFT;
                        }
                        else{
                            moves[i] = T_RIGHT;
                        }
                        break;
                    default:
                        moves[i] = NONE;
                }
            }
        }
        n_tree* choiceTree = createNTree(); //Initialize the choice tree
        fillNTree(choiceTree,moves,nbChoices,*(curr_loc),map, nbMoves); //Fill the choice tree
        printf("Moves available : ");
        for (int i = 0; i < nbChoices; i++) {
            printf("%s\t", getMoveAsString(moves[i])); //Print the moves available at the start of the move phase
        }
        printf("\n");

        //Initialize the variables needed to find the optimal path
        t_node** MinArray = NULL;
        int sizeOfMinArray = 0;
        int min = 0;
        int sizePathArray;

        findMinLeaf(choiceTree->root, &MinArray, &sizeOfMinArray, &min); //Find the minimum leaves
        t_stack* arrayOfPaths = findPathToMin(MinArray, sizeOfMinArray, &sizePathArray); //Find all possible paths to the minimum leaves
        movePhase(arrayOfPaths[0], curr_loc); //Start the move phase

        //Free the choice tree, the minimum array, and the array of paths
        freeTree(&choiceTree->root);
        free(MinArray);
        freeArrayOfPaths(arrayOfPaths,sizePathArray);

        //Increment the number of phases
        phaseNb++;
    }
    printf("MARC has reached the Base station !\n");
}





