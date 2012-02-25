//Nazwa pliku: graf.cpp
//Autor: Maciej Suchecki (grupa 3I4)

//Opis pliku: Plik zrodlowy z kodem programu obliczajacego najkrotsza
//sciezke pomiedzy danymi wierzcholkami w grafie. Czesc skladowa projektu
//numer 4 wykonanego w ramach przedmiotu 'Algorytmy i Struktury Danych'.

#include <iostream>                         //wiadomo
#include <vector>                           //kontener vector
#include <deque>                            //kontener deque
#include <set>                              //kontener set
#include <cstdio>                           //scanf(), getchar()
#include <cfloat>                           //FLT_MAX
#include <cmath>                            //sqrt()

using namespace std;

vector<float> odleglosc;                    //tablica odleglosci od zrodla
vector<int> poprzednik;                     //tablica indeksow poprzednikow
vector< pair<float,float> > wierzcholki;    //tablica wspolrzednych wierzcholkow

//obiekt funkcyjny do porownywania wierzcholkow
struct cmp {
  bool operator() (const int &a, const int &b) {
    if(odleglosc[a] < odleglosc[b]) return true;
    if(odleglosc[a] > odleglosc[b]) return false;
    return a < b;
  }
};

//funkcja znajdujaca najkrotsza droge z wierzcholka poczatek do koniec
void Dijkstra(int poczatek, int koniec, vector< pair<int,float> > krawedzie[]) {
  int i, akt, sasiad;           //sasiad - indeks wierz. sasiedniego do akt
  float droga;                  //droga - pomiedzy akt i sasiadem
  set<int, cmp> kolejka;        //kolejka priorytetowa wierzcholkow

  odleglosc.resize(wierzcholki.size(), FLT_MAX);  //ustawiamy odleglosci
  odleglosc[poczatek] = 0;

  poprzednik.resize(wierzcholki.size(), -1);      //ustawiamy poprzednikow
  poprzednik[poczatek] = poczatek;

  //wypelniamy kolejke priorytetowa wierzcholkami
  for(i = 0; i < wierzcholki.size(); ++i) kolejka.insert(i);

  while(!kolejka.empty()) {
    akt = *(kolejka.begin());                   //pobieramy najblizszy wierz.
    kolejka.erase(kolejka.begin());

    for(i = 0; i < krawedzie[akt].size(); i++) {
      sasiad = krawedzie[akt][i].first;
      droga = krawedzie[akt][i].second;

      //jesli znalezlismy krotsza droge od zrodla do wierzcholka sasiad
      if(odleglosc[akt] + droga < odleglosc[sasiad]) {
        poprzednik[sasiad] = akt;
        kolejka.erase(kolejka.find(sasiad));
        odleglosc[sasiad] = odleglosc[akt] + droga;
        kolejka.insert(sasiad);
      }
    }
  }

  //wypisujemy wynik
  deque<float> wynik;
  wynik.push_back(odleglosc[koniec]);

  while(koniec != poczatek) {
    wynik.push_back(koniec);
    koniec = poprzednik[koniec];
  }

  wynik.push_back(poczatek);

  while(!wynik.empty()) { 
    cout << wynik.back() << " ";
    wynik.pop_back();
  }

  cout << endl;
}

int main() {
  float x, y;                   //zmienne sluzace do wczytywania danych
  int a, b;

  while(cin) {                  //wczytywanie wierzcholkow
    scanf("%f %f", &x, &y);
    if(getchar() != '\n') break;
    wierzcholki.push_back(make_pair(x, y));
  }

  //tworzymy tablice wektorow przechowujaca krawedzie
  vector< pair<int,float> > krawedzie[wierzcholki.size()];

  a = (int)x;
  b = (int)y;
  scanf("%f", &x);

  while(cin) {                  //wczytywanie krawedzi
    krawedzie[a].push_back(make_pair(b, x));
    scanf("%d %d %f", &a, &b, &x);
    if(getchar() != '\n') break;
  }

  scanf("%d %d", &a, &b);
  Dijkstra(a, b, krawedzie);

  int indeks;
  //zmieniamy wagi krawedzi na odleglosci geometryczne
  for (int i = 0; i < wierzcholki.size(); i++) {
    for (int j = 0; j < krawedzie[i].size(); j++) {
      indeks = krawedzie[i][j].first;
      x = wierzcholki[i].first;
      x -= wierzcholki[indeks].first;
      x *= x;
      y = wierzcholki[i].second;
      y -= wierzcholki[indeks].second;
      y *= y;
      krawedzie[i][j].second = sqrt(x + y);
    }
  }

  Dijkstra(a, b, krawedzie);

  return 0;
}
