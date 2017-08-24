//
// Created by guillaume on 28/03/17.
//

#ifndef UNTITLED_ARRANGEMENT_H
#define UNTITLED_ARRANGEMENT_H

typedef struct Arrangement_s {
    int n;
    int k;
    int nbArr;
    int position;
    int **arr;
} Arrangement;


void destroyArrangement(Arrangement *arrangement);

Arrangement *buildArrangement(int *ensemble, int n, int k);

void printArrangement(Arrangement *arrangement);

#endif //UNTITLED_ARRANGEMENT_H
