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
  Macierz A, B;			//obiekty przechowujace macierze
  double skalar;		//liczba potrzeba do mnozenia macierzy

  system("clear");		//czyszczenie terminala

  cout << "Wpisz elementy macierzy oddzielone spacjami, ";
  cout << "po kazdym wierszu wpisz srednik." << endl << "A = ";

  cin >> A;				//wczytanie macierzy A

  cout << endl << "Wpisz elementy macierzy oddzielone spacjami, ";
  cout << "po kazdym wierszu wpisz srednik." << endl << "B = ";

  cin >> B;				//wczytanie macierzy B

  cout << endl << "Wpisz liczbe: ";
  cin >> skalar;			//wczytanie liczby 

  cout << endl << "A + B = " << endl << A+B;
  cout << endl << "A - B = " << endl << A-B;
  cout << endl << "A * B = " << endl << A*B;
  cout << endl << skalar << " * A = " << endl << A*skalar;
  cout << endl << skalar << " * B = " << endl << B*skalar;
  cout << endl << "++A = " << endl << ++A;
  cout << endl << "++B = " << endl << ++B;
  cout << endl << "Wyznacznik macierzy A jest rowny: " << A.Wyznacznik() << endl;
  cout << endl << "Wyznacznik macierzy B jest rowny: " << B.Wyznacznik() << endl;
 
  return 0;				//zkonczenie programu

}//main()
