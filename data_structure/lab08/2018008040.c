#include<stdio.h>
#include<stdlib.h>
#include<time.h>

FILE *fin;
FILE *fout;

typedef struct _DisjointSet{
    int size_maze;
    int *ptr_arr;
}DisjointSets;

void init(DisjointSets *sets, DisjointSets *maze_print, int num);
void Union(DisjointSets *sets, int i, int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void printMaze(DisjointSets *sets, int num);
void freeMaze(DisjointSets *sets, DisjointSets *maze_print);

int main(int argc, char* argv[]){
    srand((unsigned int)time(NULL));

    int num, i;
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    DisjointSets *sets, *maze_print;
    fscanf(fin, "%d", &num);

    sets = (DisjointSets*)malloc(sizeof(DisjointSets));
    maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));

    init(sets, maze_print, num);
    createMaze(sets, maze_print, num);
    printMaze(maze_print, num);

    freeMaze(sets, maze_print);

    fclose(fin);
    fclose(fout);

    return 0;
}

void init(DisjointSets *sets, DisjointSets *maze_print, int num){
    int i;
    sets->size_maze = num*num;
    sets->ptr_arr = (int*)malloc(sizeof(int)*(sets->size_maze + 1));
    for(i=1;i<=sets->size_maze;i++) sets->ptr_arr[i] = i;

    maze_print->size_maze = num*num*2;
    maze_print->ptr_arr = (int*)malloc(sizeof(int)*(maze_print->size_maze + 1));
    for(i=1;i<=maze_print->size_maze;i++) maze_print->ptr_arr[i] = 1;

    maze_print->ptr_arr[maze_print->size_maze -1] =0;
}
void Union(DisjointSets *sets, int i, int j){
    int x = find(sets,i);
    int y = find(sets,j);
    if(x == y) return;
    sets->ptr_arr[x] = y;//union x into y
}
int find(DisjointSets *sets, int i){
    if(i != sets->ptr_arr[i]) return sets->ptr_arr[i] = find(sets, sets->ptr_arr[i]); //if i is not root, set i into child of parent
    return sets->ptr_arr[i];
}
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num){
    while(find(sets,1) != find(sets,num*num)) { //while start and end is not linked
        int random = (rand() % (num*num*2)) + 1; //random number between 1~num*num*2
        if((random%2 == 1)&&((random+1)%(num*2) !=0 )) { // random number is odd(right wall) except rightmost wall
            if(find(sets,(random+1)/2) != find(sets, (random+1)/2+1)){ //if cell next to wall is disjoint
                Union(sets, (random+1)/2, (random+1)/2+1); //union two cell
                maze_print->ptr_arr[random] = 0; //remove the wall
            }
        }
        else if((random%2 == 0) && (random <= 2*num*(num-1))){ // random number is even(down wall) except last line
            if(find(sets, random/2) != find(sets, random/2 + num)){ // if two cell is disjoint
                Union(sets, random/2, random/2 + num); // union two cell
                maze_print->ptr_arr[random] = 0; // remove the wall
            }
        }
        else continue;
    }
}
void printMaze(DisjointSets *sets, int num){
    fprintf(fout,"+");
    for(int i=0; i<num; i++){
        fprintf(fout, "---+");
    } //first line
    fprintf(fout, "\n");
    for(int a=0; a<num; a++){
        if(a == 0) fprintf(fout, " "); //start wall
        else fprintf(fout, "|");
        for(int c=0; c<num; c++){
            if(sets->ptr_arr[2*a*num + 2*c + 1] == 1) fprintf(fout, "   |"); //if wall exist
            else fprintf(fout, "    "); //wall doesn't exist
        }
        fprintf(fout, "\n");

        fprintf(fout, "+");
        for(int c=0; c<num; c++){
            if(sets->ptr_arr[2*a*num + 2*c + 2] == 1) fprintf(fout, "---+"); //if wall exist
            else fprintf(fout, "   +"); //wall doesn't exist
        }
        fprintf(fout, "\n");
    }
}

void freeMaze(DisjointSets *sets, DisjointSets *maze_print){
    free(sets->ptr_arr);
    free(maze_print->ptr_arr);
    free(sets);
    free(maze_print);
}

