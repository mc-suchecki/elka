
Æwiczenie 4
Synchronizacja procesów z wykorzystaniem monitorów


1. Cel æwiczenia

Nale¿y napisaæ program w jêzyku C++ w ¶rodowisku systemu Linux realizuj±cy
rozwi±zanie problemu zadanego przez prowadz±cego æwiczenie. Problem jest
rozwiniêciem æwiczenia nr 3.


2. Operacje monitorowe 

Przyk³adowa notacja monitora (za Hoare) jest nastêpuj±ca:

type mon = monitor                                 //1
   var ...{zmienne wewnêtrzne monitora};
   var c1,...,cP:condition;                        //2
procedure entry X (...);
var ...
begin                                              //3
   if ... then ci.wait;                            //4
   ... {w³a¶ciwa tre¶æ procedury}
   if not cj.empty                                 //5 
   then cj.signal                                  //6
end;                                               //7
procedure entry Y ...
...

begin 
  {inicjowanie zmiennych wewnêtrznych}             //8
end.

Do realizacji monitora s³u¿y specjalna biblioteka realizuj±ca nastêpuj±ce
elementy monitora, odwo³uj±ce siê do wskazanych miejsc w kodzie: 

// 1 typ "mon" s³u¿±cy do "powo³ywania" monitorów, w szczególno¶ci
// zawieraj±cych zmienn± semaforow± do wzajemnego wykluczania "mutex". Ka¿dy
// monitor musi zawieraæ dok³adnie jedn± zmienn± typu "mon": m:mon.

// 2 typ warunków Hoare'a, pozwalaj±cy na powo³ywanie warunków
// synchronizuj±cych. 

// 3 wej¶cie do monitora "enter". Musi byæ umieszczone na pocz±tku ka¿dej
// metody monitora i tylko tam: enter(m);

// 4 zawieszenie na warunku: wait(ci);

// 5 badanie niepusto¶ci warunku: empty(cj);

// 6 wznawianie procesu: signal(cj);

// 7 wyj¶cie z monitora "leave". Musi byæ umieszczone na koñcu ka¿dej metody
// monitora i tylko tam: leave(m);

// 8 inicjowanie monitora i zmiennych warunkowych: initm(m); initc(c1,m); ...


3. Zadanie do zrealizowania

Nale¿y zrealizowaæ typ "bufor komunikacyjny" przy pomocy monitora. W czasie
implementacji nale¿y zapewniæ synchronizacjê tak± sam± jak w æwiczeniu 3.

Nale¿y zrealizowaæ wiêzy pomiêdzy buforami, te same co w æwiczeniu 3,
zmodyfikowane o dodatkowe warunki wskazane dla æwiczenia 4 przez prowadz±cego.

