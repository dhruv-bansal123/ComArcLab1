/*
	Name 1: Dhruv Bansal
	Name 2: Carolyn Hoang
	UTEID 1: db45988
	UTEID 2: ch52677
*/
#include <stdio.h> /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h> /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */

#define MAX_LABEL_LEN 20
#define MAX_SYMBOLS 255
int symbol_count = 0;
typedef struct {
	int address;
	char label[MAX_LABEL_LEN + 1];	/* Question for the reader: Why do we need to add 1? */ // because we need to append a null character to the end of each symbol
} TableEntry;
TableEntry symbolTable[MAX_SYMBOLS];


int toNum( char * pStr )
{
   char * t_ptr;
   char * orig_pStr;
   int t_length,k;
   int lNum, lNeg = 0;
   long int lNumLong;

   orig_pStr = pStr;
   if( *pStr == '#' )				/* decimal */
   { 
     pStr++;
     if( *pStr == '-' )				/* dec is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isdigit(*t_ptr))
       {
	 printf("Error: invalid decimal operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNum = atoi(pStr);
     if (lNeg)
       lNum = -lNum;
 
     return lNum;
   }
   else if( *pStr == 'x' )	/* hex     */
   {
     pStr++;
     if( *pStr == '-' )				/* hex is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isxdigit(*t_ptr))
       {
	 printf("Error: invalid hex operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
     lNum = (lNumLong > INT_MAX)? INT_MAX : lNumLong;
     if( lNeg )
       lNum = -lNum;
     return lNum;
   }
   else
   {
	printf( "Error: invalid operand, %s\n", orig_pStr);
	exit(4);  /* This has been changed from error code 3 to error code 4, see clarification 12 */
   }
}

char codes[][6] ={ 
    "add\0\0\0", //0
    "and\0\0\0", //1
    "halt\0\0", //2
    "jmp\0\0\0", //3
    "jsr\0\0\0", //4
    "jsrr\0\0", //5
    "ldb\0\0\0", //6
    "ldw\0\0\0", //7
    "lea\0\0\0", //8
    "nop\0\0\0", //9
    "not\0\0\0", //10
    "ret\0\0\0", //11
    "lshf\0\0", //12
    "rshfl\0", //13
    "rti\0\0\0", //14
    "stb\0\0\0", //15
    "stw\0\0\0", //16
    "trap\0\0", //17
    "xor\0\0\0", //18
    "br\0\0\0\0", //19
    "brn\0\0\0", //20
    "brz\0\0\0", //21
    "brp\0\0\0", //22
    "brzp\0\0", //23
    "brnp\0\0", //24
    "brnz\0\0", //25
    "brnzp\0",//26
    ".orig\0",//27
    ".fill\0",//28
    ".end\0\0",//29
    };
  //30 codes
int isOpcode (char * lPtr){
  for (int i = 0; i<30; i++){
    if (0 == strcmp(lPtr, codes[i]))
      return i;
  }
  return -1;
}

#define MAX_LINE_LENGTH 255
	enum{
	  DONE, OK, EMPTY_LINE
	};

int readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char ** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4){
  char * lRet, * lPtr;
  int i;
  if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) ) return( DONE );
  for( i = 0; i < strlen( pLine ); i++ ) pLine[i] = tolower( pLine[i] );
  
  /* convert entire line to lowercase */
  *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

  /* ignore the comments */
  lPtr = pLine;

  while( *lPtr != ';' && *lPtr != '\0' && *lPtr != '\n' ) lPtr++;

  *lPtr = '\0';

  if( !(lPtr = strtok( pLine, "\t\n ," ) ) ) 
    return( EMPTY_LINE );

  if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ) /* found a label */{
    *pLabel = lPtr;
    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
  }
  
  *pOpcode = lPtr;

  if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
  
  *pArg1 = lPtr;
  
  if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

  *pArg2 = lPtr;
  if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

  *pArg3 = lPtr;

  if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

  *pArg4 = lPtr;

  return( OK );
}

FILE* lInfile = NULL;
FILE* outfile = NULL;

void add(FILE* outfile, char* Arg1, char* Arg2, char* Arg3, char* Arg4 ){
  char code = 1;
  char dest = Arg1[1] - 48;
  char source1 = Arg2[1] - 48;
  if('r' == Arg3[0]){
    char source2 = Arg3[1] - 48;
    int output = code<<12 | (dest<<9) | (source1 << 6) | (source2);
    fprintf(outfile, "0x%.4X\n", output);
  } else{
    // int immediate = toNum(Arg3);
    // convert source to a int and combine with the immediate
    // int source = toNum(Arg2);
    // place in destination
    // combine into one long hex and output to the file
    // "0x" + 1 + 
    // Indicate with bit 5, whether or not 
    // might be easiest to create a 16 bit thing and have place holders, break everything down and insert by bit depending on the hexcode 
  }
}
void ldw(FILE* outfile, char* Arg1, char* Arg2, char* Arg3, char* Arg4, int current_address){
  char code = 6;
  char dest = Arg1[1] - 48;
  char source1 = Arg2[1] - 48;
  int offset = toNum(Arg3)/2;
  int output = code<<12 | (dest<<9) | (source1 << 6) | (offset);
  fprintf(outfile, "0x%.4X\n", output);
}
void lea(FILE* outfile, char* Arg1, char* Arg2, char* Arg3, char* Arg4, int current_address){
  char code = 14;
  char dest = Arg1[1] - 48;
  char source1 = Arg2[1] - 48;
  int k = -1;
  for (int i =0; i<symbol_count; i++){
    if (0 == strcmp(Arg3, symbolTable[i].label)){
      k = i;
    }
  }
  int offset = (symbolTable[k].address - current_address)/2;
  int output = code<<12 | (dest<<9) | (offset);
  fprintf(outfile, "0x%.4X\n", output);
}

int main(int argc, char* argv[]) {
	
  /* open the source file */
  lInfile = fopen(argv[1], "r");
  outfile = fopen(argv[2], "w");
		 
  if (!lInfile) {
    printf("Error: Cannot open file %s\n", argv[1]);
    exit(4);
	}

  if (!outfile) {
    printf("Error: Cannot open file %s\n", argv[2]);
    exit(4);
  }



  /* Do stuff with files */
  char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1, *lArg2, *lArg3, *lArg4;
  int lRet;


  //first pass - generate the symbol table
  int start_address = 0;
  int line_counter = 0;
	do{
		lRet = readAndParse( lInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
		if( lRet != DONE && lRet != EMPTY_LINE ){
      //implement code to do stuff later
        
        //printf("%s", lLabel);
        //printf(" %s", lOpcode);
        //printf(" %s", lArg1);    //dest
        //printf(" %s\n", lArg2);  //source
        //printf(" %s\n", lArg3);    //this gets the register and the immediete
        //printf(" %s\n", lArg4);
        
      if (0 == strcmp(lOpcode, ".orig\0")){
        start_address = toNum(lArg1);
        line_counter-=2;
      }

      if (0 != strcmp(lLabel, "\0")){
        strcpy(symbolTable[symbol_count].label, lLabel);
        symbolTable[symbol_count].address = start_address + line_counter;
        symbol_count++;
      }

      line_counter+=2;
    }
	} while( lRet != DONE );
  
  /*
  for (int i = 0; i<symbol_count; i++){
    printf("%d ", symbolTable[i].address);
    printf("%s\n", symbolTable[i].label);
  }
  */

  //rewind the input doc
  rewind(lInfile);

  //second pass - write the actual output
  int current_address = 0;
  int end_found =0;
	do{
		lRet = readAndParse( lInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
		if( lRet != DONE && lRet != EMPTY_LINE ){
      //implement code to do stuff later
      if (0 == strcmp(lOpcode, ".orig\0")){
        current_address = toNum(lArg1);
      } 
      int op_result = isOpcode(lOpcode);
      switch (op_result){
        case 0: add(outfile, lArg1, lArg2, lArg3, lArg4); break;// 1/2 work
        case 1: //and(); break;
        case 2: fprintf(outfile, "0xF019\n"); break;//d works
        case 3: //jmp(); break;
        case 4: //jsr(); break;
        case 5: //jsrr(); break;
        case 6: //ldb(); break;
        case 7: ldw(outfile, lArg1, lArg2, lArg3, lArg4, current_address); break;//d works
        case 8: lea(outfile, lArg1, lArg2, lArg3, lArg4, current_address); break;//d 
        case 9: //nop(); break;//d
        case 10: //not(); break;//d
        case 11: //ret(); break;
        case 12: //lshf(); break;
        case 13: //rshfl(); break;
        case 14: //rti(); break;
        case 15: //stb(); break;//d
        case 16: //stw(); break;//d
        case 17: //trap(); break;//d
        case 18: //xor(); break;//d
        case 19: //br(); break;
        case 20: //brn(); break;
        case 21: //brz(); break;
        case 22: //brp(); break;
        case 23: //brzp(); break;//d
        case 24: //brnp(); break;//d
        case 25: //brnz(); break;//d
        case 26: //brnzp(); break;//d
        case 27: fprintf(outfile, "0x%.4X\n", toNum(lArg1)); break; //work
        case 28: fprintf(outfile, "0x%.4X\n", toNum(lArg1)); break; //work
        case 29: end_found = 1; break;
      }

      current_address+=2;

    }
	} while(0 == end_found);


  //close file at the end
  fclose(lInfile);
  fclose(outfile);
}