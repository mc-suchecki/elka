//Nazwa pliku: test.cpp
//Autor: Maciej Suchecki (grupa 2I4)

//Opis pliku: Program testujacy klase ktora umozliwia skladowanie danych
//w kolejce FIFO. Czesc skladowa projektu numer 2 wykonanego w ramach
//przedmiotu 'Programowanie Obiektowe'.

#include "kolejka.h"

int main()
{
  Kolejka<int> kol1, kol2, wynik;

  cin >> kol1;

  cin >> kol2;

  cout << endl << "Pierwsza kolejka:" << endl << kol1 << endl;

  cout << "Druga kolejka:" << endl << kol2 << endl;

  wynik = kol1;
  cout << "wynik = kol1 :" << endl << wynik << endl;

  wynik = kol2;
  cout << "wynik = kol2 :" << endl << wynik << endl;

  wynik += kol1;
  cout << "wynik += kol1 :" << endl << wynik << endl;

  wynik = kol1 + kol2;
  cout << "wynik = kol1 + kol2 :" << endl << wynik << endl;

  wynik *= kol2;
  cout << "wynik *= kol2:" << endl << wynik << endl;

  wynik -= kol1;
  cout << "wynik -= kol1 :" << endl << wynik << endl;

  wynik = kol1 - kol2;
  cout << "wynik = kol1 - kol2:" << endl << wynik << endl;

  bool porownanie;

  porownanie = (kol1 == kol2);
  cout << endl << "kol1 == kol2: " << porownanie << endl;

  porownanie = (kol1 < kol2);
  cout << endl << "kol1 < kol2: " << porownanie << endl;

  porownanie = (kol1 > kol2);
  cout << endl << "kol1 > kol2: " << porownanie << endl;

  porownanie = (kol1 <= kol2);
  cout << endl << "kol1 <= kol2: " << porownanie << endl;

  porownanie = (kol1 >= kol2);
  cout << endl << "kol1 >= kol2: " << porownanie << endl;

  return 0;			//poprawne wykonanie programu

}//main()
