
Æwiczenie 2. 
Szeregowanie procesów


1. Cel æwiczenia

Celem  æwiczenia  jest zaprojektowanie mechanizmu szeregowania w systemie
MINIX. W trakcie æwiczenia nale¿y zamieniæ standardow± procedurê szereguj±c±
zgodnie z algorytmem szeregowania o cechach wskazanych przez prowadz±cego.


2. Szeregowanie w systemie MINIX

W systemie MINIX procesy s± podzielone na trzy klasy: 

- zadania systemowe (TASK)

- procesy serwerowe (SERVER)

- procesy u¿ytkowe (USER)

Procesy TASK maja bezwzglêdny priorytet nad procesami SERVER, a te z kolei nad
procesami USER. Procesy systemowe TASK i SERVER s± realizowane w re¿imie
pob³a¿aj±cym, to znaczy proces realizuje siê tak d³ugo, a¿ sam zrzecze siê
procesora.  Proces USER po wyczerpaniu kwantu czasu jest przenoszony na koniec
kolejki procesów gotowych. Procedura szereguj±ca wybiera do realizacji zawsze
proces bêd±cy g³ow± kolejki procesów gotowych.


3. Przyk³adowy algorytm szeregowania

Poni¿ej przedstawiono przyk³adowy algorytm szeregowania. Proszê pamiêtaæ, ¿e
jets to tylko przyk³ad, a w³a¶ciwe zadanie do zrealizowania w ramach
laboratorium znajduje siê w punkcie 6.

W przyk³adowym algorytmie szeregowania obowi±zuj± nastêpuj±ce zasady:

- proces ma dwa atrybuty: priorytet bazowy BASE_PRI i priorytet aktualny
  ACT_PRI.

- dwie zmienne systemowe MAX_AGE i MIN_PRI, MAX_AGE>MIN_PRI, dziel±
  szeregowane procesy na trzy kategorie:

	  * priorytet bazowy > MAX_AGE - proces realizowany w re¿imie 
	pob³a¿ania (oczywi¶cie z wyj±tkiem procesów klas TASK i SERVER), priorytet
	bie¿±cy zawsze równy bazowemu,
    
	  * priorytet bazowy > MIN_PRI, <= MAX_AGE - proces 
	realizowany w re¿imie starzenia: proces któremu jest zabierany procesor
	otrzymuje priorytet bie¿±cy równy bazowemu, wszystkie inne z tej grupy
	zwiêkszaj± priorytet bie¿±cy o 1 (maksymalnie do MAX_AGE); proces któremu
	jest zabierany procesor jest wstawiany do kolejki za innymi procesami o
	tym samym priorytecie bie¿±cym,
    
	  * priorytet bazowy < MIN_PRI - proces realizowany w re¿imie 
	priorytetów statycznych z podzia³em czasu: proces któremu jest zabierany
	procesor jest wstawiany do kolejki za innymi procesami o tym samym
	priorytecie bie¿±cym; priorytet bie¿±cy zawsze równy bazowemu.


4. Cechy funkcjonalne przyk³adowego algorytmu w systemie MINIX:

- realizacja szeregowania zgodnie z przedstawionym algorytmem,

- warto¶ci pocz±tkowe zmiennych: MAX_AGE=1000, MIN_PRI=100,

- ka¿dy nowo tworzony proces otrzymuje priorytet bazowy i bie¿±cy równe
  MIN_PRI,

- system udostêpnia nowe wywo³anie - ustaw parametr szeregowania:

	void set_PRI (int nr; unsigned VALUE) 

	nr = 1  nadaj bie¿±cemu procesowi priorytet VALUE 
	nr = 2  ustaw zmienna MAX_AGE na VALUE 
	nr = 3  ustaw zmienna MIN_PRI na VALUE

5. Wskazówki implementacyjne przy implementacji algorytmu przyk³adowego

a) plik kernel/proc.h:
	
	- w strukturze 'proc' umie¶ciæ priorytet bazowy i bie¿±cy procesu,
	
	- zadeklarowaæ zmienne systemowe MAX_AGE i MIN_PRI.

b) plik kernel/proc.c:
	
	- w funkcji 'sched()', która jest procedur± szereguj±c±, zamiast
	  przenoszenia procesu bie¿±cego na koniec kolejki procesów gotowych
	  zrealizowaæ zasady algorytmu przyk³adowego,
	
	- w funkcji 'ready(rp)', która budzi proces, zadbaæ o umieszczenie go w
	  odpowiednim miejscu struktur algorytmu (je¿eli jest to proces klasy
	  USER).

c) plik kernel/system.c:
	
	- w funkcji 'do_fork(m_ptr)', która tworzy nowy proces, w czê¶ci
	  dotycz±cej procesów klasy USER zadbaæ o odpowiednie zainicjowanie
	  priorytetu bazowego i bie¿±cego procesu.

d) plik kernel/main.c:
	
	- w funkcji 'main()', na pocz±tku zadbaæ o w³a¶ciwe zainicjowanie
	  zmiennych systemowych MAX_AGE i MIN_PRI, w pêtli powo³uj±cej deskryptory
	  procesów (for (rp=BEG...)) zadbaæ o w³a¶ciwe wype³nienie priorytetów, w
	  czê¶ci koñcowej powo³uj±cej proces INIT zadbaæ równie¿ o odpowiednie
	  warto¶ci priorytetów.

e) dodaæ do systemu wywo³anie systemowe zgodnie ze sk³adni± podan± w punkcie
4, z tym, ¿e odwo³anie ma nast±piæ do samego mikroj±dra za po¶rednictwem
jednego z modu³ów MM/FS. Dlatego te¿ funkcja realizuj±ca dodane wywo³anie
systemowe (np. o nazwie do_setpri()) w jednym z modu³ów MM/FS powinna mieæ
poni¿sza postaæ:

PUBLIC void do_setpri() 
{ 	
	message m; 
	m = mm_in; 
	_taskcall(SYSTASK, SYS_SETPRI, &m); 
}

gdzie SYS_SETPRI jest zdefiniowana przez nas sta³a w pliku
/usr/include/minix/com.h. 

Ponadto, do pliku /usr/src/kernel/system.c nale¿y dodaæ obs³ugê funkcji o
numerze SYS_SETPRI i zdefiniowaæ sam± funkcjê obs³uguj±c± to wywo³anie. W
obs³udze mo¿na wykorzystaæ makro proc_addr( id ) zwracaj±ce wskazanie na
strukturê proc zadanego procesu.


6. Zadanie do zrealizowania

Prowadz±cy poleci studentom zrealizowaæ algorytm szeregowania o zadanych
w³asno¶ciach funkcjonalnych. Przyk³ad: zrealizowaæ algorytm szeregowania który
zapewni w³a¶ciwe traktowanie procesów trzech kategorii: interaktywnych (np.
gra w statki), obliczeniowych (obliczenia numeryczne) oraz masywnego
wej¶cia/wyj¶cia realizowanego w tle (np. proces sk³adowania dysku na ta¶mie).

