//
// Created by guillaume on 08/03/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "Graph.h"
#include "Arrangement.h"

int my_rand(int min, int max) {
    static int first = 0;

    if (first == 0) {
        srand((unsigned int) time(NULL));
        first = 1;
    }
    return (rand() % (max - (min - 1)) + min);
}


Graph *createGraph(unsigned int size) {

    Graph *graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    graph->size = size;

    graph->node = malloc(sizeof(char *) * size);
    if (graph->node == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->size; i++) {
        graph->node[i] = malloc(sizeof(char) * SIZE_MAX_NAME);
        if (graph->node[i] == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }

        for (int c = 0; c < SIZE_MAX_NAME; c++) {
            graph->node[i][c] = '\0';
        }
    }

    graph->edge = malloc(sizeof(int *) * size);
    if (graph->edge == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->size; i++) {
        graph->edge[i] = malloc(sizeof(int) * size);
        if (graph->edge[i] == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
    }

    for (int y = 0; y < graph->size; y++) {
        for (int x = 0; x < graph->size; x++) {
            graph->edge[y][x] = NO_NEIGHBOUR;
        }
    }

    graph->distance = malloc(sizeof(int *) * size);
    if (graph->distance == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->size; i++) {
        graph->distance[i] = malloc(sizeof(int) * size);
        if (graph->distance[i] == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
    }

    for (int y = 0; y < graph->size; y++) {
        for (int x = 0; x < graph->size; x++) {
            graph->distance[y][x] = NO_ACCESS;
        }
    }


    return graph;
}

bool equalsString(const char *string, const char *string1) {
    unsigned int i = 0;
    if (strlen(string) != strlen(string1)) {
        return false;
    }
    for (i = 0; i < strlen(string); i++) {
        if (string[i] != string1[i]) {
            return false;
        }
    }
    return true;

}

Graph *constGraphTerm() {

    Graph *graph = NULL;

    unsigned int size = 0;
    printf("Entrer le nombre de noeud :\n");
    scanf("%d", &size);

    graph = createGraph(size);

    printf("Entrer le nom des noeuds :\n");
    for (int i = 0; i < graph->size; i++) {

        printf("Nom du noeud %d :\n", i);
        scanf("%s", graph->node[i]);
        (void) getchar();
    }

    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; ++j) {
            if (i != j && equalsString(graph->node[i], graph->node[j])) {
                fprintf(stderr, "Two nodes are equals");
                exit(EXIT_FAILURE);
            }
        }
    }

    printf("Entrer les arretes :\n");
    for (int y = 0; y < graph->size; y++) {
        for (int x = 0; x < graph->size; x++) {
            if (x != y) {
                printf("%s et %s ont une connexion ? (1=oui, 0=non)\n", graph->node[y], graph->node[x]);
                int r;
                scanf("%d", &r);
                if (r == 1) {
                    int p = NO_NEIGHBOUR;
                    printf("Entrer le poid :\n");
                    scanf("%d", &p);
                    graph->edge[y][x] = p;
                }
            }
        }
    }

    findDistance(graph);

    return graph;
}


Graph *createGraphWithFile(char filename[]) {

    FILE *file = fopen(filename, "r");
    if(file==NULL){
        perror("fopen()");
        exit(EXIT_FAILURE);
    }


    int c = 0;

    while(c!=EOF){

        c=getc(file);

        printf("%c", c);
    }


    fclose(file);

    return NULL;
}


Graph *createRandomGraph(int min, int max) {

    int randomValue = my_rand(min, max);

    Graph *graph = createGraph((unsigned int) randomValue);

    for (int i = 0; i < graph->size; i++) {
        strcpy(graph->node[i], "node");
        char numberNode[3];
        numberNode[0] = '_';
        numberNode[1] = (char) (i + 48);
        numberNode[2] = '\0';
        strcat(graph->node[i], numberNode);
    }

    for (int y = 0; y < graph->size; y++) {
        for (int x = 0; x < graph->size; x++) {
            int asEdge = my_rand(0, 1);
            if (!asEdge) {
                graph->edge[y][x] = NO_NEIGHBOUR;
            } else {
                graph->edge[y][x] = my_rand(1, 9);
            }

        }
    }

    findDistance(graph);

    return graph;
}


Graph *createRandomConnectivityGraph(int min, int max) {
    Graph *graph = createRandomGraph(min, max);

    while (!isConnectivityGraph(graph)) {
        destroyGraph(graph);
        graph = createRandomGraph(min, max);
    }

    return graph;
}


void printGraph(Graph *graph) {
    printf("Node : ");
    for (int i = 0; i < graph->size; i++) {
        printf("%s ", graph->node[i]);
    }
    printf("\n");
    printf("Edges :\n");
    printf("[\n");
    for (int y = 0; y < graph->size; y++) {
        printf(" [ ");
        for (int x = 0; x < graph->size; x++) {
            if (graph->edge[y][x] != NO_NEIGHBOUR) {
                printf("%d ", graph->edge[y][x]);
            } else {
                printf("+ ");
            }

        }
        printf("]\n");
    }
    printf("]\n");

    printf("\n");
    printf("Distances :\n");
    printf("[\n");
    for (int y = 0; y < graph->size; y++) {
        printf(" [ ");
        for (int x = 0; x < graph->size; x++) {
            if (graph->distance[y][x] != NO_ACCESS) {
                printf("%d ", graph->distance[y][x]);
            } else {
                printf("+ ");
            }

        }
        printf("]\n");
    }
    printf("]\n");
}


bool canIgo(Graph *graph, int s, int d, bool **mark) {
    assert((s >= 0) && (s < graph->size) && (d >= 0) && (d < graph->size));

    if (s == d) {
        return true;
    }

    if (mark[0] == NULL) {
        mark[0] = malloc(sizeof(bool) * graph->size);
        if (*mark == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < graph->size; ++i) {
            mark[0][i] = false;
        }
    }

    mark[0][s] = true;

    Vector *vector = neighbour(graph, s);

    for (unsigned int j = 0; j < vector->elementCount; ++j) {
        unsigned int v = *((unsigned int *) elementAtVector(vector, j));
        if (!mark[0][v]) {

            if (canIgo(graph, v, d, mark)) {
                allDestroyVector(vector);
                return true;
            }
        }
    }

    allDestroyVector(vector);
    return false;
}


bool isConnectivityGraph(Graph *graph) {

    if (isCompleteGraph(graph)) {
        return true;
    }

    for (int i = 0; i < graph->size; ++i) {
        for (int j = 0; j < graph->size; ++j) {
            bool **mark = malloc(sizeof(bool *));
            mark[0] = NULL;
            if (!canIgo(graph, i, j, mark)) {
                free(mark[0]);
                free(mark);
                return false;
            }
            free(mark[0]);
            free(mark);
        }
    }

    return true;
}


bool isCompleteGraph(Graph *graph) {

    int neighbour = 0;

    for (int i = 0; i < graph->size; ++i) {
        for (int j = 0; j < graph->size; ++j) {
            if ((i != j) && (graph->edge[i][j] != NO_NEIGHBOUR)) {
                neighbour++;
            }
        }
    }

    if (((graph->size - 1) * graph->size) == neighbour) {
        return true;
    }

    return false;
}


Vector *neighbour(Graph *graph, int n) {
    assert(n >= 0 && n < graph->size);

    Vector *vector = createVector();

    for (unsigned int i = 0; i < graph->size; i++) {
        if (graph->edge[n][i] != NO_NEIGHBOUR) {
            unsigned int *node = malloc(sizeof(unsigned int));
            *node = i;
            addElementVector(vector, node);
        }
    }

    return vector;
}

/*
 * a -> b
 */
int valueEdge(Graph *graph, int a, int b) {
    assert(a >= 0 && b >= 0 && a < graph->size && b < graph->size);

    return graph->edge[a][b];
}


Vector *dijkstra(Graph *graph, int a, int b) {
    assert((a >= 0) && (b >= 0) && (a < graph->size) && (b < graph->size));


    unsigned int label[graph->size];

    bool mark[graph->size];

    int parent[graph->size];
    for (int k = 0; k < graph->size; ++k) {
        parent[k] = -1;
    }

    /* label initialisation */
    for (int i = 0; i < graph->size; i++) {
        label[i] = (unsigned int) -1;
    }
    label[a] = 0;
    parent[a] = -1;

    /* mark initialisation */
    for (int i = 0; i < graph->size; i++) {
        mark[i] = false;
    }

    bool notMark = false;
    for (int m = 0; m < graph->size; m++) {
        if (!mark[m]) {
            notMark = true;
            break;
        }
    }

    /* run */
    while (notMark) {

        /* Selection of the smallest label and marking */
        unsigned int valLabel = (unsigned int) -1;
        unsigned int selectLabel = 0;
        for (unsigned int i = 0; i < graph->size; i++) {
            if (!mark[i] && (label[i] <= valLabel)) {
                valLabel = label[i];
                selectLabel = i;
            }
        }
        mark[selectLabel] = true;

        Vector *vector = neighbour(graph, selectLabel);

        for (unsigned int i = 0; i < vector->elementCount; i++) {
            unsigned int node = *((unsigned int *) elementAtVector(vector, i));
            int value = label[selectLabel] + valueEdge(graph, selectLabel, node);
            if (!mark[node] && (label[node] > value)) {
                label[node] = (unsigned int) value;
                parent[node] = selectLabel;
            }
        }

        allDestroyVector(vector);


        notMark = false;
        for (int m = 0; m < graph->size; m++) {
            if (!mark[m]) {
                notMark = true;
                break;
            }
        }
    }


    Vector *answer = createVector();

    int *destination = malloc(sizeof(int));
    if (destination == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    *destination = b;
    addElementVector(answer, destination);

    int node = parent[b];

    while (node >= 0) {

        int *nodeP = malloc(sizeof(int));
        if (nodeP == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
        *nodeP = node;
        addElementVector(answer, nodeP);

        node = parent[node];
    }


    if (*((int *) lastElementVector(answer)) != a) {
        allDestroyVector(answer);
        return NULL;
    }

    return answer;

}


void findDistance(Graph *graph) {
    for (int i = 0; i < graph->size; ++i) {
        for (int j = 0; j < graph->size; ++j) {
            Vector *vector = dijkstra(graph, i, j);
            if (vector == NULL) {
                graph->distance[i][j] = NO_ACCESS;
            } else {
                int somme = 0;
                for (int k = vector->elementCount - 1; k > 0; --k) {
                    int a = *((int *) vector->elementData[k]);
                    int b = *((int *) vector->elementData[k - 1]);
                    somme += valueEdge(graph, a, b);
                }
                graph->distance[i][j] = somme;
                allDestroyVector(vector);
            }
        }
    }
}


Vector *firstRouteSolution(Graph *graph, unsigned int v) {

    assert(v < graph->size);

    Vector *vector = createVector();
    vector->size = sizeof(unsigned int);

    bool mark[graph->size];

    /* mark initialisation */
    for (unsigned int i = 0; i < graph->size; i++) {
        mark[i] = false;
    }


    int select = v;

    unsigned int *pInt = malloc(sizeof(unsigned int));
    if (pInt == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    *pInt = v;

    addElementVector(vector, pInt);

    for (int i = 0; i < graph->size - 1; i++) {

        mark[select] = true;

        pInt = malloc(sizeof(unsigned int));
        if (pInt == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }

        int value = MAX_INT;

        for (unsigned int k = 0; k < graph->size; k++) {
            if (!mark[k]) {
                if (graph->distance[select][k] <= value) {
                    *pInt = k;
                    value = graph->distance[select][k];
                }
            }
        }


        addElementVector(vector, pInt);
        select = *pInt;
    }


    pInt = malloc(sizeof(unsigned int));
    if (pInt == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    *pInt = v;

    addElementVector(vector, pInt);

    assert(vector->elementCount == (graph->size + 1));

    return vector;
}

bool isCorrectPath(Vector *vector) {

    assert(vector->size == sizeof(int));

    if (vector->elementCount < 2) {
        return false;
    }

    int s = *((int *) elementAtVector(vector, 0));
    int d = *((int *) elementAtVector(vector, vector->elementCount - 1));

    if (s != d) {
        return false;
    }

    for (int i = 0; i < vector->elementCount - 1; i++) {
        for (int j = 0; j < vector->elementCount - 1; ++j) {
            if (i != j) {
                int a = *((int *) elementAtVector(vector, (unsigned int) j));
                int b = *((int *) elementAtVector(vector, (unsigned int) i));
                if (a == b) {
                    return false;
                }
            }
        }
    }
    return true;
}


Vector *baseConverter(unsigned int b, int n) {

    Vector *vector = createVector();
    vector->size = sizeof(int);


    while (n >= b) {
        int *rest = malloc(sizeof(int));
        if (rest == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
        rest[0] = n % b;
        addElementVector(vector, rest);
        n = n / b;
    }

    int *pInt = malloc(sizeof(int));
    if (pInt == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    pInt[0] = n;
    addElementVector(vector, pInt);


    Vector *number = createVector();
    number->size = sizeof(int);


    for (int i = (vector->elementCount - 1); i >= 0; i--) {
        addElementVector(number, elementAtVector(vector, (unsigned int) i));
    }

    destroyVector(vector);

    return number;
}


unsigned int myPow(unsigned int n, unsigned int p) {
    if (p == 0) {
        return 1;
    }
    return n * myPow(n, p - 1);
}

Vector *secondRouteSolution(Graph *graph, unsigned int v) {
    assert(v < graph->size);

    Vector *path = createVector();

    unsigned int maxNumber = 0;
    for (int p = graph->size - 2; p >= 0; p--) {
        maxNumber += myPow(graph->size, (unsigned int) p) * (graph->size - 1);
    }

    unsigned int minNumber = myPow(graph->size, (unsigned int) graph->size - 2);

    /* construction des chemins possible */
    for (unsigned int j = minNumber; j <= maxNumber; ++j) {
        Vector *base = baseConverter(graph->size, j);

        int *pInt = NULL;

        Vector *numberPath = createVector();
        numberPath->size = base->size;


        pInt = malloc(sizeof(int));
        if (pInt == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
        *pInt = v;
        addElementVector(numberPath, pInt);


        if (base->elementCount == graph->size - 2) {
            pInt = malloc(sizeof(int));
            if (pInt == NULL) {
                perror("malloc()");
                exit(EXIT_FAILURE);
            }
            *pInt = 0;
            addElementVector(numberPath, pInt);
        }


        for (unsigned int i = 0; i < base->elementCount; ++i) {
            addElementVector(numberPath, elementAtVector(base, i));
        }

        destroyVector(base);

        pInt = malloc(sizeof(int));
        if (pInt == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
        *pInt = v;
        addElementVector(numberPath, pInt);


        if (isCorrectPath(numberPath)) {
            addElementVector(path, numberPath);
        } else {
            allDestroyVector(numberPath);
        }
    }

    /* recherche du meilleur chemein */
    int bestSize = 2147483647;
    Vector *bestPath = NULL;

    for (unsigned int i = 0; i < path->elementCount; ++i) {
        Vector *select = elementAtVector(path, i);

        int size = calculatePathSize(graph, select);
        if (bestSize >= size) {
            bestSize = size;
            bestPath = select;
        }
    }

    for (unsigned int f = 0; f < path->elementCount; f++) {
        Vector *select = elementAtVector(path, f);
        if (select != bestPath) {
            allDestroyVector(select);
        }
    }


    assert(bestPath != NULL);

    destroyVector(path);

    return bestPath;
}


int calculatePathSize(Graph *graph, Vector *vector) {
    assert(vector->size == sizeof(unsigned int));

    int somme = 0;

    for (unsigned int i = 0; i < vector->elementCount - 1; i++) {
        unsigned int n = *((unsigned int *) elementAtVector(vector, i));
        unsigned int nn = *((unsigned int *) elementAtVector(vector, i + 1));

        somme += graph->distance[n][nn];
    }

    return somme;
}


Vector *findOptimalPath(Graph *graph, unsigned int v) {

    assert(v >= 0 && v < graph->size);

    Vector *solution = createVector();

    register int sizeE = graph->size - 1;
    int ensemble[sizeE];

    int count = 0;
    for (unsigned int i = 0; i < graph->size; i++) {
        if (i != v) {
            ensemble[count] = i;
            count++;
        }
    }

    Arrangement *arrangement = buildArrangement(ensemble, sizeE, sizeE);


    register unsigned int bestSize = (unsigned int) -1;
    for (unsigned int y = 0; y < arrangement->nbArr; y++) {

        Vector *path = createVector();
        path->size = sizeof(unsigned int);

        int *init = malloc(sizeof(unsigned int));
        if (init == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
        init[0] = v;
        addElementVector(path, init);

        for (unsigned int x = 0; x < arrangement->k; x++) {
            unsigned int *pInt = malloc(sizeof(unsigned int));
            if (pInt == NULL) {
                perror("malloc()");
                exit(EXIT_FAILURE);
            }

            pInt[0] = (unsigned int) arrangement->arr[y][x];

            addElementVector(path, pInt);
        }

        init = malloc(sizeof(unsigned int));
        if (init == NULL) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
        init[0] = v;
        addElementVector(path, init);

        register int size = calculatePathSize(graph, path);
        if (size < bestSize) {
            allDestroyVector(solution);
            bestSize = (unsigned int) size;
            solution = path;
        } else {
            allDestroyVector(path);
        }
    }

    destroyArrangement(arrangement);

    return solution;
}


void destroyGraph(Graph *graph) {

    for (int i = 0; i < graph->size; i++) {
        free(graph->node[i]);
        graph->node[i] = NULL;
    }

    free(graph->node);
    graph->node = NULL;

    for (int i = 0; i < graph->size; i++) {
        free(graph->edge[i]);
        graph->edge[i] = NULL;
    }
    free(graph->edge);

    for (int i = 0; i < graph->size; i++) {
        free(graph->distance[i]);
        graph->distance[i] = NULL;
    }
    free(graph->distance);

    free(graph);
}

