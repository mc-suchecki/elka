# Nazwa pliku:  filtr.s
# Autor:        Maciej Suchecki (3I4)
# Opis:         Program wykonuje algorytm filtra medianowego na plikach .bmp

# SEKCJA DANYCH
        .data
input:	.asciiz "in.bmp"
output:	.asciiz "out.bmp"
header:	.space 54
info:   .space 12
loerr:	.asciiz "Nie udalo sie zaladowac pliku!\n"

# SEKCJA KODU
	.text
	.globl main
	
main:
	# otwieramy plik
	li $v0, 13		# 13 - otwarcie pliku
	la $a0, input   	# sciezka pliku
	li $a1, 0x8000  	# flagi binary, read
	li $a2, 0444    	# tryb r--r--r--
	syscall
	move $t0, $v0           # zapisujemy deskryptor pliku w t0
	
	# wczytujemy naglowek
	li $v0, 14		# 14 - oczyt z pliku
	move $a0, $t0		# deskryptor pliku
	la $a1, header		# bufor docelowy
	li $a2, 54		# ilosc bajtow do wczytania (54 - naglowek)
	syscall

        # sprawdzamy czy plik wczytano poprawnie
	beq $t0, 0xffffffff, load_error
	
	# odczytujemy rozmiar tablicy pikseli z naglowka i alokujemy pamiec
	la $s2, header
	li $v0, 9		# wywolujemy SBRK podajac dlugosc bufora w a0
        ulw $a0, 34($s2)        # pod 34 bajtem naglowka mamy rozmiar tablicy
        move $s2, $a0           # kopiujemy rozmiar tablicy, przyda sie pozniej
	syscall
	move $s0, $v0 		# kopiujemy sobie adres zaalokowanego bufora
	
        # alokujemy pamiec na drugi bufor
	li $v0, 9		# wywolujemy SBRK jeszcze raz (drugi bufor)
        move $a0, $s2           # zadany rozmiar
	syscall
	move $s1, $v0 		# kopiujemy sobie adres zaalokowanego bufora

	#wczytywanie pliku
	li $v0, 14		# 14 - czytanie z pliku
	move $a0, $t0		# deskryptor pliku
	la $a1, ($s0)		# bufor do wczytania
	move $a2, $s2		# ilosc bajtow do wczytania
	syscall
	
	#zamykanie pliku
	li $v0, 16
	move $a0, $t0
	syscall
	
        # przygotowujemy deskryptor obrazu
        la $t2, info            # adres deskryptora
        usw $s0, ($t2)          # adres bufora wejsciowego
        la $t3, header          # adres naglowka
        ulw  $t4, 18($t3)       # pobieramy szerokosc obrazka
        usw $t4, 4($t2)         # zapisujemy szerokosc obrazka
        ulw  $t4, 22($t3)       # pobieramy wysokosc obrazka
        usw $t4, 8($t2)         # zapisujemy wysokosc obrazka

        # zapisujemy argumenty i wywolujemy funkcje MedianFilter
        la $a0, info            # deskryptor - rozdzielczosc i bufor wejsciowy
        li $a1, 3               # rozmiar maski
        move $a2, $s1           # bufor wyjsciowy
        jal MedianFilter

	# otwieramy plik do zapisu
	li $v0, 13 		# 13 - otwarcie pliku
	la $a0, output 		# otwieramy do zapisu lub tworzymy out.bmp
	li $a1, 577 		# flagi O_CREAT|O_TRUNC|O_WRONLY
	li $a2, 420 		# tryb rw-r--r--
	syscall
	move $t0, $v0 		# zapisujemy deskryptor pliku
	
	# zapisujemy naglowek do pliku wynikowego
	li $v0, 15		# 15 - zapis
	move $a0, $t0		# deskryptor pliku
	la $a1, header          # zapisujemy naglowek
	li $a2, 54              # dlugosc naglowka
	syscall	

	# zapisujemy tablice pikseli do pliku wynikowego
	li $v0, 15		# 15 - zapis
	move $a0, $t0		# deskryptor pliku
	la $a1, ($s1)		# zapisujemy z bufora wynikowego funkcji
	move $a2, $s2		# dlugosc tablicy pikseli
	syscall	
	
	#zamykanie pliku
	li $v0, 16		# 16 - zamkniecie pliku
	move $a0, $t0		# deskryptor pliku
	syscall

	# zakonczenie programu
	li $v0, 10
	syscall

load_error:
        # wystapil blad przy odczycie pliku - wyswietlamy komunikat
	li $v0, 4
	la $a0, loerr	
	syscall

	# zakonczenie programu
	li $v0, 10
	syscall

MedianFilter:
##### FUNKCJA WYWOLUJACA FILTR MEDIANOWY #####
# argumenty:
# a0 - deskryptor pliku
# a1 - rozmiar maski
# a2 - adres bufora wynikowego

        # prolog
 	addi	$sp, $sp, -36
	sw	$s7, 32($sp)
	sw	$s6, 28($sp)
	sw	$s5, 24($sp)
	sw	$s4, 20($sp)
	sw	$s3, 16($sp)
	sw	$s2, 12($sp)
	sw	$s1, 8($sp)
	sw	$s0, 4($sp)
	sw	$ra, 0($sp) 

        # zapisujemy adres obrazka zrodlowego
        ulw  $t0, ($a0)

        # obliczamy ile skrajnych pikseli musimy pominac
        addi $t1, $a1, -1
        li $t2, 2
        divu $t1, $t2           # (maska - 1)/2
        mflo $t1

        # obliczamy ile bajtow zajmuje jeden wiersz pikseli
        ulw  $t2, 4($a0)
        li $t3, 3               # 24 bity/piksel
        multu $t2, $t3
        mflo $t2                # t2 - ilosc bajtow/wiersz
        li $t3, 4
        divu $t2, $t3
        mfhi $t3
        li $t4, 4
        subu $t3, $t4, $t3      # t3 - padding w bajtach

        # przepisujemy pierwsze linie bez zmian
        add $t4, $t3, $t2       # dlugosc wiersza
        multu $t1, $t4          # dlugosc wiersza * ilosc linii do pom.
        mflo $t4

przepisz:
        lbu $t5, ($t0)          # pobieramy bajt
        sb $t5, ($a2)           # zapisujemy bajt
        addi $t0, $t0, 1
        addi $a2, $a2, 1        # przesuwamy wskazniki
        addi $t4, $t4, -1       # zmniejszamy licznik
        bne $t4, 0, przepisz    # wykonujemy petle dopoki t4!=0

        # alokujemy bufor na wartosci pikseli maski
        move $t7, $a0           # zapisujemy wartosc a0
        multu $a1, $a1          # maska * maska
        mflo $a0
        li $t6, 3
        multu $a0, $t6          # maska * maska * 3
        mflo $a0
	li $v0, 9		# wywolujemy SBRK
	syscall
	move $s0, $v0 		# kopiujemy sobie adres zaalokowanego bufora
        move $a0, $t7           # przywracamy a0

        # obliczamy ilosc wierszy do przetworzenia



        # epilog
	lw	$s7, 32($sp)
	lw	$s6, 28($sp)
	lw	$s5, 24($sp)
	lw	$s4, 20($sp)
	lw	$s3, 16($sp)
	lw	$s2, 12($sp)
	lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)
	addi	$sp, $sp, 36
        
        # zakonczenie funkcji
        jr $ra

FillBuffer:
##### FUNKCJA WYPELNIAJACA BUFOR PIKSELI #####
# argumenty:
# a0 - adres bufora
# a1 - rozmiar maski
# a2 - adres piksela z obrazu zrodlowego
# a3 - szerokosc obrazu w pikselach

        # prolog
 	addi	$sp, $sp, -36
	sw	$s7, 32($sp)
	sw	$s6, 28($sp)
	sw	$s5, 24($sp)
	sw	$s4, 20($sp)
	sw	$s3, 16($sp)
	sw	$s2, 12($sp)
	sw	$s1, 8($sp)
	sw	$s0, 4($sp)
	sw	$ra, 0($sp) 

        # obliczamy ile skrajnych pikseli musimy pominac
        addi $s1, $a1, -1
        srl $s1, $s1, 1         # (maska-1)/2

        # obliczamy ile bajtow zajmuje jeden wiersz pikseli
        lw $s2, 4($a0)
        li $s3, 3               # 24 bity/piksel
        mul $s2, $s3, $s2       # s2 - ilosc bajtow/wiersz
        li $s3, 4
        divu $s2, $s3
        mfhi $s3
        li $s4, 4
        subu $s3, $s4, $s3      # s3 - padding w bajtach
        add $s2, $s2, $s3       # s2 - dlugosc wiersza

        # wyliczamy sobie maska*maska
        mul $s5, $a1, $a1

        # ustawiamy sie na poczatku
        addi $s3, $s2, 1
        mul $s3, $s3, $s1
        li $s4, 3
        mul $s3, $s3, $s4
        sub $a2, $a2, $s3

        # ustawiamy zmienne uzywane w petlach
        move $s6, $a1

FillBuffer_loop1:
        move $s7, $a1

FillBuffer_loop2:
        # kopiujemy piksel
        lbu $s4, ($a2)
        sb $s4, ($a0)           # 1 kolor
        addi $a2, $a2, 1
        add $a0, $a0, $s5
        lbu $s4, ($a2)
        sb $s4, ($a0)           # 2 kolor
        addi $a2, $a2, 1
        add $a0, $a0, $s5
        lbu $s4, ($a2)
        sb $s4, ($a0)           # 3 kolor
        addi $a2, $a2, 1
        sub $a0, $a0, $s5
        sub $a0, $a0, $s5
        addi $a0, $a0, 1

        addi $s7, $s7, -1
        bne $s7, 0, FillBuffer_loop2

        # przesuwamy 'piksel' do nowej linii
        add $a2, $a2, $s2
        sub $a2, $a2, $a1

        addi $s6, $s6, -1
        bne $s6, 0, FillBuffer_loop1

        # epilog
	lw	$s7, 32($sp)
	lw	$s6, 28($sp)
	lw	$s5, 24($sp)
	lw	$s4, 20($sp)
	lw	$s3, 16($sp)
	lw	$s2, 12($sp)
	lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)
	addi	$sp, $sp, 36

        jr $ra

CountPixel:
##### FUNKCJA LICZACA WARTOSC PIKSELA #####
# argumenty:
# a0 - adres bufora
# a1 - rozmiar maski
# a2 - adres pod ktory nalezy zapisac wynik

        # prolog
 	addi	$sp, $sp, -4
	sw	$ra, 0($sp) 

        # obliczamy rozmiar bufora
        mul $a1, $a1, $a1

        # pierwszy kolor
        jal Median
        sb $v0, ($a2)

        # nastepny
        add $a0, $a0, $a1
        addi $a2, $a2, 1
        jal Median
        sb $v0, ($a2)

        # ostatni
        add $a0, $a0, $a1
        addi $a2, $a2, 1
        jal Median
        sb $v0, ($a2)

        # epilog
	lw	$ra, 0($sp)
	addi	$sp, $sp, 4

        jr $ra

Median:
##### FUNKCJA LICZACA MEDIANE #####
# argumenty:
# a0 - adres bufora
# a1 - rozmiar bufora

        # prolog
 	addi	$sp, $sp, -36
	sw	$s7, 32($sp)
	sw	$s6, 28($sp)
	sw	$s5, 24($sp)
	sw	$s4, 20($sp)
	sw	$s3, 16($sp)
	sw	$s2, 12($sp)
	sw	$s1, 8($sp)
	sw	$s0, 4($sp)
	sw	$ra, 0($sp) 

        add $s0, $zero, $zero

median_loop1:
        addi $s0, $s0, 1
        bgt $s0, $a1, median_end
        add $s1, $a1, $zero

median_loop2:
        bge $s0, $s1, median_loop1
        addi $s1, $s1, -1
        mul $s4, $s1, 4
        addi $s3, $s4, -4
        add $s7, $s4, $a0
        add $s2, $s3, $a0
        lw $s5, ($s7)
        lw $s6, ($s2)

        # jesli el. sa w zlej kolejnosci to zamieniamy
        bgt $s5, $s6, median_loop2
        sw $s5, ($s2)
        sw $s6, ($s7)
        j median_loop2
        
median_end:
        # zwracamy srodkowy element
        addi $a1, $a1, -1
        li $s7, 2
        div $a1, $s7
        mflo $a1
        mul $a1, $a1, 4
        add $a0, $a0, $a1
        lbu $v0, ($a0)

        # epilog
	lw	$s7, 32($sp)
	lw	$s6, 28($sp)
	lw	$s5, 24($sp)
	lw	$s4, 20($sp)
	lw	$s3, 16($sp)
	lw	$s2, 12($sp)
	lw	$s1, 8($sp)
	lw	$s0, 4($sp)
	lw	$ra, 0($sp)
	addi	$sp, $sp, 36

        jr $ra
