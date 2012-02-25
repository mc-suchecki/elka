#include <stdio.h>

float suma=0, liczba=1, stara;		//liczba przechowuje aktualnie zczytywana liczbe, stara przechowuje poprzednia
int n=1, znak='\n', u=0;		//n przechowuje ilosc liczb, znak sluzy do zapobiegania wpr. znakow, u do usuwania

void oblicz_sume();			//wczytywanie liczb i obliczanie sumy

int main()
{
printf("Program liczacy srednia arytmetyczna podanych liczb.\n(wpisz k aby zakonczyc wpisywanie, c aby skasowac ostatnia liczbe)\n");
oblicz_sume();
if (n == 0) {printf("Nie wczytano zadnej liczby!\n");}
else {printf("Srednia arytmetyczna wpisanych liczb wynosi: %f\n", suma = suma/n);}
return 0;
}//main

void oblicz_sume()
{
while (1)
{
	printf("Podaj liczbe nr %d: ", n);
	stara = liczba;			//zachowanie poprzednio wpisanej liczby na wypadek usuwania
	scanf("%f", &liczba);
	znak = getchar();
	if (znak != '\n')		//zapobieganie wprowadzaniu znakow i usuwanie poprzedniej liczby
		{
		if (znak == 'c' && u == 0) {printf("Usuwanie poprzednio wpisanej liczby.\n"); u=1; n--; suma = suma - stara;}
		else {if (znak == 'k') break; else printf("Niedozwolony znak - wpisz liczbe ponownie!\n");			}
		while (1) {if (getchar() == '\n') break;}	//usuwanie wszystkich znakow z wejscia
		}//if (znak != 0)
	else {suma += liczba; n++, u=0;}		 	//obliczanie sumy
}//while (1)
n--;
}//oblicz_sume()
