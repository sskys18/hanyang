#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *fin;
FILE *fout;

typedef int ElementType;
typedef ElementType List;
typedef struct HashTbl* HashTable;

typedef struct HashTbl{
    int TableSize;
    List *TheLists;
}HashTbl;

HashTable createTable(int TableSize);
void Insert(HashTable H, ElementType key, int solution);
void Delete(HashTable H, ElementType key, int solution);
int Find(HashTable H, ElementType key, int solution);
void printTable(HashTable H);
void deleteTable(HashTable H);

int main(int argc, char *argv[]){
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    char solution_str[20];
    int solution, TableSize;

    fscanf(fin, "%s", solution_str);
    if(!strcmp(solution_str, "linear"))
        solution = 1;
    else if(!strcmp(solution_str, "quadratic"))
        solution = 2;
    else{
        fprintf(fout, "error: invalid hashing solution!");
        return 0;
    }

    fscanf(fin, "%d", &TableSize);

    HashTable H = createTable(TableSize);

    char cv;
    int key;
    while(!feof(fin)){
        fscanf(fin, "%c", &cv);
        switch(cv){
            case 'i':
                fscanf(fin, "%d", &key);
                Insert(H, key, solution);
                break;

            case 'f':
                fscanf(fin, "%d", &key);
                int result = Find(H, key, solution);
                if(result)
                    fprintf(fout, "%d is in the table\n", key);
                else
                    fprintf(fout, "%d is not in the table\n", key);
                break;

            case 'd':
                fscanf(fin, "%d", &key);
                Delete(H, key, solution);
                break;

            case 'p':
                printTable(H);
                break;
        }
    }
    deleteTable(H);

    return 0;
}

HashTable createTable(int TableSize){
    HashTable hashTable = malloc(sizeof(HashTable));
    hashTable->TableSize = TableSize;
    hashTable->TheLists = malloc(sizeof(int)*TableSize);
    for(int i=0; i<hashTable->TableSize; i++){
        hashTable->TheLists[i] = 0;
    }
    return hashTable;
}
void Insert(HashTable H, ElementType key, int solution){
    if(solution == 1){
        int n = key%H->TableSize;
        for(int i=1;i<H->TableSize;i++){
            if(key == H->TheLists[n]){
                fprintf(fout, "insertion error : %d already exists at address %d\n",key,n);
                return;
            }
            else if(H->TheLists[n] == 0&& n< H->TableSize){
                fprintf(fout, "insert %d into address %d\n", key, n);
                H->TheLists[n] = key;
                return;
            }
            else{
                if(n >= H->TableSize) n =0;
                else n++;
            }
        }
        fprintf(fout, "insertion error : table is full\n");
    }
    else if(solution == 2){
        int n = key%H->TableSize;
        for(int i=1;i<H->TableSize;i++){
            if(key == H->TheLists[n]){
                fprintf(fout, "insertion error : %d already exists at address %d\n",key,n);
                return;
            }
            else if(H->TheLists[n] == 0&& n< H->TableSize){
                fprintf(fout, "insert %d into address %d\n", key, n);
                H->TheLists[n] = key;
                return;
            }
            else{
                if(n >= H->TableSize) n =0;
                else n += i*i;
            }
        }
        fprintf(fout, "insertion error : table is full\n");
    }
}
void Delete(HashTable H, ElementType key, int solution){
    int n = key%H->TableSize;
    if(key == H->TheLists[n]){
        H->TheLists[n] = 0;
        fprintf(fout, "delete %d\n", key);
    }
    else{
        if(solution == 1){
            for(int i=1;i<H->TableSize;i++){
                n++;
                if(key == H->TheLists[n]){
                    H->TheLists[n] = 0;
                    fprintf(fout, "delete %d\n", key);
                }
            }
            fprintf(fout, "deletion error : %d is not in the table\n", key);
        }
        else if(solution == 2){
            for(int i=1;i<H->TableSize;i++){
                n += i*i;
                if(key == H->TheLists[n]) {
                    H->TheLists[n] = 0;
                    fprintf(fout, "delete %d\n", key);
                }
            }
            fprintf(fout, "deletion error : %d is not in the table\n", key);

        }
    }
}
int Find(HashTable H, ElementType key, int solution){
    int n = key%H->TableSize;
    if(key == H->TheLists[n]) return 1;
    else{
        if(solution == 1){
            for(int i=1;i<H->TableSize;i++){
                n++;
                if(key == H->TheLists[n]) return 1;
            }
            return 0;
        }
        else if(solution == 2){
            for(int i=1;i<H->TableSize;i++){
                n += i*i;
                if(key == H->TheLists[n]) return 1;
            }
            return 0;

        }
    }
}
void printTable(HashTable H){
    for(int i=0; i<H->TableSize; i++){
        fprintf(fout, "%d ",H->TheLists[i]);
    }
    fprintf(fout, "\n");
}
void deleteTable(HashTable H){
    free(H->TheLists);
    free(H);
}