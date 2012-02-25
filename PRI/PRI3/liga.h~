#ifndef liga_h
#define liga_h

//definicja listy wskaznikowej z danymi druzyn
typedef struct d {
  char nazwa[31];
  int mecze, punkty;
  int strzelone, stracone;
  int zwyciestwa, remisy, porazki;
  struct d *nast, *pop;
} druzyna;
typedef druzyna *w_druzyna;
extern w_druzyna poczatek;
extern w_druzyna koniec;

//definicja listy wskaznikowej z meczami
typedef struct m {
  char druzyna1[31];
  char druzyna2[31];
  int bramki1;
  int bramki2;
  int kolejka;
  struct m *nast, *pop;
} mecz;
typedef mecz *w_mecz;
extern w_mecz mpoczatek;
extern w_mecz mkoniec;

//wskaznik na plik zawierajacy dane ligi
extern FILE *plik;

//zmienna przechowujaca stan ligi
//0 - nie ma zadnej ligi, 1 - nowa liga
//2 - liga wczytana z pliku (nie edytowana)
//3 - zostaly wprowadzone zmiany
extern int stan;

//zmienna przechowujaca liczbe druzyn
extern int liczba_druzyn;

//deklaracje funkcji w pliki.c
void NowaLiga(void);			//funkcja tworzaca nowa lige
void OtworzLige(void);			//funkcja otwierajaca lige z pliku
void ZapiszLige(void);			//funkcja zapisujaca lige do pliku

//deklaracje funkcji w lista.c
void PokazListe(void);			//funkcja wyswietlajaca liste druzyn
void DodajDruzyne(void);		//funkcja dodajaca nowa druzyne do listy
void UsunDruzyne(void);			//funkcja usuwajaca druzyne z listy

//deklaracje funkcji w terminarz.c
void PokazTerminarz(void);		//funkcja wyswietlajaca terminarz
void GenerujTerminarz(void);		//funkcja generujaca terminarz spotkan
void DodajMecz(char*, char*, int, int, int);
//funkcja tworzaca nowy mecz (pobiera nazwy grajacych druzyn i kolejke)
void EdytujMecz(w_mecz);
//funkcja edytujaca mecz (pobiera wskaznik pierwszego meczu w kolejce)

//deklaracje funkcji w tabela.c
void PokazTabele(void);			//funkcja wyswietlajaca tabele druzyn
void RozegrajMecz(w_mecz);		//funkcja edytujaca druzyny na podst.
					//wynikow meczu podanego do niej
void CofnijMecz(w_mecz);		//funkcja cofajaca zmiany dokonane
					//przez funkcje RozegrajMecz()
int PorownajDruzyny(w_druzyna *, w_druzyna *);//funkcja zwraca 1, 
					//gdy druzyny sa wpisane w dobrej
					//kolejnosci, -1 jesli nie

#endif
