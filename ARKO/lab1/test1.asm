#autor: Maciej Suchecki
#data : 24-10-2011
#opis : Program zamieniajacy wielkie litery w ciagu na *

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
        add  $t1, $t1, $t0              #przesuwamy na nastepna litere
        lb   $t2, ($t1)                 #kopiujemy aktualny znak do t2
        beq  $t2, 0, end                #skaczemy do end jesli znak to \0
        bgtu $t2, 90, continue          #sprawdzamy, czy kod znaku
        bltu $t2, 64, continue          #zawiera sie w przedziale 64-90
        li   $t2, 42                    #wpisujemy gwiazdke do rejestru
        sb   $t2, ($t1)                 #wpisujemy gwiazdke do ciagu znakow

continue:
        #skaczemy do nastepnego znaku
        addi $t0, $t0, 1                #inkrementacja licznika petli
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
