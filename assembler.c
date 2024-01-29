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
    "brnzp\0"
    ".orig\0",
    ".fill\0",
    ".end\0\0",
    };
  //30 codes
int isOpcode (char * lPtr){
  for (int i = 0; i<27; i++){
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
  int symbol_count = 0;
  int start_address = 0;
  int line_counter = 0;
	do{
		lRet = readAndParse( lInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
		if( lRet != DONE && lRet != EMPTY_LINE ){
      //implement code to do stuff later
        /*
        printf("%s", lLabel);
        printf(" %s", lOpcode);
        printf(" %s", lArg1);
        printf(" %s", lArg2);
        printf(" %s", lArg3);
        printf(" %s\n", lArg4);
        */
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
	do{
		lRet = readAndParse( lInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
		if( lRet != DONE && lRet != EMPTY_LINE ){
      //implement code to do stuff later
      
    }
	} while( lRet != DONE );


  //close file at the end
  fclose(lInfile);
  fclose(outfile);
}