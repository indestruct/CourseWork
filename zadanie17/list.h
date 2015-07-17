#ifndef LIST_H 
#define LIST_H

struct Firm
    {
		__int64 idnomer;
		char stoka[61];
		double cena;
		int kolichestvo;
		int godnost;
		char proizvoditel[41];
		char danomer[10];
		char data[11];
		int key;
		struct Firm *next;
    };

struct Proizvoditeli
	{
		char danomer[10];
		char proizvoditel[41];
		char stoka[61];
		int broi;
		double stoinost;
		struct Proizvoditeli *next;
	};

struct Firm* EmptyList(struct Firm *Ehead);
struct Firm* AddList(struct Firm *head, struct Firm *Ehead);
int PrintList(struct Firm *head);
int Nalichnosti(struct Firm **head, struct Firm **Ehead);
int Spravka(struct Firm *head);

#endif