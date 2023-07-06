#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 1e9
 
FILE * fin;
FILE * fout;
 
typedef struct Node {
    int vertex;
    int dist;
    int prev;
} Node;
 
typedef struct Graph {
    int size;
    int ** vertices;
    Node * nodes;
} Graph;
 
typedef struct Heap {
   int size;
   int Capacity;
   Node * Element;
} Heap;
 
Graph * createGraph(int size);
void deleteGraph(Graph * g);
void printShortestPath(Graph * g);
Heap * createMinHeap(int heapsize);
void deleteMinHeap(Heap * minHeap);
void insertToMinHeap(Heap * minHeap, int vertex, int distance);
Node deleteMin(Heap * minHeap);

void main(int argc, char * argv[]) {
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");
    
    Graph * g;
    int size;
    fscanf(fin, "%d\n", &size);
    g = createGraph(size + 1);
    
    char tmp = 0;
    while (tmp != '\n' && tmp != EOF) {
        int node1, node2, weight;
        fscanf(fin, "%d-%d-%d", &node1, &node2, &weight);
        g->vertices[node1][node2] = weight;
        tmp = fgetc(fin);
    }
    
    printShortestPath(g);
    
    deleteGraph(g);
}

Graph * createGraph(int size) {
    Graph * g = (Graph *)malloc(sizeof(Graph));
    g->size = size;
    g->vertices = (int **)malloc(sizeof(int *) * size);
    g->nodes = (Node *)malloc(sizeof(Node) * size);
    
    for (int i = 0; i < size; i++) {
        g->vertices[i] = (int *)malloc(sizeof(int) * size);
        g->nodes[i].vertex = i;
        g->nodes[i].dist = INF;
        g->nodes[i].prev = -1;
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            g->vertices[i][j] = INF;
        }
    }
    
    return g;
}

void deleteGraph(Graph * g) {
    free(g->vertices);
    free(g->nodes);
    free(g);
}

void printShortestPath(Graph * g) {
    Heap * h = createMinHeap(g->size);
    g->nodes[1].dist = 0;
    insertToMinHeap(h, 1, 0);
    
    while (h->size != 0) {
        Node node = deleteMin(h);
        int vertex = node.vertex;
        int distance = node.dist;
        
        for (int i = 1; i < g->size; i++) {
            if (g->vertices[vertex][i] != INF) {
                if (g->nodes[i].dist > distance + g->vertices[vertex][i]) {
                    g->nodes[i].dist = distance + g->vertices[vertex][i];
                    g->nodes[i].prev = vertex;
                    insertToMinHeap(h, i, g->nodes[i].dist);
                }
            }
        }
    }
    
    for (int i = 2; i < g->size; i++) {
        if (g->nodes[i].dist == INF) {
            fprintf(fout, "can not reach to node %d\n", i);
        }
        else {
            int* prevs = (int*)malloc(sizeof(int)*g->size);
            prevs[1] = i;
            int cnt = 1;
            int prev = g->nodes[i].prev;
            
            while (prev != -1) {
                prevs[++cnt] = prev;
                prev = g->nodes[prev].prev;
            }
            fprintf(fout, "%d",prevs[cnt]);
            for(int j=1;j<cnt;j++){
                fprintf(fout, "->%d", prevs[cnt-j]);
            }
            fprintf(fout, " : (cost : %d)\n", g->nodes[i].dist);
        }
   }
    
    deleteMinHeap(h);
}

Heap * createMinHeap(int heapsize) {
    Heap * minHeap = (Heap *)malloc(sizeof(Heap));
    minHeap->size = 0;
    minHeap->Capacity = heapsize;
    minHeap->Element = (Node *)malloc(sizeof(Node) * minHeap->size);
    
    return minHeap;
}

void deleteMinHeap(Heap * minHeap) {
    free(minHeap->Element);
    free(minHeap);
}

void insertToMinHeap(Heap * minHeap, int vertex, int distance) {
    int i = ++minHeap->size;
    
    while ((i != 1) && (distance < minHeap->Element[i / 2].dist)) {
        minHeap->Element[i] = minHeap->Element[i / 2];
        i /= 2;
    }
    
    minHeap->Element[i].vertex = vertex;
    minHeap->Element[i].dist = distance;
}
 Node deleteMin(Heap * minHeap) {
    int parent, child;
    Node n, tmp;
   
    n = minHeap->Element[1];
    tmp = minHeap->Element[minHeap->size--];
    parent = 1;
    child = 2;
    
    while (child <= minHeap->size) {
        if ((child < minHeap->size) && (minHeap->Element[child].dist) > minHeap->Element[child + 1].dist) {
            child++;
        }
        if (tmp.dist <= minHeap->Element[child].dist) {
            break;
        }
        
        minHeap->Element[parent] = minHeap->Element[child];
        parent = child;
        child *= 2;
    }
    
    minHeap->Element[parent] = tmp;
    return n;
}
