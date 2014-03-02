#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
char currentToken;
char previousToken;
void getToken();
void match(char,char*);
void error(char*);
char* tempVariableName;
int locationInTemoVariableName;
int insideVariable,insideDigit,insideStatment;

void main()
{
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
				while((currentToken=getchar())!=EOF)
				{
					if (isalpha(currentToken))
					{
						printf("inside isalpha" );
						tempVariableName[locationInTemoVariableName];
						locationInTemoVariableName++;
						previousToken=currentToken;
					}
				}
				printf(tempVariableName);
				printf("%c\n",currentToken );
			}else if (isalpha(currentToken))
			{
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