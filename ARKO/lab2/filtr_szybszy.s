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
##### FUNKCJA WYKONUJACA FILTR MEDIANOWY #####
# argumenty:
# a0 - deskryptor pliku
# a1 - rozmiar maski
# a2 - adres bufora wynikowego

        # prolog
 	addi $sp, $sp, -32
	sw $s6, 28($sp)
	sw $s5, 24($sp)
	sw $s4, 20($sp)
	sw $s3, 16($sp)
	sw $s2, 12($sp)
	sw $s1, 8($sp)
	sw $s0, 4($sp)
	sw $ra, 0($sp) 
 
        # zapisujemy adresy deskryptora i buforow
        move $s0, $a0           # s0 - adres deskryptora
        ulw $s1, ($a0)          # s1 - adres pliku zrodlowego
        move $s2, $a2           # s2 - adres pliku wynikowego

        # alokujemy bufor do liczenia wartosci piksela
        mul $t0, $a1, $a1       # maska * maska
        add $a0, $t0, $t0       # 2 * maska * maska
        add $a0, $a0, $t0       # 3 * maska * maska
	li $v0, 9		# wywolujemy SBRK
	syscall

        # s3 - ilosc wierszy do przetworzenia
        ulw $s3, 8($s0)         # wysokosc obrazka
        sub $s3, $s3, $a1       # wysokosc - maska
        addi $s3, $s3, 1        # wysokosc - maska + 1

        # obliczamy ile bajtow zajmuje wiersz pikseli
        ulw $t0, 4($s0)         # szerokosc obrazka
        addu $t1, $t0, $t0      # 2 * szerokosc obrazka
        addu $t1, $t1, $t0      # 3 * szerokosc obrazka
        move $s5, $t1           # przyda sie pozniej
        addiu $t1, $t1, 3       # dodajemy 3 i
        srl $t1, $t1, 2         # zerujemy 2 najmlodsze bity:
        sll $t1, $t1, 2         # czyli doliczamy padding

        # modyfikujemy deskryptor - po modyfikacji zawiera:
        usw $v0, ($s0)          # 1. adres bufora do liczenia mediany
        usw $t1, 4($s0)         # 2. dlugosc wiersza w bajtach
        usw $a1, 8($s0)         # 3. rozmiar maski

        # obliczamy ilosc bajtow do przepisania bez zmian
        srl $t0, $a1, 1         # ilosc wierszy = (maska - 1) / 2
        mul $t1, $t1, $t0       # dlugosc wiersza * ilosc wierszy

przepisz:
        lbu $t2, ($s1)          # pobieramy bajt
        sb $t2, ($s2)           # zapisujemy bajt
        addi $s1, $s1, 1        # przesuwamy wskaznik zrodla
        addi $s2, $s2, 1        # przesuwamy wskaznik celu
        addi $t1, $t1, -1       # zmniejszamy licznik
        bne $t1, 0, przepisz    # wykonujemy petle t1 razy

        # obliczamy ilosc bajtow to przepisania bez zmian w wierszu
        addu $s4, $t0, $zero    # (maska - 1) / 2
        sll $t0, $t0, 1
        addu $s4, $s4, $t0      # 3 * (maska - 1) / 2

        # obliczamy w ktorym miejscu musimy przestac modyfikowac piksele
        subu $s5, $s5, $s4      # (3 * szerokosc) - s4

kopiuj_wiersz:
        # zerujemy zmienna liczaca ilosc przepisanych bajtow
        add $s6, $zero, $zero   # s6 - ilosc przepisanych bajtow
        
poczatek:
        # przepisujemy kilka bajtow bez zmian
        lbu $t0, ($s1)          # pobieramy bajt
        sb $t0, ($s2)           # zapisujemy bajt
        addi $s1, $s1, 1        # przesuwamy wskaznik zrodla
        addi $s2, $s2, 1        # przesuwamy wskaznik celu
        addi $s6, $s6, 1        # zwiekszamy licznik
        bne $s6, $s4, poczatek  # wykonujemy petle s4 razy

srodek:
        # modyfikujemy piksele
        move $a0, $s0           # argument 1 - deskryptor
        move $a1, $s1           # argument 2 - wskaznik zrodla
        move $a2, $s2           # argument 3 - wskaznik celu
        jal GetPixel            # liczymy i zapisujemy piksel
        addi $s1, $s1, 1        # przesuwamy wskaznik zrodla
        addi $s2, $s2, 1        # przesuwamy wskaznik celu

        addi $s6, $s6, 1        # zwiekszamy licznik
        bne $s6, $s5, srodek    # wykonujemy petle s5 - s4 razy
 
        # pobieramy dlugosc wiersza z deskryptora
        ulw $t0, 4($s0)         # dlugosc wiersza w bajtach

koniec:
        # przepisujemy koncowe bajty bez zmian
        lbu $t1, ($s1)          # pobieramy bajt
        sb $t1, ($s2)           # zapisujemy bajt
        addi $s1, $s1, 1        # przesuwamy wskaznik zrodla
        addi $s2, $s2, 1        # przesuwamy wskaznik celu
        addi $s6, $s6, 1        # zwiekszamy licznik
        bne $s6, $t0, koniec    # wykonujemy petle t0 razy

        addi $s3, $s3, -1       # wykonujemy petle s3 razy
        bne $s3, $zero, kopiuj_wiersz

        # obliczamy ilosc bajtow do przepisania bez zmian
        ulw $t0, 8($s0)         # rozmiar maski
        srl $t0, $t0, 1         # ilosc wierszy = (maska - 1) / 2
        ulw $t1, 4($s0)         # dlugosc wiersza
        mul $t0, $t0, $t1       # dlugosc wiersza * ilosc wierszy

przepisz2:
        lbu $t1, ($s1)          # pobieramy bajt
        sb $t1, ($s2)           # zapisujemy bajt
        addi $s1, $s1, 1        # przesuwamy wskaznik zrodla
        addi $s2, $s2, 1        # przesuwamy wskaznik celu
        addi $t0, $t0, -1       # zmniejszamy licznik
        bne $t0, 0, przepisz2   # wykonujemy petle t0 razy

        # epilog
	lw $s6, 28($sp)
	lw $s5, 24($sp)
	lw $s4, 20($sp)
	lw $s3, 16($sp)
	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 32
        
        # zakonczenie funkcji
        jr $ra

GetPixel:
##### FUNKCJA OBLICZAJACA WARTOSC DOCELOWA PIKSELA #####
# argumenty:
# a0 - adres deskryptora
# a1 - adres piksela z obrazu zrodlowego
# a2 - adres pod ktory nalezy zapisac wynik

        # prolog
 	addi	$sp, $sp, -4
        sw	$ra, 0($sp) 

        # pobieramy dane z deskryptora
        ulw $t0, ($a0)          # t0 - adres bufora do wypelnienia
        ulw $t1, 4($a0)         # t1 - dlugosc wiersza w bajtach
        ulw $t2, 8($a0)         # t2 - rozmiar maski

        # ustawiamy sie na poczatku
        srl $t3, $t2, 1
        mul $t4, $t1, $t3
        subu $a1, $a1, $t4
        li $t4, 3
        mul $t4, $t3, $t4
        subu $a1, $a1, $t4

        # obliczamy zmienna do poruszania sie po buforze
        mul $t6, $t2, $t2       # maska * maska

        # ustawiamy zmienne uzywane w petlach
        move $t3, $t2           # ilosc wierszy do wczytania

wpisz_wiersz:
        move $t4, $t2

wpisz_piksel:
        # kopiujemy piksel
        lbu $t5, ($a1)
        sb $t5, ($t0)           # 1 kolor
        addi $a1, $a1, 1
        add $t0, $t0, $t6
        lbu $t5, ($a1)
        sb $t5, ($t0)           # 2 kolor
        addi $a1, $a1, 1
        add $t0, $t0, $t6
        lbu $t5, ($a1)
        sb $t5, ($t0)           # 3 kolor
        addi $a1, $a1, 1
        sub $t0, $t0, $t6
        sub $t0, $t0, $t6
        addi $t0, $t0, 1

        addi $t4, $t4, -1
        bne $t4, 0, wpisz_piksel

        # przesuwamy 'piksel' do nowej linii
        add $a1, $a1, $t1
        sub $a1, $a1, $t2
        sub $a1, $a1, $t2
        sub $a1, $a1, $t2

        addi $t3, $t3, -1
        bne $t3, 0, wpisz_wiersz

        # ustawiamy zmienne dla wywolania Median
        ulw $a0, ($a0)          # adres bufora
        move $a1, $t6           # rozmiar bufora

        # liczymy wartosci piksela - pierwszy kolor
        jal Median
        sb $v0, ($a2)

        # nastepny kolor
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

        # zerujemy licznik petli
        add $t0, $zero, $zero

median_loop1:
        addi $t0, $t0, 1                # inkrementujemy licznik petli
        bgt $t0, $a1, median_end        # koniec jesli t0 > rozmiar bufora
        add $t1, $a1, $zero             # t1 = rozmiar bufora

median_loop2:
        bge $t0, $t1, median_loop1
        addi $t1, $t1, -1
        addi $t3, $t1, -1
        add $t7, $t1, $a0
        add $t2, $t3, $a0
        lbu $t5, ($t7)
        lbu $t6, ($t2)

        # jesli el. sa w zlej kolejnosci to zamieniamy
        bgt $t5, $t6, median_loop2
        sb $t5, ($t2)
        sb $t6, ($t7)
        j median_loop2
        
median_end:
        # zwracamy srodkowy element
        addi $a1, $a1, -1
        srl $a1, $a1, 1
        add $a0, $a0, $a1
        lbu $v0, ($a0)

        jr $ra
