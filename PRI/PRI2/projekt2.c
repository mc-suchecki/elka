#include <stdio.h>			//biblioteka standardowa
#include <stdlib.h>			//funkcja malloc

int WczytajMacierz(void);		//funkcja pobierajaca elementy macierzy
double ObliczWyznacznik(double**, int);	//funkcja obliczajaca wyznacznik macierzy

double **macierz;			//wyznacznik tablicy zawierajacej macierz
int wymiar;				//wymiar macierzy kwadratowej

int main()
{
int i;					//alokowanie pamieci na macierz
char znak=0;				//wyjscie z programu lub kontynuacja

macierz = (double**)malloc(4 * sizeof(double*));
for(i=0; i<4; i++){macierz[i] = (double*)malloc(4 * sizeof(double));} 

printf("Program obliczajacy wyznaczniki macierzy kwadratowych.\n");
printf("Wpisz elementy macierzy oddzielone spacjami, po kazdym wierszu wpisz srednik:\n");

while (znak!='n') {			//licz wyznaczniki az do wpisania 'n'
  printf("\nA = ");			//'znak zachety'

  if (WczytajMacierz()==1) {		//jesli wczytano poprawnie, podaj wynik
    printf("Wyznacznik macierzy = %f", ObliczWyznacznik(macierz, wymiar));
  } else {
    while(getchar()!='\n') continue;	//usuwanie niepotrzebnych znakow z wejscia
  }  

  do {
    printf("\nCzy chcesz obliczyc wyznacznik innej macierzy? (t/n) ");
    znak = getchar();			//wczytanie odpowiedzi
    while(getchar()!='\n') continue;	//usuwanie niepotrzebnych znakow z wejscia
  } while (znak!='t' && znak !='n'); 	//ponawianie pytania gdy odpowiedz niepoprawna
}

return 0;
}//main

int WczytajMacierz(void)
{
int w=0, k=0;				//indeksy wierszy i kolumn
char znak;				//wczytywanie znakow oddzielajacych
int spr=0;				//sprawdzanie, czy macierz kwadratowa

while (1)				//petla wczytujaca elementy macierzy
{
  scanf("%lf", &macierz[w][k]);		//wczytanie elementu macierzy
  znak = getchar();			//wczytanie znaku
  k++;					//zwiekszenie indeksu kolumn

  if (znak==';') {
    w++;				//zwiekszenie indeksu wierszy
    if (k!=spr && spr!=0) {		//sprawdzanie wymiarow
      printf("\nNieprawidlowe wymiary macierzy! Macierz musi byc kwadratowa!\n");
      return 0;
    }
    else if (w==k && w!=0 && k!=0)	//jesli ilosc wierszy = ilosc kolumn
      break;				//to zakoncz wczytywanie
    else {
      spr=k;				//zapisanie ilosci kolumn w pop. wierszu
      k=0;				//zerowanie indeksu kolumn (nowy wiersz)
    }
  } else if (znak!=' ') {		//jesli sa inne znaki niz ' ' i ';'
  printf("\nNieprawidlowy format danych!");
  return 0;
  }
}

if (w<=4) {wymiar=w; return 1;}	//sprawdzanie rozmiaru macierzy
else {printf("\nMaksymalny wymiar macierzy wynosi 4!\n"); return 0;}

if (getchar()!='\n') {			//czy nic nie zostalo na wejsciu?
  printf("\nNadmiarowe wiersze zostaly zignorowane.\n"); 
  while(getchar()!='\n') continue;	//czyszczenie wejscia
}


}//WczytajMacierz


double ObliczWyznacznik(double **tab,int n)
{
int a,b,c,d;				//indeksy kolumn i wierszy
double wynik = 0;			//zmienna przechowujaca wynik
double **tmp = NULL;			//macierz dla nastepnej funkcji

if (n == 1) wynik = tab[0][0];		//wyznaczniki najprostszych przypadkow
else if (n == 2) wynik = tab[0][0] * tab[1][1] - tab[1][0] * tab[0][1];
else {
  wynik = 0;
  for (c=0;c<n;c++) {			//tworzenie macierzy dla nast. funkcji
    tmp = malloc((n-1)*sizeof(double *));
    for (a=0;a<n-1;a++) tmp[a] = malloc((n-1)*sizeof(double));
    for (a=1;a<n;a++) {
      d = 0;

      for (b=0;b<n;b++) {
        if (b == c) continue;
        tmp[a-1][d] = tab[a][b];	//wypelnianie macierzy odpowiednimi
        d++;				//elementami z wlasciwej macierzy
      }

    }

    if (c%2==0) wynik += tab[0][c] * ObliczWyznacznik(tmp,n-1);
    else wynik -= tab[0][c] * ObliczWyznacznik(tmp,n-1);

    for (a=0;a<n-1;a++) free(tmp[a]);	//usuwanie macierzy wysylanej do
    free(tmp);				//nastepnego wywolania funkcji
  }
}

return(wynik);				//zwracanie wyznacznika

}//ObliczWyznacznik
