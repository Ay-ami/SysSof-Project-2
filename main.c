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

#define MAX_DIGITS 5 + 1
#define MAX_ID_LENGTH 11 + 1

char * RESERVED_WORDS[] = {"const", "var", "procedure", "call", "if", "then", "else", "while", "do", "read", "write", "odd"};
char SPECIAL_SYMBOLS[] = {'+', '-', '*', '/', '(' , ')', '=', ',' , '.', '<', '>',  ';' , ':' };

// token types
typedef enum {
nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
multsym = 6,  slashsym = 7, oddsym = 8, eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18,
periodsym = 19, becomessym = 20, lbracesym = 21, rbracesym = 22, ifsym = 23, thensym = 24,
whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
readsym = 32, elsesym = 33
}token_type;

struct token{
    int ID;
    char litValue[MAX_DIGITS]; // if it is a number
    char nameEnum[MAX_ID_LENGTH];
}token;

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

 //print character by character and ignores comments
void removeComments (FILE *fp, FILE *fpw, char *arr)
{
    char c, lc = NULL; //"character" and "last character"
    int commentFlag = 0, i = 0;
    while(!feof(fp))
    {
        fscanf(fp, "%c", &c);
        // checks to see if it's the beginning of a comment
        if ( c == '*' )
            if ( lc == '/' )
                commentFlag = 1;
        // prints if it's not inside of a comment and if it's not the very first thing scanned
        if(commentFlag == 0 && lc != NULL)
        {
            fprintf(fpw, "%c", lc); // yes we print "last character" and not the current one
            arr[i] = lc;
            i++;
        }
        // checks if a comment has ended
        if( c == '/')
            if ( lc == '*' )
            {
                commentFlag = 0;
                c = NULL; // no this doesn't have anything to do with that NULL up there, it's just a patch for a dumb quirk
            }
        // assigns the current character to "last character"
        lc = c;
    }
    //arr[i] = '\0';
}

int main()
{
    FILE *fp, *fpw;
    fp=openFile("input.txt", "r", fp);
    fpw=openFile("output.txt", "w", fpw);

    //test global arrays
    printf("%s", RESERVED_WORDS[0]);
    printf(" %d", nulsym);

/*
    // scan input.txt -> output.txt
    char line[100]; //I'm assuming no line will be longer than 60 characters
    while(!feof(fp)) // "while not at the end of the file"
    {
        fgets(&line, 100, fp);
        fprintf(fpw, "%s", line);
        //printf("\n%d", strlen(line)-1);
        //printf(" %d", strlen(test));
    }
    rewind(fp);
    printf("\n");
*/

    char *anArray = calloc(1000, sizeof(char));
    removeComments(fp, fpw, anArray);

    // cycle through string index by index
    int i = 0;
    while (anArray[i] != '\0')
    {
        printf("%c", anArray[i]);
        i++;
    }


    struct token tokens[strlen(anArray)];



    fclose(fp);
    fclose(fpw);

    return 0;
}
