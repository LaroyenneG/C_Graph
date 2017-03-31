//
// Created by guillaume on 09/03/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vector.h"


Vector *createVector() {

    Vector *vector = malloc(sizeof(Vector));
    if (vector == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    vector->buffer = 10;

    vector->capacityIncrement = vector->buffer;

    vector->elementData = malloc(sizeof(void *) * vector->capacityIncrement);
    if (vector->elementData == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    vector->elementCount = 0;

    vector->size=0;

    return vector;

}


void *firstElementVector(Vector *vector) {

    if (vector->elementCount <= 0) {
        return NULL;
    }
    return vector->elementData[0];

}

void addElementVector(Vector *vector, void *element) {

    if (vector->capacityIncrement <= vector->elementCount) {
        vector->capacityIncrement += vector->buffer;
        vector->elementData = realloc(vector->elementData, sizeof(void *) * vector->capacityIncrement);
        if (vector->elementData == NULL) {
            perror("realloc()");
            exit(EXIT_FAILURE);
        }
    }
    vector->elementData[vector->elementCount] = element;
    vector->elementCount++;

}

bool addVector(Vector *vector, void *element) {

    if (vector->capacityIncrement <= vector->elementCount) {
        return false;
    }
    vector->elementData[vector->elementCount] = element;
    vector->elementCount++;
    return true;

}

void clearVector(Vector *vector) {

    vector->elementCount = 0;
    free(vector->elementData);
    vector->elementData = malloc(sizeof(void *) * vector->buffer);
    if (vector->elementData == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    vector->capacityIncrement = vector->buffer;

}

bool containsVector(Vector *vector, void *pVoid) {

    for (int i = 0; i < vector->elementCount; i++) {
        if (vector->elementData[i] == pVoid) {
            return true;
        }
    }
    return false;

}

void *elementAtVector(Vector *vector, unsigned int index) {

    assert(index < vector->elementCount);
    assert(index >= 0);

    return vector->elementData[index];

}

int indexOfVector(Vector *vector, void *pVoid) {

    int index = -1;

    for (int i = 0; i < vector->elementCount; i++) {
        if (vector->elementData[i] == pVoid) {
            return i;
        }
    }

    return index;

}


void *lastElementVector(Vector *vector) {

    if (vector->elementCount == 0) {
        return NULL;
    }

    return vector->elementData[vector->elementCount - 1];

}

int lastIndexOfVector(Vector *vector, void *pVoid) {

    int index = -1;

    for (int i = 0; i < vector->elementCount; i++) {
        if (vector->elementData[i] == pVoid) {
            index = i;
        }
    }

    return index;
}


int capacityVector(Vector *vector) {
    return (vector->capacityIncrement - vector->elementCount);
}

void trimToSizeVector(Vector *vector) {

    int m = capacityVector(vector);
    assert(m >= 0);
    if (m == 0) {
        return;
    }

    vector->elementData = realloc(vector->elementData, sizeof(void *) * (vector->elementCount));
    if (vector->elementData == NULL) {
        perror("realloc()");
        exit(EXIT_FAILURE);
    }

    vector->capacityIncrement = vector->elementCount;

}

void ensureCapacityVector(Vector *vector, unsigned int minCapacity) {

    assert(capacityVector(vector) <= minCapacity);
    vector->elementData = realloc(vector->elementData, sizeof(void *) * minCapacity);
    if (vector->elementData == NULL) {
        perror("realloc()");
        exit(EXIT_FAILURE);
    }
    vector->capacityIncrement = minCapacity;

}

void destroyVector(Vector *vector) {

    free(vector->elementData);
    vector->elementData = NULL;
    free(vector);

}

void allDestroyVector(Vector *vector) {
    assert(vector != NULL);

    for (unsigned int e = 0; e < vector->elementCount; e++) {
        free(vector->elementData[e]);
        vector->elementData[e] = NULL;
    }

    destroyVector(vector);
}


/*
 * test
 */

void testFunctionVector() {

    Vector *vector = createVector();

    vector->buffer = 10;

    for (unsigned int i = 0; i < 1000; i++) {
        int *e = malloc(sizeof(int));
        *e = i;
        addElementVector(vector, e);
        assert(elementAtVector(vector, i) == e);
        assert(containsVector(vector, e));
    }

    int *q = 0;

    assert(!containsVector(vector, q));

    assert(1000 == vector->elementCount);

    int *f = elementAtVector(vector, 10);

    assert(*f == 10);

    int rest = vector->capacityIncrement - vector->elementCount;
    for (int a = 0; a <= rest; a++) {
        addVector(vector, &a);
    }


    assert(!addVector(vector, (void *) 15));

    int g = 10269;
    addElementVector(vector, &g);

    assert(*((int *) firstElementVector(vector)) == 0);

    assert(*((int *) lastElementVector(vector)) == g);

    assert(indexOfVector(vector, &g) == 1000);
    assert(1001 == vector->elementCount);

    addElementVector(vector, &g);
    assert(lastIndexOfVector(vector, &g) == 1001);

    ensureCapacityVector(vector, 100001);
    assert(vector->capacityIncrement == 100001);

    trimToSizeVector(vector);
    assert(vector->elementCount == 1002);

    clearVector(vector);
    assert(vector->capacityIncrement == 0);


    destroyVector(vector);
}