//Nazwa pliku: test.cpp
//Autor: Maciej Suchecki (grupa 2I4)

//Opis pliku: Program testujacy klase ktora umozliwia skladowanie danych
//w kolejce FIFO. Czesc skladowa projektu numer 2 wykonanego w ramach
//przedmiotu 'Programowanie Obiektowe'.

#include "kolejka.h"			//naglowek i metody klasy kolejka
#include <cstdlib>			//funkcje rand() i srand()
#include <ctime>			//funkcja time()

int main()
{
  Kolejka<int> kol1, kol2, wynik;	//testowe kolejki

  srand((unsigned)time(0));		//ustawienie funkcji rand()

  for(int i=0; i<=1000; i++)		//petla tworzaca kolejki
  {
    kol1.DodajElement(rand());		//dodawanie elementow do kol1
    kol2.DodajElement(rand());		//dodawanie elementow do kol2
  }//for  

  int wybor, bledy=0, dobre=0;		//wybieranie operacji, liczniki

  for(int i=0; i<1000; i++)		//petla wykonujaca losowe operacje
  {
    wybor = (rand()%5)+1;		//wylosowanie operacji
    switch (wybor)
    {
      case 1:
        wynik = kol1;
	if(wynik == kol1) dobre++;
	else bledy++;
        break;
      case 2:
        wynik = kol2;
	if(wynik == kol2) dobre++;
	else bledy++;
        break;
      case 3:
        wynik = kol1 + kol2;
	if(wynik == kol1 + kol2) dobre++;
	else bledy++;
        break;
      case 4:					//wykonanie operacji
        wynik = kol1 - kol2;
	if(wynik == kol1 - kol2) dobre++;
	else bledy++;
        break;
      case 5:
        wynik = kol1 * kol2;
	if(wynik == kol1 * kol2) dobre++;
	else bledy++;
        break;
     }//switch
   }//for

  cout << "Wykonano " << dobre << " poprawnych i ";
  cout << bledy << " niepoprawnych operacji." << endl;

  return 0;					//koniec

}//main
