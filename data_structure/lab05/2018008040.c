#include<stdio.h>
#include<stdlib.h>

#define MAX_NUM 10000 //limit number
#define NODE_NUM 100 // max node 

FILE *fin;
FILE *fout;

typedef struct ThreadedTree* ThreadedPtr;
typedef int ElementType;

struct ThreadedTree { // struct definition
	int left_thread;
	ThreadedPtr left_child;
	ElementType data;
	ThreadedPtr right_child;
	int right_thread;
}ThreadedTree;

ThreadedPtr thtrArray[NODE_NUM]; // struct array for insert

ThreadedPtr CreateTree();
ThreadedPtr InPred(ThreadedPtr tree);
ThreadedPtr InSucc(ThreadedPtr tree);

int Insert(ThreadedPtr root, int root_idx, ElementType data, int idx);
void printInorder(ThreadedPtr root);
void DeleteTree(ThreadedPtr root);

int main(int argc, char *argv[]) {
    fin=fopen(argv[1], "r");
    fout=fopen(argv[2], "w");
    
    ThreadedPtr root = CreateTree();

    int NUM_NODES;
    fscanf(fin, "%d", &NUM_NODES);
    if(NUM_NODES > MAX_NUM) { // if number is of the limit
        fprintf(fout, "Number out of range!\n");
        return 0;
    }
    int root_idx=0, idx=0;

    while(++idx <= NUM_NODES){
        ElementType data;
        fscanf(fin, "%d", &data);

        if(Insert(root, root_idx, data, idx) == 0) {
            return 0;
        }
    }

    printInorder(root);
    DeleteTree(root);

    fclose(fin);
    fclose(fout);

    return 0;
}

ThreadedPtr CreateTree(){
    ThreadedPtr tree = NULL;
    tree = (ThreadedPtr)malloc(sizeof(ThreadedTree));
    if(tree==NULL){
        fprintf(fout, "Out of Space!\n");
        return NULL;
    }
    tree->data = -1;
    tree->left_thread = 1;
    tree->left_child = tree;
    tree->right_thread = 1;
    tree->right_child = tree;
    return tree;
}
int my_pow(int a) {// function to operate power of interger
    int result = 1;
    for(int i =0;i<a;i++) {
        result*=2;
    }
    return result;
}
 

int Insert(ThreadedPtr root, int root_idx, ElementType data, int idx) {
    int level,index;
    index = idx;
    ThreadedPtr tmp;
    tmp = (ThreadedPtr)malloc(sizeof(ThreadedTree));
    if(tmp==NULL){ 
        fprintf(fout, "Out of Space!\n");
        return 0;
    }
    for(int i=1;;i++){ // calculate level of the node
        if(index<my_pow(i)){
        level = i;
        break;
        }
    }
    if(index==1){ // if index is 1
        root->right_thread=0;
        root->right_child=tmp;
        tmp->left_thread=1;
        tmp->left_child=root;
        tmp->right_thread=1;
        tmp->right_child=root;
    }
    else{
        if(index%2 == 0){ // if index is left child
            thtrArray[index/2]->left_thread=0;
            thtrArray[index/2]->left_child=tmp;
            tmp->left_thread=1;
            tmp->right_thread=1;
            if(index != my_pow(level)){ // if node is not at left side
                tmp->left_child=InSucc(thtrArray[index-1]);//Successor of index-1 is left child
            }
            else{
                tmp->left_child=root;
            }
            tmp->right_child=thtrArray[index/2];
        }
        else{// if index is right child
            thtrArray[index/2]->right_thread=0;
            thtrArray[index/2]->right_child=tmp;
            tmp->left_thread=1;
            tmp->right_thread=1;
            if(index != my_pow(level)-1){ // if node is not at right side
                int div = index;
                while(div %2 ==1) { // until node is parent's right child
                    div = div/2;
                }    
                tmp->right_child=thtrArray[div/2];
            }
            else{
                tmp->right_child=root;
            }
            tmp->left_child=thtrArray[index/2];
        }
    }
    tmp->data = data;
    thtrArray[index] = tmp;
    return index;
}

void printInorder(ThreadedPtr root) {
    ThreadedPtr tmp = root;
    if(tmp==NULL){
        fprintf(fout, "Out of Space!\n");
    }
    fprintf(fout,"inorder traversal :");
    for(;;){
        tmp = InSucc(tmp); //inorder traversal order
        if(tmp == root) break;
        fprintf(fout, " %d",tmp->data);
    }
    fprintf(fout,"\n");
}
void DeleteTree(ThreadedPtr root) {
    ThreadedPtr tmp = root;
    if(tmp==NULL){
        fprintf(fout, "Out of Space!\n");
    }
    for(;;) {
        ThreadedPtr suc = InSucc(tmp);
        free(tmp);
        tmp = suc;
        if(tmp==root) break;
    }
}
ThreadedPtr InPred(ThreadedPtr tree) { // function that returns Predessor
    ThreadedPtr tmp;
    tmp = tree->left_child;
    if(!tree->left_thread){
        while(!tmp->right_thread){
            tmp = tmp->right_child;
        }
    }
    return tmp;
}
ThreadedPtr InSucc(ThreadedPtr tree) { // function that returns Successor
    ThreadedPtr tmp;
    tmp = tree->right_child;
    if(!tree->right_thread){
        while(!tmp->left_thread){
            tmp = tmp->left_child;
        }
    }
    return tmp;
}
