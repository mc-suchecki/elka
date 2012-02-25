#include <stdio.h>		//bilbioteka standardowa
#include <stdlib.h>		//funkcja system()
#include "liga.h"		//deklaracje zmiennych i funkcji

//zerowanie i deklaracja wskaznikow list
w_druzyna poczatek = NULL, koniec = NULL;
w_mecz mpoczatek = NULL, mkoniec = NULL;

//zerowanie i definicja stanu ligi
int stan = 0;

//zerowanie i definicja liczby druzyn
int liczba_druzyn = 0;

//wskaznik na plik zawierajacy dane ligi
FILE *plik;

int main()
{
  char wybor=0;			//przechowuje znak wpisany przez uzytkownika

  while(1)
  {
    system("clear");		//czyszczenie terminala

    printf("Witaj w programie do obslugi ligi pilkarskiej!\n");
    printf("Wpisz jedna z liter umieszczonych w nawiasach, aby kontynuowac:");
    printf("\n\n1. (N)owa liga");
    printf("\n2. (O)tworz lige z pliku");
    printf("\n3. (Z)apisz lige do pliku");
    printf("\n4. Przejdz do (L)isty druzyn");
    printf("\n5. Przejdz do terminarza (S)potkan");
    printf("\n6. Przejdz do (T)abeli ligowej");
    printf("\n7. (W)yjdz z programu\n\n");

    switch(stan)
    {
      case 0: printf("Nie zaladowano ligi! ");
              printf("Stworz nowa lige lub wczytaj ja z pliku.\n"); break;
      case 1: printf("Stworzono nowa lige.\n"); break;
      case 2: printf("Liga wczytana z pliku.\n"); break;
      case 3: printf("Wprowadzono zmiany! ");
              printf("Zapisz lige, aby ich nie utracic.\n"); break;
    }

    wybor=getchar();			//wczytanie wyboru uzytkownika
    while(getchar()!='\n') continue;	//czyszczenie wejscia

    switch(wybor)			//na poczatku aktywne sa tylko
    {					//NowaLiga() i OtworzLige()
      case 'n': NowaLiga(); break;
      case 'o': OtworzLige(); break;
      case 'z': if(stan==3) ZapiszLige(); break;
      case 'l': if(stan!=0) PokazListe(); break;
      case 's': if(stan!=0) PokazTerminarz(); break;
      case 't': if(stan!=0) PokazTabele(); break;
      case 'w': return 0;
    }//switch(wybor)

  }//while(1)

}//main
