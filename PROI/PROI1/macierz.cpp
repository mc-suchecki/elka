//Nazwa pliku: macierz.cpp
//Autor: Maciej Suchecki (grupa 2I4)

//Opis pliku: Plik zrodlowy z definicjami metod klasy umozliwiajacej
//wykonywanie operacji na macierzach. Czesc skladowa projektu
//numer 1 wykonanego w ramach przedmiotu 'Programowanie Obiektowe'.

#include <iostream>			//obsluga strumieni wejscia i wyjscia
#include "macierz.h"			//plik naglowkowy z definicja klasy Macierz

using namespace std;			//standardowa przestrzen nazw

//////////////////////////////////KONSTRUKTORY/////////////////////////////////

//konstruktor domyslny
Macierz::Macierz()
{
  wiersze = kolumny = 0;		//wyzerowanie wymiarow
  macierz = NULL;			//wskaznik nie wskazuje na nic
}//Macierz::Macierz

//konstruktor
Macierz::Macierz(double **m, unsigned int w, unsigned int k)
{
  unsigned int i, j;			//zmienne wykorzystywane w petlach

  wiersze = w;				//zapisanie ilosci wierszy macierzy
  kolumny = k;				//zapisanie ilosci kolumn macierzy

  macierz = new double* [w];		//alokacja pamieci (wiersze)

  for(i=0 ; i<w ; i++)			//alokacja pamieci (kolumny)
    macierz[i] = new double [k];

  for(i=0 ; i<w ; i++)			//skakanie po wierszach
    for(j=0 ; j<k ; j++)		//skakanie po kolumnach
      macierz[i][j] = m[i][j];		//przepisywanie elementow
}//Macierz::Macierz

//konstruktor kopiujacy
Macierz::Macierz(const Macierz & tmp)
{
  unsigned int i, j;			//zmienne wykorzystywane w petlach

  wiersze = tmp.wiersze;		//zapisanie ilosci wierszy macierzy
  kolumny = tmp.kolumny;		//zapisanie ilosci kolumn macierzy

  macierz = new double* [tmp.wiersze];	//alokacja pamieci (wiersze)

  for(i=0 ; i<tmp.wiersze ; i++)	//alokacja pamieci (kolumny)
    macierz[i] = new double [tmp.kolumny];

  for(i=0 ; i<tmp.wiersze ; i++)	//skakanie po wierszach
    for(j=0 ; j<tmp.kolumny ; j++)	//skakanie po kolumnach
      macierz[i][j] = tmp.macierz[i][j];//przepisywanie elementow
}//Macierz::Macierz

//destruktor
Macierz::~Macierz()
{
  if(macierz!=NULL)
  {
    for(unsigned int i=0 ; i<wiersze ; i++)	//zwalnianie pamieci (kolumny)
      delete [] macierz[i];

    delete [] macierz;			//zwalnianie pamieci (wiersze)

  }//jesli macierz nie byla pusta

}//Macierz::~Macierz

////////////////////////////METODY PRZECIAZAJACE OPERATORY/////////////////////

//dodawanie macierzy
Macierz Macierz::operator+(const Macierz & tmp) const
{
  if(wiersze!=tmp.wiersze || kolumny!=tmp.kolumny)
  {
    cout << "Nie mozna dodawac macierzy o roznych wymiarach!" << endl;
    Macierz blad;			//nowa macierz (pusta)
    return blad;			//zwracanie
  }//sprawdzanie czy wymiary macierzy sa rowne
 
  unsigned int i, j;			//zmienne wykorzystywane w petlach

  Macierz wynik = *this;
  
  for(i=0 ; i<wynik.wiersze ; i++)		//skakanie po wierszach
    for(j=0 ; j<wynik.kolumny ; j++)		//skakanie po kolumnach
      wynik.macierz[i][j] += tmp.macierz[i][j];	//dodawanie elementow

  return wynik;					//zwrocenie wyniku

}//Macierz operator+(const Macierz & tmp) const

//odejmowanie macierzy
Macierz Macierz::operator-(const Macierz & tmp) const
{
  if(wiersze!=tmp.wiersze || kolumny!=tmp.kolumny)
  {
    cout << "Nie mozna odejmowac macierzy o roznych wymiarach!" << endl;
    Macierz blad;			//nowa macierz (pusta)
    return blad;			//zwracanie
  }//sprawdzanie czy wymiary macierzy sa rowne
 
  unsigned int i, j;				//zmienne wykorzystywane w petlach

  Macierz wynik = *this;
  
  for(i=0 ; i<wynik.wiersze ; i++)		//skakanie po wierszach
    for(j=0 ; j<wynik.kolumny ; j++)		//skakanie po kolumnach
      wynik.macierz[i][j] -= tmp.macierz[i][j];	//odejmowanie elementow

  return wynik;					//zwrocenie wyniku

}//Macierz operator-(const Macierz & tmp) const

//mnozenie macierzy przez skalar
Macierz Macierz::operator*(const double tmp) const
{
  unsigned int i, j;				//zmienne wykorzystywane w petlach

  Macierz wynik = *this;
  
  for(i=0 ; i<wynik.wiersze ; i++)		//skakanie po wierszach
    for(j=0 ; j<wynik.kolumny ; j++)		//skakanie po kolumnach
      wynik.macierz[i][j] *= tmp;		//mnozenie elementow

  return wynik;					//zwrocenie wyniku

}//Macierz operator*(const double tmp) const

//mnozenie macierzy
Macierz Macierz::operator*(const Macierz & tmp) const
{
  if(tmp.wiersze!=kolumny)
  {
    cout << "Nie mozna pomnozyc macierzy o takich wymiarach!" << endl;
    Macierz blad;			//nowa macierz (pusta)
    return blad;			//zwracanie
  }//czy liczba kolumn 1 macierzy jest rowna liczbie wierszy 2?

  double **tab;				//wskaznik do tablicy zawierajacej wynik
  unsigned int i, j, l;			//zmienne wykorzystywane w petlach

  tab = new double* [wiersze];		//alokacja pamieci (wiersze)

  for(i=0 ; i<wiersze ; i++)		//alokacja pamieci (kolumny)
    tab[i] = new double [tmp.kolumny];

  for(i=0 ; i<tmp.wiersze ; i++)	//skakanie po wierszach
    for(j=0 ; j<tmp.kolumny ; j++)	//skakanie po kolumnach
      for(l=0 , tab[i][j]=0 ; l<tmp.wiersze ; l++)
        tab[i][j] += macierz[i][l]*tmp.macierz[l][j];

  Macierz wynik(tab, wiersze, tmp.kolumny);	//zapisanie wyniku

  for(i=0 ; i<wiersze ; i++)		//zwalnianie pamieci (kolumny)
    delete [] tab[i];

  delete [] tab;			//zwalnianie pamieci (wiersze)

  return wynik;				//zwrocenie wyniku

}//Macierz operator*(const Macierz & tmp) const

Macierz & Macierz::operator=(const Macierz & tmp)
{
cout << "Operator przypisania." << endl;
  unsigned int i, j;			//zmienne wykorzystywane w petlach

  if(tmp.macierz != NULL)
  {
    for(unsigned int i=0 ; i<wiersze ; i++)//zwalnianie pamieci (kolumny)
      delete [] macierz[i];

    delete [] macierz;			//zwalnianie pamieci (wiersze)
  }//jesli macierz nie jest pusta

  wiersze = tmp.wiersze;		//zapisanie ilosci wierszy macierzy
  kolumny = tmp.kolumny;		//zapisanie ilosci kolumn macierzy

  macierz = new double* [tmp.wiersze];	//alokacja pamieci (wiersze)

  for(i=0 ; i<tmp.wiersze ; i++)	//alokacja pamieci (kolumny)
    macierz[i] = new double [tmp.kolumny];

  for(i=0 ; i<tmp.wiersze ; i++)	//skakanie po wierszach
    for(j=0 ; j<tmp.kolumny ; j++)	//skakanie po kolumnach
      macierz[i][j] = tmp.macierz[i][j];//przepisywanie elementow

  return *this;				//aby umozliwic wielokrotne przyp.

}//Macierz & Macierz::operator=(const Macierz)

//dodawanie macierzy (z przypisaniem)
Macierz & Macierz::operator+=(const Macierz & tmp)
{
  *this = *this + tmp;
  return *this;
}//Macierz & Macierz::operator+=(const Macierz & tmp)

//odejmowanie macierzy (z przypisaniem)
Macierz & Macierz::operator-=(const Macierz & tmp)
{
  *this = *this - tmp;
  return *this;
}//Macierz & Macierz::operator+=(const Macierz & tmp)

//porownywanie macierzy
bool Macierz::operator==(const Macierz & tmp)
{
  if(!macierz && !tmp.macierz) return 1;		//obie macierze puste
  
  if(!macierz || !tmp.macierz) return 0;		//jedna z macierzy pusta

  if(wiersze!=tmp.wiersze || kolumny!=tmp.kolumny) return 0;	//rozne wymiary

  unsigned int i, j;				//zmienne uzywane w petlach

  for(i=0 ; i<wiersze ; i++)				//skakanie po wierszach
    for(j=0 ; j<kolumny ; j++)				//skakanie po kolumnach
      if(macierz[i][j]!=tmp.macierz[i][j]) return 0;	//porownywanie elementow

  return 1;		//jesli petla sie wykonala, to macierze sa identyczne

}//bool operator==(const Macierz &)

//inkrementacja przedrostkowa
Macierz & Macierz::operator++()
{
  if(macierz==NULL) return *this;

  unsigned int i, j;				//zmienne uzywane w petlach

  for(i=0 ; i<wiersze ; i++)			//skakanie po wierszach
    for(j=0 ; j<kolumny ; j++)			//skakanie po kolumnach
      macierz[i][j]++;				//porownywanie elementow

  return *this;					//zwrocenie wyniku 

}//Macierz & Macierz::operator++()

//inkrementacja przyrostkowa
Macierz Macierz::operator++(int)
{
  if(macierz==NULL) return *this;

  Macierz wynik = *this;			//zachowanie tmp przed inkrementacja

  unsigned int i, j;				//zmienne uzywane w petlach

  for(i=0 ; i<wiersze ; i++)			//skakanie po wierszach
    for(j=0 ; j<kolumny ; j++)			//skakanie po kolumnach
      macierz[i][j]++;				//porownywanie elementow

  return wynik;					//zwrocenie wyniku 

}//Macierz & Macierz::operator++(int)

//dekrementacja przedrostkowa
Macierz & Macierz::operator--()
{
  if(macierz==NULL) return *this;

  unsigned int i, j;				//zmienne uzywane w petlach

  for(i=0 ; i<wiersze ; i++)			//skakanie po wierszach
    for(j=0 ; j<kolumny ; j++)			//skakanie po kolumnach
      macierz[i][j]--;				//porownywanie elementow

  return *this;					//zwrocenie wyniku 

}//Macierz & Macierz::operator--()

//dekrementacja przyrostkowa
Macierz Macierz::operator--(int)
{
  if(macierz==NULL) return *this;

  Macierz wynik = *this;			//zachowanie tmp przed inkrementacja

  unsigned int i, j;				//zmienne uzywane w petlach

  for(i=0 ; i<wiersze ; i++)			//skakanie po wierszach
    for(j=0 ; j<kolumny ; j++)			//skakanie po kolumnach
      macierz[i][j]--;				//porownywanie elementow

  return wynik;					//zwrocenie wyniku 

}//Macierz & Macierz::operator++(int)

//wypisywanie macierzy (cout)
ostream & operator<<(ostream & os, const Macierz & tmp)
{
  if(tmp.macierz==NULL) return os;	//zwroc strumien jesli macierz pusta

  unsigned int i, j;			//zmienne wykorzystywane w petlach
  
  for(i=0 ; i<tmp.wiersze ; i++)		//skakanie po wierszach
  {
    for(j=0 ; j<tmp.kolumny ; j++)		//skakanie po kolumnach
      cout << tmp.macierz[i][j] << "\t";	//wypisywanie elementow
    cout << endl;				//nastepny wiersz
  }

  return os;				//zwrocenie strumienia

}//ostream & operator<<(ostream & os, const Macierz & tmp)

//wpisywanie macierzy (cin)
istream & operator>>(istream & is, Macierz & tmp)
{
  int w=0, k=0;				//indeksy wierszy i kolumn
  int spr=0;				//sprawdzanie ilosci kolumn w wierszach
  char znak=0;				//wczytywanie znakow oddzielajacych

  double bufor[MAX_SIZE];		//przechowuje aktualnie wczytany wiersz
  double* wsk[MAX_SIZE];		//przechowuje wskazniki do wierszy

  while(1)
  {
    while(1)
    {
      cin >> bufor[k];			//wczytanie liczby
      cin.get(znak);			//wczytanie znaku

      k++;				//zwiekszenie indeksu kolumn

      if(znak==';' || znak=='\n') break;	//wczytano caly wiersz

      if(k>MAX_SIZE)
      {
        cout << "Przekroczono maksymalny rozmiar macierzy!" << endl;
        return is;			//zwrocenie strumienia
      }//jesli przekroczono bufor

      if(znak!=' ')
      {
        cout << "Nieprawidlowy format danych!" << endl;
        return is;			//zwrocenie strumienia
      }//jesli wczytano znak inny niz spacja

    }//wczytywanie wierszy

    if(k!=spr && spr!=0)
    {
      cout << "Ilosc kolumn w wierszach nie jest stala!" << endl;
      return is;			//zwrocenie strumienia
    }//jesli ilosc kolumn we wczytanym wierszu jest inna od poprzednich

    spr = k;				//zachowanie ilosci kolumn w wierszu

    wsk[w] = new double[k];		//alokacja pamieci na wczytany wiersz

    for(k-- ; k>=0 ; k--)		//przepisanie wiersza do tablicy dynamicznej
      wsk[w][k] = bufor[k];

    w++;				//zwiekszenie indeksu wierszy
    k = 0;				//wyzerowanie indeksu kolumn

    if(w>MAX_SIZE)
    {
      cout << "Przekroczono maksymalny rozmiar macierzy!" << endl;
      return is;			//zwrocenie strumienia
    }//jesli przekroczono bufor

    cin.get(znak);			//wczytanie znaku

    if(znak=='\n') break;		//jesli koniec linii zakonczenie petli
    else cin.putback(znak);		//jesli nie odkladamy znak

  }//while(1)

  if(tmp.macierz!=NULL)
  {
    for(unsigned int i=0 ; i<tmp.wiersze ; i++)//zwalnianie pamieci (kolumny)
      delete [] tmp.macierz[i];

    delete [] tmp.macierz;		//zwalnianie pamieci (wiersze)
  }//jesli macierz nie byla pusta

  tmp.wiersze = w;			//zapisanie ilosci wierszy macierzy
  tmp.kolumny = spr;			//zapisanie ilosci kolumn macierzy

  tmp.macierz = new double* [w];	//alokacja pamieci (wiersze)

  for(w-- ; w>=0 ; w--)			//skakanie po wierszach
    tmp.macierz[w] = wsk[w];		//przepisywanie wierszy

  return is;				//zwrocenie strumienia

}//istream & operator>>(istream & is, Macierz &)

//funkcja zwracajaca wyznacznik macierzy
double Macierz::Wyznacznik()
{
  if(wiersze == kolumny && wiersze!=0)
  {
    return ObliczWyznacznik(macierz, wiersze);	//wywolanie funkcji
  } else
  {
    cout << "Nie mozna obliczyc wyznacznika macierzy niekwadratowej!" << endl;
    return 0;					//nie da sie obliczyc wyznacznika
  }//sprawdzenie czy macierz jest kwadratowa

}//double Macierz::Wyznacznik()

//funkcja rekurencyjnie obliczajaca wyznacznik macierzy
double ObliczWyznacznik(double **tab,int n)
{
  int a,b,c,d;				//indeksy kolumn i wierszy
  double wynik = 0;			//zmienna przechowujaca wynik
  double **tmp = NULL;			//macierz dla nastepnej funkcji

  if (n == 1) wynik = tab[0][0];	//wyznaczniki najprostszych przypadkow
  else if (n == 2) wynik = tab[0][0] * tab[1][1] - tab[1][0] * tab[0][1];
  else {
    wynik = 0;
    for (c=0;c<n;c++) {			//tworzenie macierzy dla nast. funkcji
      tmp = new double * [n-1];
      for (a=0;a<n-1;a++) tmp[a] = new double [n-1];
      for (a=1;a<n;a++) {
        d = 0;

        for (b=0;b<n;b++) {
          if (b == c) continue;
          tmp[a-1][d] = tab[a][b];	//wypelnianie macierzy odpowiednimi
          d++;				//elementami z wlasciwej macierzy
        }

      }

      if (c%2==0) wynik += tab[0][c] * ObliczWyznacznik(tmp,n-1);
      else wynik -= tab[0][c] * ObliczWyznacznik(tmp,n-1);

      for (a=0;a<n-1;a++) delete [] tmp[a];	//usuwanie macierzy wysylanej do
      delete [] tmp;				//nastepnego wywolania funkcji
    }
  }

  return(wynik);				//zwracanie wyznacznika

}//ObliczWyznacznik

