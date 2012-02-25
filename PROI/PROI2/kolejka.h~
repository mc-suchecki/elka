//Nazwa pliku: kolejka.h
//Autor: Maciej Suchecki (grupa 2I4)

//Opis pliku: Plik naglowkowy z deklaracja klasy umozliwiajacej
//skladowanie danych w kolejce FIFO. Czesc skladowa projektu
//numer 2 wykonanego w ramach przedmiotu 'Programowanie Obiektowe'.

#ifndef KOLEJKA_H_
#define KOLEJKA_H_

#include <iostream>		//strumen wejscia i wyjscia
#include <string>		//obsluga klasy string

using namespace std;		//standardowa przestrzen nazw

template <typename Typ>
class Kolejka;			//deklaracja klasy Kolejka (do klasy Element)

template <typename Typ>
ostream & operator<<(ostream &, const Kolejka<Typ> &);

template <typename Typ>
istream & operator>>(istream &, Kolejka<Typ> &);

//definicja elementu listy jednokierunkowej
template <typename Typ>
class Element
{
  private:
    Typ zawartosc;		//przechowywana zawartosc
    Element *nast;		//wskaznik na nastepny element
  public:
    Element() {nast = NULL; zawartosc = 0;}	//konstruktor domyslny
    Element(const Typ &tmp) : zawartosc(tmp) {nast = NULL;} //konstruktor
    friend ostream & operator<<<Typ>(ostream &, const Kolejka<Typ> &);//cout
    friend class Kolejka<Typ>;	//dzieki temu tylko klasa Kolejka ma dostep
};				//do prywatnych danych klasy Element

//definicja wlasciwej klasy ktora wykorzystuje klase Element
template <typename Typ>
class Kolejka
{
  private:
    Element<Typ> *poczatek;		//wskaznik na poczatek kolejki
    Element<Typ> *koniec;		//wskaznik na koniec kolejki

  public:
    //konstruktory i destruktory
    Kolejka<Typ>();			//konstruktor domyslny
    Kolejka<Typ>(const Kolejka<Typ> &);	//konstruktor kopiujacy
    ~Kolejka<Typ>();			//destruktor

    //metody klasy
    void DodajElement(Typ);	//metoda dodajaca element na koncu kolejki
    Typ PobierzElement();	//metoda pobierajaca pierwszy element
    void UsunKolejke();		//metoda usuwajaca wszystkie elementy kolejki

    //metody przeciazajace operatory
    const Typ operator[](int numer) const;		//odwolanie do elementu
    Kolejka<Typ> & operator=(const Kolejka<Typ> &);	//przypisywanie kolejek
    Kolejka<Typ> & operator+=(const Kolejka<Typ> &);	//laczenie kolejek
    Kolejka<Typ> operator+(const Kolejka<Typ> &) const; //laczenie kolejek
    Kolejka<Typ> & operator-=(const Kolejka<Typ> &);	//usuwanie ident. el.
    Kolejka<Typ> operator-(const Kolejka<Typ> &) const;	//usuwanie ident. el.
    Kolejka<Typ> & operator*=(const Kolejka<Typ> &);	//usuwanie roznych el.
    Kolejka<Typ> operator*(const Kolejka<Typ> &) const;	//usuwanie roznych el.
    bool operator==(const Kolejka<Typ> &) const;	//porownywanie zawartosci
    bool operator<(const Kolejka<Typ> &) const;		//porownywanie dlugosci
    bool operator<=(const Kolejka<Typ> &) const;	//porownywanie dlugosci
    bool operator>(const Kolejka<Typ> &) const;		//porownywanie dlugosci
    bool operator>=(const Kolejka<Typ> &) const;	//porownywanie dlugosci
    friend ostream & operator<<<Typ>(ostream &, const Kolejka<Typ> &);//cout
    friend istream & operator>><Typ>(istream &, Kolejka<Typ> &);//wpisywanie
};

/////////////////////////////////KONSTRUKTORY//////////////////////////////////

//konstruktor domyslny
template <typename Typ>
Kolejka<Typ>::Kolejka()
{
  poczatek = koniec = NULL;		//wyzerowanie wskaznikow
}//Kolejka::Kolejka()

//konstruktor kopiujacy
template <typename Typ>
Kolejka<Typ>::Kolejka(const Kolejka<Typ> & tmp)
{
  poczatek = koniec = NULL;		//wyzerowanie wskaznikow

  Element<Typ> *el = tmp.poczatek;	//pomocniczy wskaznik

  while(el)
  {
    DodajElement(el->zawartosc);	//dodanie nowego elementu
    el = el->nast;			//przejscie do nastepnego
  }//while(el)
}//Kolejka::Kolejka(const Kolejka tmp)

//destruktor
template <typename Typ>
Kolejka<Typ>::~Kolejka()
{
  UsunKolejke();			//zwolnienie pamieci po elementach kolejki
}//Kolejka::~Kolejka()

/////////////////////////////////METODY KLASY//////////////////////////////////

//metoda dodajaca element na koncu kolejki
template <typename Typ>
void Kolejka<Typ>::DodajElement(Typ tmp)
{
  Element<Typ> *el = new Element<Typ>(tmp);	// nowy element kolejki

  if(!poczatek) poczatek = el;		//jesli lista jest pusta, wpisz el
  else koniec->nast = el;		//jesli nie, dolacz el do konca

  koniec = el;				//dopisanie el na koncu

  el->nast = NULL;			//po el nic nie ma  

}//bool Kolejka<Typ>::DodajElement(Typ tmp)

//metoda pobierajaca pierwszy element
template <typename Typ>
Typ Kolejka<Typ>::PobierzElement()
{
  Element<Typ> *tmp = poczatek->nast;	//pomocniczy wskaznik

  Typ wynik = poczatek->zawartosc;	//zapisanie zawartosci

  delete poczatek;			//usuniecie pierwszego elementu

  poczatek = tmp;			//nowy poczatek

  return wynik;				//zwrocenie zawartosci pierwszego elementu

}//Typ Kolejka<Typ>::PobierzElement()

//metoda czyszczaca zawartosc kolejki
template <typename Typ>
void Kolejka<Typ>::UsunKolejke()
{
  if(!poczatek) return;			//jesli kolejka jest pusta

  Element<Typ> *tmp;			//wskaznik na element kolejki

  while(poczatek)			//dopoki nie bedzie konca kolejki
  {
    tmp = poczatek->nast;		//ustaw tmp na nastepnym elemencie
    delete poczatek;			//usun pierwszy element
    poczatek = tmp;			//przejdz do nastepnego
  }//while(tmp)

  poczatek = koniec = NULL;		//wyzerowanie wskaznikow

}//void Kolejka<Typ>::UsunKolejke()

///////////////////////////////PRZECIAZENIA OPERATOROW/////////////////////////

//odwolanie do konkretnego elementu kolejki po numerze
template <typename Typ>
const Typ Kolejka<Typ>::operator[](int numer) const
{
  if(numer<0) return 0;			//nie ma takiego elementu

  Element<Typ> *tmp = poczatek;		//pomocniczy wskaznik

  while(numer!=0)
  {
    if(tmp->nast==NULL) return 0;	//przeszlismy cala kolejke
    else tmp = tmp->nast;		//przechodzenie po kolejce
    numer--;				//zmniejszanie licznika
  }//while

  return tmp->zawartosc;		//zwrocenie zawartosci elementu

}//Typ operator[](int numer)

//przeciazony operator = realizujacy przypisywanie kolejek
template <typename Typ>
Kolejka<Typ> & Kolejka<Typ>::operator=(const Kolejka<Typ> & tmp)
{
  UsunKolejke();			//zwolnienie pamieci po elementach kolejki

  Element<Typ> *el = tmp.poczatek;	//pomocniczy wskaznik

  while(el)
  {
    DodajElement(el->zawartosc);	//dodanie nowego elementu
    el = el->nast;			//przejscie do nastepnego
  }//while(el)

  return *this;				//zwrocenie wyniku przypisania

}//Kolejka Kolejka<Typ>::operator=(const Kolejka<Typ> & tmp)

//przeciazony operator += realizujacy laczenie kolejek
template <typename Typ>
Kolejka<Typ> & Kolejka<Typ>::operator+=(const Kolejka<Typ> & tmp)
{
  Element<Typ> *el = tmp.poczatek;	//pomocniczy wskaznik
 
  while(el)
  {
    DodajElement(el->zawartosc);	//dodanie nowego elementu
    el = el->nast;			//przejscie do nastepnego
  }//while(el)

  return *this;				//zwrocenie wyniku laczenia

}//Kolejka Kolejka<Typ>::operator+=(const Kolejka<Typ> & tmp)

//przeciazony operator + realizujacy laczenie kolejek
template <typename Typ>
Kolejka<Typ> Kolejka<Typ>::operator+(const Kolejka<Typ> & tmp) const
{
  Kolejka<Typ> wynik = *this;		//zmienna przechowujaca wynik

  wynik += tmp;				//polaczenie kolejek

  return wynik;				//zwrocenie wyniku

}//Kolejka Kolejka<Typ>::operator+(const Kolejka<Typ> & tmp)

//przeciazony operator -= realizujacy usuwanie tych samych elementow kolejek
template <typename Typ>
Kolejka<Typ> & Kolejka<Typ>::operator-=(const Kolejka<Typ> & tmp)
{
  Element<Typ> *el = tmp.poczatek;	//el sluzy do 'czytania' kolejki tmp
  Element<Typ> *el2=poczatek, *el3=NULL;//el2 i el3 do kasowania elementow

  while(el)
  {
    while(el2)
    {
      if(el->zawartosc == el2->zawartosc)//jesli zawartosci sa takie same
      {
        if(el2!=poczatek && el2!=koniec)//usuwamy element w srodku kolejki
          el3->nast = el2->nast;	//przepisanie wskaznika
          
        if(el2 == poczatek)		//usuwamy poczatek
          poczatek = el2->nast;		//nowy poczatek

        if(!el2->nast)			//usuwamy koniec
        {
          koniec = el3;			//nowy koniec - element przed usuwanym
          if(el3) el3->nast = NULL;	//nie ma nic po nowym koncu
        }//if(poczatek==el2)

        delete el2;			//usuniecie pasujacego elementu

        if(poczatek==NULL && koniec==NULL)	//pusta kolejka
          return *this;				//wyjscie

        if(el3) el2 = el3->nast;	//przejscie do nastepnego elementu
        else el2 = poczatek;

      }//if(zaw==zaw)
      else {

        el3 = el2;			//wskaznik na poprzedni element
        el2 = el2->nast;		//przejscie do nastepnego elementu

      }//else

    }//while(el2)

    el3 = NULL;				//wyzerowanie wskaznika
    el2 = poczatek;			//powrot wskaznika
    el = el->nast;			//przejscie do nastepnego

  }//while(el)

  return *this;				//zwrocenie wyniku odejmowania

}//Kolejka<Typ> & operator-=(const Kolejka<Typ> & tmp)

//przeciazony operator - realizujacy usuwanie tych samych elementow kolejek
template <typename Typ>
Kolejka<Typ> Kolejka<Typ>::operator-(const Kolejka<Typ> & tmp) const
{
  Kolejka<Typ> wynik = *this;		//zmienna przechowujaca wynik

  wynik -= tmp;				//polaczenie kolejek

  return wynik;				//zwrocenie wyniku

}//Kolejka Kolejka<Typ>::operator+(const Kolejka<Typ> & tmp)

//przeciazony operator *= realizujacy usuwanie roznych elementow kolejek
template <typename Typ>
Kolejka<Typ> & Kolejka<Typ>::operator*=(const Kolejka<Typ> & tmp)
{
  Element<Typ> *el = tmp.poczatek;	//el sluzy do 'czytania' kolejki tmp
  Element<Typ> *el2=poczatek,*el3=NULL;	//el2 i el3 do kasowania elementow

  while(el2)
  {
    while(el)
    {
      if(el->zawartosc == el2->zawartosc)	//jesli jest odpowiednik
      {
        el3 = el2;				//przejdz do nastepnego elementu
        el2 = el2->nast;
        break;					//wyjdz z petli przeszukiwania tmp
      }
      else if(el->nast) el = el->nast;		//nie ma - szukaj dalej
      else 				//nie ma takiego elementu w tmp - kasuj
      {
        if(el2!=poczatek && el2!=koniec)//usuwamy element w srodku kolejki
          el3->nast = el2->nast;	//przepisanie wskaznika

        else {
          if(el2 == poczatek)		//usuwamy poczatek
            poczatek = el2->nast;	//nowy poczatek

          else if(!el2->nast)		//usuwamy koniec
          {
            koniec = el3;		//nowy koniec - element przed usuwanym
            if(el3) el3->nast = NULL;	//nie ma nic po nowym koncu
          }//if(poczatek==el2)

        }//if(srodek)

        delete el2;			//usuniecie pasujacego elementu

        if(el3) el2 = el3->nast;	//przejscie do nastepnego elementu
        else el2 = poczatek;

        if(poczatek==NULL && koniec==NULL)	//pusta kolejka
          return *this;				//wyjscie

        break;				//przejscie do nastepnego elementu

      }//if(zaw==zaw)

    }//while(el)

  el = tmp.poczatek;			//wracamy na poczatek tmp

  }//while(el2)

  return *this;				//zwrocenie wyniku odejmowania

}//Kolejka<Typ> & Kolejka<Typ>::operator*=(const Kolejka<Typ> & tmp)

//przeciazony operator * realizujacy usuwanie roznych elementow kolejek
template <typename Typ>
Kolejka<Typ> Kolejka<Typ>::operator*(const Kolejka<Typ> & tmp) const
{
  Kolejka<Typ> wynik = *this;		//zmienna przechowujaca wynik

  wynik *= tmp;				//polaczenie kolejek

  return wynik;				//zwrocenie wyniku

}//Kolejka Kolejka<Typ>::operator*(const Kolejka<Typ> & tmp)

//przeciazony operator == relizujacy porownywanie kolejek
template <typename Typ>
bool Kolejka<Typ>::operator==(const Kolejka<Typ> & tmp) const
{
  Element<Typ> *el = tmp.poczatek;	//wskaznik 'przeszukujacy' kolejke tmp
  Element<Typ> *el2 = poczatek;		//wskaznik 'przeszukujacy' kolejke this

  //jesli jedna z kolejek jest pusta wystarczy sprawdzic pierwsze elementy
  if(!el || !el2) return (!el && !el2);

  while(1)
  {
    if(el->zawartosc != el2->zawartosc) return 0;	//element ma inna zawartosc
    
    if(el->nast && el2->nast) {				//takie same elementy;
      el = el->nast;					//sprawdzamy dalej
      el2 = el2->nast;
    }
    
    else if(!el->nast && !el2->nast) return 1;		//koniec kolejki
    
    else return 0;					//kolejki roznej dlugosci

  }//while(1)

}//bool operator==(const Kolejka<Typ> & tmp) const

//przeciazony operator < realizujacy porownywanie dlugosci kolejek
template <typename Typ>
bool Kolejka<Typ>::operator<(const Kolejka<Typ> & tmp) const
{
  Element<Typ> *right = tmp.poczatek;	//wskaznik 'przeszukujacy' kolejke tmp
  Element<Typ> *left = poczatek;	//wskaznik 'przeszukujacy' kolejke this

  while(1)
  {
    if(!right) return 0;		//koniec prawej kolejki
    
    if(!left) return 1;			//koniec lewej (ale nie prawej) kolejki

    left = left->nast;			//nie ma konca zadnej kolejki;
    right = right->nast;		//idziemy dalej

  }//while(1)

}//bool Kolejka<Typ>::operator<(const Kolejka<Typ> & tmp) const

//przeciazony operator <= realizujacy porownywanie dlugosci kolejek
template <typename Typ>
bool Kolejka<Typ>::operator<=(const Kolejka<Typ> & tmp) const
{
  Element<Typ> *right = tmp.poczatek;	//wskaznik 'przeszukujacy' kolejke tmp
  Element<Typ> *left = poczatek;	//wskaznik 'przeszukujacy' kolejke this

  while(1)
  {
    if(!left) return 1;			//koniec lewej kolejki

    if(!right) return 0;		//koniec prawej (ale nie lewej) kolejki

    left = left->nast;			//nie ma konca zadnej kolejki;
    right = right->nast;		//idziemy dalej

  }//while(1)

}//bool Kolejka<Typ>::operator<=(const Kolejka<Typ> & tmp) const

//przeciazony operator > realizujacy porownywanie dlugosci kolejek
template <typename Typ>
bool Kolejka<Typ>::operator>(const Kolejka<Typ> & tmp) const
{
  Element<Typ> *right = tmp.poczatek;	//wskaznik 'przeszukujacy' kolejke tmp
  Element<Typ> *left = poczatek;	//wskaznik 'przeszukujacy' kolejke this

  while(1)
  {
    if(!left) return 0;			//koniec lewej kolejki

    if(!right) return 1;		//koniec prawej (ale nie lewej) kolejki

    left = left->nast;			//nie ma konca zadnej kolejki;
    right = right->nast;		//idziemy dalej

  }//while(1)

}//bool Kolejka<Typ>::operator>(const Kolejka<Typ> & tmp) const

//przeciazony operator >= realizujacy porownywanie dlugosci kolejek
template <typename Typ>
bool Kolejka<Typ>::operator>=(const Kolejka<Typ> & tmp) const
{
  Element<Typ> *right = tmp.poczatek;	//wskaznik 'przeszukujacy' kolejke tmp
  Element<Typ> *left = poczatek;	//wskaznik 'przeszukujacy' kolejke this

  while(1)
  {
    if(!right) return 1;		//koniec prawej kolejki

    if(!left) return 0;			//koniec lewej (ale nie prawej) kolejki

    left = left->nast;			//nie ma konca zadnej kolejki;
    right = right->nast;		//idziemy dalej

  }//while(1)

}//bool Kolejka<Typ>::operator>=(const Kolejka<Typ> & tmp) const
    
//przeciazony operator << realizujacy wypisywanie elementow kolejki
template <typename Typ>
ostream & operator<<(ostream & os, const Kolejka<Typ> & tmp)
{
  Element<Typ> *el = tmp.poczatek;	

  while(el)
  {
    cout << el->zawartosc << endl;	//wypisanie elementu kolejki
    el = el->nast;			//przejscie do nastepnego elementu
  }//while()

  return os;				//zwrocenie strumienia

}//ostream & operator<<(ostream & os, const Kolejka<Typ> & tmp)

//przeciazony operator >> realizujacy wpisywanie elementow kolejki
template <typename Typ>
istream & operator>>(istream & is, Kolejka<Typ> & tmp)
{
  tmp.UsunKolejke();		//zwolnienie pamieci po elementach kolejki

  Typ zmienna;			//zmienna przechowujaca wpisywana wartosc

  cout << "Wpisz kolejne elementy kolejki, po kazdym wcisnij ENTER." << endl;
  cout << "Aby zakonczyc, wcisnij Ctrl+D (EOF)." << endl;

  while(1)
  {
    cin >> zmienna;			//pobranie wpisanej wartosci

    if(is.eof()) break;			//jesli wcisnieto Ctrl+D

    tmp.DodajElement(zmienna);		//dodanie elementu do kolejki      

  }//while(1)

  cin.clear();				//resetowanie stanu strumienia
  cin.sync();

  return is;				//zwrocenie strumienia
}//istream & operator>>(istream &, Kolejka<Typ> &)

#endif
