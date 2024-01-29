/*
  Name 1: Dhruv Bansal
  Name 2: Carolyn Hoang
  UTEID 1: db45988
  UTEID 2: ch52677
*/
#include <stdio.h>  /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h>  /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */

#define MAX_LABEL_LEN 20
#define MAX_SYMBOLS 255
typedef struct
{
  int address;
  char label[MAX_LABEL_LEN + 1]; /* Question for the reader: Why do we need to add 1? */ // because we need to append a null character to the end of each symbol
} TableEntry;
TableEntry symbolTable[MAX_SYMBOLS];
int symbol_count = 0;

int toNum(char *pStr)
{
  char *t_ptr;
  char *orig_pStr;
  int t_length, k;
  int lNum, lNeg = 0;
  long int lNumLong;

  orig_pStr = pStr;
  if (*pStr == '#') /* decimal */
  {
    pStr++;
    if (*pStr == '-') /* dec is negative */
    {
      lNeg = 1;
      pStr++;
    }
    t_ptr = pStr;
    t_length = strlen(t_ptr);
    for (k = 0; k < t_length; k++)
    {
      if (!isdigit(*t_ptr))
      {
        printf("Error: invalid decimal operand, %s\n", orig_pStr);
        exit(4);
      }
      t_ptr++;
    }
    lNum = atoi(pStr);
    if (lNeg)
      lNum = -lNum;

    return lNum;
  }
  else if (*pStr == 'x') /* hex */
  {
    pStr++;
    if (*pStr == '-') /* hex is negative */
    {
      lNeg = 1;
      pStr++;
    }
    t_ptr = pStr;
    t_length = strlen(t_ptr);
    for (k = 0; k < t_length; k++)
    {
      if (!isxdigit(*t_ptr))
      {
        printf("Error: invalid hex operand, %s\n", orig_pStr);
        exit(4);
      }
      t_ptr++;
    }
    lNumLong = strtol(pStr, NULL, 16); /* convert hex string into integer */
    lNum = (lNumLong > INT_MAX) ? INT_MAX : lNumLong;
    if (lNeg)
      lNum = -lNum;
    return lNum;
  }
  else
  {
    printf("Error: invalid operand, %s\n", orig_pStr);
    exit(4); /* This has been changed from error code 3 to error code 4, see clarification 12 */
  }
}

char codes[][6] = {
    "add\0\0\0",
    "and\0\0\0",
    "halt\0\0",
    "jmp\0\0\0",
    "jsr\0\0\0",
    "jsrr\0\0",
    "ldb\0\0\0",
    "ldw\0\0\0",
    "lea\0\0\0",
    "nop\0\0\0",
    "not\0\0\0",
    "ret\0\0\0",
    "lshf\0\0",
    "rshfl\0",
    "rti\0\0\0",
    "stb\0\0\0",
    "stw\0\0\0",
    "trap\0\0",
    "xor\0\0\0",
    "br\0\0\0\0",
    "brn\0\0\0",
    "brz\0\0\0",
    "brp\0\0\0",
    "brzp\0\0",
    "brnp\0\0",
    "brnz\0\0",
    "brnzp\0"};
// 27 codes

int isOpcode(char *lPtr)
{
  for (int i = 0; i < 27; i++)
  {
    if (0 == strcmp(lPtr, codes[i]))
      return i;
  }
  return -1;
}

int isValidLabel(char *pStr)
{
  // Checks if the label is using any of the trap instructions
  if ((0 == strcmp(pStr, "in")) || (0 == strcmp(pStr, "getc")) || (0 == strcmp(pStr, "out")) || (0 == strcmp(pStr, "puts")) || (0 == strcmp(pStr, "halt")))
    return -1;

  // Checks if there are repeats in the symbolTable 
  for (int i = 0; i < symbol_count; i++)
  {
    if (0 == strcmp(pStr, symbolTable[i].label))
      return -1;
  }

  // Checks for alphanumeric correctness
  for (int i = 0; i < strlen(pStr); i++)
  {
    if (!isalnum(pStr[i]))
      return -1;
  }

  return 0;
} 

#define MAX_LINE_LENGTH 255
enum
{
  DONE,
  OK,
  EMPTY_LINE
};

int readAndParse(FILE *pInfile, char *pLine, char **pLabel, char **pOpcode, char **pArg1, char **pArg2, char **pArg3, char **pArg4)
{
  char *lRet, *lPtr;
  int i;

  // 0. Gets 1 line from the file, assigns the ptr of string form file to pline with length MaxLineLength - 1 (+ null terminator)
  if (!fgets(pLine, MAX_LINE_LENGTH, pInfile))
    return (DONE);

  /* convert entire line to lowercase */
  for (i = 0; i < strlen(pLine); i++)
    pLine[i] = tolower(pLine[i]);

  // By default, assigns all arguments, opcode, and label the line (to account for more or less arguments/ label/ comments)
  *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

  /* ignore the comments */
  // 1. Get the start of the first item (label or opcode or comment or something else)
  lPtr = pLine;

  // 2. Iterate up to comments and newlines (stop loop at this spot)
  while (*lPtr != ';' && *lPtr != '\0' && *lPtr != '\n')
    lPtr++;

  // By default, indicate the end of new item with null terminator (string, 0)
  *lPtr = '\0';

  // 3. Get the first token, if there is nothing left, indicate empty line
  if (!(lPtr = strtok(pLine, "\t\n ,")))
    return (EMPTY_LINE);

  /* found a label */
  // 5. Check if label, not opcode nor pseudo-op
  if (isOpcode(lPtr) == -1 && lPtr[0] != '.')
  {
    *pLabel = lPtr;
    // Get the next token (only label on this line)
    if (!(lPtr = strtok(NULL, "\t\n ,")))
      return (OK);
  }

  // 6. There is an intruction on the same line as the label
  // Continue with breaking down instructions with their respective arguments
  // NULL is passed as an arg in strtok() because strtok() maintains a static pointer of the previously passed string
  *pOpcode = lPtr;

  if (!(lPtr = strtok(NULL, "\t\n ,")))
    return (OK);

  *pArg1 = lPtr;

  if (!(lPtr = strtok(NULL, "\t\n ,")))
    return (OK);

  *pArg2 = lPtr;

  if (!(lPtr = strtok(NULL, "\t\n ,")))
    return (OK);

  *pArg3 = lPtr;

  if (!(lPtr = strtok(NULL, "\t\n ,")))
    return (OK);

  *pArg4 = lPtr;

  return (OK);
}

int decodePseudoOp(char *opcode, char *arg1)
{
  // .orig
  if (0 == strcmp(opcode, ".orig\0")) return toNum(arg1);

  // .end
  if (0 == strcmp(opcode, ".end\0\0")) return 0; // Ending with no problems

  // .fill
  if (0 == strcmp(opcode, ".fill\0")) 
  {
    // TODO: Figure out how memory is saved before implementing
    return 0;
  }

  return -1;
}

// Registers (this should be safe for now since the assembler reads line by line)
// Chose global array since manipulation is fast and accessible
int registers[8] = {};

// Will need to include PSR and condition code bits later

int decodeInstruction(char *label, char *opcode, char *arg1, char *arg2, char *arg3, char *arg4)
{
  int opcode_type = isOpcode(opcode); 
  if (opcode_type == -1) return -1; // Something went wrong, invalid opcode

  // Implement the following later 
  switch (opcode_type) 
  {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    case 10:
      break;
    case 11:
      break;
    case 12:
      break;
    case 13:
      break;
    case 14:
      break;
    case 15:
      break;
    case 16:
      break;
    case 17:
      break;
    case 18:
      break;
    case 19:
      break;
    case 20:
      break;
    case 21:
      break;
    case 22:
      break;
    case 23:
      break;
    case 24:
      break;
    case 25:
      break;
    case 26:
      break;
    case 27:
      break;
    default:
      return -1;
  }

  return -1;
}

FILE *lInfile = NULL;
FILE *outfile = NULL;

int main(int argc, char *argv[])
{

  /* open the source file */
  lInfile = fopen(argv[1], "r");
  outfile = fopen(argv[2], "w");

  if (!lInfile)
  {
    printf("Error: Cannot open file %s\n", argv[1]);
    exit(4);
  }

  if (!outfile)
  {
    printf("Error: Cannot open file %s\n", argv[2]);
    exit(4);
  }

  /* Do stuff with files */
  char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1, *lArg2, *lArg3, *lArg4;
  int lRet;

  // first pass - generate the symbol table
  int start_address = 0;
  int line_counter = 0;

  do
  {
    lRet = readAndParse(lInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4);
    if (lRet != DONE && lRet != EMPTY_LINE)
    {
      // implement code to do stuff later
      // printf("%s", lLabel);
      // printf(" %s", lOpcode);
      // printf(" %s", lArg1);
      // printf(" %s", lArg2);
      // printf(" %s", lArg3);
      // printf(" %s\n", lArg4);

      if (0 == strcmp(lOpcode, ".orig\0"))
      {
        start_address = toNum(lArg1);
        continue;
      }

      if (0 != strcmp(lLabel, "\0"))
      {
        // TODO: Need to implement, check if this is a valid label
        if (isValidLabel(lLabel) == -1) return -1; // Cannot parse invalid label

        strcpy(symbolTable[symbol_count].label, lLabel);
        symbolTable[symbol_count].address = start_address + line_counter;
        symbol_count++;
      }

      line_counter += 2;
    }
  } while (lRet != DONE);

  // for (int i = 0; i < symbol_count; i++)
  // {
  //   printf("%X ", symbolTable[i].address);
  //   printf("%s\n", symbolTable[i].label);
  // }

  // rewind the input doc
  rewind(lInfile);

  // second pass - write the actual output
  do
  {
    lRet = readAndParse(lInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4);
    if (lRet != DONE && lRet != EMPTY_LINE)
    {
      // Parse assembly code (using symbol table)
      // Translate assembly to machine code
      // Write machine code to output file
      int first_byte, second_byte;

      // For now, ignore the case in which instructions start with a label (for branching purposes)

      // Something to consider: how are we implementing memory (is it going to be a dynamically growing array/ map that takes record of how the information is being decoded)

      // Decoding instructions or pseudo-ops
      if (0 != strcmp(lOpcode, "\0"))
      {
        if (1 /* lOpcode[0], "." */) {
          int error = decodePseudoOp(lOpcode, lArg1);

          // Double check the return value for any errors
        }
        else {
          int error = decodeInstruction(lLabel, lOpcode, lArg1, lArg2, lArg3, lArg4);

          // Double check the return value for any errors
        }
      }

      // Shift program counter (important to keep track for jumping and branching)
      line_counter += 2;

      // Write to output
      // Note that you'll have to write twice to the output for word alignment
      fprintf(outfile, "%X \n", first_byte);
      fprintf(outfile, "%X \n", second_byte);
    }
  } while (lRet != DONE);

  // Close file at the end
  fclose(lInfile);
  fclose(outfile);

  return 0;
}
