#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "list.h"
#include "logic.h"
#include "exits.h"
#include "validation.h"


struct Date 
{
	int d;
	int m;
	int y;
};
void Convert(struct Date *D, char *SDate);
int compare( const void *arg1, const void *arg2);

int SortList(struct Proizvoditeli *head)
{
	struct Proizvoditeli *ptr = head;
	int	i;
	int count = 0;
	struct Proizvoditeli **buffer;

	if(ptr == NULL)
	{
		return 1;
	}

	while(ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}

	buffer = (struct Proizvoditeli **)malloc(count*sizeof(struct Proizvoditeli *));
	if(buffer == NULL)
	{
		return NOMEM;
	}

	ptr = head;

	for(i = 0; i < count; i++)
	{
		buffer[i] = ptr;
		ptr = ptr->next;
	}

	qsort(buffer, count, sizeof(struct Proizvoditeli *), compare);

	for(i = 0; i < count; i++)
	{
		printf("%s\n", buffer[i]->danomer);
		printf("%s\n", buffer[i]->proizvoditel);
		printf("%d\n", buffer[i]->broi);
		printf("%f\n", buffer[i]->stoinost);
	}

	/* ListSort
	ptr = buffer[0]; 

	for(i = 1; i < count; i ++)
	{
	ptr->next = buffer[i];
	ptr = ptr->next;
	}
	head = ptr;*/

	free(buffer);
	return SUCC;
}
int compare( const void *arg1, const void *arg2 )
{
	struct Proizvoditeli *F1, *F2;
	F1 = *(struct Proizvoditeli **) arg1;
	F2 = *(struct Proizvoditeli **) arg2;
	if(F1->stoinost < F2->stoinost)
	{
		return -1;
	}
	else if(F1->stoinost > F2->stoinost)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

struct Firm* VuvejdaneSpisuk(struct Firm *ptr)
{
		int x = 0;
		int d = ESCAPE;
	    ptr->idnomer = IdNomer();
			if(ptr->idnomer == ESCAPE)
			{
				return NULL;
			}
		x = Naimenovanie(ptr->stoka);
			if(x == ESCAPE)
			{
				return NULL;
			}
		ptr->cena = EdCena();
			if(ptr->cena == ESCAPE)
			{
				return NULL;
			}
		ptr->kolichestvo = Kolichestvo();
			if(ptr->kolichestvo == ESCAPE)
			{
				return NULL;
			}
		ptr->godnost = SrokNaGodnost();
			if(ptr->godnost == ESCAPE)
			{
				return NULL;
			}
		x = Proizvoditel(ptr->proizvoditel);
			if(x == ESCAPE)
			{
				return NULL;
			}
		x = DaNomer(ptr->danomer);
			if(x == ESCAPE)
			{
				return NULL;
			}
		while(d != SUCC)
		{
			x = Data(ptr->data);
			if(x == ESCAPE)
			{
				return NULL;
			}
			d = DateValidate(ptr->data);
			if(d == ERROR)
			{
				printf("\n");
				printf("Datata ne e validna");
			}
		}
		return ptr;
}
void IztekulSrok(struct Firm *head)
{
	struct Firm *ptr = head;
	char currData[11];
    struct tm date;
	struct tm currDate;
    time_t timer;
	time_t currTimer;
    struct Date D;
	struct Date currD;
	
	currTimer = time(NULL);
	timer = time(NULL);
	date = *gmtime(&timer);
	currDate = *gmtime(&currTimer);

    printf("Vuvedete data za sravnenie:");
	Data(currData);
	Convert(&currD, currData);
	date.tm_year = currD.y - 1900;
	date.tm_mon = currD.m - 1;
	date.tm_mday = currD.d + ptr->godnost;
	currTimer = mktime(&currDate);
	currDate = *gmtime(&currTimer);
  
	printf("%d.%d.%d\n", currDate.tm_mday, currDate.tm_mon+1, currDate.tm_year+1900);

	while(ptr != NULL)
	{
		Convert(&D, ptr->data);

		date.tm_year = D.y - 1900;
		date.tm_mon = D.m - 1;
		date.tm_mday = D.d + ptr->godnost;
		timer = mktime(&date);
		date = *gmtime(&timer);
    
		printf("%d.%d.%d\n", date.tm_mday, date.tm_mon+1, date.tm_year+1900);

		if(currDate.tm_year > date.tm_year)
		{
			printf("Produktut %s e s iztekul srok\n", ptr->stoka);
		}
		if(currDate.tm_year == date.tm_year && currDate.tm_mon > date.tm_mon)
		{
			printf("Produktut %s e s iztekul srok\n", ptr->stoka);
		}
		if(currDate.tm_mon == date.tm_mon && currDate.tm_mday > date.tm_mday)
		{
			printf("Produktut %s e s iztekul srok\n", ptr->stoka);
		}

		ptr = ptr->next;
	}
}
void Convert(struct Date *D, char *SDate)
{
		char day[2], month[2], year[4];
	
		strncpy(day, SDate, 2);
		strncpy(month, SDate + 3, 2);
		strncpy(year, SDate + 6, 4);
		D->d = atoi(day);
		D->m = atoi(month);
		D->y = atoi(year);
}
int DateValidate(char Date[])
{
	struct Date D;
	int leap = 0;

	Convert(&D, Date);
	if(D.m > 12)
	{
		return ERROR;
	}
	if((D.y % 4) == 0)
	{
		leap = 1;
	}

	if(D.m == 1 && D.d > 31)
	{
		return ERROR;
	}
	if(leap == 1)
	{
		if(D.m == 2 && D.d > 29)
		{
			return ERROR;
		}
	}
	else
	{
		if(D.m == 2 && D.d > 28)
		{
			return ERROR;
		}
	}
	if(D.m == 3 && D.d > 31)
	{
		return ERROR;
	}
	if(D.m == 4 && D.d > 30)
	{
		return ERROR;
	}
	if(D.m == 5 && D.d > 31)
	{
		return ERROR;
	}
	if(D.m == 6 && D.d > 30)
	{
		return ERROR;
	}
	if(D.m == 7 && D.d > 31)
	{
		return ERROR;
	}
	if(D.m == 8 && D.d > 31)
	{
		return ERROR;
	}
	if(D.m == 9 && D.d > 30)
	{
		return ERROR;
	}
	if(D.m == 10 && D.d > 31)
	{
		return ERROR;
	}
	if(D.m == 11 && D.d > 30)
	{
		return ERROR;
	}
	if(D.m == 12 && D.d > 31)
	{
		return ERROR;
	}
	return SUCC;
}