#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
char currentToken;
char previousToken;
char variables [50][80];
int valuesOfVariables[50];
int locationInVariableArray;
void getToken();
void match(char,char*);
void error(char*);
char tempVariableName[80];
int locationInTemoVariableName;
int insideVariable,insideDigit,insideStatment;

void main()
{
	locationInVariableArray=0;
	previousToken=-1;
	insideDigit=0;
	insideVariable=0;
	insideStatment=0;
	printf("calcpars" );

	while ((currentToken=getchar()) != EOF)
	{
		
			
			if (currentToken=='?')
			{
				locationInTemoVariableName=0;
				printf("question mark" );
				previousToken=currentToken;
				while((currentToken=getchar())!=EOF && currentToken != ' ' && isalpha(currentToken))
				{
				
						printf("inside isalpha" );
						printf("%c\n", currentToken );
						tempVariableName[locationInTemoVariableName]=currentToken;
						locationInTemoVariableName++;
						previousToken=currentToken;
					
					
				}
				printf("%s, %s\n",tempVariableName,variables[0] );
				if (isThereAVariable(tempVariableName))
				{
					printf("there is a variable %i, %i, %i\n",valuesOfVariables[isThereAVariable(tempVariableName)],isThereAVariable(tempVariableName),valuesOfVariables[0] );
				}
				
			}else if (isalpha(currentToken))
			{
				locationInTemoVariableName=0;
				tempVariableName[locationInTemoVariableName]=currentToken;
				locationInTemoVariableName++;
				while((currentToken=getchar())!=EOF && isalpha(currentToken) && currentToken != ' ')
				{
					tempVariableName[locationInTemoVariableName]=currentToken;
						locationInTemoVariableName++;
						previousToken=currentToken;
				}
				printf(" variable 0%s\n", variables[0]);
				if (isThereAVariable(tempVariableName))
				{
					printf("is a match %c", currentToken);
				}else
				{
					stringCopyForMe(locationInVariableArray,tempVariableName);
					printf("%s\n",variables[locationInVariableArray] );
					int sum=currentToken-'0';
					while((currentToken=getchar())!=EOF && isdigit(currentToken))
					{
						sum = sum*10 + (currentToken-'0');

					}
					printf("%i\n", sum );
					valuesOfVariables[locationInVariableArray]=sum;
					locationInVariableArray++;
				}
				printf("is alpha" );

			}else if (isdigit(currentToken))
			{
				printf("is digit" );
			}

		
		

		
		printf(" previous Token %c\n", previousToken);
		printf("%c\n", currentToken);

		if (previousToken=='$')
		{
			if (currentToken=='$')
			{
				exit(1);
			}
		}

		previousToken=currentToken;
	}
}
void getToken(){
/* tokens are characters */
	currentToken = getchar();
}
void match(char c, char* message){
	if (currentToken == c) getToken();
	else error(message);
}

void error(char* message){
	printf("parse error: %s\n", message);
	exit(1);
}
int isThereAVariable(char * variableName){
	int i;
	for (i=0;i<50;i++)
	{
		if (strcmp(variableName,variables[i])==0)
		{
			return i;
		}
	}
	return -1;
}
int stringCopyForMe(int location, char* stringToCopy){
	int i;
	for (i=0;i<80 ;i++)
	{
		variables[location][i] = stringToCopy[i];
	}
}
int stringCompareMine (int location, char * stringToCompare)
{
	int i=0;
	int isTheSame=1;
	while (i<80 && stringToCompare[i]!='\0')
	{
		if (variables[location][i]!=stringToCompare[i])
		{
			isTheSame=0;
		}
		i++;
	}
}