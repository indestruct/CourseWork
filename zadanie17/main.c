#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "list.h "
#include "file.h"
#include "logic.h"
#include "exits.h"

int main(void)
{
	int x, c = 0;
	struct Firm *tmp = NULL;
	struct Firm *Ehead = NULL;
	struct Firm *head = NULL;
	Ehead = EmptyList(Ehead);
	if(Ehead == NULL)
	{
		printf("No memory!\n");
		return 0;
	}

	do{
		printf("1: Dobavqne na nova stoka\n");
		printf("2: Promqna na nalichnostite\n");
		printf("3: Stoki s iztekul srok na godnost\n");
		printf("4: Spravka za vsichki proizvoditeli\n");
		printf("5: Spravka za vsichki nalichni stoki\n");
		printf("6: Zapis v fail\n");
		printf("7: Chetene ot fail\n");
		printf("8: Izhod\n");
		c = getch();
		switch(c)
		{
		case '1':
			{
				head = AddList(head, Ehead);
				if(head == NULL)
				{
					printf("\n");
					printf("Firmata ne e dobavqne.\n");
				}
				else
				{
					printf("\n");
					printf("Firmata e dobavena.\n");
				}
				break;
			}
		case '2':
			{
				x = Nalichnosti(&head, &Ehead);
				if(x == SUCC)
				{
					printf("Promqnata e uspeshna");
				}
				break;
			}
		case '3':
			{
				IztekulSrok(head);
				break;
			}
		case '4':
			{
				x = Spravka(head);
				if(x == NOMEM)
				{
					printf("No memory\n");
				}
				else if(x == ERROR)
				{
					printf("Nqma dobaveni firmi");
				}
				break;
			}
		case '5':
			{
				x = PrintList(head);
				if(x == ERROR)
				{
					printf("Ne sa namereni firmi za printirane\n");
				}
				break;
			}
		case '6':
			{
				x = WriteToBin(head);
				if(x == ERROR)
				{
					printf("Neuspeshno zapisvane v fail\n");
				}
				else
				{
					printf("Uspeshno zapisvane v fail");
				}
				break;
			}
		case '7':
			{
				x = ReadFromBin(&head);
				if(x == ERROR)
				{
					printf("Neuspeshno chetene ot fail\n");
				}
				break;
			}
		}
	} while(c != '8');
	return 0;
}