        section .text
        global WriteBits
        global ReadCode

; funkcja wypelnia linie obrazu na podstawie tablicy dlugosci odcinkow
; pierwszy argument - dlugosc tablicy
; drugi argument - wskaznik na tablice
; trzeci argument - docelowy bajt obrazu
WriteBits:
  push ebp
  mov ebp, esp
  push ebx              ; prolog
  push esi
  push edi

  mov dl, 128           ; maska
  mov edi, 0            ; licznik petli
  mov ecx, [ebp+16]     ; adres zrodlowy

main_loop:
  mov eax, [ebp+12]
  mov ebx, 0
  mov bx, [eax+2*edi]   ; adres + licznik petli

write_white:
  cmp ebx, 0
  jle main_loop_middle  ; dopoki ebx > 0

  mov al, [ecx]         ; pobieramy bajt zrodlowy
  or al, dl             ; suma bitowa zrodla z maska
  mov [ecx], al         ; zapisujemy bajt w pamieci
  shr dl, 1             ; przesuwamy maske w prawo
  dec ebx

  cmp dl, 0
  jne write_white       ; sprawdzamy czy maska = 0
  mov dl, 128           ; resetujemy maske
  inc ecx               ; przesuwamy sie na nastepny bajt
  jmp write_white       ; powtarzamy

main_loop_middle:
  inc edi               ; sprawdzamy nastepna liczbe w RLE
  mov eax, [ebp+12]
  mov ebx, 0
  mov bx, [eax+2*edi]   ; adres + licznik petli

write_black:
  cmp ebx, 0
  jle main_loop_end     ; dopoki ebx > 0

  mov al, [ecx]         ; pobieramy bajt zrodlowy
  not dl                ; negujemy maske
  and al, dl            ; iloczyn bitowy zrodla z maska
  not dl                ; przywracamy maske
  mov [ecx], al         ; zapisujemy bajt w pamieci
  shr dl, 1             ; przesuwamy maske w prawo
  dec ebx

  cmp dl, 0
  jne write_black       ; sprawdzamy czy maska = 0
  mov dl, 128           ; resetujemy maske
  inc ecx               ; przesuwamy sie na nastepny bajt
  jmp write_black       ; powtarzamy

main_loop_end:
  inc edi               ; sprawdzamy nastepna liczbe w RLE
  mov eax, [ebp+8]      ; wczytujemy dlugosc RLE
  cmp edi, eax
  jl main_loop          ; powtarzamy wszystko

  pop edi
  pop esi
  pop ebx               ; epilog
  mov esp, ebp  
  pop ebp
  ret

; funkcja odczytuje kod T4 i zwraca zakodowana dlugosc odcinka
; pierwszy argument - wskazanie na tablice kodow (bialych/czarnych)
; drugi argument - wskazanie na bajt strumienia kodow T4
; trzeci argument - maska (wskazuje gdzie dokladnie zaczyna sie kod)
ReodCode:
  push ebp
  mov ebp, esp
  push ebx              ; prolog
  push esi
  push edi

  mov dl, 0             ; indeks w tablicy kodow
  mov dh, 1             ; aktualna dlugosc kodu
  xor eax, eax          ; zwracany wynik
  ;mov eax, 1
  mov esi, [ebp+16]     ; adres maski
  mov cl, [esi]         ; maska
  mov esi, [ebp+12]     ; adres bajtu z kodem
  mov esi, [esi]
  mov ch, [esi]         ; bajt z kodem

  mov bl, cl
  and bl, ch            ; pobieramy pierwszy bit kodu
  xor edi, edi          ; i zapisujemy go w edi
  cmp bl, 0
  je RC_check_mask
  mov edi, 1

RC_check_mask:
  shr cl, 1
  cmp cl, 0
  jne RC_main_loop      ; sprawdzamy czy musimy przesunac 
  mov cl, 128           ; wskaznik i zresetowac maske
  mov esi, [ebp+12]
  inc esi
  mov ch, [esi]
  mov [ebp+12], esi

RC_main_loop:
  shl edi, 1
  mov bl, cl
  and bl, ch            ; pobieramy kolejny bit kodu
  cmp bl, 0
  je RC_check_mask2
  inc edi

RC_check_mask2:
  shr cl, 1
  cmp cl, 0
  jne RC_check_length   ; sprawdzamy czy musimy przesunac 
  mov cl, 128           ; wskaznik i zresetowac maske
  mov esi, [ebp+12]
  inc esi
  mov ch, [esi]
  mov [ebp+12], esi

RC_check_length:
  inc dh
  cmp dh, 13            ; inkrementujemy dlugosc kodu
  jg RC_error           ; i sprawdzamy czy nie jest wieksza od 13
  ;cmp dh, 11;
  ;jg RC_end;

RC_read_loop2:
  mov esi, [ebp+8]
  xor ebx, ebx
  mov bl, dl
  lea esi, [esi+8*ebx]  
  cmp [esi], dh         ; zaden kod sie nie zgadza, 
  jg RC_main_loop       ; wczytujemy nastepny bit
  add esi, 2
  ;mov ebx, edi
  xor ebx, ebx
  mov bx, [esi]
  cmp ebx, edi
  ;cmp [esi], bx         ; sprawdzamy kod
  jne RC_read_loop
  add esi, 2
  add ax, [esi]         ; dodajemy dlugosc odp. znal. kodowi
  mov ebx, [esi]
  cmp ebx, 64
  jl RC_end             ; wczytalismy kod terminalny
  mov bl, cl
  and bl, ch
  cmp bl, 0             ; pobieramy pierwszy bit kodu
  xor edi, edi          ; i zapisujemy go w edi
  je RC_check_mask3
  mov edi, 1

RC_check_mask3:
  shr cl, 1
  cmp cl, 0
  jne RC_val_reset      ; sprawdzamy czy musimy przesunac 
  mov cl, 128           ; wskaznik i zresetowac maske
  mov esi, [ebp+12]
  inc esi
  mov ch, [esi]
  mov [ebp+12], esi

RC_val_reset:
  mov dh, 1             ; szukamy od poczatku
  mov dl, 0
  jmp RC_main_loop

RC_end:
  ;mov esi, [ebp+8]
  ;xor ebx, ebx
  ;mov bl, dl
  ;lea esi, [esi+8*ebx]  
  ;mov eax, [esi]
  ;mov eax, ebx
  mov esi, [ebp+16]
  mov [esi], cl         ; zapisujemy maske
  pop edi
  pop esi
  pop ebx               ; epilog
  mov esp, ebp  
  pop ebp
  ret

RC_error:
  mov ax, 0xFFFF
  pop edi
  pop esi               ; blad - zwracamy 0xFFFF
  pop ebx
  mov esp, ebp  
  pop ebp
  ret

RC_read_loop:
  inc dl
  jmp RC_read_loop2
