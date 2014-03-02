#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
int token;
int currentVariable=0; 
char variables[50][80];
char tempStrg[80];
int constantValue[50];
/* holds the current input character for the parse */
/* declarations to allow arbitrary recursion */
void command();
int expr();
int term();
int factor();
int number();
int digit();
void error(char* message){
	printf("parse error: %s\n", message);
	exit(1);
	}
void getToken(){
/* tokens are characters */
	token = getchar();
	}
	void match(char c, char* message){
	if (token == c) getToken();
	else error(message);
	}
	void getLetter()
	{
		if (isalpha(token))
		{
			getToken();
		}else
		{
			error("not a letter");
		}
	}
	void command(){
	/* command -> expr '\n' */
	int result = expr();
	if (token == '\n') /* end the parse and print the result */
	printf("The result is: %d\n",result);
	else error("tokens after end of expression");
	}
	int expr(){
		/* expr -> term { '+' term } */
		int result = term();
		while (token == '+'){
			match('+', "+ expected");
			result += term();
			}
		return result;
		}
	int term(){
		/* term -> factor { '*' factor } */
		int result = factor();
		while (token == '*'){
			match('*', "* expected");
	 		result *= factor();
	 	}
		return result;
	}
	int factor(){
		/* factor -> '(' expr ')' | number */
		int result;
		if (token == '('){
		match('(', "( expected");
		result = expr();
		match(')', ") expected");
	}
	else
	result = number();
	return result;
	}
	void variable (){
		int locationInTempString=0;
		int result=letter();
		tempStrg[locationInTempString]=result;

		while(isalpha(token))
		{
			locationInTempString++;
			tempStrg[locationInTempString]=letter();
		}
		strcpy(variables[currentVariable],tempStrg);

	}
	int letter (){
		int result =token;
		if (isalpha(token))
		{
			getLetter();

		}else
		{
			error("not a letter");
		}
		return result;
	}
	int number(){
	/* number -> digit { digit } */
	int result = digit();
	while (isdigit(token))
	/* the value of a number with a new trailing digit
	is its previous value shifted by a decimal place
	plus the value of the new digit
	 */
		result = 10 * result + digit();
	return result;
	}
	int digit(){
		/* digit -> '0' | '1' | '2' | '3' | '4'
		| '5' | '6' | '7' | '8' | '9' */
		int result;
		if (isdigit(token)){
			/* the numeric value of a digit character
			is the difference between its ascii value and the
			ascii value of the character '0'
			*/
			result = token - '0';
			match(token, "( expected");
		}
		else
		error("digit expected");
		return result;
	}


	void parse(){
		getToken(); /* get the first token */
		command(); /* call the parsing procedure for the start symbol */
		}
	int main(){
		parse();
		return 0;
		}