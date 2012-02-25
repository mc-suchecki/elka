#autor: Maciej Suchecki
#data : 24-10-2011
#opis : Program zmieniajacy litery po znaku - na wielkie (usuwa -)

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

        #inicjalizacja zmiennych dla petli
        li $t0, 0                       #aktualna pozycja w ciagu
        li $t1, 0                       #liczba napotkanych znakow -

loop:
        #petla wykonujaca zamiane liter
        la   $t2, input                 #wskaznik na 1 znak
        add  $t2, $t2, $t0              #przesuwamy na nastepna litere
        lb   $t3, ($t2)                 #wczytujemy aktualna litere
        beq  $t3, 45, found             #skocz jesli aktualny znak to '-'

        #wczytalismy zwykly znak
        beq  $t3, 10, end               #jesli aktualny znak to '\n' to koniec
        beq  $t1, 0, continue           #nie bylo wczesniej '-', nie robimy nic
        sub  $t4, $t2, $t1              #obliczenie adresu docelowego znaku
        sb   $t3, ($t4)                 #zapisanie znaku w odpowiednim miejscu
        j    continue                   #nastepna litera
        
found:
        #znalezlismy '-'
        lb   $t3, 1($t2)                #wczytujemy nastepny znak
        bgtu $t3, 122, notupper         #sprawdzamy czy musimy zamieniac
        bltu $t3, 97, notupper          #sprawdzamy czy musimy zamieniac
        addiu $t3, $t3, -32             #zmieniamy znak na wielki

notupper:
        #pozostalo przesunac znak
        sub  $t4, $t2, $t1              #obliczenie adresu docelowego znaku
        sb   $t3, ($t4)                 #przesuniecie znaku o liczbe znalezionych '-'
        addi $t1, $t1, 1                #inkrementacja licznika '-'
        addi $t0, $t0, 1                #pomijamy jeden znak

continue:
        #skaczemy do nastepnego znaku
        addi $t0, $t0, 1                #inkrementacja licznika petli
        j    loop                       #nastepne przejscie petli

end:
        #wpisanie znakow konca ciagu
        sub  $t2, $t2, $t1              #obliczenie nowego konca ciagu
        li   $t4, 10                    #znak nowej linii
        sb   $t4, ($t2)                 #wpisanie go do rejestru

        li   $t4, 0                     #znak konca ciagu
        sb   $t4, 1($t2)                #wpisanie go do rejestru

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
