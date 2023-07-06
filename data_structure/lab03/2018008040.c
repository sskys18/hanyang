#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node
{
	ElementType element;
	Position next;
};
FILE *input;
FILE *output;


List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast( Position P, List L );
void Insert( ElementType X, List L, Position P );
void PrintList(List L);
void Delete( ElementType X, List L );
Position Find(ElementType X, List L );
Position FindPrevious(ElementType X, List L );
void DeleteList( List L );

List MakeEmpty( List L) {
	L = (List) malloc(sizeof(struct Node));
	L->element = 0;
	L->next = NULL; //header node initialize
	return L;
}

int IsEmpty( List L ) {
	return L->next == NULL; //
}

int IsLast( Position P, List L ) {
	return P->next == NULL;
}

Position Find( ElementType X, List L ) {
	Position p;
	p = L->next;
	while( p != NULL && p->element != X) {
		p = p->next;
	}
	return p;
}	

Position FindPrevious( ElementType X, List L ) {
	Position p;
	p = L;
	while (p->next != NULL && p->next->element != X) {
		p = p->next;
	}
	return p;
}

void Insert( ElementType X, List L, Position P ) {
	Position tmp;
	tmp = (Position) malloc(sizeof(struct Node));
	tmp->element = X;
	tmp->next = P->next;
	P->next = tmp;
}

void PrintList(List L) {
	Position p;
	p = L->next;
	while( p != NULL) { 
		fprintf(output,"key:%d ",p->element);
		p = p->next;
	}
}

void Delete( ElementType X, List L ){
	Position p, tmp;
	p = FindPrevious(X, L);
	tmp = p->next;
	p->next = tmp->next;
	free(tmp);
}

void DeleteList( List L ) {
	Position p, tmp;
	p = L->next;
	L->next = NULL;
	while( p != NULL) { // until p indicates last node
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

int main(int argc, char *argv[]) {
	char command;
	int key1, key2;
	FILE *input;
	Position header = NULL;
	Position tmp= NULL;
	if (argc== 1) {
		input = fopen("input.txt", "r");
		output = fopen("output.txt", "w");
	}
	else {
		input = fopen(argv[1], "r");
		output = fopen(argv[2], "w");
	}
	header = MakeEmpty(header); //list initialize
	while (1) {
		command = fgetc(input); // choose what command to do
		if (feof(input)) break;
		switch (command) {
		case 'i': 
			fscanf(input, "%d %d", &key1, &key2);//duplication check
			tmp = Find(key1, header);
			if (tmp!= NULL) { // key1 is already exixt
				fprintf(output, "insertion(%d) failed : the key already exists in the list\n", key1);
				break;
			}
			if (key2 == -1) { // save next to header
				Insert(key1,NULL,header);
				break;
			}
			tmp = Find(key2, header);
			if (tmp== NULL) { // no node address exists
				fprintf(output, "insertion(%d) failed : can not find the location to be inserted\n", key1);
				break;
			}
		
			Insert(key1, header, tmp);
			break;
		case 'd':
			fscanf(input, "%d", &key1);
			tmp = Find(key1, header);
			if( tmp == NULL) { // no element key1 exists
         	 		fprintf(output,"deletion(%d) failed: element %d is not in the list\n", key1, key1);
				break;
			}
			Delete(key1, header);
			break;
		case 'f':
			fscanf(input, "%d", &key1);
			tmp= FindPrevious(key1, header);
			if (IsLast(tmp, header)) // key1 dosen't exist
				fprintf(output, "finding(%d) failed : element %d is not in the list\n", key1, key1);
			else {
				if (tmp->element > 0) // key1 is next to header
					fprintf(output, "key of the previous node of %d is %d\n", key1, tmp->element);
				else
					fprintf(output, "key of the previous node of %d is head\n", key1);
			}
			break;
		case 'p':
			if( header->next == NULL) { // there is no node next to header
		                fprintf(output,"empty list!");
			}
			PrintList(header);
			break;
		default:
			break;
		} 
	}
	DeleteList(header); // delete the entire list
	fclose(input);
	fclose(output);
	return 0;
}
