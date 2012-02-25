all:    main asm link clean

main:   main.c
	gcc -c -m32 -fpack-struct=1 main.c -o main.o

asm:    asm.s
	nasm -f elf asm.s -o asm.o

link:   main.o asm.o
	gcc -m32 -fpack-struct=1 -o t4 main.o asm.o
clean:
	rm ./asm.o
	rm ./main.o
	rm ./spim.bmp
