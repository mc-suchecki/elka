//Nazwa pliku: gui.cpp
//Autor: Maciej Suchecki (grupa 2I4)

//Opis pliku: Plik zrodlowy programu stanowiacego prosty system zarzadzania
//interfejsem uzytownika z poziomu konsoli oraz plikow. Czesc skladowa
//projektu nr 3 wykonanego w ramach przedmiotu 'Programowanie Obiektowe'.

#include "interfejs.h"		//plik naglowkowy z deklaracjami klas
#include <cstdlib>		//plik naglowkowy z definicja funkcji system

vector<Window*> okna;		//tablica przechowujaca wskazniki na okna

void DodajOkno();		//dodawanie okna do interfejsu
void UsunOkno();		//usuwanie okna z interfejsu
void WybierzOknoDoEdycji();	//wybor okna do edycji
void WybierzOkno(Window *);	//wybor okna do edyzji (zawierajace sie okna)
void EdytujOkno(Window *);	//edycja danych okna
void ZmienNazwe(Window *);	//zmiana nazwy okna
void ZmienTytul(Window *);	//zmiana tytulu okna
void ZmienRozmiar(Window *);	//zmiana rozmiaru okna
void PrzesunOkno(Window *);	//przesuwanie okna
void DodajWidzet(Window *);	//funkcja dodajaca widzet do okna
void UsunWidzet(Window *);	//funkcja usuwajaca widzet z okna
void PrzesunOkna();		//przesuwanie grup okien
void SkalujOkna();		//zmiana rozmiaru grupy okien
void UsunOknoWOknie(Window *);	//usuwanie okna zawartego w innym
void ZwolnijPamiec();		//zwalnia pamiec przed wyjsciem z programu

int main()
{
  char wybor;			//znak wpisany przez uzytkownika

  while(1)
  {
    system("clear");

    cout << "Program do obslugi interfejsu graficznego. Lista okien:" << endl;

    vector<Window*>::const_iterator it = okna.begin();	//iterator do tablicy

    //petla wypisujaca okna
    for(int i=1; it != okna.end(); ++it, ++i)
    {
      cout << " " << i << ". ";			//wypisanie indeksu
      (*(*it)).ShowInfo();			//wypisanie danych okna
    }//for

    cout << endl << "Wybierz funkcje: (d)odaj okno, (u)sun okno, ";
    cout << "(e)dytuj okno, (p)rzesun okna" << endl << "Zmien (r)ozmiar okien,";
    cout << " (w)czytaj okna z pliku, (z)apisz okna do pliku, (k)oniec" << endl;

    cin.get(wybor);			//pobranie wpisanego znaku
    cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

    switch(wybor)
    {
      case 'd': DodajOkno(); break;		//dodawanie okna
      case 'u': UsunOkno(); break;		//usuwanie okna
      case 'e': WybierzOknoDoEdycji(); break;	//edycja okna
      case 'p': if(!okna.empty()) PrzesunOkna(); break;	//przesuwanie okien
      case 'r': if(!okna.empty()) SkalujOkna(); break;	//skalowanie okien
      case 'w': break;
      case 'z': break;
      case 'k': ZwolnijPamiec(); return 0;	//zakonczenie programu
    }//switch(wybor)

  }//while(1)

}//main()

//funkcja dodajaca okno do interfejsu
void DodajOkno()
{
  string nazwa;					//zmienna pomocnicza

  Window *okno = new Window;			//alokacja pamieci
  okna.push_back(okno);				//dodanie okna do tablicy

  cout << "Podaj nazwe okna: ";
  getline(cin, nazwa);				//edycja nazwy okna
  (*okno).Rename(nazwa);

  cout << "Podaj tytul okna: ";
  getline(cin, nazwa);				//edycja tytulu okna
  (*okno).EditTitle(nazwa);

}//void DodajOkno()

//funkcja usuwajaca okno z interfejsu
void UsunOkno()
{
  Window *okno = NULL;				//wskaznik na okno
  int numer;					//numer okna do usuniecia

  cout << "Podaj numer okna do usuniecia: ";
  cin >> numer;					//wczytanie numeru okna
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  if(numer<=0 || numer>(int)okna.size())	//sprawdzenie numeru
  {
    cout << "Niewlasciwy numer, nie usunieto zadnego okna. Nacisnij ENTER.";
    while(cin.get()!='\n') continue;	//zignorowanie nastepnych znakow
    return;					//powrot do menu
  }//if

  okno = okna[(numer-1)];			//skopowanie wskaznika
  delete okno;					//zwolnienie pamieci

  okna.erase(okna.begin()+(numer-1));		//usuniecie wskaznika z tablicy

  cout << "Usunieto okno o numerze " << numer << ". Nacisnij ENTER.";
  while(cin.get()!='\n') continue;	//zignorowanie nastepnych znakow

}//void UsunOkno()

//funkcja sluzaca do wybierania okna do edycji
void WybierzOknoDoEdycji()
{
  int numer;					//numer okna do edycji

  cout << "Podaj numer okna do edycji: ";
  cin >> numer;
  cin.ignore(1000, '\n');			//ignorowanie nastepnych znakow

  if(numer<=0 || numer>(int)okna.size())	//sprawdzenie numeru
  {
    cout << "Nie ma okna o takim numerze! Nacisnij ENTER.";
    while(cin.get()!='\n') continue;		//ignorowanie nastepnych znakow
    return;					//powrot do menu
  }//if
      
  EdytujOkno(okna[(numer-1)]);			//wywolanie funkcji edytujacej

}//void WybierzOknoDoEdycji()

//funkcja sluzaca do wybierania okna do edycji (wersja dla zawierajacych sie okien)
void WybierzOkno(Window *okno)
{
  int numer;					//numer okna do edycji

  cout << "Podaj numer okna do edycji: ";
  cin >> numer;
  cin.ignore(1000, '\n');			//ignorowanie nastepnych znakow

  Window *tmp = (*okno).GetWindowPointer(numer);

  if(tmp == NULL)				//sprawdzenie numeru
  {
    cout << "Nie ma okna o takim numerze! Nacisnij ENTER.";
    while(cin.get()!='\n') continue;		//ignorowanie nastepnych znakow
    return;					//powrot do menu
  }//if
      
  EdytujOkno(tmp);				//wywolanie funkcji edytujacej

}//void WybierzOknoDoEdycji()

//funkcja edytujaca dane konkretnego okna
void EdytujOkno(Window *okno)
{
  char wybor;			//znak wpisany przez uzytkownika

  while(1)
  {
    system("clear");

    cout << (*okno) << endl;	//wypisanie danych okna

    cout << endl << "Wybierz funkcje: Zmien (n)azwe/(t)ytul/(r)ozmiar okna, ";
    cout << "(w)roc poziom wyzej," << endl << "(p)rzesun okno, (d)odaj widzet";
    cout << ", (u)sun widzet, D(o)daj/U(s)un/Ed(y)tuj okno."  << endl;

    cin.get(wybor);			//pobranie wpisanego znaku
    cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

    switch(wybor)
    {
      case 'n': ZmienNazwe(okno); break;	//zmiana nazwy okna
      case 't': ZmienTytul(okno); break;	//zmiana tytulu okna
      case 'r': ZmienRozmiar(okno); break;	//zmiana rozmiaru okna
      case 'p': PrzesunOkno(okno); break;	//przesuwanie okna
      case 'd': DodajWidzet(okno); break;	//dodawanie widzetow
      case 'u': UsunWidzet(okno); break;	//usuwanie widzetow
      case 'o': (*okno).AddWindow(); break;	//dodawanie okien
      case 's': UsunOknoWOknie(okno); break;	//usuwanie okien
      case 'y': WybierzOkno(okno); break;	//edycja okna
      case 'w': return;				//powrot do menu
    }//switch(wybor)

  }//while(1)

}//EdytujOkno(Window *okno)

//funkcja zmieniajaca nazwe okna
void ZmienNazwe(Window *okno)
{
  string nazwa;					//nowa nazwa okna

  cout << "Podaj nowa nazwe okna: ";
  getline(cin, nazwa);				//edycja nazwy okna

  (*okno).Rename(nazwa);			//zmiana nazwy

}//void ZmienNazwe(int numer)

//funkcja zmieniajaca tytul okna
void ZmienTytul(Window *okno)
{
  string tytul;					//nowy tytul okna

  cout << "Podaj nowy tytul okna: ";
  getline(cin, tytul);				//edycja tytulu okna

  (*okno).EditTitle(tytul);			//zmiana tytulu

}//void ZmienTytul(int numer)

//funkcja zmieniajaca rozmiar okna
void ZmienRozmiar(Window *okno)
{
  int x, y;					//nowe wymiary okna

  cout << "Podaj nowa szerokosc okna: ";
  cin >> x;					//wczytanie szerokosci
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  cout << "Podaj nowa wysokosc okna: ";
  cin >> y;					//wczytanie wysokosci
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  (*okno).Resize(x, y);			//zmiana rozmiaru

}//void ZmienRozmiar(int numer)

//funkcja zmieniajaca polozenie okna
void PrzesunOkno(Window *okno)
{
  int x, y;					//nowe wymiary okna

  cout << "Podaj pozioma wspolrzedna przesuniecia (- przesuwaja w lewo): ";
  cin >> x;
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  cout << "Podaj pionowa wspolrzedna przesuniecia (- przesuwaja do gory): ";
  cin >> y;
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  (*okno).Move(x, y);			//przesuniecie okna

}//void PrzesunOkno(int numer)

//funkcja dodajaca widzet do okna
void DodajWidzet(Window *okno)
{
  int numer_typu, x, y, a, b;		//typ wybranego elementu, pozycja
  string nazwa, tekst;			//nazwa i tekst dodawanego widzetu

  cout << "Wybierz typ widzetu: 1-Etykieta, 2-Przycisk, 3-Przycisk wyboru, ";
  cout << endl << "4-Pasek postepu, 5-Pole tekstowe: ";

  cin >> numer_typu;				//pobranie wyboru uzytkownika
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  if(numer_typu<1 && numer_typu>5) return;	//sprawdzenie wyboru

  cout << "Podaj nazwe widzetu: ";
  getline(cin, nazwa); 

  cout << "Podaj wspolrzedna x polozenia widzetu: ";
  cin >> x;
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  cout << "Podaj wspolrzedna y polozenia widzetu: ";
  cin >> y;
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow
  
  switch(numer_typu)
  {
    case 1:
      cout << "Podaj tekst etykiety: ";			//pobranie danych
      getline(cin, tekst);
      (*okno).AddLabel(nazwa, tekst, x, y);
      break;
    case 2:
      cout << "Podaj tekst przycisku: ";		//pobranie danych
      getline(cin, tekst);
      cout << "Podaj szerokosc przycisku: ";
      cin >> a;
      cin.ignore(1000, '\n');			//ignorowanie nastepnych znakow
      cout << "Podaj wysokosc przycisku: ";
      cin >> b;
      cin.ignore(1000, '\n');			//ignorowanie nastepnych znakow
      (*okno).AddButton(nazwa, tekst, x, y, a, b);	      
      break;
    case 3:
      cout << "Podaj tekst przycisku wyboru: ";		//pobranie danych
      getline(cin, tekst);
      (*okno).AddCheckBox(nazwa, tekst, x, y, 0);
      break;
    case 4:
      cout << "Podaj szerokosc paska postepu: ";
      cin >> a;
      cin.ignore(1000, '\n');			//ignorowanie nastepnych znakow
      cout << "Podaj wysokosc paska postepu: ";
      cin >> b;
      cin.ignore(1000, '\n');			//ignorowanie nastepnych znakow
      (*okno).AddProgressBar(nazwa, x, y, a, b, 0);	      
      break;
    case 5:
      cout << "Podaj tekst pola tekstowego: ";		//pobranie danych
      getline(cin, tekst);
      cout << "Podaj szerokosc pola: ";
      cin >> a;
      cin.ignore(1000, '\n');			//ignorowanie nastepnych znakow
      cout << "Podaj wysokosc pola ";
      cin >> b;
      cin.ignore(1000, '\n');			//ignorowanie nastepnych znakow
      (*okno).AddTextBox(nazwa, tekst, x, y, a, b);	      
      break;
  }//switch(numer_typu)

}//void DodajWidzet(int numer)
	
//funkcja usuwajaca widzet z okna
void UsunWidzet(Window *okno)
{		
  int numer_widzetu;				//numer widzetu do usuniecia

  cout << "Podaj numer widzetu do usuniecia: ";
  cin >> numer_widzetu;				//wczytanie numeru widzetu
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  (*okno).DeleteWidget(numer_widzetu);	//usuniecie widzetu

}//void UsunWidzet(int numer)

//funkcja przesuwajaca grupe okien
void PrzesunOkna()
{
  int numer, x, y;			//numery okien i zadane przesuniecie

  cout << "Podaj pozioma wspolrzedna przesuniecia (- przesuwaja w lewo): ";
  cin >> x;
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  cout << "Podaj pionowa wspolrzedna przesuniecia (- przesuwaja do gory): ";
  cin >> y;
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  cout << "Podaj numery okien do przesuniecia oddzielone spacja: ";

  while(cin >> numer)
  {
    if(numer<=0 || numer>(int)okna.size()) continue;	//sprawdzenie numeru

    (*(okna[(numer-1)])).Move(x, y);			//przesuniecie okna

    if(cin.get()=='\n') break;		//jesli koniec linii zakonczenie petli

  }//while(cin >> numer)

}//void PrzesunOkna()

//funkcja zmieniajaca rozmiar grupy okien
void SkalujOkna()
{
  int numer, x, y;			//numery okien i zadane wymiary

  cout << "Podaj zadana szerokosc okien: ";
  cin >> x;
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  cout << "Podaj zadana wysokosc okien: ";
  cin >> y;
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  cout << "Podaj numery okien do zmiany rozmiaru oddzielone spacja: ";

  while(cin >> numer)
  {
    if(numer<=0 || numer>(int)okna.size()) continue;	//sprawdzenie numeru

    (*(okna[(numer-1)])).Resize(x, y);			//przesuniecie okna

    if(cin.get()=='\n') break;		//jesli koniec linii zakonczenie petli

  }//while(cin >> numer)

}//void SkalujOkna()

//funkcja zwalniajaca pamiec przed wyjsciem z programu
void ZwolnijPamiec()
{
  vector<Window*>::const_iterator it = okna.begin();	//iterator do tablicy

  //petla zwalniajca pamiec
  for(; it != okna.end(); ++it)
  {
    delete (*it);					//zwolnienie pamieci
  }//for

}//void ZwolnijPamiec()

//usuwanie okna zawartego w innym
void UsunOknoWOknie(Window *okno)
{
  int numer_okna;				//numer okna do usuniecia

  cout << "Podaj numer okna do usuniecia: ";
  cin >> numer_okna;				//wczytanie numeru okna
  cin.ignore(1000, '\n');		//ignorowanie nastepnych znakow

  (*okno).DeleteWindow(numer_okna);	//usuniecie okna

}//void UsunOknoWOknie(int number)

