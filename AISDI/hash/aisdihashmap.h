#include <utility>
#include <iterator>

#define HASH_SIZE 65537			//wielkosc tablicy mieszajacej

//funkcja porownujaca klucze - zwraca 0 jesli klucze sa rowne
template <class Key>
inline int _compFunc(const Key& key1, const Key& key2) {
  return key1 != key2;
};

//funkcja mieszajaca
template <class K>
unsigned int hashF(const K& k) {
  const char *klucz = k.c_str();
  unsigned int hash = 5381;
  int znak;

  while (znak = *klucz++)
    hash = ((hash << 5) + hash) + znak;

  return hash % HASH_SIZE;
};

//mapa z podobnym interfejsem do std::map
template<class K, class V, unsigned hashFunc(const K&),
         int compFunc(const K&,const K&)=&_compFunc<K> >
class AISDIHashMap
{
  private:
    //klasa reprezentujaca element listy jednokierunkowej
    struct Node
    {
      std::pair<K, V> data;               //wartosc i klucz
      Node *next;                         //wskaznik na nastepny element
      Node *prev;                         //wskaznik na poprzedni element
      unsigned hash;                      //hash elementu

      Node() {};                          //konstruktor domyslny
      Node(const struct Node &n) :        //konstruktor kopiujacy
           data(n.data), next(n.next), prev(n.prev) {};

      Node(const std::pair<K, V> d, Node *n = NULL, Node *p = NULL) : 
           data(d), next(n), prev(p) {};
    };

    Node *hash_table[HASH_SIZE];          //tablica mieszajaca
    Node *guard;                          //wskaznik na straznika
    unsigned int map_size;                //ilosc elementow w mapie
  
  public:
    typedef std::pair<K, V> T;	

    //konstruktor domyslny
    AISDIHashMap() : map_size(0) {
      guard = new Node(std::make_pair(K(), V()));
      guard->next = guard->prev = guard;	//ustawiamy straznika
      guard->hash = 0;

      Node **wsk = hash_table;
      for(int i=0; i<HASH_SIZE; ++i)            //zerujemy tablice mieszajaca
        *(wsk++)= NULL;
    }

    //konstruktor kopiujacy
    explicit AISDIHashMap(const AISDIHashMap<K, V, hashFunc, compFunc>& a) {
      guard = new Node(std::make_pair(K(), V()));
      guard->hash = 0;				//ustawiamy straznika

      map_size = a.map_size;			//kopiujemy ilosc elementow

      Node **wsk = hash_table;
      for(int i=0; i<HASH_SIZE; ++i)            //zerujemy tablice mieszajaca
        *(wsk++)= NULL;

      Node *tmp = guard;			//wskazniki przechodzace mapy
      Node *tmp2 = a.guard->next;
      unsigned int prev_hash = tmp2->hash;	//hash poprzedniego elementu

      //kopiujemy elementy
      for(; tmp2 != a.guard; tmp = tmp->next, tmp2 = tmp2->next) {
        tmp->nast = new Node(tmp2->data, NULL, tmp);
	tmp->nast->hash = tmp2->hash;

	//sprawdzamy czy nie musimy wstawic elementu do tablicy
        if(prev_hash != tmp->nast->hash) {
	  prev_hash = tmp->nast->hash;
	  hash_table[prev_hash] = tmp->nast;
	}
      }

      tmp->nast = guard;		//laczymy koniec mapy ze straznikiem
      guard->prev = tmp;

    }

    //destruktor
    ~AISDIHashMap() {
      Node *tmp = guard->next;                  //pomocniczy wskaznik

      while(tmp != guard) {
        tmp = tmp->next;                        //usuwamy elementy
        delete(tmp->prev);
      }

      delete(guard);                            //usuwamy straznika
    }
  
    class const_iterator : public std::iterator<std::forward_iterator_tag,
                                                 std::pair<K, V> >
    {
      protected:
        Node* node;                             //wskaznik na element
        Node* guard;                            //wskaznik na straznika
        friend class AISDIHashMap;

      public:
        const_iterator() {}
        const_iterator(Node *n, Node *g) : node(n), guard(g) {}
        const_iterator(const const_iterator &n) : 
	               node(n.node), guard(n.guard) {}

        inline const T* operator*() const
        {
          return node->data;
        }
      
        inline const T* operator->() const
        {
          return &(node->data);
        }

        inline const_iterator& operator++() {
          if(node != guard) node = node->next;
          return *this;
        }

        inline const_iterator operator++(int) {
          if(node == guard) return *this;
          const_iterator tmp = *this;
          node = node->next;
          return tmp;
        }

        inline const_iterator& operator--() {
          if(node->prev != guard) node = node->prev;
          return *this;
        }

        inline const_iterator operator--(int) {
          if(node->prev == guard) return *this;
          const_iterator tmp = *this;
          node = node->prev;
          return tmp;
        }
    
        inline bool operator==(const const_iterator &another) const
        {
          return (node == another.node);
        }
      
        inline bool operator!=(const const_iterator &another) const
        {
          return (node != another.node);
        }
    };
     
    class iterator: public const_iterator
    {
      private:
        friend class AISDIHashMap;

      public:
        iterator() {}
        iterator(Node *x, Node *g) : const_iterator(x, g) {}
        iterator(const iterator &a) {
          this->node = a.node;
          this->guard = a.guard;
        }

        inline T& operator*() const
        {
          return this->node->data;
        }
       
        inline T* operator->() const
        {
          return &(this->node->data);
        }
            
        inline iterator& operator++()
        {
          ++(*(const_iterator*)this);
          return (*this);
        }
            
        inline iterator operator++(int)
        {
          iterator tmp = *this;
          ++*this;
          return tmp;
        }
       
        inline iterator& operator--()
        {
          --(*(const_iterator*)this);
          return (*this);
        }
            
        inline iterator operator--(int)
        {
          iterator tmp = *this;
          --*this;
          return tmp;
        }
    };

    //funkcje zwracajace iterator na pierwszy element w mapie
    inline iterator begin() {
      return iterator(guard->next, guard);
    }
   
    inline const_iterator begin() const {
      return const_iterator(guard->next, guard);
    }

    //funkcje zwracajace iterator element za ostatnim w mapie
    inline iterator end() {
      return iterator(guard, guard);
    }
    
    inline const_iterator end() const {
      return const_iterator(guard, guard);
    }
    
    //wstawia element do mapy
    std::pair<iterator, bool> insert(const std::pair<K, V>& entry)
    {
      unsigned hash = hashFunc(entry.first);       //hash wst. elementu
      Node *tmp = hash_table[hash];                //pomocniczy wskaznik
      
      if(tmp != NULL) {                            //mamy element o takim hashu
        while(tmp->hash == hash && tmp != guard) {
          if(!compFunc(tmp->data.first, entry.first))
	    return std::make_pair(iterator(tmp, guard), false);
  	  tmp = tmp->next;
        }
        Node *n = new Node(entry, tmp, tmp->prev);
        tmp->prev->next = n;
        tmp->prev = n;
        n->hash = hash;
        map_size++;
        return std::make_pair(iterator(n, guard), true);
      }

      //tablica mieszajaca pusta - wstawiamy pierwszy element o takim hashu
      Node *n = new Node(entry, guard,guard->prev);
      guard->prev->next = n;
      guard->prev = n;
      n->hash = hash;
      hash_table[hash] = n;
      map_size++;
      return std::make_pair(iterator(n, guard), true);
    }

    //szuka elementu o podanym kluczu w mapie, zwraca iterator
    iterator find(const K& k) {
      unsigned hash = hashFunc(k);                 //hash szuk. elementu

      //sprawdzamy miejsce w tablicy mieszajacej
      if(hash_table[hash] == NULL) return end();

      Node *tmp = hash_table[hash];                //pomocniczy wskaznik

      do {
        if(!compFunc(tmp->data.first, k))
          return iterator(tmp, guard);             //znalezlismy element
        tmp = tmp->next;
      } while(tmp->hash == hash && tmp != guard);

      return end();                                //nie ma takiego el.
    }

    const_iterator find(const K& k) const {
      unsigned hash = hashFunc(k);                 //hash szuk. elementu

      //sprawdzamy miejsce w tablicy mieszajacej
      if(hash_table[hash] == NULL) return end();

      Node *tmp = hash_table[hash];                //pomocniczy wskaznik

      do {
        if(!compFunc(tmp->data.first, k))
          return iterator(tmp, guard);             //znalezlismy element
        tmp = tmp->next;
      } while(tmp->hash == hash && tmp != guard);

      return end();                                //nie ma takiego el.
    }
     
    //operator indeksowania
    V& operator[](const K& k)
    {
      iterator i = (insert(std::make_pair(K(k), V()))).first;
      return i->second;
    }

    //sprawdza, czy mapa jest pusta
    bool empty() const {
      return guard == guard->next;
    }
  
    //zwraca ilosc elementow w mapie
    unsigned size() const {
      return map_size;
    }
  
    //zwraca ilosc elementow w mapie o podaym kluczu
    unsigned count(const K& _Key) const {
      unsigned hash = hashFunc(_Key);              //hash szuk. elementu

      //sprawdzamy miejsce w tablicy mieszajacej
      if(hash_table[hash] == NULL) return 0;

      Node *tmp = hash_table[hash];                //pomocniczy wskaznik

      do {
        if(!compFunc(tmp->data.first, _Key))
          return 1;                                //znalezlismy element
        tmp = tmp->next;
      } while(tmp->hash == hash && tmp != guard);

      return 0;                                    //nie ma takiego el.
    }

    //usuwa element z mapy
    iterator erase(iterator i) {
      //sprawdzamy czy i nie wskazuje na straznika i czy jest z tej mapy
      if(i.node == guard || i.guard != guard) return i;

      Node *tmp = i.node;
      unsigned int hash = tmp->hash;

      //sprawdzamy czy nie trzeba zmodyfikowac tablicy mieszajacej
      if(tmp == hash_table[hash]) {
        if(tmp->next->hash != hash || tmp->next == guard) {
          hash_table[hash] = NULL;
        } else {
          hash_table[hash] = tmp->next;
        }
      }

      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      i = iterator(tmp->next, guard);
      delete tmp;
      map_size--;
      return i;
    }

    //usuwa zakres elementow z mapy
    iterator erase(iterator first, iterator last) {
      //sprawdzamy czy pierwszy iterator nie wskazuje na straznika
      if(first == end()) return end();

      //sprawdzamy czy iteratory sa w dobrej kolejnosci
      Node *tmp = last.node;
      for(; tmp != guard; tmp = tmp->next)
  	if(tmp == first.node) return end(); 
        
      //kasujemy elementy
      while(first != last) erase(first++);

      return last;
    }
    
    //usuwa element z mapy
    unsigned erase(const K& key) {
      unsigned hash = hashFunc(key);               //hash szuk. elementu

      //sprawdzamy miejsce w tablicy mieszajacej
      if(hash_table[hash] == NULL) return 0;

      Node *tmp = hash_table[hash];                //pomocniczy wskaznik

      if(!compFunc(tmp->data.first, key)) {
        if(tmp->next->hash != hash || tmp->next == guard) {
          hash_table[hash] = NULL;
        } else {
          hash_table[hash] = tmp->next;
        }
      } else {
        do {
          if(tmp == guard) return 0;               //doszlismy do konca
          if(tmp->next->hash != hash) return 0;
          tmp = tmp->next;
        } while(compFunc(tmp->data.first, key) != 0);
      }

      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      delete tmp;
      map_size--;
      return 1;
    }
  
    //usuwa wszystkie elementy z mapy
    void clear() {
      Node *tmp = guard;                //pomocniczy wskaznik

      while(tmp != guard) {
        tmp = tmp->next;                //usuwamy elementy
        delete(tmp->prev);
      }
  
      guard->next = guard->prev = guard;
  
      Node **wsk = hash_table;
      for(int i=0; i<HASH_SIZE; ++i)    //zerujemy tablice mieszajaca
        *(wsk++)= NULL;
  
      map_size = 0;
    }
};
