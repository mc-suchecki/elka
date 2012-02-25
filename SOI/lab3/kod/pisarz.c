//Nazwa pliku: pisarz.c
//Autor: Maciej Suchecki (grupa 3I4)

//Opis pliku: Plik wykonywalny z kodem 'pisarza', ktory dodaje do bufora
//komunikacyjnego stworzonego przez 'nadzorce' wiadomosci. Plik jest czescia
//implementacji bufora komunikacyjnego sterowanego semaforami, pisanego na
//potrzeby laboratorium numer 3 z przedmiotu Systemy Operacyjne.

#include "bufor.h"                      //plik naglowkowy ze stalymi
#include <sys/ipc.h>
#include <sys/shm.h>                    //pliki do obslugi semaforow i pamieci
#include <sys/sem.h>
#include <stdio.h>                      //operacje wejscia-wyjscia

int main()
{
  int pamiec_id, semafor_id, *bufor;    //identyfikatory, wskaznik na bufor

  //pobieramy id pamieci wspoldzielonej
  pamiec_id = shmget(klucz_pamieci, rozmiar_bufora + 2, 0);
  if(pamiec_id == -1) {/*printf("BLAD przy uzyskaniu id pamieci!\n");*/ return 1;}

  //pobieramy id semaforow
  semafor_id = semget(klucz_semafora, 3, 0);
  if(semafor_id == -1) {/*printf("BLAD przy uzyskaniu id semafora!\n");*/ return 1;}

  //zmieniamy wartosc semafora EMPTY (zmienia sie ilosc elementow)
  semafor.sem_num = EMPTY;
  semafor.sem_op = -1;
  if(semop(semafor_id, &semafor, 1) == -1) {
    //printf("BLAD - nieudane przestawienie semafora EMPTY\n");
    return 1;
  }

  //zmieniamy wartosc semafora MUTEX (aby zapobiec dostepowi do bufora)
  semafor.sem_num = MUTEX;
  semafor.sem_op = -1;
  if(semop(semafor_id, &semafor, 1) == -1) {
    //printf("BLAD - nieudane przestawienie semafora MUTEX\n");
    return 1;
  }

  //podlaczamy wspoldzielona pamiec do przestrzeni adresowej naszego procesu
  if((bufor = shmat(pamiec_id, NULL, 0)) == (void *) -1) {
    //printf("BLAD - brak dostepu do pamieci wspoldzielonej\n");
    return 1;
  }

  bufor[++*bufor] = ++bufor[rozmiar_bufora + 1];                //MAGIC!

  printf("Pisarz dodal do bufora w miejscu %d wartosc %d.\n", *bufor, bufor[*bufor]);

  //odlaczamy wspoldzelona pamiec
  if(shmdt(bufor) == -1) {
    //printf("BLAD - nieudane odlaczenie pamieci wspoldzielonej\n");
    return 1;
  }

  //zmieniamy wartosc semafora MUTEX (aby przywrocic dostep do bufora)
  semafor.sem_num = MUTEX;
  semafor.sem_op = 1;
  if(semop(semafor_id, &semafor, 1) == -1) {
    //printf("BLAD - nieudane przestawienie semafora MUTEX\n");
    return 1;
  }

  //zmieniamy wartosc semafora FULL (zmienia sie ilosc elementow)
  semafor.sem_num = FULL;
  semafor.sem_op = 1;
  if(semop(semafor_id, &semafor, 1) == -1) {
    //printf("BLAD - nieudane przestawienie semafora FULL\n");
    return 1;
  }

  return 0;                             //poprawne zakonczenie programu

}//main
