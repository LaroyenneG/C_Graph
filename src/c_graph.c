#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

#include "Graph.h"

void testAlgorithm(Graph *graph) {
    assert(isConnectivityGraph(graph));

    unsigned int n = (unsigned int) my_rand(0, graph->size - 1);


    /*
     * 1ére variante simple
     */
    clock_t start1, finish1;
    double duration1;

    printf("\nAlgorithm 1 in process...\n");
    start1 = clock();
    Vector *vector1 = firstRouteSolution(graph, n);
    finish1 = clock();

    int somme1 = calculatePathSize(graph, vector1);

    for (int i = 0; i < vector1->elementCount; ++i) {
        printf("%s", graph->node[(*(unsigned int *) elementAtVector(vector1, (unsigned int) i))]);
        if (i + 1 < vector1->elementCount) {
            printf(" -> ");
        }
    }
    printf("\nTravel size = %d \n", somme1);

    duration1 = (double) (finish1 - start1) / CLOCKS_PER_SEC;
    printf("Execution time = %lf s\n", duration1);

    allDestroyVector(vector1);


    /*
     * 2ème variante optimal
     */

    clock_t start2, finish2;
    double duration2;

    printf("\nAlgorithm 2 in process...\n");
    start2 = clock();
    Vector *vector2 = findOptimalPath(graph, n);
    finish2 = clock();


    int somme2 = calculatePathSize(graph, vector2);

    for (int i = 0; i < vector2->elementCount; ++i) {
        printf("%s", graph->node[(*(unsigned int *) elementAtVector(vector2, (unsigned int) i))]);
        if (i + 1 < vector2->elementCount) {
            printf(" -> ");
        }
    }
    printf("\nTravel size = %d \n", somme2);

    duration2 = (double) (finish2 - start2) / CLOCKS_PER_SEC;
    printf("Execution time = %lf s\n", duration2);

    allDestroyVector(vector2);
}


int main() {


    printf("Welcome in C_Graph (Recommended Memory: 8Go)\n\n");

    unsigned int size=0;
    printf("Enter the size of the graph :\n");
    scanf("%u", &size);

    assert(size <= 12);

    Graph *graph = createRandomConnectivityGraph(size, size);

    printGraph(graph);

    testAlgorithm(graph);

    destroyGraph(graph);

    return 0;
}