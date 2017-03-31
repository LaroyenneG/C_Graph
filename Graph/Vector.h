//
// Created by guillaume on 09/03/17.
//

#include <stdbool.h>

#ifndef COMPLEXITE_VECTOR_H
#define COMPLEXITE_VECTOR_H

typedef struct vector {

    unsigned int capacityIncrement;
    unsigned int elementCount;
    unsigned int buffer;

    size_t size;

    void **elementData;

} Vector;

Vector *createVector();

void *firstElementVector(Vector *vector);

void addElementVector(Vector *vector, void *element);

bool addVector(Vector *vector, void *element);

void clearVector(Vector *vector);

bool containsVector(Vector *vector, void *pVoid);

void *elementAtVector(Vector *vector, unsigned int index);

int indexOfVector(Vector *vector, void *pVoid);

void *lastElementVector(Vector *vector);

int lastIndexOfVector(Vector *vector, void *pVoid);

void destroyVector(Vector *vector);

int capacityVector(Vector *vector);

void trimToSizeVector(Vector *vector);

void ensureCapacityVector(Vector *vector, unsigned int minCapacity);

void allDestroyVector(Vector *vector);

#endif //COMPLEXITE_VECTOR_H
