/** 
@file ListMap.h

Zawiera deklaracje klasy ListMap.
Jest to mapa (Slownik) zrobiona na liscie/pierscieniu.
Implementacja tej klasy jest przedmiotem cwiczenia na laboratoriach z AISDI.
      
@author
Pawel Cichocki, Michal Nowacki

@date  
last revision
- 2006.01.06 Michal Nowacki: wersja polska
- 2005.11.17 Michal Nowacki: prev pointer
- 2005.11.04 Pawel Cichocki: cosmetic code improvements
- 2005.11.04 Pawel Cichocki: a public method for obtaining the count from CCount
- 2005.11.03 Pawel Cichocki: const_iterator done properly now
- 2005.10.27 Pawel Cichocki: cosmetic changes
- 2005.10.27 Michal Nowacki: removed templates, and moved the implementation to another file
- 2005.10.25 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <assert.h>
#include <stdlib.h>
#include <iterator>

#include <string>

/// Prosty licznik do podstawowej kontroli wycieków pamiêci
class CCount
{
private:
  static int count;
  CCount() {count++;}
  ~CCount()
  {
     assert(count>0);
     //if(count>0) 
        count--;
     //else
     //   cerr<<"ERROR (CCount): More destructors than constructors called!"<<std::endl;
  }
  friend struct ListNode;
  //friend int Test2();
public:
   /// Publiczna metoda do pobierania wartoœci licznika.
   static int getCount() { return count; }
};

//////////////////////////////////////////////////////////////////////////////
// ListMap i zwi¹zane klasy
//////////////////////////////////////////////////////////////////////////////

/// Klasa opakowywuj¹ca dane 
struct ListNode : CCount
{
   typedef std::pair<int,std::string> T;
   ListNode* next;   ///< WskaŸnik na kolejny element na liœcie/pierœcieniu
   ListNode* prev;   ///< WskaŸnik na poprzedni element nal liœcie/pierœcieniu
   T data;           ///< Dane
   void* internalDataPointer;   ///< wskaŸnik pomocniczy
   ListNode(const std::pair<int,std::string>& d) : next(NULL), prev(NULL), data(d) {}
   ListNode(const std::pair<int,std::string>& d, ListNode* n, ListNode* p) : next(n), prev(p), data(d) {}
};

/// Map'a z metodami jak std::map.
/// Mapa powinna zostaæ zaimplementowana jako lista lub pierœcieñ
/// w wersji jedno- lub dwukierunkowej zgodnie z wytycznymi prowadz¹cych.
class ListMap
{
public:
   typedef int Key;
   typedef std::string Val;

protected:
   typedef ListNode/*<Key, Value>*/ Node;
   Node* first;

public:
   typedef size_t size_type;
   typedef std::pair<Key, Val> P;

   ListMap();
   ListMap( const ListMap& );
   ListMap & operator=(const ListMap &);
   ~ListMap();

   /// const_iterator.
   /// U¿yty równie¿ jako klasa bazowa dla  (not const) iterator.
   class const_iterator : public std::iterator<std::forward_iterator_tag,
                                               std::pair<Key, Val> >
   {
   public:
      typedef std::pair<Key, Val> T;

   protected:
      /// Points to the list element
      Node* node;
      friend class ListMap;

      const_iterator(Node* x) : node(x) {}
   public:
      const_iterator() {}
      const_iterator(const const_iterator& a) : node(a.node) {}

      inline const T& operator*() const
      {
         return node->data;
      }

      inline const T* operator->() const
      {
         return &(node->data);
      }

      // preincrementacja
      /*inline*/ const_iterator& operator++();
      // postincrementacja
      /*inline*/ const_iterator operator++(int);
      // predekrementacja
      /*inline*/ const_iterator& operator--();
      // postdekrementacja
      /*inline*/ const_iterator operator--(int);

      inline bool operator==(const const_iterator& a) const
      {
         return node == a.node;
      }

      inline bool operator!=(const const_iterator& a) const
      {
         return node != a.node;
      }
   };

   /// Iterator.
   class iterator : public const_iterator
   {
      iterator(Node* x) : const_iterator(x) {}
      friend class ListMap;

   public:
      iterator() {}
      iterator(const const_iterator& a) : const_iterator(a) {}
      iterator(const iterator& a) { node = a.node; }

      inline T& operator*() const
      {
         return node->data;
      }
      inline T* operator->() const
      {
         return &(node->data);
      }

      iterator& operator++()
      {  // preincrementacja
         ++(*(const_iterator*)this);
         return (*this);
      }

      iterator operator++(int)
      {  // postincrementacja
         iterator temp = *this;
         ++*this;
         return temp;
      }

      iterator& operator--()
      {  // predekrementacja
         --(*(const_iterator*)this);
         return (*this);
      }

      iterator operator--(int)
      {  // postdekrementacja
         iterator temp = *this;
         --*this;
         return temp;
      }
   };
   
   /// Zwraca iterator addresuj¹cy pierwszy element w mapie.
   iterator begin();
   const_iterator begin() const;

   /// Zwraca iterator addresuj¹cy element za ostatnim w mapie.   
   iterator end();
   const_iterator end() const;
   
   /// Wstawienie elementu do mapy.
   /// @returns Para, której komponent bool jest równy true gdy wstawienie zosta³o
   ///          dokonane, równy false gdy element identyfikowany przez klucz
   ///          ju¿ istnia³ w mapie. Iterator ustawiony jest na ten wstawiony 
   ///          lub istniej¹cy ju¿ w mapie element.
   std::pair<iterator, bool> insert(const std::pair<Key, Val>& entry);

   /// Wstawienie elementu do mapy.
   /// Matoda zak³ada, ¿e w mapie nie wystêpuje element identyfikowany przez key
   iterator unsafe_insert(const std::pair<Key, Val>& entry);

   /// Zwraca iterator addresuj¹cy element w mapie dla którego klucz jest równy 
   /// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
   iterator find(const Key& k);
   const_iterator find(const Key& k) const;
 
   /// Udostêpnia wartoœæ powi¹zan¹ z kluczem key. Wstawia element do mapy jeœli 
   /// nie istnia³.
   /// @returns Referencje do wartoœci powi¹zanej z kluczem.
   Val& operator[](const Key& k);   

   /// Sprawdzenie czy mapa jest pusta.
   bool empty( ) const;

   /// Zwraca iloœæ elementów w mapie.
   size_type size() const;

   /// Zwraza iloœæ elementów skojarzonych z kluczem key.
   size_type count(const Key& _Key) const;

   /// Usuwa element z mapy.
   /// @returns iterator adresuj¹cy pierwszy element za usuwanym.
   iterator erase(iterator i);
   
   /// Usuwa zakres elementów z mapy.
   /// Zakres jest zdefiniowany poprzez iteratory first i last
   /// first jest okreœla pierwszy element do usuniêcia, a last okreœla element 
   /// po ostatnim usuniêtym elemencie.
   /// @returns iterator adresuj¹cy pierwszy element za usuwanym.
   iterator erase(iterator first, iterator last);
   
   /// Usuwa element z mapy.
   /// @returns Iloœæ usuniêtych elementów.
   ///          (nie jest to multimapa, wiêæ mo¿e byæ to wartoœæ 1 lub 0 )
   size_type erase(const Key& key);

   /// Usuniêcie wszystkich elementów z mapy.
   void clear( );
   
   /// Porównanie strukturalne map.
   /// Czy reprezentacja danych jest identyczna.
   /// Zwraca true jeœli wewnêtrzne struktury map s¹ identyczne.
   bool struct_eq(const ListMap& another) const;
   /// Porównanie informacyjne map.
   /// Czy informacje trzymane w mapach s¹ identyczne.
   /// Zwraca true jeœli mapy zwieraj¹ takie same pary klucz-wartoœæ.
   bool info_eq(const ListMap& another) const;

   /// Zwraca true jeœli mapy zwieraj¹ takie same pary klucz-wartoœæ.
   inline bool operator==(const ListMap& a) const { return info_eq(a); }
};

