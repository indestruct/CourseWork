#ifndef VALIDATION_H
#define VALIDATION_H

#define insON          1
#define insOFF         0
#define SPECIAL      224  //leading symbol of functional keys
#define LEFTARR	      75
#define RIGHTARR	  77
#define UPARR		  72
#define DOWNARR		  80
#define INS           82
#define ESC			  27
#define ZERO		  48
#define ONE			  49
#define TWO			  50
#define THREE		  51
#define NINE		  57
#define ACAP		  65
#define ZCAP		  90
#define AMIN		  97
#define ZMIN		 122
#define ENTER		  13
#define BACKSPACE	   8
#define SPACE		  32
#define COMMA		  44
#define POINT		  46

__int64 IdNomer(void);
int Naimenovanie(char buffer[]);
double EdCena(void);
int Kolichestvo(void);
int SrokNaGodnost(void);
int Proizvoditel(char buffer[]);
int DaNomer(char buffer[]);
int Data(char buffer[]);

#endif