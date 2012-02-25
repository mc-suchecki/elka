#include <stdio.h>		//biblioteka standardowa
#include <stdlib.h>		//funkcja free()
#include <string.h>		//funkcja strcpy()
#include "liga.h"		//deklaracje zmiennych i funkcji

void NowaLiga(void)
{
  w_druzyna tmp1 = poczatek;	//wskaznik do kasowania listy druzyn
  w_mecz tmp2 = mpoczatek;	//wskaznik do kasowania listy meczy

  char znak;			//zmienna sluzaca do wczytywania odpowiedzi

  switch(stan)
  {
    case 0:
      stan = 1;			//jesli nie bylo wczesniej ligi,
      return;			//zmien tylko stan ligi i wyjdz

    case 3:		//jesli liga byla edytowana od ostatniego zapisu
      printf("Zostana utracone zmiany dokonane w poprzedniej lidze.\n");
      printf("Czy na pewno chcesz kontynuowac? (t/n) ");
      znak=getchar();

      switch(znak)
      {
        case 't':
          break;				//przejdz dalej
        case 'n':
          while(getchar()!='\n') continue;	//czysc wejscie
          return;				//i wyjdz z funkcji
        default:
          printf("\nNieprawidlowa odpowiedz, wcisnij ENTER aby kontynuowac.");
          while(getchar()!='\n') continue;	//czysc wejscie
          return;				//i wyjdz z funkcji
      }//switch(znak)

    case 1:	//jesli aktualna liga nie byla edytowana od ostatniego zapisu
    case 2:
      while(tmp1 != NULL)		//dopoki nie ma konca listy druzyn
      {
        poczatek = tmp1->nast;		//nowy poczatek
        free(tmp1);			//usun element	
        tmp1 = poczatek;		//przesun sie dalej na liscie
      }//while(tmp_d != NULL)

      poczatek = NULL;	koniec = NULL;	//na wszelki wypadek

      while(tmp2 != NULL)		//dopoki nie ma konca listy meczy
      {   
        mpoczatek = tmp2->nast;		//nowy poczatek
        free(tmp2);			//usun element
        tmp2 = mpoczatek;		//przesun sie dalej na liscie
      }//while(tmp_d != NULL)

      mpoczatek = NULL;	mkoniec = NULL;	//na wszelki wypadek

      liczba_druzyn = 0;		//wyzeruj liczbe druzyn
      stan = 1;				//nowa liga	

  }//switch(stan)

  return;				//wyjdz z funkcji

}//NowaLiga

void OtworzLige()
{
  char nazwa_pliku[256];		//max 255 znakow
  char nazwa_druzyny1[31];		//tablica przechowujaca odcztana nazwe
  char nazwa_druzyny2[31];		//tablica przechowujaca odcztana nazwe
  w_druzyna tmp_d = poczatek;		//wskaznik do tworzenia listy druzyn
  int bramki1, bramki2, kolejka;	//przechowuja odczytane dane z pliku
 
  NowaLiga();				//ostrzezenie i kasowanie danych

  if(stan != 1)	return;			//wyjdz jesli kasowanie sie nie udalo

  printf("Podaj nazwe pliku do odczytu: ");

  scanf("%s", nazwa_pliku);		//pobierz nazwe pliku
  while(getchar()!='\n') continue;	//czyszczenie wejscia
 
  if((plik = fopen(nazwa_pliku, "r")) == NULL)	//nie mozna otworzyc
  {
    printf("Nieudane otwarcie pliku %s!\n", nazwa_pliku);
    while(getchar()!='\n') continue;	//czyszczenie wejscia
    stan = 0;				//nie wczytano ligi
    return;				//powrot do menu
  }//if((plik = fopen(nazwa_pliku, "r")) == NULL)

  while(fgets(nazwa_druzyny1, 31, plik))//wczytujemy liste druzyn
  {
    if(nazwa_druzyny1[0] == '\n') break;//jesli byla pusta linia

    nazwa_druzyny1[strlen(nazwa_druzyny1)-1] = '\0';	//kasowanie '\n'

    if((tmp_d = (w_druzyna)malloc(sizeof(druzyna))) != NULL)
    {
      tmp_d->pop = koniec;			//podpiecie konca listy do tmp
      if(koniec != NULL) koniec->nast = tmp_d;	//jesli lista niepusta podepnij tmp
      tmp_d->nast = NULL;			//po tmp nie ma nic
      koniec = tmp_d;				//tmp jest na koncu
      if(poczatek == NULL) poczatek = tmp_d;	//jesli lista pusta tmp na poczatek

      strcpy(tmp_d->nazwa, nazwa_druzyny1);	//wpisanie nazwy druzyny
      (*tmp_d).mecze = 0;
      (*tmp_d).punkty = 0;			//wyzerowanie
      (*tmp_d).strzelone = 0;			//danych
      (*tmp_d).stracone = 0;			//druzyny
      (*tmp_d).zwyciestwa = 0;
      (*tmp_d).remisy = 0;
      (*tmp_d).porazki = 0;

      liczba_druzyn++;				//zwieksz liczbe druzyn

    } else {printf("Brak wolnej pamieci!"); return;}

  }//while(fgets(nazwa_druzyny, 30, plik))

  while(fscanf(plik, "%[a-zA-Z0-9 ]-%[a-zA-Z0-9 ]\t%d-%d\t%d\n", nazwa_druzyny1,
        nazwa_druzyny2, &bramki1, &bramki2, &kolejka) != EOF)
  {
    DodajMecz(nazwa_druzyny1, nazwa_druzyny2, kolejka, bramki1, bramki2);
  }//while(fscanf() != EOF)

  fclose(plik);				//zamkniecie pliku

  printf("Liga zostala wczytana! Wcisnij ENTER, aby kontynuowac.");
  while(getchar()!='\n') continue;	//czyszczenie wejscia
  stan = 2;				//nie bylo zmian od zapisu

}//OtworzLige

void ZapiszLige()
{
  char nazwa_pliku[256];		//max 255 znakow
  w_druzyna tmp_d = poczatek;		//wskaznik do czytania listy druzyn
  w_mecz tmp_m = mpoczatek;		//wskaznik do czytania listy meczy

  if(poczatek == NULL) return;		//nie ma co zapisywac

  printf("Podaj nazwe pliku do zapisu: ");

  scanf("%s", nazwa_pliku);		//pobierz nazwe pliku
  while(getchar()!='\n') continue;	//czyszczenie wejscia

  if((plik = fopen(nazwa_pliku, "w")) == NULL)	//nie mozna otworzyc
  {
    printf("Nieudane otwarcie pliku %s!\n", nazwa_pliku);
    while(getchar()!='\n') continue;	//czyszczenie wejscia
    return;				//powrot do menu
  }//if((plik = fopen(nazwa_pliku, "w")) == NULL)

  while(tmp_d != NULL)			//zapisujemy liste druzyn
  {
    fprintf(plik, "%s\n", tmp_d->nazwa);
    tmp_d = tmp_d->nast;		//nastepna druzyna
  }//while(tmp_d != NULL)

  fprintf(plik, "\n");			//odstep przed lista meczy

  while(tmp_m != NULL)			//zapisujemy liste meczy
  {
    fprintf(plik, "%s-%s\t%d-%d\t%d\n", tmp_m->druzyna1,
    tmp_m->druzyna2, tmp_m->bramki1, tmp_m->bramki2, tmp_m->kolejka );

    tmp_m = tmp_m->nast;		//nastepny mecz
  }//while(tmp_d != NULL)

  fclose(plik);				//zamkniecie pliku

  printf("Zapisano! Wcisnij ENTER, aby kontynuowac.");
  while(getchar()!='\n') continue;	//czyszczenie wejscia
  stan = 2;				//nie bylo zmian od zapisu

}//ZapiszLige
