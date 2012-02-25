/** 
@file main.cc

Plik z funkcja main() do cwiczenia na laboratoriach z AISDI.

@author
Pawel Cichocki, Michal Nowacki

@date  
last revision
- 2006.01.06 Michal Nowacki: wersja polska
- 2005.10.27 Pawel Cichocki: added some comments
- 2005.10.26 Michal Nowacki: creation - separated from another file

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <iostream>

#ifdef _SUNOS
#include "/home/common/dyd/aisdi/liniowe/ListMap.h"
#else
#include "ListMap.h"
#endif

int CCount::count=0;

int Test2();
void test();

int main()
{
   std::cout << "AISDI struktury liniowe: wchodze do funkcji main." << std::endl;
   test();
   // Biblioteka z bardziej rygorystyczna wersja tych testow bedzie udostepniona na nastepnych zajeciach.
   Test2();
   //system("PAUSE");
   return EXIT_SUCCESS;
}
