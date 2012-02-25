//Nazwa pliku: interfejs.h
//Autor: Maciej Suchecki (grupa 2I4)

//Opis pliku: Plik naglowkowy z deklaracjami klas wykorzystywanych w prostej
//implementacji graficznego interfejsu uzytkownika. Czesc skladowa projektu
//numer 3 wykonanego w ramach przedmiotu 'Programowanie Obiektowe'.

#ifndef INTERFEJS_H
#define INTERFEJS_H

#include <iostream>		//potrzebne do przeciazenia operatora <<
#include <string>		//klasa string (nazwy i tekst w widzetach)
#include <vector>		//szablon klasy vector z biblioteki STL

using namespace std;			//standardowa przestrzen nazw

//abstrakcyjna klasa Widget stanowiaca baze dla widzetow klasy Window
class Widget
{
  protected:
    string name;			//nazwa widzetu
    unsigned int pos_x, pos_y;		//pozycja widzetu w oknie
  public:
    Widget(string n="NoName", unsigned int x=0, unsigned int y=0)
	    : name(n), pos_x(x), pos_y(y) {}		//konstruktor
    virtual ~Widget() {}				//destruktor
    void Move(int, int);				//zmiana pozycji
    void Rename(string str) {name = str;}		//zmiana nazwy
    virtual int MaxX() = 0;				//zwraca maks. x
    virtual int MaxY() = 0;				//zwraca maks. y
    virtual Widget & operator=(const Widget &);		//operator przyp.
    virtual void Show() const;				//wypisywanie
    virtual void Write(ostream &) const;		//wypisywanie do pliku
};

//klasa Label symbolizujaca etykiete
class Label : public Widget
{
  protected:
    string text;			//tekst widoczny na etykiecie
  public:
    Label(string n="NoName", string t="Text", unsigned x=0, unsigned y=0)
      : Widget(n, x, y) {text = t;}			//konstruktor
    virtual ~Label() {}					//destruktor
    void EditText(string);				//edytowanie tekstu
    virtual void Show() const;				//wypisywanie
    virtual void Write(ostream &) const;		//wypisywanie do pliku
    virtual int MaxX() {return pos_x;}			//zwraca maks. x
    virtual int MaxY() {return pos_y;}			//zwraca maks. y
    virtual Label & operator=(const Label &);		//operator przyp.
};

//klasa Button symbolizujaca przycisk
class Button : public Label
{
  private:
    bool pressed;			//przechowuje stan przycisku
    unsigned int size_x, size_y;	//przechowuje wymiary przycisku
  public:
    Button(string n="NoName", string t="Button", unsigned x=0, unsigned y=0,
	  unsigned sx=1, unsigned sy=1) : Label(n, t, x, y)
      {size_x = sx; size_y = sy; pressed = false;}	//konstruktor
    virtual ~Button() {}				//destruktor
    void Resize(int, int);				//zmiana rozmiaru
    bool IsPressed();					//odczytanie stanu
    virtual void Show() const;				//wypisywanie
    virtual void Write(ostream &) const;		//wypisywanie do pliku
    virtual int MaxX() {return pos_x+size_x;}		//zwraca maks. x
    virtual int MaxY() {return pos_y+size_y;}		//zwraca maks. y
    virtual Button & operator=(const Button &);		//operator przyp.
};

//klasa CheckBox symbolizujaca przycisk wyboru
class CheckBox : public Label
{
  private:
    bool checked;			//przechowuje stan przycisku
  public:
    CheckBox(string n="NoName", string t="CheckBox", unsigned x=0,
	    unsigned y=0, bool c="false") : Label(n, t, x, y)
	      {checked = c;}				//konstruktor
    virtual ~CheckBox() {}				//destruktor
    virtual void Show() const;				//wypisywanie
    virtual void Write(ostream &) const;		//wypisywanie do pliku
    void SetState(bool c) {checked = c;}	//zaznaczanie/odznaczanie
    virtual int MaxX() {return pos_x;}			//zwraca maks. x
    virtual int MaxY() {return pos_y;}			//zwraca maks. y
    virtual CheckBox & operator=(const CheckBox &);	//operator przyp.
    friend ostream & operator<<(ostream &, const CheckBox &);//cout
};

//klasa ProgressBar symbolizujaca pasek postepu
class ProgressBar : public Widget
{
  private:
    unsigned int progress;		//postep procesu w procentach
    unsigned int size_x, size_y;	//przechowuje wymiary paska
  public:
    ProgressBar(string n="NoName", unsigned x=0, unsigned y=0, unsigned sx=1,
	       unsigned sy=1, unsigned p=0) : Widget(n, x, y)//konstruktor
		 {size_x = sx; size_y = sy; progress = p;}
    virtual ~ProgressBar() {}				//destruktor
    void Resize(int, int);				//zmiana rozmiaru
    virtual void Show() const;				//wypisywanie
    virtual void Write(ostream &) const;		//wypisywanie do pliku
    virtual int MaxX() {return pos_x+size_x;}		//zwraca maks. x
    virtual int MaxY() {return pos_y+size_y;}		//zwraca maks. y
    void UpdateProgress(unsigned int);			//zmiana postepu
    virtual ProgressBar & operator=(const ProgressBar&);//operator przyp.
};

//klasa TextBox symbolizujaca pole tekstowe
class TextBox : public Widget
{
  private:
    string text;			//zawartosc pola tekstowego
    unsigned int size_x, size_y;	//przechowuje wymiary pola tekstowego
  public:
    TextBox(string n="NoName", string t="Text", unsigned x=0, unsigned y=0,
           unsigned sx=1, unsigned sy=1) : Widget(n, x, y)
             {size_x = sx; size_y = sy; text = t;}	//konstruktor
    virtual ~TextBox() {}				//destruktor
    void Resize(int, int);				//zmiana rozmiaru
    void EditText(string);				//edytowanie tekstu
    virtual int MaxX() {return pos_x+size_x;}		//zwraca maks. x
    virtual int MaxY() {return pos_y+size_y;}		//zwraca maks. y
    virtual void Show() const;				//wypisywanie
    virtual void Write(ostream &) const;		//wypisywanie do pliku
    virtual TextBox & operator=(const TextBox &);	//operator przyp.
};

//klasa Window symbolizujaca okno mogace zawierac ww. widzety
class Window
{
  private:
    string name, title;			//przechowuja nazwe i tytul
    unsigned int size_x, size_y;	//przechowuja rozmiary okna
    unsigned int pos_x, pos_y;		//przechowuja pozycje okna
    vector<Widget*> widgets;		//tablica zawierajaca elementy okna
    vector<Window*> windows;		//tablica z oknami zawartymi w klasie
  public:
    Window(string n="Window", string t="Title", unsigned sx=100,//konstruktor
          unsigned sy=100, unsigned px=0, unsigned py=0) : name(n),
	    title(t), size_x(sx), size_y(sy), pos_x(px), pos_y(py) {}
    ~Window();						//destruktor
    void Rename(string);				//zmiana nazwy okna
    void EditTitle(string);				//zmiana tytulu
    bool Resize(int, int);				//zmiana rozmiaru
    void Move(int, int);				//przesuniecie okna
    void ShowInfo();					//wyswietlenie danych
    void DeleteWidget(int);				//usuwanie elementu
    void AddLabel(string, string, int, int);		//dodanie etykiety
    void AddButton(string, string, int, int, int, int);	//dodanie przycisku
    void AddCheckBox(string, string, int, int, bool);	//dodanie przycisku w.
    void AddProgressBar(string, int, int, int, int, int);//dodanie paska post.
    void AddTextBox(string, string, int, int, int, int);//dodanie pola tekst.
    void AddWindow();					//dodanie okna
    void DeleteWindow(int);				//usuniecie okna
    Window * GetWindowPointer(int);			//zwraca wskaznik
    friend ostream & operator<<(ostream &, const Window &);//cout
    void Write(ostream &);				//zapis do pliku
};

#endif
