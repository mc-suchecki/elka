all:    main asm link

main:   main.c
	gcc -c -m32 main.c -o main.o

asm:    cnt.s
	nasm -f elf cnt.s -o cnt.o

link:   main.o cnt.o
	gcc -m32 -o cnt main.o cnt.o
