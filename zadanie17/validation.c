#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "list.h"
#include "validation.h"
#include "exits.h"

static int insMode = insON;
void SpecialSymbols(char *buffer, int *size, int *i);
void BackSpace(char *buffer, int *size, int *i);
void PutCharacter(unsigned char tmp, char *buffer, int *size, int *i);
void PutCharacterInsert(unsigned char tmp, char *buffer, int *size, int *i);


void SpecialSymbols(char *buffer, int *size, int *i)
{
	CONSOLE_CURSOR_INFO CURSOR;
	unsigned char tmp;
	tmp = getch();

	if(tmp == LEFTARR && (*i) > 0)
	{
		putch('\b');
		(*i)--;
	}
	if(tmp == RIGHTARR && (*i) < (*size))
	{
		putch(buffer[(*i)]);
		(*i)++;
	}
	if(tmp == INS)
	{
		if(insMode == insON)
		{
			insMode = insOFF;
			CURSOR.dwSize = 100;
			SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &CURSOR);
		}
		else
		{
			insMode = insON;
			CURSOR.dwSize = 20;
			SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &CURSOR);
		}
	}
}
void BackSpace(char *buffer, int *size, int *i)
{
	int k;

	if((*size) == (*i))
	{
		putch('\b');
		putch(' ');
		putch('\b');
		(*i)--;
		(*size)--;
	}
	else
	{
		(*i)--;
		for(k = (*i); k <= (*size); k++)
		{
			buffer[k] = buffer[(k + 1)];
		}

		(*size)--;
		putch('\b');

		for(k = (*i); k < (*size); k++)
		{
			putch(buffer[k]);
		}

		putch(' ');

		for(k = (*size); k >= (*i); k--)
		{
			putch('\b');
		}
	}
}
void PutCharacter(unsigned char tmp, char *buffer, int *size, int *i)
{
	putch(tmp);
	buffer[(*i)] = tmp;
	(*i)++;
	(*size)++;
}
void PutCharacterInsert(unsigned char tmp, char *buffer, int *size, int *pos)
{
	int i;

	for (i = (*size); i >= (*pos); i--) 
	{
		buffer[i] = buffer[(i - 1)];
	}

	buffer[(*pos)] = tmp;
	(*size)++;

	for(i = (*pos); i < (*size); i++)
	{
		putch(buffer[i]);
	}

	(*pos)++;

	for(i = (*size); i > (*pos); i--)
	{
		putch('\b');
	}
}
__int64 IdNomer(void)
{
	__int64 idnomer;
	char buffer[11];
	unsigned char tmp;
	int pos = 0, size = 0;

	printf("Vuvedete ID Nomer:");
	while(1)
	{
		tmp = getch();

		if(tmp == SPECIAL)
		{
			SpecialSymbols(buffer, &size, &pos);
		}
		else if(tmp == ESC)
		{
			return ESCAPE;     
		}
		else if(tmp == BACKSPACE && pos > 0  && pos <= 11)
		{
			BackSpace(buffer, &size, &pos);
		}
		else if(tmp >= ZERO && tmp <= NINE && size < 10)
		{
			if(insMode == insOFF)
			{
				PutCharacter(tmp, buffer, &size, &pos);
			}
			else
			{
				if(pos == size)
				{
					PutCharacter(tmp, buffer, &size, &pos);
				}
				else
				{
					PutCharacterInsert(tmp, buffer, &size, &pos);
				}
			}
		}
		else if(tmp == ENTER)
		{
			if(size == 10)
			{
				idnomer = _atoi64(buffer);
				return idnomer;
			}
		}
	}
}
int Naimenovanie(char buffer[])
{
	char tmp;
	int i = 0;

	printf("\n");
	printf("Vuvedete naimenovanie na stokata:");
	while(1)
	{
		tmp = getch();

		if((tmp >= ACAP && tmp <= ZCAP && i < 60) || (tmp >= AMIN && tmp <= ZMIN && i < 60))
		{
			putch(tmp);
			buffer[i] = tmp;
			i++;    
		}
		else if(tmp == ENTER)
		{
			buffer[i] = '\0';
			break;
		}
		else if(tmp == ESC)
		{
			return ESCAPE;
		}
		else if(tmp == BACKSPACE && i > 0)
		{
			putch('\b');
			putch(' ');
			putch('\b');
			i--; 
		}
		else if(tmp == SPACE && i < 60)
		{
			putch(' ');
			buffer[i] = ' ';
			i++; 
		}
	}
	return SUCC;
}
double EdCena(void)
{
	char buffer[100];
	double cena;
	char tmp;
	int i = 0;

	printf("\n");
	printf("Vuvedete edinichna cena:");
	while(1)
	{
		tmp = getch();
		if(tmp == ENTER)
		{
			cena = atof(buffer);
			return cena;
		}
		else if(tmp >= ZERO && tmp <= NINE)
		{
			putch(tmp);
			buffer[i] = tmp;
			i++;    
		}
		else if(tmp == ESC)
		{
			return ESCAPE;     
		}
		else if(tmp == BACKSPACE && i > 0)
		{
			putch('\b');
			putch(' ');
			putch('\b');
			i--; 
		}
		else if(tmp == COMMA || tmp == POINT)
		{
			putch('.');
			buffer[i] = '.';
			i++;
		}
	}
}
int Kolichestvo(void)
{
	char buffer[9];
	int kolichestvo;
	char tmp;
	int i = 0;

	printf("\n");
	printf("Vuvedete kolichestvo na stokata:");
	while(1)
	{
		tmp = getch();
		if(tmp == ENTER)
		{
			kolichestvo = atoi(buffer);
			return kolichestvo;
		}
		else if(tmp >= ZERO && tmp <= NINE && i < 9)
		{
			putch(tmp);
			buffer[i] = tmp;
			i++;    
		}
		else if(tmp == BACKSPACE && i > 0)
		{
			putch('\b');
			putch(' ');
			putch('\b');
			i--; 
		}
		else if(tmp == ESC)
		{
			return ESCAPE;     
		}
	}
}
int SrokNaGodnost(void)
{
	char buffer[9];
	int godnost;
	char tmp;
	int i = 0;

	printf("\n");
	printf("Vuvedete srok na godnost na stokata:");
	while(1)
	{
		tmp = getch();
		if(tmp == ENTER)
		{
			godnost = atoi(buffer);
			return godnost;
		}
		else if(tmp >= ZERO && tmp <= NINE && i < 9)
		{
			putch(tmp);
			buffer[i] = tmp;
			i++;    
		}
		else if(tmp == BACKSPACE && i > 0)
		{
			putch('\b');
			putch(' ');
			putch('\b');
			i--; 
		}
		else if(tmp == ESC)
		{
			return ESCAPE;     
		}
	}

}
int Proizvoditel(char buffer[])
{
	char tmp;
	int i = 0;

	printf("\n");
	printf("Vuvedete proizvoditel:");
	while(1)
	{
		tmp = getch();


		if((tmp >= ACAP && tmp <= ZCAP && i < 40) || (tmp >= AMIN && tmp <= ZMIN && i < 40) || (tmp >= ZERO && tmp <= NINE && i < 40))
		{
			putch(tmp);
			buffer[i] = tmp;
			i++;    
		}
		else if(tmp == ENTER)
		{
			buffer[i] = '\0';
			break;
		}
		else if(tmp == ESC)
		{
			return ESCAPE;
		}
		else if(tmp == BACKSPACE && i > 0)
		{
			putch('\b');
			putch(' ');
			putch('\b');
			i--; 
		}
		else if(tmp == SPACE && i < 40)
		{
			putch(' ');
			buffer[i] = ' ';
			i++; 
		}
	}
	return SUCC;
}
int DaNomer(char buffer[])
{
	char tmp;
	int i = 0;

	printf("\n");
	printf("Vuvedete danuchen nomer:");	

	while(1)
	{
		tmp = getch();
		if(i == 0)
		{
			if(tmp >= ACAP && tmp <= ZCAP)
			{
				putch(tmp);
				buffer[i] = tmp;
				i++;
			}
		}
		else if(tmp == BACKSPACE && i > 0)
		{
			putch('\b');
			putch(' ');
			putch('\b');
			i--; 			
		}
		else if(tmp == ENTER && i == 9)
		{
			buffer[i] = '\0';
			return SUCC;
		}
		else if(tmp >= ZERO && tmp <= NINE && i < 9)
		{
			putch(tmp);
			buffer[i] = tmp;
			i++;
		}
		else if(tmp == ESC)
		{
			return ESCAPE;
		}
	}
}
int Data(char buffer[])
{
	char tmp;
	int i = 0;

	printf("\n");
	printf("Vuvedete data na proizvodstvo:");
	while(1)
	{
		tmp = getch();
		switch(i)
		{
			case 0:
			{
				if(tmp >= ZERO && tmp <= THREE)
				{
					putch(tmp);
					buffer[i] = tmp;
					i++;
				}
				break;
			}
			case 1:
			{
				if(tmp >= ZERO && tmp <= NINE)
				{
					putch(tmp);
					buffer[i] = tmp;
					i++;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
				}
				break;
			}
			case 2:
			{	
				if(tmp == COMMA || tmp == POINT)
				{
					putch('.');
					buffer[i] = '.';
					i++;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
				}
				break;
			}
			case 3:
			{
				if(tmp == ZERO || tmp == ONE)
				{
					putch(tmp);
					buffer[i] = tmp;
					i++;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
					
				}
				break;
			}
			case 4:
			{
				if(tmp >= ONE && tmp <= NINE)
				{
					putch(tmp);
					buffer[i] = tmp;
					i++;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
				}
				break;
			}
			case 5:
			{	
				if(tmp == COMMA || tmp == POINT)
				{
					putch('.');
					buffer[i] = '.';
					i++;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
				}
				break;
			}
			case 6:
			{
				if(tmp == ONE || tmp == TWO)
				{
					putch(tmp);
					buffer[i] = tmp;
					i++;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
				}
				break;
			}
			case 7:
			{
				if(tmp == ZERO || tmp == NINE)
				{
					putch(tmp);
					buffer[i] = tmp;
					i++;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
				}
				break;
			}
			case 8:
			{
				if(tmp == NINE || tmp == ZERO || tmp == ONE)
				{
					putch(tmp);
					buffer[i] = tmp;
					i++;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
				}
				break;
			}
			case 9:
			{
				if(tmp >= ZERO && tmp <= NINE)
				{
					putch(tmp);
					buffer[i] = tmp;
					i++;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
				}
				break;
			}
			case 10:
			{
				if(tmp == ENTER)
				{
					buffer[i] = '\0';
					return 0;
				}
				else if(tmp == BACKSPACE)
				{
					putch('\b');
					putch(' ');
					putch('\b');
					i--;
				}
				break;
			}
		}
	}
}