Æwiczenie 6
Konstrukcja systemu plików

1. Cel æwiczenia

  Nale¿y napisaæ w ¶rodowisku systemu Minix program w jêzyku C (oraz skrypt
  demonstruj±cy wykorzystanie tego programu) realizuj±cy podstawowe funkcje
  systemu plików.

2. Funkcje programu 

  System plików nale¿y zorganizowaæ w du¿ym pliku o zadanej wielko¶ci, który
  bêdzie "wirtualnym dyskiem". Program powinien tworzyæ dysk wirtualny, oraz
  dokonywaæ zapisów i odczytów w celu zrealizowania podstawowych operacji na
  dysku, zwi±zanych z zarz±dzaniem katalogiem, alokacj± plików oraz
  utrzymywaniem unikalno¶ci nazw.

3. Zadanie do zrealizowania

  W pliku na dysku nale¿y zorganizowaæ system plików z jednopoziomowym
  katalogiem.  Elementem katalogu jest opis pliku, zawieraj±cy co najmniej
  nazwê, wielko¶æ i sposób rozmieszczenia pliku na wirtualnym dysku. Nale¿y
  zaimplementowaæ nastêpuj±ce operacje, dostêpne dla u¿ytkownika programu:

	- tworzenie wirtualnego dysku,
	
	- kopiowanie pliku z dysku systemu Minix na dysk wirtualny,
	
	- kopiowanie pliku z dysku wirtualnego na dysk systemu Minix,
	
	- wy¶wietlanie katalogu dysku wirtualnego,
		
	- usuwanie pliku z wirtualnego dysku,
	
	- usuwanie wirtualnego dysku,

	- wy¶wietlenie zestawienia z aktualn± map± zajêto¶ci wirtualnego dysku -
	  czyli listy kolejnych obszarów wirtualnego dysku z opisem: adres, typ
	  obszaru, rozmiar, stan (np. dla bloków danych: wolny/zajêty).

  Program ma kontrolowaæ wielko¶æ dostêpnego miejsca na wirtualnym dysku i
  pojemno¶æ katalogu, reagowaæ na próby przekroczenia tych wielko¶ci. 

  Nie trzeba realizowaæ funkcji otwierania pliku ani czytania/pisania
  fragmentów pliku.

  Nie trzeba realizowaæ funkcji zwi±zanych z wspó³bie¿nym dostêpem. Zak³ada
  siê dostêp sekwencyjny i wy³±czny do wirtualnego dysku.

  Nale¿y przygotowaæ demonstracjê (zgrupowanie serii poleceñ w postaci skryptu
  interpretera sh) prezentuj±c± s³abe i silne strony przyjêtego rozwi±zania w
  kontek¶cie ewentualnych zewnêtrznej i wewnêtrznej fragmentacji.


