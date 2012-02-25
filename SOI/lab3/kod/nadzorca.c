//Nazwa pliku: nadzorca.c
//Autor: Maciej Suchecki (grupa 3I4)

//Opis pliku: Plik wykonywalny z kodem 'nadzorcy', ktory tworzy bufor
//komunikacyjny dla procesow, a nastepnie wywoluje zadana w argumentach liczbe,
//losujac przy kazdym wywolaniu typ - czytelnik lub pisarz. Plik jest czescia
//implementacji bufora komunikacyjnego sterowanego semaforami, pisanego na
//potrzeby laboratorium numer 3 z przedmiotu Systemy Operacyjne.

#include "bufor.h"                      //plik naglowkowy ze stalymi
#include <sys/ipc.h>
#include <sys/shm.h>                    //pliki do obslugi semaforow i pamieci
#include <sys/sem.h>
#include <stdlib.h>                     //obsluga funkcji atoi oraz rand
#include <unistd.h>                     //wywolania systemowe - fork i exec
#include <stdio.h>                      //operacje wejscia-wyjscia

int main(int argc, char *argv[])
{
  int procesy, pamiec_id, semafor_id;   //ilosc procesow, id semaforow i pamieci
  int indeks, los, pid = 1;             //zmienne uzywane w petli
  char znak;
  
  //////////////////////////TWORZYMY BUFOR KOMUNIKACYJNY/////////////////////

  //alokujemy pamiec wspoldzielona
  pamiec_id = shmget(klucz_pamieci, (rozmiar_bufora + 2)*sizeof(int), 0777 | IPC_CREAT | IPC_EXCL);
  if(pamiec_id == -1) {/*printf("BLAD przy alokacji pamieci!\n");*/ return 1;}

  //tworzymy semafory
  semafor_id = semget(klucz_semafora, 3, 0777 | IPC_CREAT | IPC_EXCL);
  if(semafor_id == -1) {/*printf("BLAD przy tworzeniu semafora!\n");*/ return 1;}

  //ustawiamy semafory
  if(semctl(semafor_id, MUTEX, SETVAL, 1) == -1 ||
     semctl(semafor_id, FULL, SETVAL, 0) == -1 ||
     semctl(semafor_id, EMPTY, SETVAL, rozmiar_bufora) == -1)
  {
    //printf("BLAD przy ustawianiu semafora!\n");
    return 1;
  }//if

  printf("Co chcesz uruchomic? (p)roducent/(k)onsument/(w)yjdz: ");

  //petla uruchamiajaca procesy
  while(1)
  {
    if(pid != 0) {
      znak = getchar();
    }

    switch(znak)
    {
      case 'k':
        //wywolujemy czytelnika
        pid = fork();
        if(pid == 0) {
          char* argumenty[] = {"./czytelnik", NULL};
          execvp(*argumenty, argumenty);
          pid = 1;
          return 0;
        }
        break;
      case 'p':
        //wywolujemy pisarza
        pid = fork();
        if(pid == 0) {
          char* argumenty[] = {"./pisarz", NULL};
          execvp(*argumenty, argumenty);
          pid = 1;
          return 0;
        }
        break;
      case 'w':
        //zwolnienie pamieci i usuniecie semaforow
        semctl(semafor_id, 0, IPC_RMID);
        shmctl(pamiec_id, IPC_RMID, NULL);
        return 0;
      default:
        break;
    }//switch

  }//for

  return 0;                             //poprawne zakonczenie programu

}//main
