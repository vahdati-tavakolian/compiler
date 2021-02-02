#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1000

//DEFINE our source program's keywords , identifier , numbers --- We can also use regular expression for this part
char keyword[30][30] = {"Benevis" , "Begir" , "agar" , "ta" , "Sahih" , "Ashari" , "Harf"};
char logop[30][30] = {"&B" , "&BM" , "&K" , "&KM" , "&MM"}; //logical operation like > , >= , < , <= , == in c
char mathop[30][30] = {"Jam" , "Kam" , "Zarb" , "Tagsim" , "Bagimonde"}; //Mathematical Operators like + , -  , * , / , % in c
char id[20] , num[10];


/* Function declarations */
int  isEmpty(const char *str);
void removeEmptyLines(FILE *srcFile, FILE *tempFile);
void printFile(FILE *fptr);
void recognitionToken(FILE *srcFile2, FILE *tokens);
int check_keyword(char s[]);
int check_mathop(char s[]);
int check_logop(char s[]);

int main()
{
    FILE *srcFile;
    FILE *tempFile;

    char path[100] = "/home/parham/Desktop/git/srcFile2.txt";


    /* Input file path */    //in my computer : /home/parham/Desktop/srcFile2.txt
    //printf("Enter file path: ");
    //scanf("%s", path);


    /* Try to open file */
    srcFile  = fopen(path, "r");
    tempFile = fopen("remove-blanks.tmp", "w");


    /* Exit if file not opened successfully */
    if (srcFile == NULL || tempFile == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");

        exit(EXIT_FAILURE);
    }



    printf("\nFile contents before removing all empty lines.\n\n");
    printFile(srcFile);


    // Move src file pointer to beginning
    rewind(srcFile);

    // Remove empty lines from file.
    removeEmptyLines(srcFile, tempFile);


    /* Close all open files */
    fclose(srcFile);
    fclose(tempFile);


    /* Delete src file and rename temp file as src */
    remove(path);
    rename("remove-blanks.tmp", path);


    printf("\n\n\nFile contents after removing all empty line.\n\n");

    // Open source file and print its contents
    srcFile = fopen(path, "r");
    printFile(srcFile);
    fclose(srcFile);
    
    char path2[100] = "/home/parham/Desktop/git/tokens.txt";
    
    /* Input file path */    //in my computer : /home/parham/Desktop/tokens.txt
    //printf("\n\nEnter token's file path: ");
    //scanf("%s", path2);
    
    //Define new file that point to the same address of srcFile
    FILE *srcFile2 , *tokens;
    srcFile2 = fopen(path,"r");
    tokens = fopen(path2,"w");
	
	recognitionToken(srcFile2 , tokens);
	
	fclose(tokens);
    fclose(srcFile2);
    

    return 0;
}


/*
Print contents of a file.
*/
void printFile(FILE *fptr)
{
    char ch;

    while((ch = fgetc(fptr)) != EOF)
        putchar(ch);
}



/*
Checks, whether a given string is empty or not.
A string is empty if it only contains white space
characters.

Returns 1 if given string is empty otherwise 0.
*/
int isEmpty(const char *str)
{
    char ch;

    do
    {
        ch = *(str++);

        // Check non whitespace character
        if(ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && ch != '\0')
            return 0;

    } while (ch != '\0');

    return 1;
}



/*
Function to remove empty lines from a file.
*/
void removeEmptyLines(FILE *srcFile, FILE *tempFile)
{
    char buffer[BUFFER_SIZE];

    while ((fgets(buffer, BUFFER_SIZE, srcFile)) != NULL)
    {
        /* If current line is not empty then write to temporary file */
        if(!isEmpty(buffer))
            fputs(buffer, tempFile);
    }
}

void recognitionToken(FILE *srcFile2, FILE *tokens)
{
	char c;
	int state=0;
	int i=0 , j=0;
	
	/*
	state 1 = for alphanometric characters and use for recognition keyword, id, logop, mathop
	state 2 = for digit characters and use for recognition numbers
	state 3-5 = for recognition COMMENTS
	*/ 
	
	while((c = fgetc(srcFile2)) != EOF)
	{
		switch(state)
		{
			case 0: if(isalpha(c) || c == '_' || c == '&'){
							state=1;
							id[i++] = c;
					}
						else if(isdigit(c)){  //hamoon 3
							state=2;
							num[j++] = c;
						}
							else if(c == '/'){  //hamoon 10
								state=3;
							}
								else if(c == ' ' || c == '\t' || c == '\n')  //if we see a whitespace character we set the state to 0 until see another type character
									state=0;
									else
									{
										//fprintf(tokens,"\n%c",c);
										if(c == '^')
										{
											fprintf(tokens , "semicolon : %c\n",c);
											fprintf(tokens , "$");
										}
										else if(c == '(')
											fprintf(tokens , "ParantezBaz : %c\n",c);
										else if(c == ')')
											fprintf(tokens , "ParantezBaste : %c\n",c);
										else if(c == '[')
											fprintf(tokens , "BelakBaz : %c\n",c);
										else if(c == ']')
											fprintf(tokens , "BelakBaste : %c\n",c);
										else if(c == ']')
											fprintf(tokens , "BelakBaste : %c\n",c);
										else if(c == ']')
											fprintf(tokens , "BelakBaste : %c\n",c);
										else if(c == '{')
											fprintf(tokens , "AkoladBaz : %c\n",c);
										else if(c == '}')
											fprintf(tokens , "AkoladBaste : %c\n",c);
										else if(c == ',')
											fprintf(tokens , ", : %c\n",c);
									}
					break;
					
			case 1: if(isalnum(c))  //isalnum(): this function checks whether the given character is alphanomeric or not from <ctype.h> library
					{
						state=1;
						id[i++] = c;
					}
					else
					{
						id[i] = '\0';
						if(check_keyword(id))
							fprintf(tokens, "Keyword : %s\n",id);
						else if(check_logop(id))
							fprintf(tokens, "logop : %s\n",id);
						else if(strcmp(id,"YekiBala") == 0 )
							fprintf(tokens , "++ : %s\n",id);
						else if(strcmp(id,"YekiPain") == 0)
							fprintf(tokens , "-- : %s\n",id);
						else if(check_mathop(id))
							fprintf(tokens, "mathop : %s\n",id);
						else if(id[i-1] == '&')
							fprintf(tokens , "EqualOperation : %s\n",id);
						else
							fprintf(tokens, "id : %s\n",id);
						
						state=0;
						i=0;
						
						ungetc(c,srcFile2);
					}
					
					break;
					
			case 2 :if(isdigit(c)||c =='.')
						{
							num[j++]=c;
							state = 2;
						}
						else
						{
							num[j] = '\0';
							fprintf(tokens,"num : %s\n",num);
							state=0 ; 
							j=0;
							ungetc(c,srcFile2);	
						}
						
						break;
					 
		    case 3: if(c == '*')
					  state=4;
					else
					  //fprintf(tokens, "inavalid lexeme\n");
					
			        break;
			  
			case 4: if(c != '*')
					  state=4;
					else
					  state=5;
						
					break;
					
			case 5: if(c == '*')
						state=5;
					else if(c == '/')
						state=0;
					else
						state=4;

					break;
						 
		}	
	}
}

int check_keyword(char s[])
{
	for (int i=0 ; i <7; i++)
	{
		if(strcmp(s,keyword[i]) == 0)  //strcmp is a function from <string.h> library for comparisson two const char * 
			return 1;
	}
	
	return 0;
}

int check_mathop(char s[])
{
	for (int i=0 ; i <7; i++)
	{
		if(strcmp(s,mathop[i]) == 0)   //strcmp is a function from <string.h> library for comparisson two const char *
			return 1;
	}
	return 0;
}

int check_logop(char s[])
{
	for (int i=0 ; i <5; i++)
	{
		if(strcmp(s,logop[i]) == 0)   //strcmp is a function from <string.h> library for comparisson two const char *
			return 1;
	}
	return 0;
}



