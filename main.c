#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Based on Wirth�s definition for EBNF we have the following rule:
[ ] means an optional item,
{ } means repeat 0 or more times.
Terminal symbols are enclosed in quote marks.
A period is used to indicate the end of the definition of a syntactic class.
*/

#define MAX_DIGITS 5 + 1
#define MAX_ID_LENGTH 11 + 1

//                            0       1         2          3      4     5       6        7      8       9      10      11
char * RESERVED_WORDS[] = {"const", "var", "procedure", "call", "if", "then", "else", "while", "do", "read", "write", "odd"};
char SPECIAL_SYMBOLS[] = {'+', '-', '*', '/', '(' , ')', '=', ',' , '.', '<', '>',  ';' , ':' };
char *LITERAL_ID[] = {"", " ", "id", "number", "+", "-", "*", "/", "odd", "=", "<>", "<", "<=", ">", ">=",
"(", ")", ",", ";", ".", ":=", "{", "}", "if", "then", "while", "do", "call", "const", "var", "procedure",
"write", "read", "else"};
/*char *LITERAL_ID[] = {" ", "nulsym", "identsym", "numbersym", "plussym", "minussym",
"multsym",  "slashsym", "oddsym", "eqsym", "neqsym", "lessym", "leqsym", "gtrsym", "geqsym",
"lparentsym", "rparentsym", "commasym", "semicolonsym", "periodsym", "becomessym", "lbracesym",
"rbracesym", "ifsym", "thensym", "whilesym", "dosym", "callsym", "constsym", "varsym", "procsym",
"writesym", "readsym", "elsesym"};*/
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
    int value; // if it is a number
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

// returns 1 if true, returns 0 if false
int isTrueString (char* bigStr, int place, int whichWord)
{
    int i = 0;
    char word[strlen(RESERVED_WORDS[whichWord])]; // word is as long as the reserved word we want to compare it to
    strcpy(word, RESERVED_WORDS[whichWord]);// copy the reserved word into the empty string "word"

    // if the string would have been too long for bigStr then it is false automatically
    if (strlen(bigStr) < place + strlen(word))
        return 0;
    // check letter by letter
    for (i = 0 ; i < strlen(word) ; i++)
    {
        if (word[i] != bigStr[place + i])
            return 0;
    }
    // check if it is the whole word or simply a substring
    if(bigStr[place + i] != ' ')
        return 0;

    // return the word's length if it truly is the same word
    return 1;
}

void lexemeTable (FILE *fpw, struct token *tokens)
{
    fprintf(fpw, "\n\nLexeme Table: \n");
    fprintf(fpw, "lexeme \t\t token type\n");

    for(int i = 0 ; tokens[i].ID != 0 ; i++)
    {
        if ( tokens[i].ID == 2 ) // if var
        {
            fprintf(fpw, "%-11s %6d\n", tokens[i].nameEnum, tokens[i].ID);
        }
        else if (tokens[i].ID == 3)
        {
             fprintf(fpw, "%-11d %6d\n", tokens[i].value, tokens[i].ID);
        }
        else{
            fprintf(fpw, "%-11s %6d\n", LITERAL_ID[tokens[i].ID], tokens[i].ID);
        }
    }

}

void lexemeList (FILE *fpw, struct token *tokens)
{
    fprintf(fpw, "\n\nLexeme List\n");

    for(int i = 0 ; tokens[i].ID != 0 ; i++)
    {
        fprintf(fpw, "%d ",tokens[i].ID);
        if (tokens[i].ID == 2)
        {
            fprintf(fpw, "%s ", tokens[i].nameEnum);
        }
        fprintf(fpw, " ");
    }
}

int main()
{
    FILE *fp, *fpw;
    fp=openFile("input.txt", "r", fp);
    fpw=openFile("output.txt", "w", fpw);

    /*
    //test global arrays
    printf("%s", RESERVED_WORDS[0]);
    printf(" %d", nulsym);
    */

    char *anArray = calloc(1000, sizeof(char));
    removeComments(fp, fpw, anArray);

    // an array of structs for the tokens which is the length of the array we just built
    struct token tokens[strlen(anArray)];

    /*
    // Dummy Tokens:
    tokens[0].ID = 4;
    tokens[0].value = 0;
    strcpy(tokens[0].nameEnum, "");

    tokens[1].ID = 3;
    tokens[1].value = 99;
    strcpy(tokens[1].nameEnum, "");

    tokens[2].ID = 5;
    tokens[2].value = 0;
    strcpy(tokens[2].nameEnum, "");

    tokens[3].ID = 2;
    tokens[3].value = 0;
    strcpy(tokens[3].nameEnum, "steve");

    tokens[4].ID = 0; // "done" token

    // print out dummy tokens in the console
    int sizeOfStruct = 4;
    for(int i = 0 ; tokens[i].ID != 0 ; i++)
    {
        printf("ID: %d\n", tokens[i].ID);
        printf("litVal: %d\n", tokens[i].value);
        printf("nameEnum: %s\n", tokens[i].nameEnum);
    }
    */

    // print lexeme table
    lexemeTable(fpw, tokens);

    // print lexeme list
    lexemeList(fpw, tokens);

    fclose(fp);
    fclose(fpw);

    return 0;
}
