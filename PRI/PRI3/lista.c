#include <stdio.h>		//biblioteka standardowa
#include <stdlib.h>		//funkcje malloc() i system()
#include <string.h>		//funkcja strlen()
#include "liga.h"		//deklaracje zmiennych i funkcji

void PokazListe(void)
{
  int numer;			//sluzy do numerowania listy
  char wybor;			//zmienna sluzaca do wyboru opcji
  w_druzyna tmp;		//wskaznik na strukture pomocnicza

  while(1)
  {
    tmp = poczatek;			//poczatek listy
    numer = 1;				//zerowanie numeracji    

    system("clear");			//czyszczenie terminala

    printf("LISTA DRUZYN:\t\t   (D)odaj druzyne (U)sun druzyne (W)yjdz do menu");
    printf("\n\n");

    if(poczatek == NULL) printf("Lista jest pusta!\n");
    else {
      while(tmp!=NULL)			//dopoki nie ma konca listy
      {
        printf("%2d. %-30s", numer, tmp->nazwa);	//wypisz nazwy druzyn

	if(numer%2)
          printf("\t");			//jesli numer nieparzysty, odstep
        else
          printf("\n");			//jesli numer parzysty, nowa linia

        tmp = tmp->nast;		//przejscie do nastepnej druzyny
        numer++;			//zwiekszanie numeru na liscie
      }   
    }

    wybor=getchar();			//wczytywanie wyboru uzytkownika
    while(getchar()!='\n') continue;	//czyszczenie wejscia

    switch(wybor)			//sprawdz co wybral uzytkownik
    {
      case 'd': if(!mpoczatek) DodajDruzyne(); break;
      case 'u': if(!mpoczatek) UsunDruzyne(); break;
      case 'w': return;
    }//switch(wybor)

  }//while(1)

}//PokazListe

void DodajDruzyne(void)
{
  w_druzyna tmp;			//wskaznik na strukture pomocnicza
  int wczytane=0;			//zapamietuje liczbe wczytanych znakow
  char znak;				//przechowuje wczytany znak
  
  if((tmp = (w_druzyna)malloc(sizeof(druzyna))) != NULL)
  {
    tmp->pop = koniec;				//podpiecie konca listy do tmp
    if(koniec != NULL) koniec->nast = tmp;	//jesli lista niepusta podepnij tmp
    tmp->nast = NULL;				//po tmp nie ma nic
    koniec = tmp;				//tmp jest na koncu
    if(poczatek == NULL) poczatek = tmp;	//jesli lista pusta tmp na poczatek
  
    printf("Podaj nazwe nowej druzyny (do 30 znakow): ");

    while((znak=getchar()) != '\n' && wczytane<=30)
    {	//dopoki jest cos w wejsciu i jest miejsce w tablicy
      (*tmp).nazwa[wczytane] = znak;		//wpisuj litere do tablicy
      wczytane++;				//i zliczaj litery
    }//while

    tmp->nazwa[wczytane] = '\0';		//znak konca napisu

    (*tmp).mecze = 0;
    (*tmp).punkty = 0;				//wyzerowanie
    (*tmp).strzelone = 0;			//danych
    (*tmp).stracone = 0;			//druzyny
    (*tmp).zwyciestwa = 0;
    (*tmp).remisy = 0;
    (*tmp).porazki = 0;

    if(wczytane==31)				//jesli skonczyla sie tablica
      while(getchar()!='\n') continue;		//skasuj, to co zostalo w stdin

    stan = 3;					//zostaly wprowadzone zmiany
    liczba_druzyn++;				//zwieksz liczbe druzyn
    return;					//wroc do PokazListe()

  } else {printf("Brak wolnej pamieci!"); return;}

}//DodajDruzyne

void UsunDruzyne(void)
{
  w_druzyna tmp;			//wskaznik na strukture pomocnicza
  int indeks;				//numer na liscie kasowanej druzyny

  printf("Podaj numer druzyny do usuniecia: ");

  if(scanf("%d", &indeks) != 0)		//jesli poprawnie pobrano indeks
  {
    while(getchar()!='\n') continue;	//czyszczenie wejscia
    tmp = poczatek;			//ustawia wskaznik na poczatku listy
        
    if(indeks>liczba_druzyn || indeks<1)//jesli indeks jest poza zakresem
    {
      printf("Nie ma druzyny o takim numerze! Nacisnij ENTER aby kontynuowac.");
    } else {

      for(;indeks>1;indeks--)
        tmp = tmp->nast;		//dojdz do elementu o podanym numerze

      if(tmp->pop == NULL)		//jesli usuwamy pierwszy element
        poczatek = tmp->nast;		//element po tmp jest teraz na poczatku
      else
        tmp->pop->nast = tmp->nast;	//ustawianie wskaznika w poprzednim el.

      if(tmp->nast == NULL)		//jesli usuwany ostatni element
        koniec = tmp->pop;		//element przed tmp jest teraz na koncu
      else
        tmp->nast->pop = tmp->pop;	//ustawianie wskaznika w nastepnym el.

      free(tmp);			//zwalnianie pamieci po tmp

      printf("Druzyna usunieta! Nacisnij ENTER aby kontynuowac.");

      liczba_druzyn--;			//zmniejsz ilosc druzyn
      stan = 3;				//zostaly wprowadzone zmiany

    }//if(tmp==NULL || indeks<1)

  } else {
    while(getchar()!='\n') continue;	//czyszczenie wejscia
    printf("Nieprawidlowe dane! Nacisnij ENTER aby kontynuowac.");
  }//if

  while(getchar()!='\n') continue;	//czyszczenie wejscia

}//UsunDruzyne
