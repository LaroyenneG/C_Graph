//
// Created by guillaume on 08/03/17.
//


#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include "../lib/Vector.h"

#define NO_NEIGHBOUR -1000
#define NO_ACCESS -1002
#define SIZE_MAX_NAME 50
#define MAX_INT 2147483647

typedef struct graph {
    int **edge;
    int **distance;
    unsigned int size;
    char **node;
} Graph;


Graph *createGraph(unsigned int size);

Graph *constGraphTerm();

void printGraph(Graph *graph);

void destroyGraph(Graph *graph);

bool isConnectivityGraph(Graph *graph);

bool isCompleteGraph(Graph *graph);

Vector *dijkstra(Graph *graph, int a, int b);

Vector *neighbour(Graph *graph, int n);

int my_rand(int min, int max);

int valueEdge(Graph *graph, int a, int b);

Graph *createRandomGraph(int min, int max);

void findDistance(Graph *graph);

bool canIgo(Graph *graph, int s, int d, bool **mark);

Graph *createRandomConnectivityGraph(int min, int max);

Graph *createRandomCompleteGraph();

Vector *firstRouteSolution(Graph *graph, unsigned int v);

int calculatePathSize(Graph *graph, Vector *vector);

Vector *secondRouteSolution(Graph *graph, unsigned int v);

Vector *baseConverter(unsigned int b, int n);

Vector *findOptimalPath(Graph *graph, unsigned int v);

Graph* createGraphWithFile(char file[]);

#endif //GRAPH_GRAPH_H
