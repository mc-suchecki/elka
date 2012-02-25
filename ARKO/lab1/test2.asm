#autor: Maciej Suchecki
#data : 24-10-2011
#opis : Program zmieniajacy pozycje znakow w kolejnych parach

#sekcja danych
        .data
input:  .space 80
prompt: .asciiz "Podaj ciag znakow: "
msg1:   .asciiz "Ciag po konwersji: "

#sekcja kodu
        .text
main:
        #wyswietlenie znaku zachety
        li $v0, 4
        la $a0, prompt
        syscall

        #pobranie ciagu z konsoli
        li $v0, 8
        la $a0, input
        syscall

        #inicjalizacja zmiennej dla petli
        li $t0, 0

loop:
        #petla wykonujaca zamiane liter
        la   $t1, input                 #wskaznik na 1 znak
        add  $t1, $t1, $t0              #wskaznik na pierwsza litere z pary
        addi $t2, $t1, 1                #wskaznik na druga litere z pary
        lb   $t3, ($t1)                 #wczytujemy pierwszy znak z pary
        lb   $t4, ($t2)                 #wczytujemy drugi znak z pary
        beq  $t3, 10, end               #jesli pierwszy znak = \n, to koniec
        beq  $t4, 10, end               #jesli drugi znak = \n, to koniec
        sb   $t3, ($t2)                 #wpisanie pierwszego znaku na miejscu 2
        sb   $t4, ($t1)                 #wpisanie drugiego znaku na miejscu 1

        #skaczemy do nastepnych znakow
        addi $t0, $t0, 2                #inkrementacja licznika petli
        j    loop                       #nastepne przejscie petli

end:
        #wyswietlenie ciagu wynikowego
        li $v0, 4
        la $a0, msg1
        syscall

        li $v0, 4
        la $a0, input
        syscall

        #konczenie pracy programu
        li $v0, 10
        syscall
