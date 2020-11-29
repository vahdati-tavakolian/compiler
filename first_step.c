#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void find_lexeme(char *str, int a);
#define OUT    0 
#define IN    1 

struct lex
{
	char lexeme[15];
	char type[15];
	int value;
	float value2;
};

int main(int argc, char **argv)
{
	FILE *fadr;
	
    char *filename = "/home/parham/Desktop/gozaresh/3/codes/file.txt";  //this is the location of our txt file change it to yours if need
 
    fadr = fopen(filename, "r");  //"r" it's for READING a file
    
    if (fadr == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    
    int max = -1;
    char a;
    while( ( a = fgetc(fadr) ) != EOF )  //EOF point to the end of the file
       max=max+1;
	
	//printf("%d\n",max);   //just for testing
	
	fclose(fadr);  //we should close the file before use EOF again
//---------------------------------------------------------------------
	fadr = fopen(filename, "r");
    
    char str[max];  //we use "max" for length of our string that define up
    
	char ch;
    
    int counter=0;
    while ((ch = fgetc(fadr)) != EOF)  //for read a character from file
    {
		str[counter] = ch;
        counter++;
	}
	
	/*
	for(int i=0;i<counter;i++)	//just for testing
	{
		printf("%c",str[i]);
	}
	*/
	
	find_lexeme(str,counter);  //counter it's size of str
    
    fclose(fadr);
	
	return 0;
}

void find_lexeme(char *str,int a)
{
	char *str2;		//we define str2 and copy str into it for work and change it
	for(int i=0;i<a;i++) 
	{
		str2[i] = str[i];
	}
	
	printf("%s\n",str2);  //just for testing
	
	int state = OUT;
    unsigned lex_counter = 0;  //to coun number of exemes in our string
  
    // Scan all characters one by one 
    while (*str2) 
    { 
        // If next character is a separator, set the  
        // state as OUT 
        if (*str2 == ' ' || *str2 == '\n' || *str2 == '\t') 
            state = OUT; 
  
        // If next character is not a word separator and
        // state is OUT, then set the state as IN and  
        // increment lex counter 
        else if (state == OUT) 
        { 
            state = IN; 
            ++lex_counter; 
        } 

        // Move to next character 
        ++str2; 
    }
    

	printf("Number of lexemes: %d",lex_counter);		//just for testing
	
	struct lex lex_array[lex_counter];
	
	/*for(int j=0;j<=lex_counter;j++)
	{
		lex_array[j].lexeme = 
	}*/
	
}
