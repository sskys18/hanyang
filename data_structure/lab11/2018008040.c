#include <stdlib.h>
#include <stdio.h>
#define INF 1e9

FILE *fin;
FILE *fout;

typedef struct HeapStruct{
    int Capacity;
    int Size;
    int *Elements;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap *heap, int value);
int Find(Heap *heap, int value);
int DeleteMax(Heap *heap);
void PrintHeap(Heap *heap);
int IsFull(Heap *heap);

int main(int argc, char *argv[]){
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    char cv;
    Heap* maxHeap;
    int heapSize, key, max_element;

    while(!feof(fin)){
        fscanf(fin, "%c", &cv);
        switch (cv)
        {
        case 'n':
            fscanf(fin, "%d", &heapSize);
            maxHeap = CreateHeap(heapSize);
            break;
        case 'i':
            fscanf(fin, "%d", &key);
            Insert(maxHeap, key);
            break;
        case 'd':
            max_element = DeleteMax(maxHeap);
            if(max_element != -INF){
                fprintf(fout, "max_element : %d deleted\n", max_element);
            }
            break;
        case 'p':
            PrintHeap(maxHeap);
            break;
        case 'f':
            fscanf(fin, "%d", &key);
            if(Find(maxHeap, key)) fprintf(fout, "%d is in the heap\n", key);
            else fprintf(fout, "finding error : %d is not in the heap\n", key);
            break;
        
        }
    }
    return 0;
}

Heap* CreateHeap(int heapsize){
    Heap* heap = (Heap *)malloc(sizeof(Heap)); //create heap object
    if(heap == NULL){
        fprintf(fout,"Out of space!\n");
        return NULL;
    }
    heap->Capacity = heapsize+1; //set capacity to heapsize + 1 because we don't use index 0
    heap->Size = 0; // total number in arraay
    heap->Elements = (int*) malloc(heap->Capacity*sizeof(int)); //create array
    if(heap->Elements == NULL){
        fprintf(fout,"Out of space!\n");
        return NULL;
    }
    return heap;
}
void Insert(Heap *heap, int value){
    
    int i;
    i = ++heap->Size; //increase heap size
    if(IsFull(heap)){ //if heap is full
        fprintf(fout, "insert error : heap is full\n");
        --heap->Size;
        return;
    }
    for(int j=1;j<=heap->Size;j++){
        if(heap->Elements[j] == value){ //already in the heap
            fprintf(fout, "insert error : %d is already in the heap\n", value);
            --heap->Size;
            return;
        }
    }
    while( i!= 1 && value > heap->Elements[i/2]){ //while insert value is larger than parent value
        
        heap->Elements[i] = heap->Elements[i/2]; //swap parent and child
        i /= 2;
    }
    heap->Elements[i] = value;
    fprintf(fout, "insert %d\n", value);
}
int Find(Heap *heap, int value){
    for(int i=0;i<heap->Size;i++){
        if(heap->Elements[i] == value) return 1;
    }
    return 0;
}
int DeleteMax(Heap *heap){
    int parent, child;
    int min_element, last_element;
    if(heap->Size == 0){ //heap is empty
        fprintf(fout, "delete error : heap is empty\n");
        return -INF;
    }

    min_element = heap->Elements[1]; //min value of heap
    last_element = heap->Elements[heap->Size--]; //max value of heap

    parent = 1;
    child  = 2;
    while(child <= heap->Size){
        if((child < heap->Size) && ((heap->Elements[child] < heap->Elements[child+1]))){ //pick larger one between left child and right child
            child++; //choose right child
        }
        if(last_element >= heap->Elements[child]) break; //if last node is larger than child node
        heap->Elements[parent] = heap->Elements[child]; // swap parent and child node
        parent = child; //one level down
        child *= 2;
    }
    heap->Elements[parent] = last_element; //put last node into right place

    return min_element; //return max value
}
void PrintHeap(Heap *heap){
    if(heap->Size == 0){
        fprintf(fout, "print error : heap is empty\n");
        return;
    }
    for(int i=1;i<=heap->Size;i++){
        fprintf(fout, "%d ",heap->Elements[i]);
    }
    fprintf(fout, "\n");
}
int IsFull(Heap *heap){
    if(heap->Capacity <= heap->Size) return 1; //if heap is full
    else return 0;
}
