#include "bufor.h"                      //plik naglowkowy ze stalymi
#include <sys/ipc.h>
#include <sys/shm.h>                    //pliki do obslugi semaforow i pamieci
#include <sys/sem.h>
#include <stdlib.h>                     //obsluga funkcji atoi oraz rand
#include <unistd.h>                     //wywolania systemowe - fork i exec
#include <stdio.h>                      //operacje wejscia-wyjscia

int main()
{
  int pamiec_id, semafor_id;

  //pobieramy id pamieci wspoldzielonej
  pamiec_id = shmget(klucz_pamieci, rozmiar_bufora + 2, 0);
  if(pamiec_id == -1) {printf("BLAD przy uzyskaniu id pamieci!\n"); return 1;}

  //pobieramy id semaforow
  semafor_id = semget(klucz_semafora, 3, 0);
  if(semafor_id == -1) {printf("BLAD przy uzyskaniu id semafora!\n"); return 1;}

  //zwolnienie pamieci i usuniecie semaforow
  semctl(semafor_id, 0, IPC_RMID);
  shmctl(pamiec_id, IPC_RMID, NULL);
  return 0;

}
