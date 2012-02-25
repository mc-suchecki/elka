#include <stdio.h>

extern unsigned cnt(unsigned v, unsigned stoff, unsigned enoff);

int main() {
  int liczba = 0x55555555, i = 0;

  printf("liczba = %d ", cnt(liczba, 0 , 31));

  printf("(binarnie: ");
  for(i = 0; i < 32; i++)
    printf("%d", cnt(liczba, i, i));

  printf(")\n");

  printf("Zmieniam stoff:\n");
  for(i = 0; i < 32; i++)
    printf("%d ", cnt(liczba, i, 31));

  printf("\nZmieniam stend:\n");
  for(i = 0; i < 32; i++)
    printf("%d ", cnt(liczba, 0, i));
  
  printf("\n");

  return 0;
}
