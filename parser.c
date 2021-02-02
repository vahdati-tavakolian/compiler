#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char prod[39][30] = {"Stmt->expr^Stmt" , "Stmt->var^Stmt" , "Stmt->cond[Stmt]Stmt" , "Stmt->loop[Stmt]Stmt" ,
				     "Stmt->inp^Stmt" , "Stmt->outp^Stmt" , "Stmt->!" , "var->Sahih id var'" , "var->Ashari id var\"" ,
				     "var->Harf id & ch" , "var'->!" , "var'->& num" , "var\"->!" , "var\"->& num" ,
				     "inp->Begir(literal,id)" , "outp->Benevis(liretal,id)" , "cond->agar{expr logop expr}" , "loop->ta{expr logop expr}" ,
				     "expr->E expr'" , "expr->mathop expr*" , "expr->(expr\"" , "expr'->!" , "expr'->mathop expr*" , "expr\"->E mathop expr*)",
				     "expr\"->mathop expr*)" , "E->num E'" , "E->id" , "E->YekiBala" , "E'->YekiPain" , "mathop->Jam" ,
				     "mathop->Bagimonde" , "mathop->Kam" , "mathop->Tagsim" , "mathop->Zarb" ,
				     "logop->&B" , "logop->&BM" , "logop->&K" , "logop->KM" , "logop->&MM"};
				  
char table[15][31][20] = {{"expr^Stmt","expr^Stmt","var^Stmt","var^Stmt","var^Stmt","","inp^Stmt","outp^Stmt","cond[Stmt]Stmt",
						   "ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","!","!","ll","ll","ll"},
						  {"ll","ll","Sahihidvar'","Ashariidvar\"","Harfid&ch","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","&num","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","!","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","&num","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","!","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","ll","Begir(literal,id)","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","ll","ll","Benevis(liretal,id)","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","ll","ll","ll","agar{exprlogopexpr}","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","ll","ll","ll","ll","ta{exprlogopexpr}","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"Eexpr'","Eexpr'","ll","ll","ll","ll","ll","ll","ll","ll","mathopexpr",
						   "mathopexpr","mathopexpr","mathopexpr","mathopexpr","ll","ll","ll","ll","ll","ll","ll","ll","(expr\"","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","mathopexpr","mathopexpr","mathopexpr","mathopexpr","mathopexpr",
						   "ll","ll","!","!","!","!","!","!","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"Emathopexpr*)","Emathopexpr*)","ll","ll","ll","ll","ll","ll","ll","ll",
						   "mathopexpr","mathopexpr","mathopexpr","mathopexpr","mathopexpr","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"numE'","id","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","YekiBala","YekiPain","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","Jam","Bagimonde","Kam","Tagsim","Zarb","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						  {"ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","ll","&B","&BM","&K","&KM","&MM","ll","ll","ll","ll","ll","ll","ll","ll","ll"},
						 };
						 
int stack[1000];
int top = 0;
char x[100][10];
int counter=0;

#define BUFFER_SIZE 1000			

void printtable();
void input(FILE *tokens);
void changeinp(const char *buffer);
int ll1(const char *inp);
int pop();
void push(int x);
void update_stack(const char *st);
void run();
void print_stack();


int main()
{
	for(int i =0;i<1000;i++)
	{
		stack[i]=0;
	}
	
	stack[0]=43;
	top++;
	stack[1]=1;
	top++;
	
	/*printf("The Grammar is:\n");
	for(int i=0;i<39;i++)
	{
		printf("%s\n",prod[i]);
	}*/
	
	//printtable();  //for print parsing table
	
	FILE *tokens;
	char path[100]= "/home/parham/Desktop/git/tokens.txt";
	tokens  = fopen(path, "r");
	if (tokens == NULL)
	{
		printf("Unable to open file.\n");
		printf("Please check you have read/write previleges.\n");
		exit(EXIT_FAILURE);
	}

	input(tokens);

	fclose(tokens);
	
	return 0;
}

void printtable()
{
	printf("Predictive Parsing Table is:\n\n");
	printf("\tnum   id   Sahih   Ashari   Harf   &   Begir   Benevis   agar   ta   Jam   Bagimonde   Kam   Tagsim   Zarb   YekiBala   YekiPain   &B   &BM   &K   &KM   &MM   ^   (   )   [   ]   $\n");
	for(int i=0;i<189;i++)
		printf("-");
		
	printf("\n");
		
	for(int j=0;j<15;j++)
	{
		if(j == 0)
			printf("Stmt");
		else if(j == 1)
			printf("var");
		else if(j == 2)
			printf("var");
		else if(j == 3)
			printf("var");
		else if(j == 4)
			printf("var");
		else if(j == 5)
			printf("var");
		else if(j == 6)
			printf("var");
		else if(j == 7)
			printf("var");
		else if(j == 8)
			printf("var");
		else if(j == 9)
			printf("var");
		else if(j == 10)
			printf("var");
		else if(j == 11)
			printf("var");
		else if(j == 12)
			printf("var");
		else if(j == 13)
			printf("var");
		else
			printf("var");
			
		for(int k=0;k<28;k++)
		{
			printf("    %s",table[j][k]);
		}
		printf("\n");
	}
	
}

void input(FILE *tokens)  //read each line of input
{
	char buffer[BUFFER_SIZE];
    
    while ((fgets(buffer, BUFFER_SIZE, tokens)) != NULL)
    {        
		changeinp(buffer);
		run();
    }
 
}

void changeinp(const char *buffer)  //separate input to words that we nee
{
	char newString[20][20]; 
    int i,j,ctr;
    
    j=0; ctr=0;
    for(i=0;i<=(strlen(buffer));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(buffer[i]==' '||buffer[i]=='\0'||buffer[i]=='\n')
        {
            newString[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j] = buffer[i];
            j++;
        }
    }
    
    
    for(i=0;i < ctr;i++)
    {
		if(strcmp(newString[i],"Keyword") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"EqualOperation") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"semicolon") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"ParantezBaz") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"ParantezBaste") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"BelakBaz") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"BelakBaste") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"++") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"--") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"mathop") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"logop") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"AkoladBaz") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],"AkoladBaste") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		else if(strcmp(newString[i],",") == 0)
		{
			//ll1(newString[i+2]);
			strcpy(x[counter++],newString[i+2]);
			break;
		}
		//------------------------------------------
		else if(strcmp(newString[i],"id") == 0)
		{
			//ll1(newString[i]);
			strcpy(x[counter++],newString[i]);
			break;
		}
		else if(strcmp(newString[i],"num") == 0)
		{
			//ll1(newString[i]);
			strcpy(x[counter++],newString[i]);
			break;
		}
		else if(strcmp(newString[i],"$") == 0)
		{
			//ll1(newString[i]);
			strcpy(x[counter++],newString[i]);
			break;
		}
		
	}
	
}

int pop()
{
	if (top == 0)
		printf("stack underflow\n");
	else
		return stack[top--];
}

void push(int x)
{
	if (top == 999)
		printf("stack overflow\n");
	else 
		stack[++top]=x;
}


int ll1(const char *inp)
{
	int temp=0;
	
	/*if(strcmp(inp,"Stmt")==0)
		temp = 1;
	else if(strcmp(inp,"var")==0)
		temp = 2;
	else if(strcmp(inp,"var'")==0)
		temp = 3;
	else if(strcmp(inp,"var\"")==0)
		temp = 4;
	else if(strcmp(inp,"inp")==0)
		temp = 5;
	else if(strcmp(inp,"outp")==0)
		temp = 6;
	else if(strcmp(inp,"cond")==0)
		temp = 7;
	else if(strcmp(inp,"loop")==0)
		temp = 8;
	else if(strcmp(inp,"expr")==0)
		temp = 9;
	else if(strcmp(inp,"expr'")==0)
		temp = 10;
	else if(strcmp(inp,"expr\"")==0)
		temp = 11;
	else if(strcmp(inp,"E")==0)
		temp = 12;
	else if(strcmp(inp,"E'")==0)
		temp = 13;
	else if(strcmp(inp,"mathop")==0)
		temp = 14;
	else if(strcmp(inp,"logop")==0)
		temp = 15;*/
	if(strcmp(inp,"num")==0)
		temp = 16;
	else if(strcmp(inp,"id")==0)
		temp = 17;
	else if(strcmp(inp,"Sahih")==0)
		temp = 18;
	else if(strcmp(inp,"Ashari")==0)
		temp = 19;
	else if(strcmp(inp,"Harf")==0)
		temp = 20;
	else if(strcmp(inp,"&")==0)
		temp = 21;
	else if(strcmp(inp,"Begir")==0)
		temp = 22;
	else if(strcmp(inp,"Benevis")==0)
		temp = 23;
	else if(strcmp(inp,"agar")==0)
		temp =24;
	else if(strcmp(inp,"ta")==0)
		temp = 25;
	else if(strcmp(inp,"Jam")==0)
		temp = 26;
	else if(strcmp(inp,"Bagimonde")==0)
		temp = 27;
	else if(strcmp(inp,"Kam")==0)
		temp = 28;
	else if(strcmp(inp,"Tagsim")==0)
		temp = 29;
	else if(strcmp(inp,"Zarb")==0)
		temp = 30;
	else if(strcmp(inp,"YekiBala")==0)
		temp = 31;
	else if(strcmp(inp,"YekiPain")==0)
		temp = 32;
	else if(strcmp(inp,"&B")==0)
		temp = 33;
	else if(strcmp(inp,"&BM")==0)
		temp = 34;
	else if(strcmp(inp,"&K")==0)
		temp = 35;
	else if(strcmp(inp,"&KM")==0)
		temp = 36;
	else if(strcmp(inp,"&MM")==0)
		temp = 37;
	else if(strcmp(inp,"^")==0)
		temp = 38;
	else if(strcmp(inp,"(")==0)
		temp = 39;
	else if(strcmp(inp,")")==0)
		temp = 40;
	else if(strcmp(inp,"[")==0)
		temp = 41;
	else if(strcmp(inp,"]")==0)
		temp = 42;
	else if(strcmp(inp,"$")==0)
		temp = 43;
	else if(strcmp(inp,"{")==0)
		temp = 44;
	else if(strcmp(inp,"}")==0)
		temp = 45;
	else if(strcmp(inp,",")==0)
		temp = 46;
		
	return temp;
}

void update_stack(const char *st)
{
	if(strcmp(st,"expr^Stmt")==0)
	{
		push(1);
		push(38);
		push(9);
	}
	else if(strcmp(st,"var^Stmt")==0)
	{
		push(1);
		push(38);
		push(2);
	}
	else if(strcmp(st,"inp^Stmt")==0)
	{
		push(1);
		push(38);
		push(5);
	}
	else if(strcmp(st,"outp^Stmt")==0)
	{
		push(1);
		push(38);
		push(6);
	}
	else if(strcmp(st,"cond[Stmt]Stmt")==0)
	{
		push(1);
		push(42);
		push(1);
		push(41);
		push(7);
	}
	else if(strcmp(st,"!")==0)
	{
		pop();
	}
	else if(strcmp(st,"Sahihidvar")==0)
	{
		push(2);
		push(17);
		push(18);
	}
	else if(strcmp(st,"Sahihidvar'")==0)
	{
		push(3);
		push(17);
		push(18);
	}
	else if(strcmp(st,"Ashariidvar\"")==0)
	{
		push(4);
		push(17);
		push(19);
	}
	else if(strcmp(st,"Harfid&ch")==0)
	{
		push(17);
		push(4);
		push(17);
		push(19);
	}
	else if(strcmp(st,"&num")==0)
	{
		push(16);
		push(21);
	}
	else if(strcmp(st,"Begir(literal,id)")==0)
	{
		push(40);
		push(17);
		push(46);
		push(17);
		push(39);
		push(22);
	}
	else if(strcmp(st,"Benevis(literal,id)")==0)
	{
		push(40);
		push(17);
		push(46);
		push(17);
		push(39);
		push(23);
	}
	else if(strcmp(st,"agar{exprlogopexpr}")==0)
	{
		push(45);
		push(9);
		push(15);
		push(9);
		push(44);
		push(24);
	}
	else if(strcmp(st,"ta{exprlogopexpr}")==0)
	{
		push(45);
		push(9);
		push(15);
		push(9);
		push(44);
		push(25);
	}
	else if(strcmp(st,"Eexpr'")==0)
	{
		push(10);
	}
	else if(strcmp(st,"mathopexpr")==0)
	{
		push(9);
		push(14);
	}
	else if(strcmp(st,"(expr\"")==0)
	{
		push(11);
		push(39);
	}
	else if(strcmp(st,"Emathopexpr*)")==0)
	{
		push(40);
		push(9);
		push(14);
		push(12);
	}
	else if(strcmp(st,"numE'")==0)
	{
		push(13);
		push(16);
		push(14);
		push(12);
	}
	else if(strcmp(st,"id")==0)
	{
		push(17);
	}
	else if(strcmp(st,"YekiPain")==0)
	{
		push(32);
	}
	else if(strcmp(st,"Jam")==0)
	{
		push(26);
	}
	else if(strcmp(st,"YekiPain")==0)
	{
		push(32);
	}
	else if(strcmp(st,"Kam")==0)
	{
		push(28);
	}
	else if(strcmp(st,"Bagimande")==0)
	{
		push(27);
	}
	else if(strcmp(st,"Tagsim")==0)
	{
		push(29);
	}
	else if(strcmp(st,"Zarb")==0)
	{
		push(30);
	}
	else if(strcmp(st,"&B")==0)
	{
		push(33);
	}
	else if(strcmp(st,"&BM")==0)
	{
		push(34);
	}
	else if(strcmp(st,"&K")==0)
	{
		push(35);
	}
	else if(strcmp(st,"&KM")==0)
	{
		push(36);
	}
	else if(strcmp(st,"&MM")==0)
	{
		push(37);
	}
	
}

void run()
{
	//printf("%s\n",x[counter-1]);
	for(int i=0;i<counter;i++)
	{
		while(stack[top] != ll1(x[i]))
		{
			if(stack[top]>15)
				update_stack(table[pop()][ll1(x[i])-16]);
			else
				update_stack(table[pop()-1][ll1(x[i])-16]);
		}
		if(stack[top] == ll1(x[i]))
			pop();
		print_stack();
		//printf("%s\n",table[pop()-1][ll1(x[i])-16]);
	}
	
}

void print_stack()
{
	int i =0;
	while(stack[i]>0)
	{
		printf("%d\n",stack[i]);
		i++;
	}
	printf("**********\n");
}
















