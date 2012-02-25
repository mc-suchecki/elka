#include <stdio.h>			//biblioteka standardowa
#include <stdlib.h>			//funkcje malloc() i system()
#include <string.h>			//funkcja strcpy()
#include "liga.h"			//deklaracje zmiennych i funkcji

void PokazTerminarz()
{
  char wybor;				//zmienna sluzaca do wyboru opcji
  w_mecz tmp = mpoczatek;		//wskaznik na strukture pomocnicza
  int numer = 0, kolejka = 1;		//numer meczu na liscie, numer kolejki

  while(1)
  {
    system("clear");			//czyszczenie terminala

    printf("TERMINARZ SPOTKAN:\t     ");
    printf("(G)eneruj terminarz (E)dytuj mecz (W)yjdz do menu\n");
    printf("\t\t\t     (P)oprzednia kolejka (N)astepna kolejka\n\n");

    if(kolejka==1) tmp = mpoczatek;	//ustawiamy na poczatku listy meczy

    if(mpoczatek == NULL)		//jesli lista meczy jest pusta
      printf("Wygeneruj terminarz, aby moc edytowac wyniki meczy.");
    else {
      printf("\t\t\t      KOLEJKA %d\n", kolejka);

      while((*tmp).kolejka == kolejka)	//dopoki jestesmy w dobrej kolejce
      {
        numer++;			//wypisuj mecze i ich wyniki
        printf("\n%2d.%30s - %-30s %2d - %-2d\n", numer,
        tmp->druzyna1, tmp->druzyna2, tmp->bramki1, tmp->bramki2);

        if(tmp->nast != NULL) tmp=tmp->nast;	//nastepny mecz
        else break;				//wyjdz, jesli koniec listy
      }//while((*tmp).kolejka == kolejka)

      if(tmp->nast != NULL) tmp=tmp->pop;	//przeszlismy o jeden za duzo
      numer--;
      for(;numer>0;numer--) tmp = tmp->pop;	//na poczatek kolejki

    }//if(mpoczatek == NULL)

    wybor=getchar();			//wczytywanie wyboru uzytkownika
    while(getchar()!='\n') continue;	//czyszczenie wejscia

    switch(wybor)
    {
      case 'p':
        if(tmp->pop != NULL)	//jesli nie jestesmy w pierwszej kolejce
        {
          kolejka--;		//cofnij sie o jedna kolejke
          if(kolejka==1) tmp = mpoczatek;
          else while((*(tmp->pop)).kolejka>=kolejka) tmp = tmp->pop;
        }//if(tmp->pop != NULL)
        break;
      case 'n':
        if((*mkoniec).kolejka != kolejka)	//jezeli nie jestesmy w
        {					//ostatniej kolejce
          kolejka++;		//idz kolejke do przodu
          while((*tmp).kolejka<kolejka) tmp = tmp->nast;
        }//if((*mkoniec).kolejka!=kolejka)
        break;
      case 'g': GenerujTerminarz(); break;
      case 'e': EdytujMecz(tmp); break;
      case 'w': return;
    }//switch(wybor)

  }//while(1)

}//PokazTerminarz

void GenerujTerminarz()
{
  int i, ile_gralo, kolejka;		//ile_gralo (druzyn w danej kolejce)
  w_druzyna tmp1, tmp2, tmp3;		//wskazniki na struktury pomocnicze

  if(liczba_druzyn<2) return;		//wyjscie, jak jest 0 lub 1 druzyn

  if(mpoczatek == NULL)			//jezeli lista meczy jest pusta
  {
    tmp1 = poczatek;			//1 wskaznik na pierwszej druzynie
    tmp2 = koniec;			//2 wskaznik na ostatniej druzynie
    kolejka = 1;			//zaczynamy od pierwszej kolejki

    if(liczba_druzyn == 3)		//dla 3 druzyn algorytm nie dziala
    {
      DodajMecz(poczatek->nazwa, koniec->nazwa, 1, 0, 0);
      DodajMecz(poczatek->nazwa, poczatek->nast->nazwa, 2, 0, 0);
      DodajMecz(poczatek->nast->nazwa, koniec->nazwa, 3, 0, 0);
      poczatek->mecze = 0;
      poczatek->nast->mecze = 0;
      koniec->mecze = 0;
      stan = 3;
      return;
    }//if(liczba_druzyn==3)

    if(liczba_druzyn%2) (*tmp1).mecze=kolejka;

    for(i=1;i<(liczba_druzyn+liczba_druzyn%2);i++)
    {
      ile_gralo = 0;			//nowa kolejka - nikt jeszcze nie gral

      if(!(liczba_druzyn%2)) tmp2 = koniec;	//2 wskaznik na ostatniej druz.

      while(ile_gralo<liczba_druzyn-liczba_druzyn%2)	//dopoki zostala jedna
      {							//albo zero druzyn
        if((*tmp1).mecze<kolejka)
        {				//jesli tmp1 nie grala w tej kolejce
          (*tmp1).mecze=kolejka;	//zeby nie wziac dwoch tych samych
          if((*tmp2).mecze<kolejka)	//i tmp2 tez nie grala w tej kolejce
          {
            DodajMecz(tmp1->nazwa, tmp2->nazwa, kolejka, 0, 0);
            (*tmp2).mecze=kolejka;		//tmp2 'zagralo'
            ile_gralo=ile_gralo+2;		//znalezlismy jedna pare
            if(ile_gralo==2 && tmp1->pop!=NULL) tmp2=tmp1->pop;
          } else {
            (*tmp1).mecze--;			//'odblokowujemy' tmp1
            if(tmp2->pop==NULL) tmp2=koniec;	//zapetlenie przejscia            
            else tmp2=tmp2->pop;		//przejdz do poprzedniej
          }//if((*tmp2).mecze<kolejka)
        } else {
          if(tmp1->nast==NULL) tmp1=poczatek;	//zapetlenie przejscia
          else tmp1=tmp1->nast;			//przejdz do nastepnej
        }//if((*tmp).mecze<kolejka)
      }//while(ile_gralo<liczba_druzyn-liczba_druzyn%2)

      kolejka++;				//nastepna kolejka

      if(liczba_druzyn%2)		//jezeli mamy nieparzysta liczbe druzyn
      {
        (*tmp2).mecze=kolejka;		//tmp2 nie gra w nastepnej kolejce
        tmp3=tmp1;
        tmp1=tmp2;			//zamieniamy tmp1 i tmp2 miejscami
        tmp2=tmp3;
      }
      else tmp1=tmp2;			//jesli parzysta, tylko jedna zamiana

    }//for(i=1;i<(liczba_druzyn+liczba_druzyn%2);i++)

  for(tmp1 = poczatek; tmp1 != NULL; tmp1 = tmp1->nast)
  {
    tmp1->mecze = 0;			//zerowanie liczby rozegranych meczy
  }//for

  stan = 3;				//wprowadzono zmiany
	
  }//if(mpoczatek == NULL)

}//GenerujTerminarz

void DodajMecz(char *druzyna1, char *druzyna2, int kolejka, int b1, int b2)
{
  w_mecz tmp;				//wskaznik na strukture pomocnicza

  if((tmp = (w_mecz)malloc(sizeof(mecz))) != NULL)	//jesli jest pamiec
  {
    tmp->pop = mkoniec;				//podpiecie konca listy do tmp
    if(mkoniec != NULL) mkoniec->nast=tmp;	//podpiecie tmp do konca listy
    tmp->nast = NULL;				//po tmp nie ma nic
    mkoniec = tmp;				//tmp jest na koncu
    if(mpoczatek == NULL) mpoczatek = tmp;	//i na pocz. jak lista pusta

    strcpy(tmp->druzyna1, druzyna1);		//wpisanie nazw druzyn
    strcpy(tmp->druzyna2, druzyna2);		//rozgrywajacych mecz

    (*tmp).kolejka = kolejka;			//wpisanie numeru kolejki
    (*tmp).bramki1 = b1;
    (*tmp).bramki2 = b2;			//wpisanie liczby bramek

  }//if((tmp = (w_mecz)malloc(sizeof(mecz))) != NULL)

}//DodajMecz
	
void EdytujMecz(w_mecz tmp)
{
  int indeks, bramki1, bramki2;		//numer na liscie meczu do edycji

  printf("Podaj numer meczu do edycji: ");

  if(scanf("%d", &indeks) != 0)		//jesli poprawnie pobrano indeks
  {
    while(getchar()!='\n') continue;	//czyszczenie wejscia
    
    if(indeks<1 || indeks>((liczba_druzyn-liczba_druzyn%2)/2))
    {
      printf("Nie ma meczu o takim numerze! Nacisnij ENTER aby kontynuowac.");
    } else {

      for(;indeks>1;indeks--)
        tmp = tmp->nast;		//dojdz do meczu o podanym numerze

      printf("Podaj wynik meczu (np. 3-0): ");

      if(scanf("%d-%d", &bramki1, &bramki2) != 0 && bramki1>=0 && bramki2>=0)
      {
        tmp->bramki1 = bramki1;			//wpisanie liczby bramek
        tmp->bramki2 = bramki2;
        stan = 3;				//wprowadzono zmiany
        while(getchar()!='\n') continue;	//czyszczenie wejscia
        printf("Zmiany zostaly dokonane! Nacisnij ENTER, aby kontynuowac.");
      } else {
        while(getchar()!='\n') continue;	//czyszczenie wejscia
        printf("Nieprawidlowe dane! Nacisnij ENTER aby kontynowac.");
      }//if(scanf("%d-%d", (*tmp).bramki1, (*tmp).bramki2) != 0)

    }//if(indeks<1 || indeks>((liczba_druzyn-liczba_druzyn%2)/2))

  } else {
    while(getchar()!='\n') continue;	//czyszczenie wejscia
    printf("Nieprawidlowe dane! Nacisnij ENTER aby kontynowac.");
  }//if(scanf("%d", &indeks) != 0)

  while(getchar()!='\n') continue;	//czyszczenie wejscia

}//EdytujMecz
