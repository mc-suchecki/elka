//Nazwa pliku: monitor.cpp
//Autor: Maciej Suchecki (grupa 3I4)

//Opis pliku: Plik wykonywalny z kodem 'nadzorcy', ktory tworzy bufor
//komunikacyjny dla procesow, a nastepnie wywoluje w petli watki o typie
//(czytelnik lub pisarz) wybranym przez uzytkownika. Plik jest czescia
//implementacji bufora komunikacyjnego sterowanego monitorem, pisanego na
//potrzeby laboratorium numer 4 z przedmiotu Systemy Operacyjne.

#include "monitor.h"                    //plik naglowkowy z klasa Monitor
#include <stdlib.h>                     //obsluga funkcji atoi oraz rand
#include <unistd.h>                     //wywolania systemowe - fork i exec
#include <stdio.h>                      //operacje wejscia-wyjscia

#define BUFFER_SIZE     10              //wielkosc bufora

void* Producent(void *);                //watek producenta
void* Konsument(void *);                //watek konsumenta

//definicja klasy Bufor
class Bufor : private Monitor {
  private:
    int count;                          //ilosc elementow w buforze
    int buffer[BUFFER_SIZE];            //tablica przechowujaca bufor
    Condition full, empty;              //sygnalizacja pustego i pelnego bufora
  public:
    Bufor() : count(0) {}               //konstruktor domyslny

    //dodawanie wartosci do bufora
    void push(int value) {
      enter();
      while(count == BUFFER_SIZE) wait(full);

      buffer[count] = value;
      count++;

      if(count == 1) signal(empty);
      leave();
    }

    //pobieranie wartosci z bufora
    int pop() {
      int value;
      enter();
      if(count == 0) wait(empty);

      count--;
      value = buffer[count];

      if(count == BUFFER_SIZE - 1) signal(full);
      leave();
      return value;
    }

};

Bufor bufor_komunikacyjny;              //tworzymy egzemplarz klasy Bufor

int main(int argc, char *argv[])
{
  char znak;                            //znak wpisany przez uzytkownika
  int ilosc_watkow, *tmp;               //ilosc watkow i tymczasowy wskaznik
  pthread_t id_watku;                   //identyfikator watku

  printf("Co chcesz uruchomic? (p)roducent/(k)onsument/(w)yjdz: ");

  //petla uruchamiajaca procesy
  while(1)
  {
    znak = getchar();

    switch(znak)
    {
      case 'k':
        //wywolujemy czytelnika
        pthread_create(&id_watku, NULL, Konsument, NULL);
        break;
      case 'p':
        //wywolujemy pisarza
        tmp = (int *) malloc(sizeof(int));
        *tmp = ilosc_watkow;

        pthread_create(&id_watku, NULL, Producent, tmp);
        ilosc_watkow++;
        break;
      case 'w':
        return 0;
      default:
        break;
    }//switch

  }//while(1)

  return 0;

}//main

void* Producent(void *value) {
  bufor_komunikacyjny.push(*(int*)value);
  printf("Producent dodal do bufora wartosc %d.\n", *(int*)value);
  free(value);
  return 0;
}

void* Konsument(void *value) {
  int i = bufor_komunikacyjny.pop();
  printf("Konsument pobrał z bufora wartosc %d.\n", i);
  return 0;
}
