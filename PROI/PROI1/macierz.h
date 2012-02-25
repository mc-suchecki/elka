//Nazwa pliku: macierz.h
//Autor: Maciej Suchecki (grupa 2I4)

//Opis pliku: Plik naglowkowy z deklaracja klasy umozliwiajacej
//wykonywanie operacji na macierzach. Czesc skladowa projektu
//numer 1 wykonanego w ramach przedmiotu 'Programowanie Obiektowe'.

#ifndef MACIERZ_H_
#define MACIERZ_H_

#include <iostream>		//ostream i istream
using std::ostream;
using std::istream;

#define MAX_SIZE 10		//maksymalny rozmiar macierzy (tutaj 10x10)

class Macierz
{
  private:
    unsigned int wiersze;	//ilosc wierszy w macierzy
    unsigned int kolumny;	//ilosc kolumn macierzy
    double **macierz;		//wskaznik na tablice z elementami macierzy
  public:
    //konstruktory
    Macierz();						//konstruktor domyslny
    Macierz(double **m, unsigned int w, unsigned int k);
    Macierz(const Macierz &);				//konstruktor kopiujacy
    ~Macierz();						//destruktor
    //inne metody klasy
    double Wyznacznik();				//obliczenie wyznacznika
    //metody przeciazajace operatory
    Macierz operator+(const Macierz &) const;		//dodawanie macierzy
    Macierz operator-(const Macierz &) const;		//odejmowanie macierzy
    Macierz operator*(const double) const;		//mnozenie przez skalar
    Macierz operator*(const Macierz &) const;		//mnozenie macierzy
    Macierz & operator=(const Macierz &);		//przypisywanie
    Macierz & operator+=(const Macierz &);		//dodawanie
    Macierz & operator-=(const Macierz &);		//odejmowanie
    bool operator==(const Macierz &);			//porownywanie
    Macierz & operator++();				//inkrementacja (++M)
    Macierz operator++(int);				//inkrementacja (M++)
    Macierz & operator--();				//dekrementacja (--M)
    Macierz operator--(int);				//dekrementacja (M--)
    friend ostream & operator<<(ostream &, const Macierz &);//wypisywanie
    friend istream & operator>>(istream &, Macierz &);	//wpisywanie
};

//funkcja rekurencyjnie liczaca wyznacznik macierzy
double ObliczWyznacznik(double **, int);

#endif
