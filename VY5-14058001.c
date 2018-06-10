/**

@author
Name: Berkcan Yurtsever
Student no: 14058001
Date: 10.06.2018
E-Mail: yurtseverberkcan@gmail.com or l5814001@std.yildiz.edu.tr

IDE: Dev C++
Operating System Windows 8
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 50
char variables[SIZE][3];
int variablesCount=0;
typedef struct st // struct is defined
{
	char qu[SIZE];
	int rear;
}STACK;
void initialize(STACK *st) //initializition of stack is defined
{
	st->rear=0;
}
int isEmpty(STACK *st) //control of stack empty
{
	if(st->rear==0)
		return 1;
	else
		return 0;
}
int isFull(STACK *st) //control of stack full
{
	if(st->rear==SIZE)
		return 1;
	else
		return 0;
}
void push(STACK *st,int add) //stack push method is defined
{
	if(isFull(st))
	{
		printf("No memory in the stack\n");
		exit(0);
	}
	else
	{
		st->qu[st->rear]=add;
		st->rear++;
	}
			
}
int pop(STACK *st) //stack pop method is defined
{
	if(!isEmpty(st))
	{
		st->rear--;
		return st->qu[st->rear];
	}
}
void stackShow(STACK *st) //stackShow method is defined
{
	int i;
	if(isEmpty(st))//if stack is empty
		printf("Empty");
	for(i=0;i<st->rear;i++)
	{
		printf("%c",st->qu[i]);
	}
	
}
int charToInteger(char ch) //method of char to Integer
{
	return ch-48;
}
char integerToChar(int i) //method of integer to Char
{
	return i+48;
}
void infixToPostFix(char line[]) // line is the readed line of the file
{
	STACK st;
	initialize(&st); // stack is initialized
	
	if(line[strlen(line)-1]!='\n') //if last line character is not 'new line', then new line is added.
	{
		int lenght=strlen(line);
		line[lenght]='\n';
		line[lenght+1]='\0';
	}
	
	

	char postFix[SIZE]; // postfix is defined
	int i=4,j=0,temp; //i is equal to 4. Because of the first character after the equation sembol (=)
	printf("%s",line);
	
	while(line[i]!=';') //line is the last of the equation
	{
		if(isdigit(line[i])!=0 || isalpha(line[i])!=0 ) //is line[i] is digit or alpha then it is assigned to postFix.
		{
			postFix[j]=line[i];
			postFix[j+1]=' ';
			j+=2;
		}
		if(ispunct(line[i])!=0) // if line[i] is a operator, like +,-,-,/  or ( and )
		{
			if(isEmpty(&st)) // if stack is empty, then operator is pushed immediately
			{
				push(&st,line[i]);
				push(&st,' ');
			}
			else if(line[i]=='(') //if line[i] is a '(', then it is pushed immediately
			{
				push(&st,line[i]);
				push(&st,' ');
			}
			else if(line[i]==')') //if line[i] is a ')', then all the operator are popped and they are assinged to postFix equation
			{
				temp=0;
				while(temp!=-1) //because of curly bracket
				{
				temp=pop(&st); //for ' ' (space character)
				temp=pop(&st); //for operators
				if(temp!='(')
				{
					postFix[j]=temp;
					postFix[j+1]=' ';
					j+=2;
				}
				else //if temp is equal to '(', then loop must be finish
				{	
					temp=-1;
				}
				}
			}
			else if(line[i]=='+' || line[i]=='-') //if operator is + or -
			{
				char stackUpperItem;
				temp=pop(&st); //for space character
				stackUpperItem=pop(&st); //for operator
				if(stackUpperItem=='(') //if stackUpperItem is '(' then it is pushed agein and operator and pushed
				{
					push(&st,'(');
					push(&st,' ');
					push(&st,line[i]);
					push(&st,' ');
				}
				else if(stackUpperItem=='+' || stackUpperItem=='-') //if stack upperItem is '+' or '-'
				{
					postFix[j]=stackUpperItem; //upper item of stack is assigned to postFix equation
					postFix[j+1]=' ';
					j+=2;
					push(&st,line[i]); // line[i] operator is pushed to stack
					push(&st,' ');
				}
				else if(stackUpperItem=='*' || stackUpperItem=='/') //if stackUpperItem is * or /
				{
					postFix[j]=stackUpperItem;
					postFix[j+1]=' ';
					j+=2;
					temp=0;
					while(!isEmpty(&st) && temp!=-1) //temp!=-1 for curly bracket kontrol
					{
						temp=pop(&st); // for space character
						temp=pop(&st); // for operator
						if(temp!='(') // if temp is not '('
						{
							postFix[j]=temp;
							postFix[j+1]=' ';
							j+=2;
						}
						else //if temp is a '('
						{
							push(&st,'(');
							push(&st,' ');
							temp=-1;
						}
					}
					push(&st,line[i]); //coming line[i] operator is pushed to stack
					push(&st,' '); //for space character
				}
			}
			else if(line[i]=='*' || line[i]=='/') //if line[i] is a * or /
			{
				char stackUpperItem;
				temp=pop(&st);
				stackUpperItem=pop(&st);
				if(stackUpperItem=='(') //if stackUpperItem is '('
				{
					push(&st,'('); 
					push(&st,' ');
					push(&st,line[i]); //line[i] is pushed
					push(&st,' '); //for space character
				}
				else if(stackUpperItem=='+' || stackUpperItem=='-') //if stackUpperItem is + or -
				{
					push(&st,stackUpperItem);//stackUpperItem is pushed agein, because priority of * or / is bigger than + or -
					push(&st,' ');
					push(&st,line[i]);//line[i] is pushed
					push(&st,' ');
				}
				else if(stackUpperItem=='*' || stackUpperItem=='/') //if stackUpperItem is * or /
				{
					postFix[j]=stackUpperItem;//stackUpperItem assigned to postFix
					postFix[j+1]=' ';
					j+=2;
					push(&st,line[i]); //line[i] pushed to stack
					push(&st,' ');
				}
			}
		}
		postFix[j]='\0'; //postFix is closed with null
		printf("Postfix: "); printf("%s\t",postFix); printf("Stack: "); stackShow(&st); //each of the step postFix equation and stack are shown
		printf("\n");
		i+=2;
	}
	
	while(!isEmpty(&st)) //if stack is empty, then all the operators in the stack are assigned to postFix equation
	{
		temp=pop(&st); //for space character
		postFix[j]=pop(&st);
		postFix[j+1]=' ';
		j+=2;
	}
	postFix[j]='\0';
	printf("Intermediate output:");		printf("%s\n",postFix); //if all the infix to postfix process are done,then postFix equation is shown.
	
	
	
	int result=solvingThePostFix(postFix); //postFix equation is compututed. Now, calculute the variable value using with postFix equation
	
	int location=-1; 
	for(i=0;i<variablesCount;i++)
	{
		if(variables[i][0]==line[0]) // if variable is already exist
		{
			location=i;
		}
	}
	if(location==-1) //this means coming variable is a new, not the previos variable
	{
		variables[variablesCount][0]=line[0];
		if(result>=10) //if result is bigger than or equal to 10
		{
			variables[variablesCount][1]=result/10+48; //+48 for the int to char, result/10 for the first digit
			variables[variablesCount][2]=result%10+48; //+48 for the int to char, result%10 for the last digit
			printf("%c->%c%c\n\n",variables[variablesCount][0],variables[variablesCount][1],variables[variablesCount][2]); //variable and value are shown
		}
		else if(result<10) //if result is single digit
		{
		variables[variablesCount][1]=' '; 
		variables[variablesCount][2]=result+48; //result value converted to char
		printf("%c->%c\n\n",variables[variablesCount][0],variables[variablesCount][2]); //variable and value are shown
		}
		variablesCount++; //because of the new variable, variable count are increased
	}
	else //this means coming variable is not a new, this is one of the previous variable
	{
		variables[location][0]=line[0];	
		if(result>=10)//if result is bigger than or equal to 10
		{
		variables[location][1]=result/10+48;//+48 for the int to char, result/10 for the first digit
		variables[location][2]=result%10+48;//+48 for the int to char, result%10 for the last digit
		printf("%c->%c%c\n\n",variables[location][0],variables[location][1],variables[location][2]);//variable and value are shown
		}
		else if(result<10)//if result is single digit
		{
		variables[location][1]=' ';
		variables[location][2]=result+48;//result value converted to char
		printf("%c->%c\n\n",variables[location][0],variables[location][2]);//variable and value are shown
		}
	}	
	
	
}

int solvingThePostFix(char postFix[]) //for solve the postFix equation, and calculate the value of the variable
{
	
	char temp,number11,number12,number21,number22,biggerNumber[2];
	STACK st;
	initialize(&st);
	int i,j,k,variable1,variable2,result;
	i=0;
	printf("Postfix equation: %s",postFix);
	while(i<strlen(postFix))
	{
		if(isalpha(postFix[i])!=0)
		{
			for(k=0;k<variablesCount;k++)
			{
				if(variables[k][0]==postFix[i]) //if postFix equation variables value are known, then they are showed
				{
					printf(" and ");
					printf("%c->",variables[k][0]);
					if(variables[k][1]!=' ')
					{
						printf("%c%c",variables[k][1],variables[k][2]);
					}
					else
					{
						printf("%c",variables[k][2]);
					}
					
				}
			}
		}
		i+=2; //because of the space character i+=2
	}
	printf("\n");
	i=0;
	while(i<strlen(postFix))
	{
		if(isalpha(postFix[i])!=0) //if postFix[i] is a variable like a,b,c,d
		{
			for(k=0;k<variablesCount;k++)
			{
				if(variables[k][0]==postFix[i]) // because of the find variables value, and value is pushed to stack
				{
					if(variables[k][1]!=' ')
					{
						push(&st,variables[k][1]);
						push(&st,variables[k][2]);
						push(&st,' ');
					}
					else
					{
						push(&st,variables[k][2]);
						push(&st,' ');
					}
				}
				
			}
			
		}
		if(isdigit(postFix[i])!=0) //if postFix[i] is a number
		{
			if(postFix[i+1]!=' ') //if number is not single digit
			{
				push(&st,postFix[i]);
				push(&st,postFix[i+1]);
				push(&st,' ');
				biggerNumber[0]=postFix[i];
				biggerNumber[1]=postFix[i+1];
				result=atoi(biggerNumber); //postFix number value assign to result 
			}
			else
			{
				push(&st,postFix[i]);
				push(&st,' ');
				result=charToInteger(postFix[i]); //postFix number value assign to result
			}
		}
		else if(ispunct(postFix[i])!=0) // if character is a operator
		{
			temp=pop(&st); //for space character
			number11=pop(&st); //for variable
			number12=pop(&st); //this can be variable or space character. Ýf This is a variable this means variable is not single digit
			if(number12==' ')//this means variable is single character
			{
				variable1=charToInteger(number11);
				
			}
			else //this means variable is not a single character
			{
				biggerNumber[0]=number12;
				biggerNumber[1]=number11;
				biggerNumber[2]='\0';
				variable1=atoi(biggerNumber);
				temp=pop(&st); //for the throw extra space character
			}
			number21=pop(&st);
			if(!isEmpty(&st))
			{
				number22=pop(&st);
				if(number22==' ') //this means number21 is a single character
				{
					variable2=charToInteger(number21);
					push(&st,' ');
				}
				else //if number21 is not a single character
				{
					biggerNumber[0]=number22;
					biggerNumber[1]=number21;
					biggerNumber[2]='\0';
					variable2=atoi(biggerNumber);
				}
			}
			else
			{
				variable2=charToInteger(number21);	
			}	
			
			
			
				
			
			if(postFix[i]=='*') //for the operators, process is computed
				result=variable2*variable1;
			else if(postFix[i]=='/')
				result=variable2/variable1;
			else if(postFix[i]=='+')
				result=variable2+variable1;
			else if(postFix[i]=='-')
				result=variable2-variable1;
			if(result<10) //if result is a single character, then this pushed to stack
			{
				push(&st,integerToChar(result));
				push(&st,' ');
			}
			else //if result is not a single character
			{
				char ch1,ch2;
				ch1=result/10+'0'; //calculating the first digit of result and converted to char
				ch2=integerToChar(result%10); //calculating the second digit of result and converted to char
				
				
				
				push(&st,ch1);
				push(&st,ch2);
				push(&st,' ');
			}
		}
		i+=2;
		printf("Stack: ");	stackShow(&st);
		printf("\n");
	}
	return result; // computed the postFix value is returned because it must assign to the variable
	
}
void execute(char filePath[])
{
	FILE *filePointer;
	filePointer=fopen(filePath,"r"); //file is readed
	char line[SIZE];
	int i;
	
	while(fgets(line,SIZE-1,filePointer)!=NULL) //all the equations in the file are posted to infixToPostFix method
	{
		infixToPostFix(line);
	}
	for(i=0;i<variablesCount;i++) // if all the operators are done, then all the variables value are shown
	{
		printf("%c=",variables[i][0]);
		if(variables[i][1]!=' ')	//if variables value is bigger than or equal 10, then first digit are shown
			printf("%c",variables[i][1]);
		printf("%c ",variables[i][2]); //variables value are shown
		
	}	
	
	fclose(filePointer);
	
}

int main()
{
	char filePath[SIZE]="input.txt";
	execute(filePath); 
	
	return 0;
}
