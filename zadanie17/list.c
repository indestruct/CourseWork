#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "list.h"
#include "logic.h"
#include "exits.h"
#include "validation.h"

struct Firm* AddElements(struct Firm* Ehead);
struct Firm* SearchList(struct Firm *head);
struct Firm* DeleteFromList(struct Firm **head, struct Firm **Ehead, struct Firm *del, struct Firm *prev);

struct Firm* EmptyList(struct Firm *Ehead)
{
	int i;
	struct Firm *ptr;
	struct Firm *tmp;

	for(i = 0; i < 4; i++)
	{
		tmp = (struct Firm*)malloc(sizeof(struct Firm));
		if(tmp == NULL)
		{
			return NULL;
		}
		if(Ehead == NULL)
		{
			Ehead = tmp;
			Ehead->next = NULL;
			continue;
		}
		if(Ehead->next == NULL)
		{
			ptr = tmp;
			Ehead->next = ptr;
			ptr->next = NULL;
		}
		else
		{
			ptr->next = tmp;
			ptr = ptr->next;
			ptr->next = NULL;
		}
	}
	return Ehead;
}
struct Firm* AddElements(struct Firm* Ehead)
{
	struct Firm *tmp;
	struct Firm *ptr = Ehead->next;
	int i;

	for(i = 0; i < 4; i++)
	{
		tmp = (struct Firm*)malloc(sizeof(struct Firm));
		if(tmp == NULL)
		{
			return NULL;
		}
		ptr->next = tmp;
		ptr = ptr->next;
	}
	return Ehead;
}
struct Firm* AddList(struct Firm *head, struct Firm *Ehead)
{
	struct Firm *ptr = NULL;
	struct Firm *curr = head;
	struct Firm *Etmp = Ehead->next;

	if(Etmp->next == NULL)
	{
		Ehead = AddElements(Ehead);
	}
	if(head == NULL)
	{
		ptr = Etmp;
		Ehead->next = Etmp->next;
		ptr = VuvejdaneSpisuk(ptr);
		if(ptr == NULL)
		{
			return NULL;
		}
		head = ptr;
		head->next = NULL;
		return head;
	}

	if(head->next == NULL)
	{
		ptr = Etmp;
		Ehead->next = Etmp->next;
		ptr = VuvejdaneSpisuk(ptr);
		if(ptr == NULL)
		{
			return NULL;
		}
		ptr->next = NULL;
		head->next = ptr;
		return head;
	}
	else
	{
		while(curr->next != NULL)
		{
			curr = curr->next;	
		}
		ptr = Etmp;
		Ehead->next = Etmp->next;
		ptr = VuvejdaneSpisuk(ptr);
		if(ptr == NULL)
		{
			return NULL;
		}
		ptr->next = NULL;
		curr->next = ptr;
		return head;
	}
	return NULL;
}
int PrintList(struct Firm *head)
{
	struct Firm *ptr = head;

	if(ptr == NULL)
	{
		return ERROR;
	}

	while(ptr != NULL)
	{
		printf("ID nomer: %I64d\n", ptr->idnomer);
		printf("Naimenovanie na stokata: %s\n", ptr->stoka);
		printf("Edinichna cena: %f\n", ptr->cena);
		printf("Kolichestvo: %d\n", ptr->kolichestvo);
		printf("Srok na godnost: %d\n", ptr->godnost);
		printf("Proizvoditel: %s\n", ptr->proizvoditel);
		printf("Danuchen nomer: %s\n", ptr->danomer);
		printf("Data na proizvodstvo: %s\n", ptr->data);
		
		ptr = ptr->next;
	}

	return SUCC;
}
struct Firm* SearchList(struct Firm *head)
{
	__int64 idnomer = IdNomer();
	struct Firm *ptr = head;

	if(ptr == NULL)
	{
		return NULL;
	}
	while (ptr != NULL)
	{
		if(ptr->idnomer == idnomer)
		{
			return ptr;
		}
		else
		{
			ptr = ptr->next;
		}
	}

	return NULL;
}
struct Firm* DeleteFromList(struct Firm **head, struct Firm **Ehead, struct Firm *del, struct Firm *prev)
{
	if(del == NULL)
	{
		return NULL;
	}

	if(*head == del)
	{
		if(del->next != NULL)
		{
			*head = del->next;
		}
		else
		{
			*head = NULL;
		}
		del->next = *Ehead;
		*Ehead = del;
	}
	else if(del->next == NULL)
	{
		prev->next = NULL;

		del->next = *Ehead;
		*Ehead = del;
	}
	else
	{
		prev->next = del->next;

		del->next = *Ehead;
		*Ehead = del;
	}
}
int Nalichnosti(struct Firm **head, struct Firm **Ehead)
{
	struct Firm *ptr = *head;
	struct Firm *prev = NULL;
	char stoka[61];
	int c = 0, kolichestvo = 0, result = 1, x = 0;

	printf("1: Dobavqne na kolichestva\n");
	printf("2: Izvajdane na kolichestva\n");
	c = getch();

	x = Naimenovanie(stoka);
	if(x == ESCAPE)
	{
		return ESCAPE;
	}

	while(ptr != NULL)
	{
		result = strcmp(stoka, ptr->stoka);
		if(result == 0)
		{
			kolichestvo = Kolichestvo();
			if(kolichestvo == ESCAPE)
			{
				return ESCAPE;
			}
			switch(c)
			{
			case '1':
				{
					ptr->kolichestvo += kolichestvo;
					return SUCC;
				}
			case '2':
				{
					if(kolichestvo > ptr->kolichestvo)
					{
						return ERROR;
					}
					else
					{
						ptr->kolichestvo -= kolichestvo;
						if(ptr->kolichestvo == 0)
						{
							DeleteFromList(head, Ehead, ptr, prev);
						}
						return SUCC;
					}
				}
			}
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}	
}
int Spravka(struct Firm *head)
{
	int flag, x;
	struct Firm *ptr = head;
	struct Proizvoditeli *curr = (struct Proizvoditeli*)malloc(sizeof(struct Proizvoditeli));
	struct Proizvoditeli *currHead;
	struct Proizvoditeli *tmp;

	if(ptr == NULL)
	{
		return ERROR;
	}
	if(curr == NULL)
	{
		return NOMEM;
	}

	strcpy(curr->proizvoditel, ptr->proizvoditel);
	strcpy(curr->danomer, ptr->danomer);
	strcpy(curr->stoka, ptr->stoka);
	curr->broi = 1;
	curr->stoinost = ptr->cena;
	curr->next = NULL;
	ptr = ptr->next;
	currHead = curr;

	while(ptr != NULL)
	{
		curr = currHead;
		flag = 0;
		x = 1;

		while(curr != NULL)
		{
			x = strcmp(curr->proizvoditel, ptr->proizvoditel);
			if(x == 0)
			{
				curr->stoinost += ptr->cena;
				x = 0;
				x = strcmp(curr->stoka, ptr->stoka);
				if(x != 0)
				{
					curr->broi++;
				}
				tmp = (struct Proizvoditeli*)malloc(sizeof(struct Proizvoditeli));
				if(tmp == NULL)
				{
					return NOMEM;
				}
				strcpy(tmp->proizvoditel, ptr->proizvoditel);
				strcpy(tmp->danomer, ptr->danomer);
				strcpy(tmp->stoka, ptr->stoka);
				tmp->broi = 1;
				tmp->stoinost = ptr->cena;
				tmp->next = NULL;
				if(currHead->next == NULL)
				{
					curr = tmp;
					currHead->next = curr; 
				}
				else
				{
					curr->next = tmp;
				}
				break;
			}
			else
			{
				curr = curr->next;
			}
		}
		ptr = ptr->next;
	}

	x = SortList(currHead);
	return x;
}