#include <stdio.h>
#include <stdlib.h>

FILE *fin;
FILE *fout;

#define false 0
#define true 1

typedef struct BNode* BNodePtr;

struct BNode{
    int is_leaf; // is_leaf여부 
    int is_root;
    int *key; // key를 담을 배열
    int cnt_key; // 키 개수 확인용
    BNodePtr *child; // 자식 포인터배열 (노드들이 배열로)
    int cnt_child; // 자식 개수 확인용
    int order; //차수
}BNode;


BNodePtr root; // root 노드 기본 설정(포인터로)
// 검색하는 함수
int Find(BNodePtr node, int val){
    BNodePtr level = node;
    while (true){
        int pos;
        for (pos=0; pos<level->cnt_key; pos++){
            if (val== level->key[pos]){
                return 1;
            }
            else if (val<level->key[pos]){
                break;
            }
        }
        if (level->is_leaf) break;
        level = level->child[pos];
    }
    return 0;
}

// 포인터로 노드를 만들었고, 그걸 CreateTree라고 명명했다. 받아오는 값은 '차수'.
BNodePtr CreateTree(int order){ 
    BNodePtr newNode; // 새로운 node 구조체 선언
    newNode = (BNodePtr)malloc(sizeof(struct BNode)); // node에 동적할당
    newNode -> child = (BNodePtr*)malloc(sizeof(BNodePtr)*(order+1));
    for(int i=0;i<order+1;i++) newNode->child[i] = NULL;
    newNode -> key = (int*)malloc(sizeof(int)*order);
    for(int i=0;i<order;i++) newNode->key[i] = 0;
    newNode -> is_leaf = false; // 처음에 리프여부는 초기값 false로
    newNode -> cnt_child = 0;
    newNode -> cnt_key = 0;
    newNode -> order = order;
    return newNode;
}

BNodePtr splitChild(BNodePtr root)
{
	int i, mid;

	BNodePtr newParent;
	BNodePtr newSibling;

	newParent = CreateTree(root->order);
	newParent->is_leaf=0;

	if(root->is_root){
		newParent->is_root=1;
	}
	root->is_root=0;

	newSibling = CreateTree(root->order);
	newSibling->is_leaf= root->is_leaf;

	mid=(root->order-1)/2;
	for(i=mid+1; i<root->order; i++){
		newSibling->child[i-(mid+1)] = root->child[i];
		newSibling->key[i-(mid+1)] = root->key[i];
		newSibling->cnt_child++;

		root->child[i]=NULL;
		root->key[i]=0;
		root->cnt_child--;
	}
	
	newSibling->child[i-(mid+1)] = root->child[i];
	root->child[i]=NULL;

	newParent->key[0] = root->key[mid];
	newParent->cnt_child++;
	root->key[mid]=0;
	root->cnt_child--;

	newParent->child[0] = root;
	newParent->child[1] = newSibling;

	return newParent;
}


void Insert(BNodePtr *root, int key){
	int i,pos,mid;
	BNodePtr split;

	if((*root)->is_leaf){
		for(pos=0; pos<(*root)->cnt_child; pos++){
			if((*root)->key[pos] > key){
				break;
			}
		}
		for(i=(*root)->cnt_child; i>pos; i--){
			(*root)->key[i] = (*root)->key[i-1];
		}
		(*root)->key[pos]=key;
		(*root)->cnt_child++;

		if((*root)->cnt_child==(*root)->order&&(*root)->is_root){
			*root = splitChild(*root);
		}
	}
	else{
		for(pos=0; pos<(*root)->cnt_child; pos++){
			if((*root)->key[pos] >key){
				break;
			}
		}
		Insert(&((*root)->child[pos]),key);

		if(((*root)->child[pos])->cnt_child==(*root)->order){
			split = splitChild((*root)->child[pos]);
			for(i=(*root)->cnt_child; i>pos; i--){
				(*root)->key[i] = (*root)->key[i-1];
				(*root)->child[i+1] = (*root)->child[i];
			}
				
			(*root)->key[pos] = split->key[0];
			(*root)->cnt_child++;
			(*root)->child[pos] = split->child[0];	
			(*root)->child[pos+1] = split->child[1];
		}
		if((*root)->cnt_child==(*root)->order&&(*root)->is_root){
			*root = splitChild(*root);
		}
	}
}
// 트리 프린트 하는 함수
void PrintTree(BNodePtr node) {			 // B트리 그리기
    int i;
	for(i=0;i<node->cnt_key; i++){
        if(!node->is_leaf){
            PrintTree(root->child[i]);
        }
        fprintf(fout, "%d ", root->key[i]);
    
    }
    if(!node->is_leaf) PrintTree(root->child[i]);
}
void DeleteTree(BNodePtr node){
    free(node);
}

int main(int argc, char *argv[]){
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    int order;
    fscanf(fin, "%d", &order);
    BNodePtr root = CreateTree(order);
    
    char cv;
    int key;
    while(!feof(fin)){
        fscanf(fin, "%c", &cv);
        switch(cv){
            case 'i':
                fscanf(fin, "%d", &key);
                if(Find(root, key)) fprintf(fout, "insert error : key %d is already in the tree!\n", key);
                else Insert(&root, key);
                break;
            case 'f':
                fscanf(fin, "%d", &key);
                if(Find(root, key)) fprintf(fout, "key %d found\n",key);
                else fprintf(fout, "finding error : key %d is not in the tree!\n", key);
                break;
            case 'p':
                if(root->cnt_child== 0) fprintf(fout, "printing error : tree is empty!");
                else PrintTree(root);
                fprintf(fout, "\n");
                break;
        }
    }
    DeleteTree(root);
    fclose(fin);
    fclose(fout);

    return 0;
}