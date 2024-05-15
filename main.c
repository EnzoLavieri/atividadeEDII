#include <stdio.h>
#include <stdlib.h>

typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct Graph {
    int numVertices;
    AdjList* array;
    int isDirected;
} Graph;

AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices, int isDirected) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->isDirected = isDirected;
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));

    for (int i = 0; i < numVertices; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    if (!graph->isDirected) {
        newNode = newAdjListNode(src);
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
    }
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Lista de adjacencia do vertice %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int menu() {
    int choice;
    printf("Escolha o tipo de grafo:\n");
    printf("1. Grafo nao dirigido\n");
    printf("2. Grafo dirigido\n");
    printf("Escolha: ");
    scanf("%d", &choice);
    return choice;
}

int main() {
    int numVertices, isDirected, src, dest, choice;
    printf("Digite o numero de vertices: ");
    scanf("%d", &numVertices);

    isDirected = menu() - 1; 
    Graph* graph = createGraph(numVertices, isDirected);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar aresta\n");
        printf("2. Imprimir grafo\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite a origem da aresta: ");
                scanf("%d", &src);
                printf("Digite o destino da aresta: ");
                scanf("%d", &dest);
                addEdge(graph, src, dest);
                break;
            case 2:
                printGraph(graph);
                break;
            case 3:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Escolha invalida! Tente novamente.\n");
        }
    }

    return 0;
}
