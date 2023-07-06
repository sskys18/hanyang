#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fin;
FILE *fout;

typedef struct _Queue
{
    int* key;
    int first, rear, qsize, max_queue_size;
}Queue;

typedef struct _Graph
{
    int size;
    int* node;
    int* inDegree;
    int** matirx;
}Graph;

Graph* CreateGraph(int* node, int n);
void InsertEdge(Graph* G, int a, int b);
void PrintGraph(Graph* G);
void DeleteGraph(Graph* G);
void Topsort(Graph* G);
Queue* MakeNewQueue(int x);
int IsEmpty(Queue* Q);
int Dequeue(Queue* Q);
void Enqueue(Queue* Q, int x);
void DeleteQueue(Queue* Q);
void countInput(int* n, char* str);
void parseInput(int* arr, char* str, int n);

int main(int argc, char* argv[]){
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    char numbers[100], inputs[150];
    fgets(numbers, 100, fin);
    int n = 0;
    countInput(&n, numbers);
    int* nodes = (int*)malloc(sizeof(int)*n);
    parseInput(nodes, numbers, n);

    Graph* G = CreateGraph(nodes, n);

    fgets(inputs, 100, fin);
    int len = strlen(inputs), i, j;
    for(i = 0; i<len;i += 4){
        int a = inputs[i] - '0', b = inputs[i+2] - '0';
        InsertEdge(G, a, b);
    }
    
    PrintGraph(G);
    Topsort(G);
    DeleteGraph(G);

    fclose(fin);
    fclose(fout);

    return 0;
}

Graph* CreateGraph(int* node, int n){
    Graph* G = malloc(sizeof(Graph));
    G->size = n;
    G->node = node;
    G->inDegree = (int*)malloc(sizeof(int)*n);
    G->matirx = (int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++){
        *(G->matirx + i) = (int*)malloc(sizeof(int)*n);
    }
    return G;
}
void InsertEdge(Graph* G, int a, int b){
    int cnta,cntb;
    for(cnta=0;cnta<G->size;cnta++){
        if(a == G->node[cnta]) break;
    }
    for(cntb=0;cntb<G->size;cntb++){
        if(b == G->node[cntb]) break;
    }
    G->matirx[cnta][cntb] = 1;
    G->inDegree[cntb]++;
}
void PrintGraph(Graph* G){
    for (int i = 0; i < G->size+1; i++)
    {
        for (int j = 0; j < G->size+1; j++)
        {
            if(i==0){
                if(j==0){
                    fprintf(fout, "   ");
                }
                else fprintf(fout, "%d  ",G->node[j-1]);
            }
            else{
                if(j==0) fprintf(fout, "%d  ",G->node[i-1]);
                else fprintf(fout, "%d  ",G->matirx[i-1][j-1]);
            }       
        }
        fprintf(fout, "\n");
    }
    
}
void DeleteGraph(Graph* G){
    free(G->node);
    free(G->matirx);
    free(G);
}
void Topsort(Graph* G){
    int* result = (int*)malloc(sizeof(int)*G->size);
    Queue* q = MakeNewQueue(G->size);
    for(int i=0;i<G->size;i++){
        if(G->inDegree[i] == 0) Enqueue(q, G->node[i]);
    }
    for(int i=0;i<G->size;i++){
        if(q->first == q->rear){
            fprintf(fout, "sorting error : cycle!");
            return;
        }
        int x= Dequeue(q);
        int cnt =0;
        result[i] = x;

        for(int k=0;k<G->size;k++){
            if(result[i] == G->node[k]){
                cnt = i;
                break;
            }
        }

        for(int j=0;j<G->size;j++){
            if(G->matirx[cnt][j] == 1){
                G->matirx[cnt][j] = 0;  
                if(--G->inDegree[j] == 0) Enqueue(q, G->node[j]);
            }
        }
    }
    for(int i =0;i<G->size;i++){
        fprintf(fout,"%d ",result[i]);
    }
    fprintf(fout, "\n");
}
Queue* MakeNewQueue(int x){
    Queue* q = malloc(sizeof(Queue));
    q->first = 0;
    q->rear = -1;
    q->max_queue_size = x;
    q->qsize = 0;
    q->key = malloc(sizeof(int)*x);
    return q;
}
int IsEmpty(Queue* Q){
    if(Q->qsize == 0){
        fprintf(fout, "Queue is empty!");
        return 1;
    }
    else return 0;
}
int Dequeue(Queue* Q){
    if(IsEmpty){
        return 0;
    }
    else{
        Q->qsize--;
        Q->first = Q->first + 1;
        return Q->key[Q->first];
    }
}
void Enqueue(Queue* Q, int x){
    if(Q->qsize == Q->max_queue_size){
        fprintf(fout, "Queue is full!");
        return;
    }
    else{
        Q->qsize++;
        Q->rear = Q->rear + 1;
        Q->key[Q->rear] = x;
    }
    return;
}
void DeleteQueue(Queue* Q){
    free(Q->key);
    free(Q);
}
void countInput(int* n, char* str){
    int len = strlen(str), i;
    for(i = 0; i<len;i++){
        if(0 <= str[i] - '0' && str[i] - '0' < 10) (*n)++;
    }
}
void parseInput(int* arr, char* str, int n){
    int len = strlen(str), i;
    int cnt = 0;
    for(i = 0; i<len;i++){
        if(0 <= str[i] - '0' && str[i] - '0' < 10) arr[cnt++] = str[i] - '0';
    }
}
