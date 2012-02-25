/** 
@file asd.cc

Plik do modyfikacji w ramach cwiczenia z AISDI.
Zawiera niekompletne implementacje metod klasy ListMap,
oraz mape podobna koncepcyjnie do tej z cwicznia 1 (SmallMap)
zaimplementowana w jescze bardziej szczatkowy sposob.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY LISTMAP.
    
@author
Pawel Cichocki, Michal Nowacki

@date  
last revision
- 2006.01.06 Michal Nowacki: wersja polska
- 2005.11.17 Michal Nowacki: constructor
- 2005.11.04 Pawel Cichocki: copied comments from the header
- 2005.11.03 Pawel Cichocki: const_iterator done properly now
- 2005.10.27 Pawel Cichocki: cosmetic changes
- 2005.10.26 Michal Nowacki: removed some method bodies
- 2005.10.25 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <assert.h>
#include <algorithm>

#include <iostream>

#ifdef _SUNOS
#include "/home/common/dyd/aisdi/liniowe/ListMap.h" 
#else
#include "./ListMap.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

ListMap::ListMap()
{
  std::pair<int, std::string> para(0, "\0");
  first = new ListNode(para);           //alokacja pamieci na straznika
  first->next = first;
  first->prev = first;                  //ustawienie wskaznikow w strazniku
  first->internalDataPointer = first;
}

ListMap::ListMap(const ListMap &m)
{
  std::pair<int, std::string> para(0, "\0");
  first = new ListNode(para);           //alokacja pamieci na straznika
  first->internalDataPointer = first;

  ListNode *tmp = m.first->next;        //wskaznik do przeszukiwania pierscienia
  ListNode *tmp2 = first, *n;           //wskaznik do przeszukiwania pierscienia

  for(; tmp != m.first; tmp = tmp->next)
  {
    n = new ListNode(tmp->data, NULL, tmp2);    //nowy element pierscienia
    n->internalDataPointer = NULL;
    tmp2->next = n;                             //ustawienie wskaznika pop. el.
    tmp2 = tmp2->next;                          //zapisanie wskaznika ost. el.
  }//for

  tmp2->next = first;           //polaczenie ostatniego el. ze straznikiem
  first->prev = tmp2;
}

ListMap::~ListMap()
{
  clear();                              //usuniecie wszystkich elementow
  delete first;                         //usuniecie straznika
}

// Wstawienie elementu do mapy.
// @returns Para, której komponent bool jest równy true gdy wstawienie zosta³o
//          dokonane, równy false gdy element identyfikowany przez klucz
//          ju¿ istnia³ w mapie. Iterator ustawiony jest na ten wstawiony 
//          lub istniej¹cy ju¿ w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  for(; tmp != first; tmp = tmp->next)
  {
    if(tmp->data.first==entry.first)
    {
      iterator i = tmp;                        //iterator, ktory zwrocimy
      return std::make_pair(i, (bool)false);
    }
    if(tmp->data.first>entry.first) break;     //znalezlismy miejsce do wstawienia elementu
  }//for
  
  ListNode *n = new ListNode(entry, tmp, tmp->prev);        //dodajemy element
  n->internalDataPointer = NULL;
  tmp->prev->next = n;
  tmp->prev = n;                                            //ustawiamy wskazniki
  iterator i = n;                                           //iterator, ktory zwrocimy
  return std::make_pair(i, (bool)true);                     //zwracamy iterator na dod. el.
}

// Wstawienie elementu do mapy.
// Matoda zak³ada, ¿e w mapie nie wystêpuje element identyfikowany przez key
ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  //idziemy po pierscieniu do straznika albo do wartosci o kluczu wiekszym od entry
  for(; tmp != first && tmp->data.first<entry.first; tmp = tmp->next) {}
  
  ListNode *n = new ListNode(entry, tmp, tmp->prev);        //dodajemy element
  n->internalDataPointer = NULL;
  tmp->prev->next = n;
  tmp->prev = n;                                            //ustawiamy wskazniki
  iterator i = tmp;
  return i;                                                 //zwracamy iterator
}

// Zwraca iterator addresuj¹cy element w mapie dla którego klucz jest równy 
// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
  iterator i;

  //idziemy po pierscieniu do straznika albo do wartosci o kluczu rownym k
  for(i=begin() ; i!=end() && i->first!=k ; ++i) {}

  return i;
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
  const_iterator i;

  //idziemy po pierscieniu do straznika albo do wartosci o kluczu rownym k
  for(i=begin() ; i!=end() && i->first!=k ; ++i) {}

  return (const_iterator)i;
}

// Udostêpnia wartoæ powi¹zan¹ z kluczem key. Wstawia element do mapy jeli 
// nie istnia³.
// @returns Referencje do wartoci powi¹zanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  for(; tmp != first; tmp = tmp->next)
  {
    if(tmp->data.first == k)           //znalezlismy element o podanym kluczu
    {
      ListMap::Val &ref = tmp->data.second;
      return ref;                      //zwracamy referencje
    }
    if(tmp->data.first > k) break;     //elementu o podanym kluczu nie ma
  }//for
  
  std::pair<int, std::string> dane(k, "\0");   //dane dla nowego elementu
  ListNode *n = new ListNode(dane, tmp, tmp->prev);         //dodajemy element
  n->internalDataPointer = NULL;
  tmp->prev->next = n;
  tmp->prev = n;                                            //ustawiamy wskazniki
  ListMap::Val &ref = n->data.second;
  return ref;                          //zwracamy referencje do wartosci w ListNode
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty() const
{
  return first==first->next;           //straznik wskazuje na siebie
}

// Zwraca iloæ elementów w mapie.
ListMap::size_type ListMap::size() const
{
  unsigned long sum = 0;
  for(ListNode *tmp = first->next; tmp != first; tmp = tmp->next)
    sum++;                             //dodanie aktualnego elementu
  return sum;                          //zwrocenie wyniku
}

// Zwraza iloæ elementów skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
  const_iterator i;

  //idziemy po pierscieniu do straznika albo do wartosci o kluczu rownym k
  for(i=begin(); i!=end(); ++i)
    if(i->first == _Key) return 1;

  return 0;                            //nie znaleziono takiego klucza
}

// Usuwa element z mapy.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  for(; tmp != first; tmp = tmp->next)
  {
    if(tmp == i.node)                  //znalezlismy element
    {
      ++i;                             //zwiekszamy iterator do zwrocenia
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;     //ustawienie wskaznikow
      delete tmp;                      //zwolnienie pamieci
      return i;                        //zwracamy iterator na nastepny element
    }
    if(tmp->data.first > i->first) break;       //nie ma takiego elementu
  }//for

  return end();                        //nic nie usunieto
}

// Usuwa zakres elementów z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest okrela pierwszy element do usuniêcia, a last okrela element 
// po ostatnim usuniêtym elemencie.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
  //sprawdzamy czy pierwszy iterator nie wskazuje na straznika
  if(f.node == first) return iterator(NULL);

  //sprawdzamy czy iteratory sa w dobrej kolejnosci i wskazuja na rozne elem.
  if(l.node != first && f->first >= l->first) return iterator(NULL); 

  ListNode *tmp = first->next;    //wskaznik do przeszukiwania pierscienia

  //szukamy pierwszego elementu do usuniecia
  for(; tmp != f.node; tmp = tmp->next)
  {
    if(tmp == first) return iterator(NULL);            //przeszlismy cala liste
    if(tmp->data.first > f->first) return iterator(NULL);  //nie ma takiego el.
  }//for

  ListNode *tmp2;                 //wskaznikiem tmp2 poszukamy elementu l

  //jesli l wskazuje na straznika to usuwamy do konca mapy
  if(l.node == first) tmp2 = first;
  else {
    //szukamy elementu na ktory wskazuje iterator l
    for(tmp2 = tmp->next; ; tmp2 = tmp2->next)
    {
      if(tmp2 == first) return iterator(NULL);          //l nie ma w mapie
      if(tmp2 == l.node) break;                         //znalezlismy l
    }//for

  }//if

  tmp = tmp->prev;                //tmp wskazuje element przed pierwszym do us.

  //usuwamy elementy pomiedzy tmp i tmp2
  for(ListNode *tmp3 = tmp->next->next; tmp3 != tmp2->next; tmp3 = tmp3->next)
    delete tmp3->prev;

  tmp->next = tmp2;                                  //ustawienie wskaznikow
  tmp2->prev = tmp;

  return l;                                          //zwrocenie iteratora
}

// Usuwa element z mapy.
// @returns Iloæ usuniêtych elementów.
//          (nie jest to multimapa, wiêæ mo¿e byæ to wartoæ 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
  ListNode *tmp = first->next;         //wskaznik do przeszukiwania pierscienia

  for(; tmp != first; tmp = tmp->next)
  {
    if(tmp->data.first == key)         //znalezlismy element o podanym kluczu
    {
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;     //ustawienie wskaznikow
      delete tmp;                      //zwolnienie pamieci
      return 1;                        //usunelismy jeden obiekt
    }//if
    if(tmp->data.first > key) break;   //elementu o podanym kluczu nie ma
  }//for

  return 0;                            //nic nie usunieto

}

// Usuniêcie wszystkich elementów z mapy.
void ListMap::clear()
{
  ListNode *tmp = first->next;

  while(tmp != first) 
  {
    tmp = tmp->next;                   //nastepny element
    delete tmp->prev;                  //usunecie poprzedniego
  }//while

  first->next = first;                 //ustawienie wskaznikow
  first->prev = first;
}

// Porównanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true jeli wewnêtrzne struktury map s¹ identyczne.:
bool ListMap::struct_eq(const ListMap& another) const
{
  ListNode *tmp = first;                //wskaznik przeszukujacy pierwsza mape
  ListNode *tmp2 = another.first;       //wskaznik przeszukujacy druga mape

  //dwie puste mapy
  if(tmp->next == tmp && tmp2->next == tmp2) return true;

  //jedna pusta mapa
  if(tmp->next == tmp || tmp2->next == tmp2) return false;

  while(1)                              //petla sprawdzajaca
  {
    tmp = tmp->next;                    //przejscie do kolejnych elementow
    tmp2 = tmp2->next;

    //sprawdzamy, czy klucze aktualnych elementow sa sobie rowne
    if(tmp->data.first != tmp2->data.first) return false;
    
    //elementy sie zgadzaja, wiec jesli obie mapy sie koncza, to sa takie same
    if(tmp->next == first && tmp2->next == another.first) return true;

    //jesli tylko jedna mapa sie konczy to mapy sa rozne
    if(tmp->next == first || tmp2->next == first) return false;
  }//while(1)
}

// Porównanie informacyjne map.
// Czy informacje trzymane w mapach s¹ identyczne.
// Zwraca true jeli mapy zwieraj¹ takie same pary klucz-wartoæ.
bool ListMap::info_eq(const ListMap& another) const
{
  ListNode *tmp = first;                //wskaznik przeszukujacy pierwsza mape
  ListNode *tmp2 = another.first;       //wskaznik przeszukujacy druga mape

  //dwie puste mapy
  if(tmp->next == tmp && tmp2->next == tmp2) return true;

  //jedna pusta mapa
  if(tmp->next == tmp || tmp2->next == tmp2) return false;

  while(1)                              //petla sprawdzajaca
  {
    tmp = tmp->next;                    //przejscie do kolejnych elementow
    tmp2 = tmp2->next;

    //rozne zawartosci elementow
    if(tmp->data != tmp2->data) return false;
    
    //elementy sie zgadzaja, wiec jesli obie mapy sie koncza, to sa takie same
    if(tmp->next == first && tmp2->next == another.first) return true;

    //jesli tylko jedna mapa sie konczy to mapy sa rozne
    if(tmp->next == first || tmp2->next == first) return false;
  }//while(1)
}

// preincrementacja
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
   if(node->internalDataPointer == NULL) node = node->next;
   return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
   if(node->internalDataPointer != NULL) return *this;
   const_iterator tmp = *this;
   node = node->next;
   return tmp;
}

ListMap::const_iterator& ListMap::const_iterator::operator--()
{
   if(node->internalDataPointer == NULL) node = node->prev;
   node = node->prev;
   return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
   if(node->internalDataPointer != NULL) return *this;
   const_iterator tmp = *this;
   node = node->prev;
   return tmp;
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{ 
   return iterator(first->next); 
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{ 
   return const_iterator(first->next); 
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.   
ListMap::iterator ListMap::end()
{ 
   return iterator(first); 
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.   
ListMap::const_iterator ListMap::end() const
{ 
   return const_iterator(first); 
}

//////////////////////////////////////////////////////////////////////////////
// SmallMap
//////////////////////////////////////////////////////////////////////////////

/// Przyk³ad map'y z implementacj¹ podobn¹ do std::map.
/// To jest jedynie przyk³ad!!!
/// Normalnie implementacja powinna opieraæ siê o drzewo lub tablicê haszuj¹c¹.
template <class Key, class Val>
class SmallMap
{
   std::pair<Key, Val> tab[2];
   int isOcupied[2];
public:

   SmallMap()
   {
      for(unsigned i=0; i<2; ++i)
      {
         isOcupied[i]=0;
      }
   }

   typedef std::pair<Key, Val>* iterator;   ///< Ka¿dy wskanik jest te¿ iteratorem.

   iterator begin() { return tab; }
   iterator end() { return tab+2; }

   Val& operator[](const Key& k)
   {
      static Val val;
      for(unsigned i=0; i<2; ++i)
      {
         if(isOcupied[i]&&tab[i].first==k)
            return tab[i].second;
      }
      // create
      for(unsigned i=0; i<2; ++i)
      {
         if(!isOcupied[i])
         {
            tab[i].first=k;
            isOcupied[i]=1;
            return tab[i].second;
         }
      }
//std::cout<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
std::cerr<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
      //assert(0);
      return val;   // Ma³o sensowne, ale to jest tylko przyk³¹d
   }
};
      

//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

//Funkcja pomocnicza do wypisania elementów.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>

/// Testy u¿ytkownika
void test()
{
   // A typedef used by the test.
   //typedef std::map<int, std::string> TEST_MAP;
   //typedef SmallMap<int, std::string> TEST_MAP;
   typedef ListMap TEST_MAP;

   std::cout << "Testy uzytkownika" << std::endl;

        TEST_MAP m;  
   std::cout << "m.empty()? " << m.empty() << std::endl;
   
   m[2] = "Merry";
   std::cout << "m.size()? " << m.size() << std::endl;
   m[4] = "Jane";
   std::cout << "m.size()? " << m.size() << std::endl;
   m[8] = "Korwin";
   std::cout << "m.size()? " << m.size() << std::endl;
   m[4] = "Magdalena";
   std::cout << "m.size()? " << m.size() << std::endl;

   TEST_MAP n = m;

   std::cout << "n==m? " << n.info_eq(m) << std::endl;
   std::cout << "n.empty()? " << n.empty() << std::endl;
   std::cout << "m.empty()? " << m.empty() << std::endl;
   for_each(m.begin(), m.end(), print );
   for_each(n.begin(), n.end(), print );
   //system("PAUSE");
}

//////////////////////////////////////////////////////////////////////////////
// main - jest w pliku /home/common/dyd/aisdi/z2/main.cc
//////////////////////////////////////////////////////////////////////////////

//int main()
//{
//   std::cout << "AISDI cwiczenie 2: wchodze do funkcji main." << std::endl;
//   test();
//   // Biblioteka z bardziej rygorystyczna wersja tych testow bedzie udostepniona na nastepnych zajeciach.
//   Test2();
//   //system("PAUSE");
//   return EXIT_SUCCESS;
//}
