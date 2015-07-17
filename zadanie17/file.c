#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "exits.h"
#include "list.h"


int WriteToBin(struct Firm *head)
{
	struct Firm *ptr = head;
	FILE *fp;
	int x = 0;
	
	if(ptr == NULL)
	{
		return ERROR;
	}

	fp = fopen("Firm","w+");
	if(fp == NULL)
	{
		return ERROR;
	}

	while(ptr != NULL)
	{
		fwrite(ptr, sizeof(struct Firm), 1, fp);
		/*x = fwrite(&ptr->idnomer, sizeof(ptr->idnomer), 1, fp);
		x = fwrite(&ptr->stoka, sizeof(ptr->stoka), 1, fp);
		x = fwrite(&ptr->cena, sizeof(ptr->cena), 1, fp);
		x = fwrite(&ptr->kolichestvo, sizeof(ptr->kolichestvo), 1, fp);
		x = fwrite(&ptr->godnost, sizeof(ptr->godnost), 1, fp);
		x = fwrite(&ptr->proizvoditel, sizeof(ptr->proizvoditel), 1, fp);
		x = fwrite(&ptr->danomer, sizeof(ptr->danomer), 1, fp);
		x = fwrite(&ptr->data, sizeof(ptr->data), 1, fp);*/
		ptr = ptr->next;
	}
	fclose(fp);
	if(x == 0)
	{
		return ERROR;
	}
	else
	{		
		return SUCC;
	}
}

int ReadFromBin(struct Firm **head)
{
	FILE *fp;
	struct Firm buffer;
	struct Firm *tmp = head;
	int x = 0;

	fp = fopen("Firm","r+");
	if(fp == NULL)
	{
		return ERROR;
	}
	while(!feof(fp))
	{

		tmp = (struct Firm*)malloc(sizeof(struct Firm));
		fread(tmp, sizeof(struct Firm), 1, fp);
		/*x = fread(&buffer.idnomer, sizeof(buffer.idnomer), 1, fp);
		tmp->idnomer = buffer.idnomer;
		x = fread(&buffer.stoka, sizeof(buffer.stoka), 1, fp);
		x = fread(&buffer.cena, sizeof(buffer.cena), 1, fp);
		x = fread(&buffer.kolichestvo, sizeof(buffer.kolichestvo), 1, fp);
		x = fread(&buffer.godnost, sizeof(buffer.godnost), 1, fp);
		x = fread(&buffer.proizvoditel, sizeof(buffer.proizvoditel), 1, fp);
		x = fread(&buffer.danomer, sizeof(buffer.danomer), 1, fp);
		x = fread(&buffer.data, sizeof(buffer.data), 1, fp);*/
		tmp->next = *head;
		*head = tmp;

	}
		/*printf("ID nomer: %I64d\n", tmp->idnomer);
		printf("Naimenovanie na stokata: %s\n", buffer.stoka);
		printf("Edinichna cena: %f\n", buffer.cena);
		printf("Kolichestvo: %d\n", buffer.kolichestvo);
		printf("Srok na godnost: %d\n", buffer.godnost);
		printf("Proizvoditel: %s\n", buffer.proizvoditel);
		printf("Danuchen nomer: %s\n", buffer.danomer);
		printf("Data na proizvodstvo: %s\n", buffer.data);*/
	if(x == 0)
	{
		fclose(fp);
		return ERROR;
	}
	else
	{
		fclose(fp);
		return SUCC;
	}
}