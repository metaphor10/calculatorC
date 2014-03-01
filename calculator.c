#include <stdio.h>
#include <ctype.h>
#define IN 1
#define OUT 0
main()
{
	int c,nl,nw,nc,state;
	int constantValue[50];
	char variables[50][80];
	char possibleOp[4];
	possibleOp[0]='+';
	possibleOp[1]='-';
	possibleOp[2]='/';
	possibleOp[3]='*';
	char tempStrg[80];
	state=OUT;
	int sizeOfVariableName[50];
	int sizeOfDigit[50];
	nl=0;
	while ((c=getchar())!=EOF)
	{
		if (state==OUT)
		{
			if (c !='\n' && c != ' ' && c != '\t')
			{
				if (isalpha(c))
				{
					state=IN;
					tempStrg[nl]=c;
					nl++;


				}else if (c=='?')
				{
					state=IN;
				}
			}

		}else
		{

		}
	}
	printf("%d, %d, %d",nl,nw,nc);

}