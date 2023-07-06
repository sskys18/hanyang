/* Assembler code fragment for LC-2K */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINELENGTH 1000

int readAndParse(FILE *, char *, char *, char *, char *, char *);

int isNumber(char *);

int main(int argc, char *argv[])
{
	char *inFileString, *outFileString;
	FILE *inFilePtr, *outFilePtr;
	char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
		arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

  char labels[65536][7];
  int machine_codes[65536];
  int total_line = 0;
  int current_line = 0;
	
	if ( argc != 3 )
	{
		printf("error: usage: %s <assembly-code-file> <machine-code-file>\n", argv[0]);
		exit(1);
	}

	inFileString = argv[1];
	outFileString = argv[2];

	inFilePtr = fopen(inFileString, "r");
	if ( inFilePtr == NULL )
	{
		printf("error in opening %s\n", inFileString);
		exit(1);
	}

  /*
	outFilePtr = fopen(outFileString, "w");
	if ( outFilePtr == NULL )
	{
		printf("error in opening %s\n", outFileString);
		exit(1);
	}
  */

  while(1) { // First, store existing labels
    if(!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {
      // reached end of file
      break;
    }
    
    if(strlen(label) > 6) {
      printf("error: Valid labels contain a maximum of 6 characters!\n");
      printf("Cannot accept a label \"%s\" in line %d\n", label, total_line);
      exit(1);
    }

    if(isNumber(&label[0])) {
      printf("error: label must start with letter!\n");
      printf("Cannot accept a label \"%s\" in line %d\n", label, total_line);
      exit(1);
    }
    
    if(strcmp(label, "") != 0) { // if there exists a valid label
      for(int i = 0; i < total_line; i++) { // duplicate label checking
        if(!strcmp(labels[i], label)) {
          printf("error: Duplicate labels!\n");
          printf("Duplicate labels \"%s\" in line %d and line %d\n", label, i, total_line);
          exit(1);
        }
      }
      strcpy(labels[total_line], label);
    }
    
    //printf("line:%d, label:%s, opcode:%s, arg0:%s, arg1:%s, arg2:%s\n", total_line, label, opcode, arg0, arg1, arg2);
    total_line++;
  }

	/* this is how to rewind the file ptr so that you start reading from the
	beginning of the file */
	rewind(inFilePtr);

  while(1) {
    if(!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {
      // reached end of file
      break;
    }
    int op = 0, regA = 0, regB = 0, destReg = 0, offset = 0, result = 0;

    if(!strcmp(opcode, "add") || !strcmp(opcode, "nor")) { // R-type format
      if(!isNumber(arg0) || !isNumber(arg1) || !isNumber(arg2)) {
        printf("error: Wrong argument format exists in line %d\n", current_line);
        exit(1);
      }

      if(!strcmp(opcode, "add")) { // opcode == add
        op = 0x00000000;
      }
      else { // opcode == nor
        op = 0x00400000;
      }

      regA = atoi(arg0) << 19;
      regB = atoi(arg1) << 16;
      destReg = atoi(arg2);
      
      result = op | regA | regB | destReg;
      machine_codes[current_line] = result;
    }
    else if(!strcmp(opcode, "lw") || !strcmp(opcode, "sw") || !strcmp(opcode, "beq")) { // I-type format
      if(!isNumber(arg0) || !isNumber(arg1) || !strcmp(arg2, "")) {
        printf("error: Wrong argument format exists in line %d\n", current_line);
        exit(1);
      }
      
      if(!strcmp(opcode, "lw")) { // opcode == lw
        op = 0x00800000;
      }
      else if(!strcmp(opcode, "sw")) { // opcode == sw
        op = 0x00C00000;
      }
      else { // opcode == beq
        op = 0x01000000;
      }

      regA = atoi(arg0) << 19;
      regB = atoi(arg1) << 16;
      
      if(isNumber(arg2)) {
        offset = atoi(arg2);
      }
      else {
        int offset_updated = 0;
        for(int i = 0; i < total_line; i++) {
          if(!strcmp(labels[i], arg2)) {
            offset = i;
            offset_updated = 1;
          }
        }
        if(!offset_updated) {
          printf("error: use of undefined label \"%s\"\n", arg2);
          exit(1);
        }
        if(!strcmp(opcode, "beq")) {
          offset -= (current_line + 1);
        }
      }
      if(!(-32768 <= offset && offset <= 32767)) { // with a range of -32768 to 32767
        printf("error: Wrong offsetField range in line %d\n", current_line);
        exit(1);
      }
      if(!strcmp(opcode, "beq")) {
        offset &= 0x0000FFFF;
      }
      
      result = op | regA | regB | offset;
      machine_codes[current_line] = result;
    }
    else if(!strcmp(opcode, "jalr")) { // J-type format
      if(!isNumber(arg0) || !isNumber(arg1)) {
        printf("error: Wrong argument format exists in line %d\n", current_line);
        exit(1);
      }

      op = 0x01400000; // opcode == jalr

      regA = atoi(arg0) << 19;
      regB = atoi(arg1) << 16;

      result = op | regA | regB;
      machine_codes[current_line] = result;
    }
    else if(!strcmp(opcode, "halt") || !strcmp(opcode, "noop")) { // O-type format
      if(!strcmp(opcode, "halt")) { // opcode == halt
        machine_codes[current_line] = 0x01800000;
      }
      else if(!strcmp(opcode, "noop")) { // opcode == noop
        machine_codes[current_line] = 0x1C00000;
      }
    }
    else if(!strcmp(opcode, ".fill")) { // .fill instruction
      if(!strcmp(arg0, "")) {
        printf("error: Wrong argument format exists in line %d\n", current_line);
        exit(1);
      }

      if(isNumber(arg0)) {
        machine_codes[current_line] = atoi(arg0);
      }
      else {
        int label_updated = 0;
        for(int i = 0; i < total_line; i++) {
          if(!strcmp(labels[i], arg0)) {
            machine_codes[current_line] = i;
            label_updated = 1;
          }
        }
        if(!label_updated) {
          printf("error: use of undefined label \"%s\"\n", arg2);
          exit(1);
        }
      }
    }
    else { // Unrecognized opcode
      printf("error: unrecognized opcode\n%s\n", opcode);
      exit(1);
    }
    
    current_line++;
  }

  outFilePtr = fopen(outFileString, "w");
  if ( outFilePtr == NULL )
  { 
    printf("error in opening %s\n", outFileString);
    exit(1);
  }


	for(int i = 0; i < total_line; i++) {
    printf("(address %d): %d (hex 0x%x)\n", i, machine_codes[i], machine_codes[i]);
  }

  for(int i = 0; i < total_line; i++) {
    if(outFilePtr) {
      fprintf(outFilePtr, "%d\n", machine_codes[i]);
    }
  }

	exit(0);
}

/*
* Read and parse a line of the assembly-language file. Fields are returned
* in label, opcode, arg0, arg1, arg2 (these strings must have memory already
* allocated to them).
*
* Return values:
* 0 if reached end of file
* 1 if all went well
*
* exit(1) if line is too long.
*/
int readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
		char *arg1, char *arg2)
{
	char line[MAXLINELENGTH];
	char *ptr = line;

	/* delete prior values */
	label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

	/* read the line from the assembly-language file */
	if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
		/* reached end of file */
		return(0);
	}

	/* check for line too long (by looking for a \n) */
	if (strchr(line, '\n') == NULL) {
		/* line too long */
		printf("error: line too long\n");
		exit(1);
	}

	/* is there a label? */
	ptr = line;
	if (sscanf(ptr, "%[^\t\n\r ]", label)) {
		/* successfully read label; advance pointer over the label */
		ptr += strlen(label);
	}

	/*
	 * Parse the rest of the line.  Would be nice to have real regular
	 * expressions, but scanf will suffice.
	 */
	sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%"
			"[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]", opcode, arg0, arg1, arg2);
	return(1);
}

int isNumber(char *string)
{
	/* return 1 if string is a number */
	int i;
	return( (sscanf(string, "%d", &i)) == 1);
}
