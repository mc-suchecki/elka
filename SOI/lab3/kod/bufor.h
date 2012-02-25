//Nazwa pliku: bufor.h
//Autor: Maciej Suchecki (grupa 3I4)

//Opis pliku: Plik naglowkowy zawierajacy definicje stalych wykorzystywanych
//w implementacji bufora komunikacyjnego sterowanego semeforami, pisanej na
//potrzeby laboratorium numer 3 z przedmiotu Systemy Operacyjne.

#ifndef BUFOR_H_
#define BUFOR_H_

#include <sys/sem.h>                    //definicja struktury sembuf

#define klucz_semafora    6969          //klucz do odwolan do semafora
#define klucz_pamieci     996           //klucz do odwolan do pamieci wspoldz.

#define rozmiar_bufora    100           //rozmiar kolejki

enum{MUTEX, FULL, EMPTY};               //nazwy semaforow

struct sembuf semafor = {0, 0, 0};      //struktura potrzebna do semop()

#endif
