//
// Created by ADMIN on 11/19/2024.
//
#include <stdlib.h>
#include "moves.h"

int* generateAvails(t_move* moves, int size){
    int* avails = (int*) malloc(size*sizeof(int));
    if (avails == NULL){
        perror("Failed to allocate memory\n");
        return NULL;
    }

}