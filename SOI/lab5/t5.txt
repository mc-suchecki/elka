Æwiczenie 5
Zarz±dzanie pamiêci±


1. Cel æwiczenia

Domy¶lnie w systemie Minix algorytmem wyboru wolnego bloku z listy
wolnych bloków, wykorzystywanym do realizacji funkcji systemowych FORK i
EXEC, jest algorytm first fit, czyli wybierany jest pierwszy blok
pamiêci o wystarczaj±cym rozmiarze z listy bloków wolnych.

Celem æwiczenia jest zmiana domy¶lnego algorytmu przydzia³u pamiêci w
systemie Minix. Nale¿y umo¿liwiæ wybór algorytmu wyboru bloku z listy
bloków wolnych miêdzy standardowym first fit a tzw. algorytmem worst
fit, czyli takim, w którym wybierany jest blok pamiêci z listy wolnych
bloków o najwiêkszym rozmiarze.

Nale¿y zaimplementowaæ w systemie algorytm worst fit, a nastêpnie
zademonstrowaæ i zinterpretowaæ ró¿nice w dzia³aniu poszczególnych
algorytmów.


2. Zadanie do zrealizowania

Nale¿y zdefiniowaæ dwie dodatkowe funkcje systemowe, identyfikowane sta³ymi
HOLE_MAP oraz WORST_FIT.


2.1. Funkcja systemowa HOLE_MAP powinna umo¿liwiaæ zdefiniowanie w³asnej
funkcji o sygnaturze:

int hole_map( void *buffer, size_t nbytes )

która ma za zadanie zwróciæ w buforze buffer o rozmiarze nbytes informacje o
aktualnej zawarto¶ci listy wolnych bloków utrzymywanej przez modu³
zarz±dzania pamiêci± (MM). Struktura otrzymanej w buforze informacji powinna
byæ nastêpuj±ca: 
  
  rozmiar1, adres1, rozmiar2, adres2, ..., 0

gdzie kolejne pary rozmiar, adres odpowiadaj± informacjom o kolejnych
elementach listy wolnych bloków. Rozmiar 0 oznacza ostatni element listy.
Elementy rozmiar i adres maj± typ danych unsigned int (na poziomie modu³u MM
synonim tego typu o nazwie phys_clicks).

Funkcja hole_map ma zwracaæ przes³an± liczbê par rozmiar,adres. Nale¿y
zabezpieczyæ siê przed przepe³nieniem zadanego jako argument wywo³ania
bufora i wype³niæ go tylko liczb± par mieszcz±cych siê w buforze dbaj±c o
zakoñczenie listy pozycj± rozmiar=0.


2.2. Funkcja systemowa WORST_FIT powinna umo¿liwiaæ wybór algorytmu wyboru
elementu z listy wolnych bloków i zdefiniowanie w³asnej funkcji o
sygnaturze:

int worst_fit( int w )

która dla w=1 wymusza implementowany w ramach æwiczenia algorytm przydzia³u
worst fit, natomiast dla w=0 uaktywnia z powrotem standardowy algorytm first
fit. Warto¶ci± zwracan± powinno byæ zawsze 0.


3. W celu realizacji zadania nale¿y przede wszystkim zapoznaæ siê z
zawarto¶ci± pliku 

/usr/src/mm/alloc.c

i w pliku tym dodatkowo zaimplementowaæ odpowiednio funkcje:

PUBLIC int do_worst_fit( void );
PUBLIC int do_hole_map();

argumenty wej¶ciowe znajduj± siê w zmiennej globalnej mm_in typu message
przekazanej przez programy u¿ytkowe w wywo³aniu _syscall(). Do przekazywania
jako argumentów liczb ca³kowitych mo¿na wykorzystaæ pole m1_i1 struktury
message, a do przekazania wskazania na bufor pole m1_p1 struktury message.

Do przesy³ania zawarto¶ci buforów miêdzy pamiêci± systemu operacyjnego a
pamiêci± programów u¿ytkowych nale¿y wykorzystaæ funkcjê sys_copy(), której
przyk³ad u¿ycia mo¿na znale¼æ w realizacji funkcji systemowej READ
(w pliku /usr/src/fs/read.c).


4. Testowanie funkcjonalno¶ci systemu

Nale¿y stworzyæ programy u¿ytkowe t.c, w.c oraz x.c z nastêpuj±c±
zawarto¶ci±:

-------------------------------------------------------------
/* t.c - polecenie t wyswietla liczbe i rozmiary blokow wolnych */
#include <stdio.h>
#include <unistd.h>
#include <lib.h>
                                                                                
PUBLIC int hole_map( void *buffer, size_t nbytes)
{
	/* ... _syscall(..HOLE_MAP..) ... */
}
                                                                                
int
main( void )
{
        unsigned int    b[1024];
        unsigned int    *p, a, l;
        int     res;

		res = hole_map( b, sizeof( b ) );
        printf( "[%d]\t", res );
        p = b;
        while( *p )
        {
                l = *p++;
                a = *p++; /* tu niewykorzystywane */
                printf( "%d\t", l );
        }
        printf( "\n" );
        return 0;
}
-------------------------------------------------------------
/* w.c - polecenie w przyjmuje jako argument 1 albo 0 */
/* wlaczajac/wylaczajac algorytm worst fit w systemie Minix */
#include <stdlib.h>
#include <unistd.h>
#include <lib.h>


PUBLIC int worst_fit( int w )
{
	/* ... _syscall(..WORST_FIT..) ... */
}

int
main( int argc, char *argv[] )
{
	if( argc < 2 )
		return 1;
	worst_fit( atoi( argv[1] ) );
	return 0;
}
-------------------------------------------------------------
/* x.c - program pomocniczy x, okrojona wersja polecenia sleep */
/* wykorzystywana do testów */
#include <stdlib.h>
#include <unistd.h>

int
main( int argc, char *argv[] )
{
	if( argc < 2 )
		return 1;
	sleep( atoi( argv[1] ) );
	return 0;
}
-------------------------------------------------------------

Po przygotowaniu powy¿szych poleceñ nale¿y zinterpretowaæ rezultat
dzia³ania poni¿szego skryptu. Do czego s³u¿y polecenie chmem (man
chmem)?


#!/bin/sh
# skrypt do testowania dzia³ania funkcji systemowych 
# HOLE_MAP oraz WORST_FIT
cc -o t t.c 
cc -o w w.c
cc -o x x.c
chmem =8000 x

echo "-[ std ]----------------------------------------"
./w 0
for i in 1 2 3 4 5 6 7 8 9 10
do
	./x 10 &
	./t
	sleep 1
done
for i in 1 2 3 4 5 6 7 8 9 10
do
	./t
	sleep 1
done
echo "-[ worst ]--------------------------------------"
./w 1
for i in 1 2 3 4 5 6 7 8 9 10
do
	./x 10 &
	./t
	sleep 1
done
for i in 1 2 3 4 5 6 7 8 9 10
do
	./t
	sleep 1
done
echo "-[ std ]----------------------------------------"
./w 0


5. Uwagi do realizacji zadania

* lista modyfikowanych plików systemowych:

/usr/src/mm/proto.h
/usr/src/mm/alloc.c
/usr/src/mm/table.c
/usr/include/minix/callnr.h

* lista tworzonych programów u¿ytkowych:

w.c
t.c
x.c
skrypt_testowy

* algorytm worst fit wyboru bloku wolnego powinien byæ zrealizowany jako
fragment funkcji alloc_mem,

* przy realizacji w³asnego algorytmu wyboru bloku wolnego dopuszczalne
jest zaniedbanie aspektów zwi±zanych z wymiataniem (swap),

* nale¿y zwróciæ uwagê, ¿e rozmiar bloków przechowywany i wy¶wietlany
jest nie w bajtach a w jednostkach click,

* nale¿y pamiêtaæ o regularnym zapisywaniu zmian w plikach ¼ród³owych na
osobnej dyskietce,

* w celu poprawy warsztatu pracy w ³atwy sposób mo¿na powiêkszyæ liczbê
konsoli systemowych z dwóch do np. czterech poprzez zmianê definicji sta³ej
NR_CONS w pliku /usr/include/minix/config.h


