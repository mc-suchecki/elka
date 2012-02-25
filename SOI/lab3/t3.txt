
Æwiczenie 3
Synchronizacja procesów z wykorzystaniem semaforów

1. Cel æwiczenia

Nale¿y napisaæ program w jêzyku C w ¶rodowisku systemu Linux realizuj±cy
rozwi±zanie problemu zadanego przez prowadz±cego æwiczenie. Problem jest
zwi±zany z organizacj± N buforów komunikacyjnych, pomiêdzy którymi s±
narzucone dodatkowe wiêzy.

2. Bufor komunikacyjny

Bufor komunikacyjny jest struktur± danych mieszcz±c± maksymalnie M elementów
jednakowego typu. Elementy z bufora mog± byæ wyjmowane w kolejno¶ci
umieszczania (FIFO) lub odwrotnej (LIFO, stos). 

3. Zadanie do zrealizowania

Nale¿y zrealizowaæ typ "bufor komunikacyjny". W czasie implementacji nale¿y
zapewniæ synchronizacjê:

- nie dopu¶ciæ do czytania z pustego bufora,

- nie dopu¶ciæ do zapisu do pe³nego bufora,

- zadbaæ o "nie przeszkadzanie sobie" procesów zapisuj±cych do bufora i
  procesów czytaj±cych z bufora.
  
Dodatkowe wiêzy mog± dotyczyæ liczby elementów aktualnie przechowywanych w
buforach, kolejno¶ci zapisu do i odczytu z poszczególnych buforów, liczby
elementów zapisywanych/odczytywanych jednocze¶nie, operacji na wielu buforach
jednocze¶nie, itd.

4. Przygotowanie do zajêæ

- proszê zapoznaæ siê z definicj± semafora oraz przyk³adem zastosowania w
  problemie producent-konsument ze slajdów wyk³adu. W szczególno¶ci s± Pañstwo
  zobligowani znaæ podan± na slajdach dok³adn± definicjê semafora. Proszê nie
  pomyliæ definicji z realizacj±.
  
  http://www.ia.pw.edu.pl/~tkruk/edu/soi.b/wyklad/w04.pdf
  (Semafory: definicja, Semafory: producent-konsument),

- http://pl.wikipedia.org/wiki/Semafor_(informatyka),

- $ man semop/semget/ipcs/ipcrm,

- "5.2 Processes Semaphores" w rozdziale "Advanced Linux Programming'
  dostêpnym on-line:
  http://www.advancedlinuxprogramming.com/alp-folder/alp-ch05-ipc.pdf

- wskazanym by³oby te¿ wprowadzaj±co choæby przejrzenie rozdzia³u dotycz±cego 
  procesów:

  http://www.advancedlinuxprogramming.com/alp-folder/alp-ch03-processes.pdf

  $ man 2 fork
  $ info libc "Process Creation Example"


