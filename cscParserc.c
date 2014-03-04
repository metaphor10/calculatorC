#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char currentToken;
char previousToken;
char variables [50][80];
int valuesOfVariables[50];
char tempVariableName[80];
int locationInTemoVariableName;
int locationInVariableArray;
int sum1;
char op='+';

int main()
{
	locationInVariableArray=0;
	previousToken=-1;
	while ((currentToken=getToken()) != EOF)
	{
		if (currentToken==' ')
		{
			continue;
		}

		printf(" previous Token %c\n", previousToken);
			printf("%c\n", currentToken);
			if (currentToken=='?')
			{
				checkForVariable();
			}else if (isalpha(currentToken))
			{
				int locationOfVariableInArray;
				locationOfVariableInArray=enterAValueToAVariable();
				if (currentToken=='=')
				{
					
					sum1=0;
					while((currentToken=getToken())!= EOF)
					{
						if (isdigit(currentToken))
						{
							printf("inside number" );
							sum1 = number();
						}else if (isalpha(currentToken))
						{
							sum1 = getVariableValue();
						}else if (currentToken=='+')
						{
							currentToken=getToken();
							if (isdigit(currentToken))
							{
								sum1 = sum1 + number();
							}else if (isalpha(currentToken))
							{
								sum1 = sum1 + getVariableValue();
							}
						}
					}
					valuesOfVariables[locationOfVariableInArray]=sum1;
				}

			}


		
	}
}


int getVariableValue()
{
	if (!isalpha(currentToken))
	{
		printf("inside not is alpha" );
		locationInVariableArray++;
		tempVariableName[locationInVariableArray]='\0';
		if((isVariableInArray(tempVariableName))!=-1)
		{
			printf("inside is variable" );
			printf("%s\n",tempVariableName );
			return(isVariableInArray(tempVariableName));
		}
		else
		{
			printf("no such variab");
			exit(1);
		}
	}else
	{
		printf("inside is alpah" );
		tempVariableName[locationInVariableArray]=currentToken;
		locationInVariableArray++;
		getToken();
		return(getVariableValue());
	}
}
int isVariableInArray(char * variableName){
	int i;
	for (i=0;i<50;i++)
	{
		if (stringCompareMine(i,variableName))
		{
			return valuesOfVariables[i];
		}
	}
	return -1;
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
	return isTheSame;
}
int digit()
{
	int result;
	if (isdigit(currentToken))
	{
		result=currentToken-'0';
		getToken();

	}else
	{
		printf("not a digit" );
	}
	return result;
}
int number(){
	/* number -> digit { digit } */
	int result = digit();
	while (isdigit(currentToken))
	/* the value of a number with a new trailing digit
	is its previous value shifted by a decimal place
	plus the value of the new digit
	 */
		result = 10 * result + digit();
	return result;
	}
int isThereAVariable(char * variableName){
	int i;
	for (i=0;i<50;i++)
	{
		if (stringCompareMine(i,variableName))
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
int isVariable()
{
	int wasSucesful=0;
	while((currentToken=getToken())!=EOF && isalpha(currentToken) && currentToken != ' ')
				{
					tempVariableName[locationInTemoVariableName]=currentToken;
						locationInTemoVariableName++;
						
						wasSucesful=1;
				}
	return wasSucesful;

}
int checkForVariable()
{
	locationInTemoVariableName=0;
					printf("question mark" );
					getToken();
					tempVariableName[locationInTemoVariableName]=currentToken;
					locationInTemoVariableName++;

					
					if (isVariable())
					{
						printf("%s, %s\n",tempVariableName,variables[0] );
						if (!isThereAVariable(tempVariableName))
					{
						printf("there is a variable %i, %i, %i\n",valuesOfVariables[isThereAVariable(tempVariableName)],isThereAVariable(tempVariableName),valuesOfVariables[0] );
					}
					}
}
int enterAValueToAVariable()
{
	locationInTemoVariableName=0;
					tempVariableName[locationInTemoVariableName]=currentToken;
					locationInTemoVariableName++;
					isVariable();
					tempVariableName[locationInTemoVariableName]='\0';
					printf(" variable 0%s\n", variables[0]);
					if (!isThereAVariable(tempVariableName))
					{
						return (isThereAVariable(tempVariableName));
					}else
					{
						stringCopyForMe(locationInVariableArray,tempVariableName);
						printf("%s\n",variables[locationInVariableArray] );
						return locationInVariableArray;
						locationInVariableArray++;
					}
					printf("is alpha" );
}
void getToken()
{

	previousToken=currentToken;
	while((currentToken=getchar())==' ');
	if (currentToken=='$')
	{
		if (previousToken=='$')
		{
			exit(1);
		}
	}
}