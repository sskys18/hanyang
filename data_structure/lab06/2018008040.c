#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

typedef struct BST* Tree;
typedef struct BST{
    int value;
    struct BST* left;
    struct BST* right;
}BST;

Tree insertNode(Tree root, int key);
Tree deleteNode(Tree root, int key);
int findNode(Tree root, int key);
void printInorder(Tree root);
void deleteTree(Tree root);
Tree minNode(Tree root);//function that returns node that has smallest value
Tree min; //minnode

void main(int argc, char* argv[]){
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");
    char cv;
    int key;
    
    Tree root = NULL;

    while(!feof(fin)){
        min=minNode(root); //define node that has minium value of root
        fscanf(fin, "%c", &cv);
        switch(cv){
            case 'i':
                fscanf(fin,"%d",&key);
                if(findNode(root,key))
                    fprintf(fout, "insertion error: %d is already in the tree\n", key);//error message if value is already exist in the tree
                else{
                    root = insertNode(root, key);
                    fprintf(fout, "insert %d\n", key);
                }
                break;
            case 'f':
                fscanf(fin,"%d",&key);
                if(findNode(root,key))
                    fprintf(fout, "%d is in the tree\n", key);
                else
                    fprintf(fout, "finding error: %d is not in the tree\n", key);
                break;
            case 'd':
                fscanf(fin, "%d", &key);
                if(findNode(root, key)){
                        root = deleteNode(root,key);
                        fprintf(fout, "delete %d\n", key);
                }
                else{
                    fprintf(fout, "deletion error: %d is not in the tree\n", key);
                }
                break;
            case 'p':
                fscanf(fin, "%c", &cv);
                if(cv == 'i'){
                    if(root == NULL){
                        fprintf(fout, "tree is empty");
                    }
                    else{
                        fprintf(fout, "%d", min->value); //print minium value of the tree
                        printInorder(root);
                    }
                }
                fprintf(fout, "\n");
                break;
        }
    }
    deleteTree(root);
    fclose(fin);
    fclose(fout);
}

Tree insertNode(Tree root, int key) {
    if(root == NULL){
        root = (Tree) malloc(sizeof(struct BST)); //initialize the root
        if(root == NULL){
            fprintf(fout, "Out of space!");
            return NULL;
        }
        root->value = key;
        root->left = root-> right = NULL;
    }
    else if(key < root->value){ // if key is less than root value go to left side
        root->left = insertNode(root->left, key);
    }
    else if(key > root->value){ // if key is more than root value go to right side
        root->right = insertNode(root->right, key);
    }
}

Tree deleteNode(Tree root, int key) {
    if(key < root->value){// first find the node that has value
        root->left = deleteNode(root->left, key); 
    }
    else if(key > root->value){
        root->right = deleteNode(root->right, key);
    }
    else {
        Tree tmp;
        if(root->left == NULL){ //when found node has 1 or 0 child
            tmp = root->right;
            free(root);
            return tmp;
        }
        else if(root->right == NULL){
            tmp = root->left;
            free(root);
            return tmp;
        }
        tmp = minNode(root->right); // when found node has 2 child
        root->value = tmp->value;
        root->right = deleteNode(root->right, tmp->value);
    }
    return root;
}



int findNode(Tree root, int key) { // function that returns boolean value if exists return 1, doesn't exist return 0
    if(root == NULL){
        return 0;
    }
    if(key < root->value){
        return findNode(root->left, key);
    }
    else if(key > root->value){
        return findNode(root->right, key);
    }
    else if(key == root->value){
        return 1;
    }
    else{
        return 0;
    }

}

void printInorder(Tree root){
    if(root == NULL) return;
    printInorder(root->left);
    if(root->value != min->value) fprintf(fout, " %d", root->value); //if value is not minimum value print " d"
    else return;
    printInorder(root->right);
}

void deleteTree(Tree root) {//delete all nodes of tree
    if(root == NULL)
        return;
    if(root->left != NULL)
        deleteTree(root->left);
    if(root->right != NULL)
        deleteTree(root->right);
    free(root);
    return;
}

Tree minNode(Tree root) {
    if(root == NULL) return root;
    if(root->left == NULL){
        return root;//returns node that has minimun value of the tree
    }
    return minNode(root->left);
}
