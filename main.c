#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Based on Wirth’s definition for EBNF we have the following rule:
[ ] means an optional item,
{ } means repeat 0 or more times.
Terminal symbols are enclosed in quote marks.
A period is used to indicate the end of the definition of a syntactic class.
*/

#define MAX_DIGITS 5
#define MAX_ID_LENGTH 11

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
    FILE *fp, *fpw;
    fp=openFile("input.txt", "r", fp);
    fpw=openFile("output.txt", "w", fpw);

    //test global arrays
    printf("%s", RESERVED_WORDS[0]);
    printf(" %d", nulsym);


    // scan input.txt -> output.txt
    char aline[100]; //I'm assuming no line will be longer than 60 characters
    while(!feof(fp)) // "while not at the end of the file"
    {
        fgets(&aline, 100, fp);
        fprintf(fpw, "%s", aline);
        //printf("\n%d", strlen(aline)-1);
        //printf(" %d", strlen(test));
    }
    rewind(fp);
    printf("\n");

    //print character by character
    char c;
    while(!feof(fp))
    {
        fscanf(fp, "%c", &c);
        printf("%c", c);
    }


    fclose(fp);
    fclose(fpw);

    return 0;
}
