//
// Created by guillaume on 28/03/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arrangement.h"



void finArrangements(Arrangement *arr, int k, int *list, int ensemble[]) {
    int cpEnsemble[arr->n];

    if (k == arr->k) {
        arr->arr[arr->position] = malloc(arr->k * sizeof(int));

        for (int i = 0; i < arr->k; i++) {
            arr->arr[arr->position][i] = list[i];
        }

        arr->position++;
        return;
    }

    for (int i = 0; i < arr->n - k; i++) {
        list[k] = ensemble[i];
        for (int j = 0, count = 0; j < arr->n - k; j++) {
            if (j != i) {
                cpEnsemble[count] = ensemble[j];
                count++;
            }
        }
        finArrangements(arr, k + 1, list, cpEnsemble);
    }
}

Arrangement *createArrangement() {
    Arrangement *arrangement = malloc(sizeof(Arrangement));
    if (arrangement == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    arrangement->position = 0;
    arrangement->k = 0;
    arrangement->nbArr = 0;
    arrangement->n = 0;

    return arrangement;
}

void destroyArrangement(Arrangement *arrangement) {

    for (int i = 0; i < arrangement->nbArr; i++) {
        free(arrangement->arr[i]);
    }
    free(arrangement->arr);

    free(arrangement);
}

void confNbArrangement(Arrangement *arrangement) {
    arrangement->nbArr = 1;

    if (arrangement->k > arrangement->n) {
        fprintf(stderr, "confNbArrangement() : invalid value\n");
        return;
    }

    for (int i = arrangement->n; i > arrangement->n - arrangement->k; i--) {
        arrangement->nbArr *= i;
    }

    arrangement->arr = malloc(sizeof(int *) * arrangement->nbArr);
}


Arrangement *buildArrangement(int *ensemble, int n, int k) {

    Arrangement *arrangement = createArrangement();

    arrangement->n = n;
    arrangement->k = k;

    confNbArrangement(arrangement);

    int *list = malloc(arrangement->k * sizeof(int));

    finArrangements(arrangement, 0, list, ensemble);
    free(list);

    return arrangement;
}


void printArrangement(Arrangement *arrangement) {
    printf("-----------------------\n");
    for (int i = 0; i < arrangement->nbArr; i++) {
        printf("(");
        for (int j = 0; j < arrangement->k; j++) {
            printf("%d", arrangement->arr[i][j]);
            if (j < arrangement->k - 1) printf(", ");
        }
        printf(")\n");
    }
    printf("-----------------------\n");
}
