#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char currentToken;
char variables [50][80];
int valuesOfVariables[50];


int placeInVariableArray;
void resetVariableArray(char * );
void command();
char getToken();
void checkForVariable();
void checkIfIsAVariable();
int isThereAVariable(char * );
int stringCompareMine (int, char * );
int isVariable(char *, int );
void match(char , char* );
int expr();
void error(char* );
void parse();
int main()
{
	
	valuesOfVariables[0]=2;
	placeInVariableArray=0;
	
	parse();
	
	//printf("%s\n", tempVariableName);
}
void parse(){
		getToken(); /* get the first token */
		command(); /* call the parsing procedure for the start symbol */
}
void command(){

	/* command -> expr '\n' */
	checkForVariable();
	checkIfIsAVariable();
	 /*if(isdigit(currentToken))
	{
		//if the input is not a variable just a calculation
	}else
	{
		printf("%s\n","not correct syntax" );
	}*/
	//int result = expr();
	parse();
	
}
void checkIfIsAVariable()
{
	int placeInTempVeriableName=0;
	char tempVariableName[80];
	if (isalpha(currentToken))
	{
		//if a variable
		
		tempVariableName[placeInTempVeriableName]=currentToken;
		placeInTempVeriableName++;
		if (isVariable(tempVariableName, placeInTempVeriableName)==1)
		{
			printf("%c token after is variable\n", currentToken);
			
			if (currentToken=='=')
			{
				printf ("inside equal");
				currentToken=getToken();
				int resultOfExpression=expr();
				if (isThereAVariable(tempVariableName)!=-1)
				{
					valuesOfVariables[isThereAVariable(tempVariableName)]=resultOfExpression;
				}
				else
				{
					stringCopyForMe(placeInVariableArray,tempVariableName);
					valuesOfVariables[placeInVariableArray]=resultOfExpression;
					placeInVariableArray++;
				}
			}
		}

		


	}
}
int expr(){
		/* expr -> term { '+' term } */
		int result = term();
		while (currentToken == '+'){
			match('+', "+ expected");
			result += term();
			}
		return result;
		}
void checkForVariable()
{
	int placeInTempVeriableName=0;
	char tempVariableName[80];
	
	
	if (currentToken=='?')
	{
		printf("question mark" );
			

			
			if (isVariable(tempVariableName, placeInTempVeriableName)==1)
			{
				printf("%s, %s\n",tempVariableName,variables[0] );
				if (isThereAVariable(tempVariableName)!=-1)
				{
					printf("there is a variable %i, %i, %i\n",valuesOfVariables[isThereAVariable(tempVariableName)],isThereAVariable(tempVariableName),valuesOfVariables[0] );
				}else
				{
					printf("%s\n", "no such variable");
				}
			}else{
				printf("%s\n", "was not a variable name" );
			}
	}
			
}
char getToken()
{
	currentToken=getchar();
	
	if (currentToken=='$')
	{
		currentToken=getchar();

		if (currentToken=='$')
		{
			exit(1);
		}
	}
	
}
int isVariable(char * tempVariableName, int placeInTempVeriableName)
{
	int wasSucesful=0;
	currentToken=getToken();
	while(currentToken!=EOF && isalpha(currentToken) && currentToken != '\n' && currentToken != '\0' )
				{
					tempVariableName[placeInTempVeriableName]=currentToken;
					printf("%i\n",placeInTempVeriableName );
						placeInTempVeriableName++;
						
						wasSucesful=1;
						currentToken=getToken();
				}
	tempVariableName[placeInTempVeriableName]='\0';

	printf("%s is variable\n", tempVariableName );
	return wasSucesful;

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
void match(char c, char* message){
	if (currentToken == c) getToken();
	else error(message);
}
void error(char* message){
	printf("parse error: %s\n", message);
	exit(1);
	}
int term(){
		/* term -> factor { '*' factor } */
		int result = factor();
		while (currentToken == '*'){
			match('*', "* expected");
	 		result *= factor();
	 	}
		return result;
	}
int factor(){
		/* factor -> '(' expr ')' | number */
		int result;
		if (currentToken == '('){
		match('(', "( expected");
		result = expr();
		match(')', ") expected");
	}
	else
	result = number();
	return result;
	}
int number(){
	printf("\n inside number" );
	int result=0;
	int placeInTempVeriableName=0;
	char tempVariableName[80];
	if (isalpha(currentToken))
	{
		tempVariableName[placeInTempVeriableName]=currentToken;
		placeInTempVeriableName++;
		if (isVariable(tempVariableName, placeInTempVeriableName)==1)
		{
			if (isThereAVariable(tempVariableName))
			{
				result=valuesOfVariables[isThereAVariable(tempVariableName)];
			}
		}	
	}else
	{
		/* number -> digit { digit } */
		result = digit();
		while (isdigit(currentToken))
		/* the value of a number with a new trailing digit
		is its previous value shifted by a decimal place
		plus the value of the new digit
		 */
			result = 10 * result + digit();
	}
	
	return result;
	}
	int digit(){
		/* digit -> '0' | '1' | '2' | '3' | '4'
		| '5' | '6' | '7' | '8' | '9' */
		int result;

		if (isdigit(currentToken)){
			/* the numeric value of a digit character
			is the difference between its ascii value and the
			ascii value of the character '0'
			*/
			result = currentToken - '0';
			match(currentToken, "( expected");
		}
		else
		error("digit expected");
		return result;
	}
	int stringCopyForMe(int location, char* stringToCopy){
	int i,n;
	for (i=0;i<80 && stringToCopy[i]!='\0' ;i++)
	{
		variables[location][i] = stringToCopy[i];
		n=i;
	}
	variables[location][n+1]='\0';
}
void resetVariableArray(char * arrayToBeReset)
{
	int i;
	for (i=0;i<strlen(arrayToBeReset);i++)
	{
		arrayToBeReset[i]='\0';
	}
}