/* LC-2K Instruction-level simulator */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMMEMORY 65536 /* maximum number of words in memory */

#define NUMREGS 8 /* number of machine registers */

#define MAXLINELENGTH 1000

typedef struct stateStruct
{
	int pc;
	int mem[NUMMEMORY];
	int reg[NUMREGS];
	int numMemory;
} stateType;

void printState(stateType *);
int convertNum(int num);

int main(int argc, char *argv[])
{
	char line[MAXLINELENGTH];
	stateType state;
	FILE *filePtr;

	if ( argc != 2 )
	{
		printf("error: usage: %s <machine-code file>\n", argv[0]);
		exit(1);
	}

	filePtr = fopen(argv[1], "r");
	if ( filePtr == NULL )
	{
		printf("error: can't open file %s", argv[1]);
		perror("fopen");
		exit(1);
	}

	/* read in the entire machine-code file into memory */
	for ( state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; state.numMemory++ )
	{
		if ( sscanf(line, "%d", state.mem + state.numMemory) != 1 )
		{
			printf("error in reading address %d\n", state.numMemory);
			exit(1);
		}
		printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
	}

  state.pc = 0;
  for(int i = 0; i < NUMREGS; i++) {
    state.reg[i] = 0;
  }
  
  int halted = 0;
  int total_instr_num = 0;

  while(!halted && state.pc <= state.numMemory) {
    int opcode = 0, regA = 0, regB = 0, destReg = 0, offset = 0, result = 0;
    int instr = state.mem[state.pc];
    opcode = instr >> 22;

    printState(&state);

    regA = (instr >> 19) & 0x00000007;
    regB = (instr >> 16) & 0x00000007;

    if(opcode == 0) { // opcode == add
      destReg = instr & 0x00000007;
      state.reg[destReg] = state.reg[regA] + state.reg[regB];
    }
    else if(opcode == 1) { // opcode == nor
      destReg = instr & 0x00000007;
      state.reg[destReg] = ~(state.reg[regA] | state.reg[regB]);
    }
    else if(opcode == 2) { // opcode == lw
      offset = instr & 0x0000FFFF;
      state.reg[regB] = state.mem[convertNum(state.reg[regA] + offset)];
    }
    else if(opcode == 3) { // opcode == sw
      offset = instr & 0x0000FFFF;
      state.mem[convertNum(state.reg[regA] + offset)] = state.reg[regB];
    }
    else if(opcode == 4) { // opcode == beq
      offset = instr & 0x0000FFFF;
      if(state.reg[regA] == state.reg[regB]) {
        state.pc += convertNum(offset);
      }
    }
    else if(opcode == 5) { // opcode == jalr
      state.reg[regB] = state.pc + 1;
      state.pc = state.reg[regA] - 1;
    }
    else if(opcode == 6) { // opcode == halt
      halted = 1;
    }
    else if(opcode == 7) { // opcode == noop

    }
    else {
      printf("unknown opcode \"0x%x\"exists in %d instruction\n", state.mem[state.pc], total_instr_num);
    }
    total_instr_num++;
    state.pc++;
  }
  printf("machine halted\n");
  printf("total of %d instructions executed\n", total_instr_num);
  printf("final state of machine:\n");
  printState(&state);
	exit(0);
}

void printState(stateType *statePtr)
{
	int i;
	printf("\n@@@\nstate:\n");
	printf("\tpc %d\n", statePtr->pc);
	printf("\tmemory:\n");
	for ( i = 0; i < statePtr->numMemory; i++ )
	{
		printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
	}
	printf("\tregisters:\n");
	for ( i = 0; i < NUMREGS; i++ )
	{
		printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
	}
	printf("end state\n");
}

int convertNum(int num)
{
  /* convert a 16-bit number into a 32-bit Linux integer */
  if (num & (1 << 15) ) {
    num -= (1 << 16);
  }
  return(num);
}
