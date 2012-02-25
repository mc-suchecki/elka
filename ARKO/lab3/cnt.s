        section .text
        global cnt

cnt:
  push ebp
  mov ebp, esp

  mov edi, [ebp+8]
  mov ecx, [ebp+12]
  mov esi, [ebp+16]

  ; ustalamy zmienna liczaca wystapienia jedynek
  xor eax, eax

  ; obliczamy roznice offsetow (ilosc bitow do zbadania)
  sub esi, ecx

  ; przesuwamy bufor o stoff
  shl edi, cl

policz:
  cmp esi, 0
  jl koniec
  sal edi, 1
  adc eax, 0
  dec esi
  jmp policz

koniec:
  mov ebp, esp  
  pop ebp
  ret
