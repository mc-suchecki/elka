//Autor: Maciej Suchecki (grupa 3I4)

#include <assert.h>
#include <algorithm>
#include <iostream>

#ifdef _SUNOS
#include "/home/common/dyd/aisdi/tree/TreeMap.h" 
#else
#include "TreeMap.h"
#endif

class TreeMapDetail
{
  protected:
    friend class TreeMap;
    friend class TreeMap::iterator;
    friend class TreeMap::const_iterator;

    unsigned tree_size;

    //konstruktor domyslny
    TreeMapDetail() : tree_size(0) {}

    void clearTree(TreeNode *node) {
      if(node->left) clearTree(node->left);
      if(node->right) clearTree(node->right);
      delete node;
    }

    void copyTree(TreeMap *to, TreeNode *from) {
      to->insert(from->data);
      if(from->left) copyTree(to, from->left);
      if(from->right) copyTree(to, from->right);
    }

    void checkStruct(TreeNode *first, TreeNode *second, bool *result) {
      if(!first && !second) return;

      if(!first || !second || first->data.first != second->data.first ||
         first->data.second != second->data.second) *result = false;

      if(*result) {
        checkStruct(first->left, second->left, result);
        checkStruct(first->right, second->right, result);
      }
    }
};

//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

//konstruktor domyslny
TreeMap::TreeMap() {
  root = new TreeNode(std::make_pair(0, ""), NULL, NULL, NULL);
  detail = new TreeMapDetail();
};

//konstruktor kopiujacy
TreeMap::TreeMap(const TreeMap& m) {
  root = new TreeNode(std::make_pair(0, ""), NULL, NULL, NULL);
  detail = new TreeMapDetail();
  detail->copyTree(this, m.root->left);
};

//destruktor
TreeMap::~TreeMap() {
  clear();
  delete root;
};

//wstawianie elementu do drzewa
std::pair<TreeMap::iterator, bool> TreeMap::insert(const std::pair<Key, Val>& entry) {
  TreeNode *tmp = root->left;

  while(tmp) {                      //szukamy miejsca na nowy element

    //powinnismy nowy element wstawic z lewej
    if(tmp->data.first > entry.first) {

      //wstawiamy tutaj
      if(!tmp->left) {
        tmp->left = new TreeNode(entry, tmp, NULL, NULL);
        detail->tree_size++;
        return std::make_pair(iterator(tmp->left), true);
      }

      tmp = tmp->left;                                          //idziemy dalej
      continue;
    }

    //powinnismy nowy element wstawic z prawej
    if(tmp->data.first < entry.first) {
 
      //wstawiamy tutaj
      if(!tmp->right) {
        tmp->right = new TreeNode(entry, tmp, NULL, NULL);
        detail->tree_size++;
        return std::make_pair(iterator(tmp->right), true);
      }

      tmp = tmp->right;                                          //idziemy dalej
      continue;
    }

    //drzewo juz zawiera element o podanym kluczu
    return std::make_pair(iterator(tmp), false);
  }

  //drzewo jest puste
  detail->tree_size++;
  root->left = new TreeNode(entry, root, NULL, NULL);
  return std::make_pair(iterator(root->left), true);
}

//wstawianie elementu do drzewa (elementu o takim samym kluczu nie ma)
TreeMap::iterator TreeMap::unsafe_insert(const std::pair<Key, Val>& entry) {
  TreeNode *tmp = root->left;

  while(tmp) {                      //szukamy miejsca na nowy element

    //powinnismy nowy element wstawic z lewej
    if(tmp->data.first > entry.first) {

      //wstawiamy tutaj
      if(!tmp->left) {
        tmp->left = new TreeNode(entry, tmp, NULL, NULL);
        detail->tree_size++;
        return iterator(tmp->left);
      }

      tmp = tmp->left;                                          //idziemy dalej
      continue;
    }

    //powinnismy nowy element wstawic z prawej
    if(tmp->data.first < entry.first) {
 
      //wstawiamy tutaj
      if(!tmp->right) {
        tmp->right = new TreeNode(entry, tmp, NULL, NULL);
        detail->tree_size++;
        return iterator(tmp->right);
      }

      tmp = tmp->right;                                          //idziemy dalej
      continue;
    }
  }

  //drzewo jest puste
  detail->tree_size++;
  root->left = new TreeNode(entry, root, NULL, NULL);
  return iterator(root->left);
}

//wyszukiwanie elementu o podanym kluczu
TreeMap::iterator TreeMap::find(const Key& k) {
  TreeNode *tmp = root->left;           //ustawiamy sie na poczatku

  while(tmp) {
    if((tmp->data).first > k) tmp = tmp->left;
    else if((tmp->data).first < k) tmp = tmp->right;
    else return iterator(tmp);          //znalezlismy
  }

  return end();                         //nic nie znalezlismy
}

//wyszukiwanie elementu o podanym kluczu
TreeMap::const_iterator TreeMap::find(const Key& k) const {
  TreeNode *tmp = root->left;           //ustawiamy sie na poczatku

  while(tmp) {
    if((tmp->data).first > k) tmp = tmp->left;
    else if((tmp->data).first < k) tmp = tmp->right;
    else return const_iterator(tmp);    //znalezlismy
  }

  return end();                         //nic nie znalezlismy
}

//operator tablicowy
TreeMap::Val& TreeMap::operator[](const Key& k) {
  iterator tmp = (insert(std::make_pair(k, ""))).first;
  return tmp->second;
}

//sprawdzenie czy mapa jest pusta
bool TreeMap::empty() const {
  return root->left == NULL;
}

//zwraca ilosc elementow w drzewie
TreeMap::size_type TreeMap::size() const {
  return detail->tree_size;
}

//zwraca ilosc elementow o podanym kluczu w drzewie
TreeMap::size_type TreeMap::count(const Key& _Key) const {
  TreeNode *tmp = root->left;           //ustawiamy sie na poczatku

  while(tmp) {
    if((tmp->data).first > _Key) tmp = tmp->left;
    else if((tmp->data).first < _Key) tmp = tmp->right;
    else return 1;                      //znalezlismy
  }

  return 0;                             //nic nie znalezlismy
}

//usuwa element z drzewa, zwraca iterator na element za usuwanym
TreeMap::iterator TreeMap::erase(TreeMap::iterator i) {
  TreeNode *tmp = i.node;

  if(!tmp->left) {              //wezel ma jedno lub zero dzieci
    //ustawiamy wskazniki
    if(tmp->parent->left == tmp) tmp->parent->left = tmp->right;
    else tmp->parent->right = tmp->right;
  
  } else if(!tmp->right) {      //wezel ma jedno dziecko

    //ustawiamy wskazniki
    if(tmp->parent->left == tmp) tmp->parent->left = tmp->left;
    else tmp->parent->right = tmp->left;
  
  } else {                      //wezel ma dwojke dzieci

    //szukamy najmniejszego elementu w prawym poddrzewie
    TreeNode *node = tmp;
    tmp = tmp->right;
    while(tmp->left) tmp = tmp->left;

    //zamieniamy wartosci elementow 
    node->data.first = tmp->data.first;
    node->data.second = tmp->data.second;

    //ustawiamy wskazniki
    if(tmp->parent->left == tmp) tmp->parent->left = tmp->right;
    else tmp->parent->right = tmp->right;
  }

  //usuwamy wezel
  detail->tree_size--;
  delete tmp;
  return ++i;
}

//usuwa zakres elementow z drzewa, zwraca iterator na element za ostatnim usuwanym
TreeMap::iterator TreeMap::erase(TreeMap::iterator f, TreeMap::iterator l) {
  while(f != l) erase(f++);
  return l;
}

//usuwa element z drzewa, zwraca ilosc usunietych elementow
TreeMap::size_type TreeMap::erase(const Key& k) {
  TreeNode *tmp = root->left;           //ustawiamy sie na poczatku

  while(tmp) {
    if((tmp->data).first > k) tmp = tmp->left;
    else if((tmp->data).first < k) tmp = tmp->right;
    else {
      erase(iterator(tmp));            //znalezlismy
      return 1;
    }
  }
  
  return 0;                             //nie ma takiego elementu
}

//usuwa wszystkie elementy z mapy
void TreeMap::clear() {
  if(root->left) detail->clearTree(root->left);
}

//porownanie strukturalne
bool TreeMap::struct_eq(const TreeMap &another) const {
  //sprawdzamy czy drzewa nie sa puste
  if(!root->left && !another.root->left) return true;
  if(!root->left || !another.root->left) return false;

  //jesli drzewa maja rozne rozmiary to sa na pewno rozne
  if(detail->tree_size != another.detail->tree_size) return false;

  bool *result = new bool;
  *result = true;
  detail->checkStruct(root->left, another.root->left, result);
  return *result;
}

//porownanie informacyjne
bool TreeMap::info_eq(const TreeMap &another) const {
  //sprawdzamy czy drzewa nie sa puste
  if(!root->left && !another.root->left) return true;
  if(!root->left || !another.root->left) return false;

  //jesli drzewa maja rozne rozmiary to sa na pewno rozne
  if(detail->tree_size != another.detail->tree_size) return false;

  //sprawdzamy czy kazdy element istnieje w obu drzewach
  for(TreeMap::iterator tmp = begin(); tmp.node != root; tmp++) {
    if(another.find(tmp.node->data.first) == another.end()) return false;
  }

  return true;
}

//preinkrementacja
TreeMap::const_iterator& TreeMap::const_iterator::operator++() {
  if(!node->parent) return *this;       //jesli jestesmy na koncu (root)

  if(node->right) {                     //jesli nie jestesmy w lisciu
    node = node->right;
    while(node->left) node = node->left;
    return *this;
  }
  
  if(node->parent->left == node)        //jesli jestesmy w lewym lisciu
    node = node->parent;    
  else {                                //jesli jestesmy w prawym lisciu
    while(node->parent->right == node) node = node->parent;
    node = node->parent;
  }

  return *this;
}

//postinkrementacja
TreeMap::const_iterator TreeMap::const_iterator::operator++(int) {
  if(!node->parent) return *this;       //jesli jestesmy na koncu (root)

  TreeNode *tmp = node;

  if(node->right) {                     //jesli nie jestesmy w lisciu
    node = node->right;
    while(node->left) node = node->left;
    return tmp;
  }
  
  if(node->parent->left == node)        //jesli jestesmy w lewym lisciu
    node = node->parent;    
  else {                                //jesli jestesmy w prawym lisciu
    while(node->parent->right == node) node = node->parent;
    node = node->parent;
  }

  return tmp;
}

//predekrementacja
TreeMap::const_iterator& TreeMap::const_iterator::operator--() {
  if(node->left) {                      //jesli nie jestesmy w lisciu
    node = node->left;
    while(node->right) node = node->right;
    return *this;
  }

  if(node->parent->right == node)       //jesli jestesmy w prawym lisciu
    node = node->parent;
  else {                                //jesli jestesmy w lewym lisciu
    while(node->parent->left == node) node = node->parent;
    node = node->parent;
  }

  return *this;
}

//postdekrementacja
TreeMap::const_iterator TreeMap::const_iterator::operator--(int) {
  TreeNode *tmp = node;

  if(node->left) {                      //jesli nie jestesmy w lisciu
    node = node->left;
    while(node->right) node = node->right;
    return tmp;
  }

  if(node->parent->right == node)       //jesli jestesmy w prawym lisciu
    node = node->parent;
  else {                                //jesli jestesmy w lewym lisciu
    while(node->parent->left == node) node = node->parent;
    node = node->parent;
  }

  return tmp;
}

//operator przypisania
TreeMap& TreeMap::operator=(const TreeMap &m) {
  if(root == m.root) return *this;
  clear();
  detail->copyTree(this, m.root->left);
  return *this;
}
      
//zwraca iterator wskazujacy na pierwszy element w drzewie
TreeMap::iterator TreeMap::begin() { 
  if(!root->left) return iterator(root);

  TreeNode *tmp = root->left;
  while(tmp->left) tmp = tmp->left;
  return iterator(tmp);
}

TreeMap::const_iterator TreeMap::begin() const {
  if(!root->left) return const_iterator(root);

  TreeNode *tmp = root->left;
  while(tmp->left) tmp = tmp->left;
  return const_iterator(tmp);
}

//zwraca iterator wskazujacy na element za ostatnim w drzewie
TreeMap::iterator TreeMap::end() { 
  return iterator(root);
}

TreeMap::const_iterator TreeMap::end() const { 
  return const_iterator(root);
}

//////////////////////////////////////////////////////////////////////////////
// Tests
//////////////////////////////////////////////////////////////////////////////

/// A helper function that outputs a key-value pair.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>

/// The big mean test function ;)
void test()
{
   // A typedef used by the test.
   typedef std::map<int, std::string> TEST_MAP;
   //typedef SmallMap<int, std::string> TEST_MAP;
   //typedef TreeMap TEST_MAP;

   std::cout << "Testy uzytkownika" << std::endl;

        TEST_MAP m;  
   
   m[2] = "Merry";
   m[4] = "Jane";
   m[8] = "Korwin";
   m[4] = "Magdalena";

   for_each(m.begin(), m.end(), print );
   //system("PAUSE");
}
