//Nazwa pliku: test.cpp
//Autor: Maciej Suchecki (grupa 2I4)

//Opis pliku: Plik zrodlowy z programem testujacym klase Macierz umozliwiajaca
//wykonywanie operacji na macierzach. Czesc skladowa projektu numer 1
//wykonanego w ramach przedmiotu 'Programowanie Obiektowe'.

#include <iostream>		//obsluga strumieni wejscia i wyjscia
#include <cstdlib>		//funkcja system()
#include "macierz.h"		//plik naglowkowy z definicja klasy Macierz

using namespace std;		//standardowa przestrzen nazw

int main()
{
  char wybor=0;			//przechowuje znak wpisany przez uzytkownika
  Macierz A, B;			//obiekty przechowujace macierze
  double skalar;		//liczba potrzeba do mnozenia macierzy

  while(1)
  {
    system("clear");

    cout << "Witaj w kalkulatorze macierzy! Wpisz numer wybranej operacji:";
    cout << endl << endl << "1. Dodawanie macierzy";
    cout << endl << "2. Odejmowanie macierzy";
    cout << endl << "3. Mnozenie macierzy przez skalar";
    cout << endl << "4. Mnozenie macierzy";
    cout << endl << "5. Obliczanie wyznacznika macierzy";
    cout << endl << "6. Wyjscie z programu";
    cout << endl;

    cin.get(wybor);			//wczytanie wyboru uzytkownika
    while(cin.get()!='\n') continue;	//czyszczenie wejscia

    if(wybor=='6') return 0;		//wyjscie z programu

    cout << endl << "Wpisz elementy macierzy oddzielone spacjami, ";
    cout << "po kazdym wierszu wpisz srednik." << endl << "A = ";

    cin >> A;				//wczytanie macierzy A

    if(wybor=='3')
    {
      cout << endl << "Wpisz liczbe, przez ktora chcesz pomnozyc macierz: ";
      cin >> skalar;			//wczytanie liczby 

      cout << endl << skalar << " * A = " << endl << A;
      break;

    } else if (wybor=='5')
    {
      cout << endl << "Wyznacznik macierzy:" << endl << A << "jest rowny: " << A.Wyznacznik() << endl;
    } else
    {
      cout << endl << "Wpisz elementy macierzy oddzielone spacjami, ";
      cout << "po kazdym wierszu wpisz srednik." << endl << "B = ";

      cin >> B;				//wczytanie macierzy B

    }//jesli wybrano mnozenie przez skalar lub wyznacznik

    switch(wybor)
    {
      case '1': cout << endl << "A + B = " << endl << A+B; break;
      case '2': cout << endl << "A - B = " << endl << A-B; break;
      case '4': cout << endl << "A * B = " << endl << A*B; break;
    }//switch(wybor)

    while(cin.get()!='\n') continue;	//czyszczenie wejscia

  }//while(1)

}//main()
