#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

typedef struct AVLNode{
    ElementType element;
    AVLTree left,right;
    int height;
}AVLNode;

AVLTree Insert(ElementType x, AVLTree T);
AVLTree Delete(ElementType x, AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
void PrintInorder(AVLTree T);
void DeleteTree(AVLTree T);
int max(int a, int b); //return max value between a and b
int diff(AVLTree T); //calculate height differences between left and right child
AVLTree minNode(AVLTree T); //find node of the tree that has minimum value of T
int height(AVLTree T);//returns height of the tree

int main(int argc, char *argv[]){
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");
    AVLTree Tree = NULL;
    char cv;
    int key;

    while(!feof(fin)){
        fscanf(fin, "%c", &cv);
        switch(cv){
            case 'i':
                fscanf(fin, "%d\n", &key);
                Tree = Insert(key, Tree);
                break;
            case 'd':
                fscanf(fin, "%d\n", &key);
                Tree = Delete(key, Tree);
                break;
        }
        PrintInorder(Tree);
        fprintf(fout, "\n");
    }
    DeleteTree(Tree);
    fclose(fin);
    fclose(fout);

    return 0;
}

AVLTree Insert(ElementType x, AVLTree T){
    if(T == NULL) { //initialize T
        T = malloc(sizeof(struct AVLNode));
        if(T == NULL) fprintf(fout, "Out of Space!!!");
        T->element = x;
        T->height = 0;
        T->left = T->right = NULL;
    }
    else if(x < T->element) {
        T->left = Insert(x, T->left);
        if(diff(T) >= 2){
            if(x < T->left->element){ //LL
                T = SingleRotateWithLeft(T);
            }
            else T = DoubleRotateWithLeft(T); //LR
        }
    }
    else if(x >T->element) {
        T->right = Insert(x, T->right);
        if(diff(T) <= -2){
            if(x > T->right->element){ //RR
                T = SingleRotateWithRight(T);
            }
            else T = DoubleRotateWithRight(T); //RL
        }
     }
    else{
        fprintf(fout,"insertion error : %d is already in the tree!\n", x); // x is already in the tree
        return T;
    }
    T->height = max(height(T->left), height(T->right)) + 1; // determine height of thetree
    return T;
}
AVLTree Delete(ElementType x, AVLTree T) {
    if(T == NULL){ // x is not in the tree
        fprintf(fout, "deletion error : %d is not in the tree!\n",x);
        return T;
    }
    else if(x < T->element){//find node that has x element
        T->left = Delete(x, T->left);
    }
    else if(x > T->element){
        T->right = Delete(x, T->right);
    }
    else{
        AVLTree tmp;
        if(T->left == NULL){ // if node has 1 or 0 child
            tmp = T->right;
            free(T);
            return tmp;
        }
        else if(T->right == NULL){
            tmp = T->left;
            free(T);
            return tmp;
        }
        tmp = minNode(T->right); // node has 2 child
        T->element = tmp->element;
        T->right = Delete(T->element, T->right);
    }
    if(T == NULL) return T;
    T->height = max(height(T->left), height(T->right)) + 1; //determine height of the tree

    if(diff(T) > 1){
        if(x < T->left->element){ //LL
            T = SingleRotateWithLeft(T);
        }
        else T = DoubleRotateWithLeft(T); //LR
    }
    else if(diff(T) < -1){
        if(x > T->right->element){ //RR
            T = SingleRotateWithRight(T);
        }
        else T = DoubleRotateWithRight(T); //LL
    }
    return T;
}

Position SingleRotateWithLeft(Position node){ //LL
    Position tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    node->height = max(height(node->left), height(node->right)) + 1;
    tmp->height = max(height(tmp->left) ,height(tmp->right)) + 1;

    return tmp;
}
Position SingleRotateWithRight(Position node){ //RR
    Position tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    node->height = max(height(node->left), height(node->right)) + 1;
    tmp->height = max(height(tmp->right), height(tmp->right)) + 1;

    return tmp;
}

Position DoubleRotateWithLeft(Position node){ //LR
    node->left = SingleRotateWithRight(node->left);
    return SingleRotateWithLeft(node);
}
Position DoubleRotateWithRight(Position node){ //RL
    node->right = SingleRotateWithLeft(node->right);
    return SingleRotateWithRight(node);
}
void PrintInorder(AVLTree T){
    if(T == NULL) return;
    PrintInorder(T->left);
    fprintf(fout, "%d(%d) ",T->element,T->height);
    PrintInorder(T->right);
}
void DeleteTree(AVLTree T){
    if(T == NULL) return;
    if(T->left != NULL) DeleteTree(T->left);
    if(T->right != NULL) DeleteTree(T->right);
    free(T);
    return;
}
int max(int a, int b){
    if(a >= b) return a;
    else return b;
}
int diff(AVLTree T){
    if(T == NULL) return 0;
    else return (height(T->left) - height(T->right));
}
AVLTree minNode(AVLTree T){
    if(T == NULL) return T;
    if(T->left == NULL) return T;
    return minNode(T->left);
}
int height(AVLTree T){
    if(T == NULL) return -1; //if T is null return -1 as height
    return T->height;
}
