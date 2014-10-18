#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct symbol
{
	int kind;
	char name[12];
	int val;
	int level;
	int addr;
}symbol;

/*
typedef enum
{
	nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
	multsym = 6,  slashsym = 7, oddsym = 8, eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
	gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18,
	periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24,
	whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
	readsym = 32, elsesym = 33
} token_type;
*/
typedef enum
{
	nulsym = 1, identsym, numbersym, plussym, minussym,
	multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
	gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
	periodsym, becomessym, beginsym, endsym, ifsym, thensym,
	whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
	readsym , elsesym
} token_type;

token_type token;
int token_num = 0;
symbol* read_file();
void get_token(symbol *symbols);
void program(symbol *symbols);
void block(symbol *symbols);
void statement(symbol *symbols);
void expression(symbol *symbols);
void condition(symbol *symbols);
void term(symbol *symbols);
void factor(symbol *symbols);

void get_token(symbol *symbols)
{
	token = symbols[token_num].kind;
	//if (token == 2)
		//printf("token = %d\tname = %s\t", token, symbols[token_num].name);
	//else if (token == 3)
		//printf("token = %d\tvalue = %d\t", token, symbols[token_num].val);
	//else
		//printf("token = %d\t", token);
	token_num++;
}

int main()
{
	symbol *symbols = read_file();
	program(symbols);

	return 0;
}

void program(symbol *symbols)
{
	//printf("\t\tline 71\n");
	get_token(symbols);
	block(symbols);

	if (token != periodsym)
	{
		printf("Period Expected!\n");
		EXIT_FAILURE;
	}

}

void block(symbol *symbols)
{
	if (token == constsym)
	{
		do
		{
			//printf("\t\tline 89\n");
			get_token(symbols);
			if (token != identsym)
			{
				printf("Expected an Identity Symbol!\n");
				EXIT_FAILURE;
			}
			//printf("\t\tline 96\n");
			get_token(symbols);
			if (token != eqsym)
			{
				printf("Expected an Equal Symbol\n");
				EXIT_FAILURE;
			}
			//printf("\t\tline 103\n");
			get_token(symbols);
			if (token != numbersym)
			{
				printf("Expected a number\n");
				EXIT_FAILURE;
			}
			//printf("\t\tline 110\n");
			get_token(symbols);
			//get_token(symbols);
		} while (token == commasym);
		if (token != semicolonsym)
		{
			printf("Expected a Semicolon\n");
			EXIT_FAILURE;
		}
		//printf("\t\tline 119\n");
		get_token(symbols);
	}
	if (token == varsym)
	{
		do
		{
			//printf("\t\tline 126\n");
			get_token(symbols);
			if (token != identsym)
			{
				printf("Expected an Identity Symbol!\n");
				EXIT_FAILURE;
			}
			//printf("\t\tline 132\n");
			get_token(symbols);
		} while (token == commasym);

		if (token != semicolonsym)
		{
			printf("Expected a Semicolon\n");
			EXIT_FAILURE;
		}
		//printf("\t\tline 142\n");
		get_token(symbols);
	}
	/*
	do
	{
		get_token(symbols);
		if (token != identsym)
		{
			printf("Expected an Identity Symbol!\n");
			EXIT_FAILURE;
		}
		get_token(symbols);
		if (token != semicolonsym)
		{
			printf("Expected a Semicolon\n");
			EXIT_FAILURE;
		}
		get_token(symbols);
		block(symbols);
		if (token != semicolonsym)
		{
			printf("Expected a Semicolon\n");
			EXIT_FAILURE;
		}
		get_token(symbols);

	} while (token == procsym);
	*/
	statement(symbols);
}

void statement(symbol *symbols)
{
	if (token == identsym)
	{
		//printf("\t\tline 178\n");
		get_token(symbols);
		//printf("token = %d\n", token);
		if (token != becomessym)
		{
			printf("Expected a Becomes Symbol\n");
			EXIT_FAILURE;
		}
		//printf("\t\tline 185\n");
		get_token(symbols);
		expression(symbols);
	}
	else if (token == callsym)
	{
		//printf("\t\tline 191\n");
		get_token(symbols);
		if (token != identsym)
		{
			printf("Expected an Identity Symbol\n");
			EXIT_FAILURE;
		}
		//printf("\t\tline 198\n");
		get_token(symbols);
	}
	else if (token == beginsym)
	{
		//printf("\t\tline 203\n");
		get_token(symbols);
		statement(symbols);
		while (token == semicolonsym)
		{
			//printf("\t\tline 208\n");
			get_token(symbols);
			statement(symbols);
		}
		if (token != endsym)
		{
			printf("Expected an End Symbol\n");
			EXIT_FAILURE;
		}
		//printf("\t\tline 220\n");
		get_token(symbols);
	}
	else if (token == ifsym)
	{
		//printf("\t\tline 225\n");
		get_token(symbols);
		condition(symbols);
		if (token != thensym)
		{
			printf("Expected a Then Symbol!\n");
			EXIT_FAILURE;
		}
		//printf("\t\tline 233\n");
		get_token(symbols);
		statement(symbols);
	}
	else if (token == whilesym)
	{
		//printf("\t\tline 238\n");
		get_token(symbols);
		condition(symbols);
		if (token != dosym)
		{
			printf("Expected a Do Symbol\n");
			EXIT_FAILURE;
		}
		//printf("\t\tline 247\n");
		get_token(symbols);
		statement(symbols);
	}
	else if (token == readsym)
	{
		get_token(symbols);
		if (token != identsym)
		{
			printf("Expected an Identity Symbol!\n");
			EXIT_FAILURE;
		}
		get_token(symbols);
	}
	else if (token == writesym)
	{
		get_token(symbols);
		if (token != identsym)
		{
			printf("Expected an Identity Symbol!\n");
			EXIT_FAILURE;
		}
		get_token(symbols);
	}
}

void condition(symbol *symbols)
{
	if (token == oddsym)
	{
		//printf("\t\tline 257\n");
		get_token(symbols);
		expression(symbols);
	}
	else
	{
		expression(symbols);
		if (token != eqsym && token != neqsym && token != leqsym && token != gtrsym && token != geqsym)
		{
			printf("Unexpected Expression\n");
			EXIT_FAILURE;
		}
		//printf("\t\tline 269\n");
		get_token(symbols);
		expression(symbols);
	}
}

void expression(symbol *symbols)
{
	if (token == plussym || token == minussym)
	{
		//printf("\t\tline 279\n");
		get_token(symbols);
	}
	term(symbols);
	while (token == plussym || token == minussym)
	{
		//printf("\t\tline 285\n");
		get_token(symbols);
		term(symbols);
	}
}

void term(symbol *symbols)
{
	factor(symbols);
	while (token == multsym || token == slashsym)
	{
		//printf("\t\tline 296\n");
		get_token(symbols);
		factor(symbols);
	}
}

void factor(symbol *symbols)
{
	if (token == identsym)
	{
		//printf("\t\tline 306\n");
		get_token(symbols);
	}
	else if (token == numbersym)
	{
		//printf("\t\tline 311\n");
		get_token(symbols);
	}
	else if (token == lparentsym)
	{
		//printf("\t\tline 316\n");
		get_token(symbols);
		expression(symbols);
		if (token != rparentsym)
		{
			printf("Expected a Right Parenthesis Symbol\n");
			EXIT_FAILURE;
		}
		//printf("\t\tline 324\n");
		get_token(symbols);
	}
	else
	{
		printf("Error. Unexpected Symbol\n");
	}
}

symbol* read_file()
{
    int inc = 0;
	int x = 1;
	FILE *ifp = fopen("lexemelist.txt","r");
	symbol *symbols = malloc(sizeof(symbol) * 1000);
	int c = 0;
	int counter = -1;
	int continued = 0;
	int string_position = 0;
	while(1)
	{
		c = fgetc(ifp);//getting the character, if the character is the end of file then we break out of it
		if(c == EOF)
			break;

		if(c== ' ' || c == '\n')
		{
		    if(symbols[counter].kind == 3){

                c = fgetc(ifp);
                symbols[counter].val = (c - '0');
                c = fgetc(ifp);
                while(!inc){
                        if(c == ' ' || c == '\n')
                            inc =1;
                        else{
                    symbols[counter].val = symbols[counter].val *10 + (c- '0');
                    c = fgetc(ifp);
                        }

                }
                }
            inc = 0;
            continued = 0;

		}//check if space


		else
		{//if not space its a digit or word

			if(isdigit(c))
			{// if digit
				string_position = 0;
				if(continued == 0)
				{
				    //check if its first number
					counter++;
					continued = 1;
					symbols[counter].kind = c - '0';

				}

				else
				{//if not first number add it
					symbols[counter].kind = symbols[counter].kind * 10 + (c - '0');
				}


			}
			else
			{	//if not a number its a string
				symbols[counter].name[string_position] = c ;
				string_position ++;
				while(x)
				{
					c  = fgetc(ifp);
					if(c == EOF || c == ' ')
						x = 0;
					else
					{
						symbols[counter].name[string_position] = c ;
						string_position ++;
					}

					//printf("%s %d\n\n",symbols[counter].name, counter);
				}
				continued = 0;
			}
		}
		//printf("%d %s\n",symbols[counter].kind,symbols[counter].name);
	}


	return symbols;

}