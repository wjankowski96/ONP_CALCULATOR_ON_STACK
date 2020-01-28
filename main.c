
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct LICZBAZESPOLONA {
	double re;
	double im;
} LICZBAZESPOLONA;

typedef struct STOS {
	LICZBAZESPOLONA liczba;
	struct STOS * poprzedni;
} STOS;

void push(STOS **wierzch, LICZBAZESPOLONA dane)
{
	STOS *nowy_element;
	nowy_element = malloc(sizeof(STOS));
	if (!nowy_element)
	{
		printf("Blad przy lokowaniu pamieci!!!\n");
		return;
	}

	(nowy_element->liczba).im = dane.im;
	(nowy_element->liczba).re = dane.re;
	if (!(*wierzch))
		nowy_element->poprzedni = NULL;
	else
		nowy_element->poprzedni = (*wierzch);
	(*wierzch) = nowy_element;
}

LICZBAZESPOLONA pop(STOS **wierzch)
{
	LICZBAZESPOLONA dane = { 0, 0 };
	STOS *tmp;
	if (*wierzch)
	{
		dane.re = (*wierzch)->liczba.re;
		dane.im = (*wierzch)->liczba.im;
		tmp = (*wierzch)->poprzedni;
		free(*wierzch);
		*wierzch = tmp;
	}
	return dane;
}

int SprawdzCzyPusty(STOS *wierzch)
{
	if (!(wierzch))
	{
		printf("Stos jest pusty!!!\n");
		return 0;
	}
	else
	{
		printf("Na stosie znajdują się liczby.\n");
		return 1;
	}
}

void wyswietl(STOS *wierzch)
{
	if (wierzch) {
		STOS *tmp = wierzch;
		while (tmp) {
			printf("Re: %f\tIm: %f\n", tmp->liczba.re, tmp->liczba.im);
			tmp = tmp->poprzedni;
		}
	}
	else
		printf("Stos jest pusty!!!!\n");
}

void SkasujStos(STOS **wierzch)
{
	STOS *tmp = NULL;
	while (*wierzch)
	{
		tmp = (*wierzch)->poprzedni;
		free(*wierzch);
		*wierzch = tmp;
	}
	*wierzch = NULL;
}

LICZBAZESPOLONA dodawanie(LICZBAZESPOLONA a, LICZBAZESPOLONA b)
{
	LICZBAZESPOLONA wynik = { 0, 0 };

	wynik.re = a.re + b.re;
	wynik.im = a.im + b.im;
	return wynik;
}

LICZBAZESPOLONA odejmowanie(LICZBAZESPOLONA a, LICZBAZESPOLONA b)
{
	LICZBAZESPOLONA wynik = { 0, 0 };
	wynik.re = a.re - b.re;
	wynik.im = a.im - b.im;
	return wynik;
}

LICZBAZESPOLONA mnozenie(LICZBAZESPOLONA a, LICZBAZESPOLONA b)
{
	LICZBAZESPOLONA wynik = { 0, 0 };
	wynik.re = a.re * b.re - a.im * b.im;
	wynik.im = a.im * b.re + a.re * b.im;
	return wynik;
}

LICZBAZESPOLONA dzielenie(LICZBAZESPOLONA a, LICZBAZESPOLONA b)
{
	LICZBAZESPOLONA wynik = { 0, 0 };

	wynik.re = (a.re * b.re + a.im * b.im) / (b.re*b.re + b.im*b.im);
	wynik.im = (a.im * b.re - a.re * b.im) / (b.re*b.re + b.im*b.im);
	return wynik;
}

void koniec()
{
	system ("pause");
}

void Licz(STOS **wierzch)
{
	double Re = 0, Im = 0;
	LICZBAZESPOLONA wczytana = { 0, 0 }, tmp = { 0, 0 };
	char tablica[257], znak;
	int i = 1;

	while (1)
	{
		system("cls");
		printf("Podaj liczbe w postaci RE IM (np. 1 2 odzielając je spacją), gdzie pierwsza liczba to część rzeczywista, a druga to część urojona\n");
		printf("\nLiczby potwierdź wciskając Enter");
		wyswietl(*wierzch);
		znak = 0;
		gets(tablica);
		i = sscanf(tablica, "%lf %lf", &Re, &Im);
		wczytana.re = Re;
		wczytana.im = Im;
		if (i == 0 || i == -1)
		{
			i = sscanf(tablica, "%c", &znak);
			if (i != -1)
			{
				switch (znak)
				{
				case '+':
					if (!SprawdzCzyPusty(*wierzch) || (*wierzch)->poprzedni == NULL)
						break;
					push(wierzch, dodawanie(pop(wierzch), pop(wierzch)));
					break;
				case '-':
					if (!SprawdzCzyPusty(*wierzch) || (*wierzch)->poprzedni == NULL)
						break;
					push(wierzch, odejmowanie(pop(wierzch), pop(wierzch)));
					break;
				case '*':
					if (!SprawdzCzyPusty(*wierzch) || (*wierzch)->poprzedni == NULL)
						break;
					push(wierzch, mnozenie(pop(wierzch), pop(wierzch)));
					break;
				case '/':
					if (!SprawdzCzyPusty(*wierzch) || (*wierzch)->poprzedni == NULL)
						break;
					if ((*wierzch)->liczba.im == 0 && (*wierzch)->liczba.re == 0)
						printf("BLAD, dzielenie przez 0!!!\n");
					else
						push(wierzch, dzielenie(pop(wierzch), pop(wierzch)));
					break;
				default:
					printf("Nieprawidłowy znak\n");
					
						system("exit");
					
				}
				
			}
			else if (i == 2)
			{
				SkasujStos(wierzch);
				return;
			}
			
		}
		else if (i == 2)
			push(wierzch, wczytana);
		else if (i == 1)
		{
			wczytana.im = 0;
			push(wierzch, wczytana);
		}
		
		
	}
}

int main()
{
	STOS *wierzch = NULL;
	int wybor = 0;

	setlocale(LC_ALL, "polish_poland");

	while (1)
	{
		printf("Kalkulator liczb zespolonych\n");
	
			Licz(&wierzch);
            system("pause");
            break;
			
	}
	system("pause");
	return 0;
}