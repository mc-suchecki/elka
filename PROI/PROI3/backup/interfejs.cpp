//Nazwa pliku: interfejs.cpp
//Autor: Maciej Suchecki (grupa 2I4)

//Opis pliku: Plik zrodlowy zawierajacy implementacje metod wykorzystywanych
//w prostej implementacji graficznego interfejsu uzytkownika. Czesc skladowa
//projektu numer 3 wykonanego w ramach przedmiotu 'Programowanie Obiektowe'.

#include "interfejs.h"		//plik naglowkowy z deklaracjami uzywanych klas

//////////////////////////////////METODY WIDZETOW//////////////////////////////
////////////////////////////////////KLASA WIDGET///////////////////////////////

//metoda abstrakcyjnej klasy bazowej Widget realizujaca przesuwanie elementu
void Widget::Move(int new_pos_x, int new_pos_y)
{
  if(new_pos_x<0 || new_pos_y<0) return;//sprawdzenie poprawnosci parametrow
  pos_x = new_pos_x;			//zmiana pozycji elementu
  pos_y = new_pos_y;
}//void Widget::Move(unsigned int new_pos_x, unsigned int new_pos_y)

//przeciazony operator przypisania dla klasy Widget
Widget & Widget::operator=(const Widget & tmp)
{
  name = tmp.name;			//skopiowanie nazwy
  pos_x = tmp.pos_x;			//skopiowanie pozycji
  pos_y = tmp.pos_y;			//skopiowanie pozycji
  return *this;				//zwrocenie obiektu przypisania
}//Widget & Widget::operator=(const Widget & tmp)

//metoda klasy Widget wypisująca dane klasy
void Widget::Show() const
{
  cout << "Widzet: Nazwa-" << name;
  cout << ", Pozycja-(" << pos_x << "," << pos_y << ")" << endl;
}//void Widget::Show() const

//metoda klasy Label edytujaca tekst przez nia wyswietlany
void Label::EditText(string new_text)
{
  text = new_text;			//zapisanie nowego tekstu
}//void Label::EditText(string new_text)

////////////////////////////////////KLASA LABEL////////////////////////////////

//przeciazony operator przypisania dla klasy Label
Label & Label::operator=(const Label & tmp)
{
  name = tmp.name;			//skopiowanie nazwy
  pos_x = tmp.pos_x;			//skopiowanie pozycji
  pos_y = tmp.pos_y;			//skopiowanie pozycji
  text = tmp.text;			//skopiowanie tekstu
  return *this;				//zwrocenie obiektu przypisania
}//Label & Label::operator=(const Label & tmp)

//metoda klasy Label wypisująca dane klasy
void Label::Show() const
{
  cout << "Etykieta: Nazwa-" << name << ", Pozycja-(" << pos_x << "," << pos_y;
  cout << "), Tekst-" << text << endl;
}//void Label::Show(ostream & os) const

////////////////////////////////////KLASA BUTTON///////////////////////////////

//metoda klasy Button zmieniajaca rozmiary przycisku
void Button::Resize(int x, int y)
{
  if(x<0 || y<0) return;	//sprawdzenie poprawnosci parametrow
  size_x = x;			//zmiana danych o rozmiarze
  size_y = y;
}//void Button::Resize(unsigned int x, usigned int y)

//metoda klasy Button odczytujaca stan przycisku
bool Button::IsPressed()
{
  return pressed;		//zwrocenie stanu przycisku
}//bool Button::IsPressed()

//przeciazony operator przypisania dla klasy Button
Button & Button::operator=(const Button & tmp)
{
  name = tmp.name;			//skopiowanie nazwy
  pos_x = tmp.pos_x;			//skopiowanie pozycji
  pos_y = tmp.pos_y;			//skopiowanie pozycji
  size_x = tmp.size_x;			//skopiowanie rozmiaru
  size_y = tmp.size_y;			//skopiowanie rozmiaru
  text = tmp.text;			//skopiowanie tekstu
  pressed = tmp.pressed;		//skopiowanie stanu
  return *this;				//zwrocenie obiektu przypisania
}//Button & Button::operator=(const Button & tmp)

//metoda klasy Button wypisująca dane klasy
void Button::Show() const
{
  cout << "Przycisk: Nazwa-" << name << ", Pozycja-(" << pos_x << "," << pos_y;
  cout << "), Tekst-" << text << ", Stan-" << pressed << endl;
}//void Button::Show() const

///////////////////////////////////KLASA CHECKBOX//////////////////////////////

//przeciazony operator przypisania dla klasy CheckBox
CheckBox & CheckBox::operator=(const CheckBox & tmp)
{
  name = tmp.name;			//skopiowanie nazwy
  pos_x = tmp.pos_x;			//skopiowanie pozycji
  pos_y = tmp.pos_y;			//skopiowanie pozycji
  text = tmp.text;			//skopiowanie tekstu
  checked = tmp.checked;		//skopiowanie stanu
  return *this;				//zwrocenie obiektu przypisania
}//CheckBox & CheckBox::operator=(const CheckBox & tmp)

//metoda klasy CheckBox wypisująca dane klasy
void CheckBox::Show() const
{
  cout << "Przycisk wyboru: Nazwa-" << name << ", Pozycja-(" << pos_x << ",";
  cout << pos_y << "), Tekst-" << text << ", Stan-" << checked << endl;
}//CheckBox::Show() const

//////////////////////////////////KLASA PROGRESSBAR////////////////////////////

//metoda klasy ProgressBar zmieniajaca rozmiar paska
void ProgressBar::Resize(int x, int y)
{
  if(x<0 || y<0) return;	//sprawdzenie poprawnosci parametrow
  size_x = x;			//zmiana danych o rozmiarze
  size_y = y;
}//void ProgressBar::Resize(unsigned int x, usigned int y)

//metoda klasy ProgressBar aktualizujaca postep procesu
void ProgressBar::UpdateProgress(unsigned int p)
{
  progress = p;			//zmiana postepu procesu
}//void ProgressBar::UpdateProgress(unsigned int p)

//przeciazony operator przypisania dla klasy ProgressBar
ProgressBar & ProgressBar::operator=(const ProgressBar & tmp)
{
  name = tmp.name;			//skopiowanie nazwy
  pos_x = tmp.pos_x;			//skopiowanie pozycji
  pos_y = tmp.pos_y;			//skopiowanie pozycji
  size_x = tmp.size_x;			//skopiowanie rozmiaru
  size_y = tmp.size_y;			//skopiowanie rozmiaru
  progress = tmp.progress;		//skopiowanie stanu
  return *this;				//zwrocenie obiektu przypisania
}//ProgressBar & ProgressBar::operator=(const ProgressBar & tmp)

//metoda klasy ProgressBar wypisująca dane klasy
void ProgressBar::Show() const
{
  cout << "Pasek postepu: Nazwa-" << name << ", Pozycja-(" << pos_x << ",";
  cout << pos_y << "), Wymiary-(" << size_x << "," << size_y << "), Postep-";
  cout << progress << endl;
}//void ProgressBar::Show()

///////////////////////////////////KLASA TEXTBOX///////////////////////////////

//metoda klasy TextBox zmieniajaca rozmiar pola tekstowego
void TextBox::Resize(int x, int y)
{
  if(x<0 || y<0) return;	//sprawdzenie poprawnosci parametrow
  size_x = x;			//zmiana danych o rozmiarze
  size_y = y;
}//void TextBox::Resize(unsigned int x, usigned int y)

//metoda klasy Textbox zmieniajaca tekst w niej zawarty
void TextBox::EditText(string new_text)
{
  text = new_text;		//zmiana tekstu pola
}//void TextBox::EditText(string new_text)

//przeciazony operator przypisania dla klasy TextBox
TextBox & TextBox::operator=(const TextBox & tmp)
{
  name = tmp.name;			//skopiowanie nazwy
  pos_x = tmp.pos_x;			//skopiowanie pozycji
  pos_y = tmp.pos_y;			//skopiowanie pozycji
  size_x = tmp.size_x;			//skopiowanie rozmiaru
  size_y = tmp.size_y;			//skopiowanie rozmiaru
  text = tmp.text;			//skopiowanie stanu
  return *this;				//zwrocenie obiektu przypisania
}//TextBox & TextBox::operator=(const TextBox & tmp)

//metoda klasy TextBox wypisująca dane klasy
void TextBox::Show() const
{
  cout << "Pole tekstowe: Nazwa-" << name << ", Pozycja-(" << pos_x << ",";
  cout << pos_y << "), Wymiary-(" << size_x << "," << size_y << "), Tekst-";
  cout << text << endl;
}//void TextBox::Show()

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////METODY OKNA////////////////////////////////

//destruktor
Window::~Window()
{
  Widget *tmp;			//pomocniczy wskaznik
  Window *tmp2;			//pomocniczy wskaznik

  while(!widgets.empty())
  {
    tmp = widgets.back();	//skopiowanie wskaznika
    delete tmp;			//zwolnienie pamieci zajmowanej przez widzet
    widgets.pop_back();		//usuniecie wskaznika z pamieci
  }//while(!widgets.empty)

  while(!windows.empty())
  {
    tmp2 = windows.back();	//skopiowanie wskaznika
    delete tmp2;		//zwolnienie pamieci zajmowanej przez okno
    windows.pop_back();		//usuniecie wskaznika z pamieci
  }//while(!windows.empty)

}//Window::~Window()

//metoda klasy Window zmieniajaca nazwe okna
void Window::Rename(string new_name)
{
  name = new_name;		//zmiana nazwy okna
}//void Window::Rename(string new_name)

//metoda klasy Window zmieniajaca tytul okna
void Window::EditTitle(string new_title)
{
  title = new_title;		//zmiana tytulu okna
}//void Window::EditTitle(string new_title)

//metoda klasy Window zmieniajaca rozmiar okna
bool Window::Resize(int new_x, int new_y)
{
  if(new_x<0 || new_y<0) return false;	//sprawdzenie poprawnosci parametrow

  vector<Widget*>::const_iterator it = widgets.begin();		//iterator

  //petla obliczajaca wspolrzedne najbardziej wysunietego elementu okna
  for(; it != widgets.end(); ++it)
  {
    if( (*(*it)).MaxX() > new_x) return false;	//element wystawalby po
    if( (*(*it)).MaxY() > new_y) return false;	//zmianie rozmiaru okna
  }//for

  size_x = new_x;				//zmiana rozmiaru okna
  size_y = new_y;
  
  return true;					//poprawna zmiana

}//void Window::Resize(unsigned int x, unsigned int y)

//metoda klasy Window zmieniajaca polozenie okna
void Window::Move(int x, int y)
{
  if((int)pos_x < -x || (int)pos_y < -y) return;	//sprawdzenie danych

  pos_x += x;			//zmiana polozenia okna
  pos_y += y;
}//void Window::Move(unsigned int x, unsigned int y)

//metoda klasy Window wypisujaca dane o oknie
void Window::ShowInfo()
{
  cout << "Okno \"" << name << "\": Tytul-" << title << ", Pozycja-(" << pos_x;
  cout << "," << pos_y << "), Rozmiar-(" << size_x << "," << size_y << ")."<< endl;
}//void Window::ShowInfo()

//przeciazony operator << realizujacy wypisywanie danych o klasie
ostream & operator<<(ostream & os, const Window & tmp)
{
  os << "Okno \"" << tmp.name << "\": Tytul-" << tmp.title << ", Pozycja-(";
  os << tmp.pos_x << "," << tmp.pos_y << "), Rozmiar-(" << tmp.size_x << ",";
  os << tmp.size_y << ")." << endl << " Widzety:" << endl;

  vector<Widget*>::const_iterator it = tmp.widgets.begin();	//iterator
  vector<Window*>::const_iterator it2 = tmp.windows.begin();	//iterator

  //petla wypisujaca widzety okna
  for(int i=1; it != tmp.widgets.end(); ++it, ++i)
  {
    cout << "  " << i << ". ";		//wypisanie indeksu
    (*(*it)).Show();			//wypisanie widzetu
  }//for
  
  if(!tmp.windows.empty()) os << " Zawarte okna:" << endl;

  //petla wypisujaca zawarte okna
  for(int i=1; it2 != tmp.windows.end(); ++it2, ++i)
  {
    cout << "  " << i << ". ";		//wypisanie indeksu
    (*(*it2)).ShowInfo();		//wypisanie widzetu
  }//for

  return os;				//zwrocenie strumienia

}//ostream & operator<<(ostream & os, const Window & tmp)

//metoda klasy Window realizujaca usuwanie widzetow (number->(0...size))
void Window::DeleteWidget(int number)
{
  if(number<=0 || number>(int)widgets.size()) return;	//sprawdzenie indeksu
  Widget *tmp = widgets[(number-1)];			//skopiowanie wskaznika
  delete tmp;						//zwolnienie pamieci
  widgets.erase(widgets.begin()+(number-1));		//usuniecie elementu
}//void Window::DeleteWidget(int number)

//metoda klasy Window umozliwiajaca dodanie etykiety do okna
void Window::AddLabel(string n, string t, int px, int py)
{
  if(px<0 || py<0) return;			//sprawdzenie pozycji

  Label tmp(n, t, px, py);			//stworzenie widzetu
  Label *tmp2 = new Label;			//dynamiczna alokacja pamieci
  (*tmp2) = tmp;				//skopiowanie danych
  widgets.push_back(tmp2);			//dodanie widzetu do okna

}//void Window::AddLabel(string n, string t, int px, int py)

//metoda klasy Window umozliwiajaca dodanie przycisku do okna
void Window::AddButton(string n, string t, int px, int py, int sx, int sy)
{
  if(px<0 || py<0 || sx<0 || sy<0) return;	//sprawdzenie pozycji

  Button tmp(n, t, px, py, sx, sy);		//stworzenie widzetu
  Button *tmp2 = new Button;			//dynamiczna alokacja pamieci
  (*tmp2) = tmp;				//skopiowanie danych
  widgets.push_back(tmp2);			//dodanie widzetu do okna

}//void Window::AddButton(string n, string t, int px, int py, int sx, int sy)

//metoda klasy Window umozliwiajaca dodanie przycisku wyboru do okna
void Window::AddCheckBox(string n, string t, int px, int py, bool c)
{
  if(px<0 || py<0) return;			//sprawdzenie pozycji

  CheckBox tmp(n, t, px, py, c);		//stworzenie widzetu
  CheckBox *tmp2 = new CheckBox;		//dynamiczna alokacja pamieci
  (*tmp2) = tmp;				//skopiowanie danych
  widgets.push_back(tmp2);			//dodanie widzetu do okna

}//void Window::CheckBox(string n, string t, int px, int py, bool c)

//metoda klasy Window umozliwiajaca dodanie paska postepu do okna
void Window::AddProgressBar(string n, int px, int py, int sx, int sy, int p)
{
  if(px<0 || py<0 || sx<0 || sy<0 || p<0 || p>100) return;	//sprawdzenie

  ProgressBar tmp(n, px, py, sx, sy, p);	//stworzenie widzetu
  ProgressBar *tmp2 = new ProgressBar;		//dynamiczna alokacja pamieci
  (*tmp2) = tmp;				//skopiowanie danych
  widgets.push_back(tmp2);			//dodanie widzetu do okna

}//void Window::AddProgressBar(string n, int px, int py, int sx, int sy, int p)

//metoda klasy Window umozliwiajaca dodanie pola tekstowego do okna
void Window::AddTextBox(string n, string t, int px, int py, int sx, int sy)
{
  if(px<0 || py<0 || sx<0 || sy<0) return;	//sprawdzenie pozycji

  TextBox tmp(n, t, px, py, sx, sy);		//stworzenie widzetu
  TextBox *tmp2 = new TextBox;			//dynamiczna alokacja pamieci
  (*tmp2) = tmp;				//skopiowanie danych
  widgets.push_back(tmp2);			//dodanie widzetu do okna

}//void Window::AddTextBox(string n, int px, int py, string t, int sx, int sy)

//metoda klasy Window umozliwiajaca dodanie okna zawartego w klasie
void Window::AddWindow()
{
  Window tmp;					//stworzenie okna
  Window *tmp2 = new Window;			//alokacja pamieci
  (*tmp2) = tmp;				//skopiowanie wartosci
  windows.push_back(tmp2);			//dodanie do tablicy

}//void Window::AddWindow()

//metoda klasy Window realizujaca usuwanie okien zawartych w klasie
void Window::DeleteWindow(int number)
{
  if(number<=0 || number>(int)windows.size()) return;	//sprawdzenie indeksu
  Window *tmp = windows[(number-1)];			//skopiowanie wskaznika
  delete tmp;						//zwolnienie pamieci
  windows.erase(windows.begin()+(number-1));		//usuniecie elementu
}//void Window::DeleteWindow(int number)

//metoda klasy Window pozwalajaca uzyskac dostep do okna w niej zawartego
Window * Window::GetWindowPointer(int number)
{
  if(number<=0 || number>(int)windows.size()) return NULL;//sprawdzenie indeksu
  return windows[(number-1)];				//zwrocenie wskaznika
}//Window * GetWindowPointer(int number)
