#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ISFULL 1
#define ISEMPTY 2
#define DIVIDEZERO 3
FILE *fin;
FILE *fout;

typedef struct Stack{
	int *key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max){ //create stack to put operator
	Stack* s;
	s = malloc(sizeof(struct Stack));
	s->max_stack_size = max; //stack size 
	s->top = -1; //place
	s->key = (int*)malloc(sizeof(int*) * s->max_stack_size);//array of numbers
	return s;
}
int IsEmpty(Stack* s){ //return true if stack is empty
        return s->top < 0;
}
int IsFull(Stack* s){ // return true if stack is full
        return s->top == s->max_stack_size -1;
}
void Push(Stack* s,int X) { // Push number in stack
	s->key[++s->top] = X; 
}
int Pop(Stack* s) { // Pop number to operate
	return s->key[s->top--];
}
int Top(Stack* s) { // Return number in top of the stack
	return s->key[s->top];
}

void DeleteStack(Stack* s) { //delete stack
	free(s);
}

void main(int argc, char *argv[]) {
	fin=fopen(argv[1], "r");
	fout=fopen(argv[2], "w");

	Stack* stack;
	char input_str[101];
	int max=20, i=0, a, b, result, error_flag=0;

	fgets(input_str,101,fin);
	stack = CreateStack(max);

	fprintf(fout, "top numbers : ");
	while(input_str[i]!='#'){ //until '#'
		if(input_str[i] >= '0' && input_str[i] <= '9') { //if input_str is number
			if(!IsFull(stack)) Push(stack,input_str[i]-'0');
			else error_flag = 1;
		}
		else { //if input_str is operator
			if(IsEmpty(stack)) error_flag = 2; // if stack is empty
			else b = Pop(stack); //pop number
			if(IsEmpty(stack)) error_flag = 2; // if stack is empty
			else a = Pop(stack); // pop number
			switch (input_str[i]) {
				case '+': 
					if(!IsFull(stack)) Push(stack,a+b);
                        		else error_flag = 1; // if stack is full
					break;
				case '-':
                                        if(!IsFull(stack)) Push(stack,a-b);
                                        else error_flag = 1;
                                        break;
				case '*':
                                        if(!IsFull(stack)) Push(stack,a*b);
                                        else error_flag = 1;
                                        break;
				case '/':
					if(b==0) { // if divide by zero
						error_flag = 3;
						break;
					}
					else if(!IsFull(stack)) Push(stack,a/b);
                                        else error_flag = 1;
                                        break;
				case '%':
					if(b==0) { // if divide by zero
						error_flag = 3;
						break;	
					}
                                        else if(!IsFull(stack)) Push(stack,a%b);
                                        else error_flag = 1;
                                        break;
				defalut:
					break;
			}
		}
		if(error_flag != 0) {break;} // if error is ocuured, break
		int t = Top(stack); //top of the stack = result
		fprintf(fout, "%d ",t); //print result
		result = t;

		i++;
	}
	
	if(error_flag == ISFULL){
		fprintf(fout, "\nerror : invalid postfix expression, stack is full!\n");
	}
	else if(error_flag == ISEMPTY){
		fprintf(fout, "\nerror : invalid postfix expression, stack is empty!\n");
	}
	else if(error_flag == DIVIDEZERO){
		fprintf(fout, "\nerror : invalid postfix expression, divide by zero!\n");
	}
	else{
		if(stack->top+1 > 1){
			fprintf(fout, "\nerror : invalid postfix expression, %d elements are left!\n", stack->top+1);
		}
		else{
			fprintf(fout, "\nevaluation result : %d\n", result);
		}
	}
	DeleteStack(stack);
	fclose(fin);
	fclose(fout);
}
