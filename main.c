#include <stdio.h>
#include <stdlib.h>

/*
Based on Wirth’s definition for EBNF we have the following rule:
[ ] means an optional item,
{ } means repeat 0 or more times.
Terminal symbols are enclosed in quote marks.
A period is used to indicate the end of the definition of a syntactic class.
*/

char * RESERVED_WORDS[] = {"const", "var", "procedure", "call", "if", "then", "else", "while", "do", "read", "write", "odd"};
char SPECIAL_SYMBOLS[] = {'+', '-', '*', '/', '(' , ')', '=', ',' , '.', '<', '>',  ';' , ':' };

// token types
typedef enum {
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, lbracesym, rbracesym, ifsym, thensym,
whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
readsym , elsesym
}token_type;

// opens the file
FILE *openFile(char fileName[], char mode[], FILE *fp)
{
    fp=fopen(fileName, mode);
    if(fp==NULL)
    {
        printf("Could not open %s\n", fileName);
        exit(0);
    }
    printf("file opened\n");
    return fp;
}

int main()
{
    FILE* fp;
    fp=openFile("input.txt", "r", fp);

    printf("%s", RESERVED_WORDS[0]);
    printf(" %d", nulsym);

    char achar;

    while(!feof(fp)) // "while not at the end of the file"
    {
      fscanf(fp, "%c", achar);
      printf("%c", achar);
    }



    return 0;
}
