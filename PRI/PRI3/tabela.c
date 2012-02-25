#include <stdio.h>		//biblioteka standardowa
#include <stdlib.h>		//funkcja system()
#include <string.h>		//funkcja strcmp()
#include "liga.h"		//deklaracje zmiennych i funkcji

void PokazTabele()
{
  char wybor;			//zmienna sluzaca do wyboru opcji
  int kolejka = 0, numer = 0;	//numer aktualnej kolejki, nr druzyny
  w_druzyna tmp = poczatek;	//wskaznik do stworzenia tablicy
  w_mecz mecz = mpoczatek;	//wskaznik do 'rozgrywania' meczy

  w_druzyna tablica[liczba_druzyn];	//tablica wskaznikow na struktury

  while(tmp)
  {
    tablica[numer] = tmp;	//wpisanie wskaznika do tablicy
    numer++;			//zwiekszenie indeksu
    tmp = tmp->nast;		//przejscie dalej na liscie
  }//while(tmp)

  while(1)
  {
    system("clear");		//czyszczenie terminala

    printf("TABELA LIGOWA:\t\t    (N)astepny mecz (P)oprzedni mecz (W)yjscie do menu\n");
    printf("\t\t\t    Nastepna (K)olejka Poprzednia ko(L)ejka\n\n");

    if(mpoczatek == NULL) printf("Wygeneruj terminarz, aby wyswietlac tabele.");
    else {

    printf("\t  NAZWA DRUZYNY\t       MECZE    PKT     BRZ  BRS        ZWY  REM  POR\n");

    qsort(tablica, liczba_druzyn, sizeof(w_druzyna), PorownajDruzyny);	//sortowanie

    for(numer=0; numer<liczba_druzyn; numer++)
    {
      printf(" %-30s %2d\t%2d\t%2d   %2d\t\t%2d   %2d   %2d\n",
      tablica[numer]->nazwa, tablica[numer]->mecze, tablica[numer]->punkty,
      tablica[numer]->strzelone, tablica[numer]->stracone,
      tablica[numer]->zwyciestwa, tablica[numer]->remisy, tablica[numer]->porazki);
    }//wypisywanie tabeli

    }//if(mpoczatek==NULL)

    wybor=getchar();			//wczytanie wyboru uzytkownika
    while(getchar()!='\n') continue;	//czyszczenie wejscia

    switch(wybor)
    {
      case 'n':
        if(kolejka!=-1)			//jesli nie jestesmy przy pierwszym meczu
        {
          RozegrajMecz(mecz);
          if(mecz->nast!=NULL)		//jesli nie jestesmy na koncu
          {
            mecz=mecz->nast;
            kolejka=mecz->kolejka;
          }
          else kolejka = -1;
        }//if(kolejka!=-1)
       break;
      case 'p':
        if(kolejka!=0)			//jesli nie jestesmy przy pierwszym meczu
        {
          if(kolejka!=-1) mecz=mecz->pop;
          CofnijMecz(mecz);
          if(mecz->pop!=NULL) kolejka=mecz->kolejka;
          else kolejka = 0;
        }//if(kolejka!=0)
        break;
      case 'k':
        if(kolejka!=-1)			//jesli nie jestesmy przy ostatnim meczu
        {
          if(kolejka==0) kolejka = 2;
          else kolejka++;
          while(mecz->kolejka!=kolejka)	//dopoki nie doszlismy do nastepnej kol.
          {
            RozegrajMecz(mecz);
            if(mecz->nast!=NULL) mecz=mecz->nast;
            else {
              kolejka = -1;
              break;
            }//if(koniec)
          }//while(kolejka)
        }//if(kolejka!=-1)
        break;
      case 'l':
        if(kolejka!=0)			//jesli nie jestesmy przy pierwszym meczu
        {
          if(kolejka==-1) kolejka = liczba_druzyn - !(liczba_druzyn%2) - 1;
          else {kolejka = mecz->pop->kolejka - 1; mecz=mecz->pop;}
          while(mecz->kolejka!=kolejka)	//dopoki nie doszlismy do pop. kolejki
          {
            CofnijMecz(mecz);
            if(mecz->pop!=NULL) mecz = mecz->pop;
            else {kolejka=0; break;}
          }//while(kolejka)
          if(mecz->pop!=NULL) mecz = mecz->nast;	//ustawianie wskaznika
        }//if(kolejka!=0)
        break;
      case 'w':
        for(tmp=poczatek;tmp;tmp=tmp->nast)
        {
          (*tmp).mecze = 0;
          (*tmp).punkty = 0;			//wyzerowanie
          (*tmp).strzelone = 0;			//danych
          (*tmp).stracone = 0;			//druzyn
          (*tmp).zwyciestwa = 0;
          (*tmp).remisy = 0;
          (*tmp).porazki = 0;  
        }//for
       return;
    }//switch(wybor)

  }//while(1)

}//PokazTabele

void RozegrajMecz(w_mecz mecz)
{
  w_druzyna druzyna = poczatek;	//wskaznik do przeszukiwania listy druzyn
  int flaga = 0;		//0 - nic jeszcze nie znaleziono
				//1 - znaleziono pierwsza druzyne
  while(druzyna)		//2 - znaleziono druga druzyne
  {
    if(flaga != 1 && !strcmp(mecz->druzyna1, druzyna->nazwa))
    {
      flaga = 1;			//znaleziono 1 druzyne
      druzyna->mecze++;			//druzyna zagrala mecz
      druzyna->strzelone += mecz->bramki1;
      druzyna->stracone += mecz->bramki2;	//wpisanie bramek

      if(mecz->bramki1 > mecz->bramki2)		//pierwsza wygrala
      {
        druzyna->zwyciestwa++;
        druzyna->punkty += 3;
      } else if (mecz->bramki1 < mecz->bramki2) {//druga wygrala
        druzyna->porazki++;
      } else {					//remis
        druzyna->remisy++;
        druzyna->punkty +=1;
      }//if(kto wygral)

    } else if(flaga != 2 && !strcmp(mecz->druzyna2, druzyna->nazwa))
    {
      flaga = 2;			//znaleziono druga druzyne
      druzyna->mecze++;			//druzyna zagrala mecz
      druzyna->strzelone += mecz->bramki2;
      druzyna->stracone += mecz->bramki1;	//wpisanie bramek

      if(mecz->bramki1 < mecz->bramki2)		//druga wygrala
      {
        druzyna->zwyciestwa++;
        druzyna->punkty += 3;
      } else if (mecz->bramki1 > mecz->bramki2) {//pierwsza wygrala
        druzyna->porazki++;
      } else {					//remis
        druzyna->remisy++;
        druzyna->punkty +=1;
      }//if(kto wygral)

    }//if

  druzyna = druzyna->nast;	//przejdz do nastepnej druzyny

  }//while

}//RozegrajMecz

void CofnijMecz(w_mecz mecz)
{
  w_druzyna druzyna = poczatek;	//wskaznik do przeszukiwania listy druzyn
  int flaga = 0;		//0 - nic jeszcze nie znaleziono
				//1 - znaleziono pierwsza druzyne
  while(druzyna)		//2 - znaleziono druga druzyne
  {
    if(flaga != 1 && !strcmp(mecz->druzyna1, druzyna->nazwa))
    {
      flaga = 1;			//znaleziono 1 druzyne
      druzyna->mecze--;			//druzyna zagrala mecz
      druzyna->strzelone -= mecz->bramki1;
      druzyna->stracone -= mecz->bramki2;	//wpisanie bramek

      if(mecz->bramki1 > mecz->bramki2)		//pierwsza wygrala
      {
        druzyna->zwyciestwa--;
        druzyna->punkty -= 3;
      } else if (mecz->bramki1 < mecz->bramki2) {//druga wygrala
        druzyna->porazki--;
      } else {					//remis
        druzyna->remisy--;
        druzyna->punkty -=1;
      }//if(kto wygral)

    } else if(flaga != 2 && !strcmp(mecz->druzyna2, druzyna->nazwa))
    {
      flaga = 2;			//znaleziono druga druzyne
      druzyna->mecze--;			//druzyna zagrala mecz
      druzyna->strzelone -= mecz->bramki2;
      druzyna->stracone -= mecz->bramki1;	//wpisanie bramek

      if(mecz->bramki1 < mecz->bramki2)		//druga wygrala
      {
        druzyna->zwyciestwa--;
        druzyna->punkty -= 3;
      } else if (mecz->bramki1 > mecz->bramki2) {//pierwsza wygrala
        druzyna->porazki--;
      } else {					//remis
        druzyna->remisy--;
        druzyna->punkty -=1;
      }//if(kto wygral)

    }//if

  druzyna = druzyna->nast;	//przejdz do nastepnej druzyny

  }//while

}//CofnijMecz

int PorownajDruzyny(w_druzyna *a, w_druzyna *b)
{
  w_druzyna tmp1 = (w_druzyna) *a;
  w_druzyna tmp2 = (w_druzyna) *b;
  w_mecz mecz = mpoczatek;		//wskaznik do szukania meczu
					//w razie rownej liczby punktow
  if(tmp1->punkty > tmp2->punkty)
    return -1;		//tmp1 lepsza
  else if(tmp1->punkty < tmp2->punkty)	//porownywanie liczby punktow
    return 1;		//tmp2 lepsza
  else {
    while(1)	//idz po liscie, dopoki nie znajdziesz meczu tmp1 z tmp2
    {
      if(!strcmp(mecz->druzyna1, tmp1->nazwa) && !strcmp(mecz->druzyna2, tmp2->nazwa))
      {
        if(mecz->bramki1 > mecz->bramki2)
          return -1;	//tmp1 lepsza
        else if (mecz->bramki1 < mecz->bramki2)
          return 1;	//tmp2 lepsza
        else
          break;
      }//if(znaleziono mecz)

      if(!strcmp(mecz->druzyna1, tmp2->nazwa) && !strcmp(mecz->druzyna2, tmp1->nazwa))
      {
        if(mecz->bramki1 > mecz->bramki2)
          return 1;	//tmp1 lepsza
        else if (mecz->bramki1 < mecz->bramki2)
          return -1;	//tmp2 lepsza
        else
          break;
      }//if(znaleziono mecz)

      mecz = mecz->nast;		//sprawdzamy dalej

    }//while(1)
					//sprawdzanie roznicy bramek
    if(tmp1->strzelone - tmp1->stracone > tmp2->strzelone - tmp2->stracone)
      return -1;	//tmp1 lepsza
    else if(tmp1->strzelone - tmp1->stracone < tmp2->strzelone - tmp2->stracone)
      return 1;		//tmp2 lepsza
    else {

      if(tmp1->strzelone  > tmp2->strzelone)	//sprawdzanie strzelonych
        return -1;	//tmp1 lepsza
      else if(tmp1->strzelone < tmp2->strzelone)
        return 1;	//tmp2 lepsza
      else
        return 0;	//nie da sie rozstrzygnac, ktora lepsza
 
    }//if(roznica bramek)

  }//if(punkty)

}//PorownajDruzyny
