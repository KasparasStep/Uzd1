# Uzd1
v0.1 dokumentacija.

v0.1 sudaro 4 failai:
1)	struktura.h sudaro studentų struct abiems duomenu saugojimo variantams, bibliotekos,
	kurias importuoja kiti failai ir funkciju prototipai.
2)	Uzd1.cpp yra pagrindinis programos meniu ir kelios kitos funkcijos
	(vardu, pavardziu generavimas ir skaiciaus ivedimas)	
3)	vektorius.cpp tai programos realizavimas naudojant std::vector konteinerį
4)	c_masyvas.cpp tai programos realizavimas naudojant dinaminius masyvus ir rodykles.

Programa gali naudoti arba std::vector variantą arba dinaminių masyvų variantą.
Toliau programa gali panaudoti 3 duomenų įvedimo būdus:
1)	Vartotojas visus duomenis surašo rankiniu būdu.
2)	Vartotojas įveda vardą ir pavardę, o pažymiai sugeneruojami.
3)	Viskas sugeneruojama.

Generavimui panaudota: 20 vardų (10 vyr. g. ir 10 mot. g) ir
			10 pavardžių (pagal vardo giminę priskiriama ir atitinkama giminė pavarde)
Generuojami lygiai 5 pazymiai, kitokio pasirinkimo nera. Norint pakeisti, reikėtų keisti kodą.
Sugeneruojami 5 "namų darbų" ir egzamino balas, kurie toliau panaudojami galutinio balo skaičiavimui.

Galutinio balo skaičiavimui galima pasirinkti, ar naudoti vidurkį ar medianą.
Medianos skaičiavimui panaudojama sort funkcija.
Šis būdas skiriasi nuo v.pradinės versijos, kurioje buvo naudojamas nth_element algoritmas.
Galutinio balo formulė: 0.4 * (vidurkis arba mediana) + 0.6 * egzamino balas

Dinaminės atminties valdymas labai paprastas:
1)	Kai užsipildo masyvas (n == talpa) rezervuojamaa nauja, dvigubai didesnė atminities vieta.
2)	Dabartiniai duomenys perkeliame į naują vietą.
3)	Sena duomenu vieta atlaisvinama su delete[] .
Pradinė masyvo talpa yra 30, t. y. rezervuojama vieta 30 studentų.

Duomenu generavimui naudojama Mersenne Twister (mt19937) generatorius.
Naudojama static std::mt19937, kad sugeneruoti duomenys nebūtų vienodi.
Taip pat naudojama chrono::seed, kad generatoriaus "seed" būtų skirtingas kiekviena kartą paleidus programą.

Po kiekvieno veiksmo galima grįžti į pagrindinį meniu (reikia įrašyti "4").
Pagrindiniame meniu galima užbaigti programą (reikia įrašyti "0").

Kai duomenys įvedami rankiniu būdų, įvedimą galima sustabdyti įrašant "stop".

Programoje yra minimalus klaidų valdymas. Naudojama try-catch ir std::stoi.
Taip pat naudojama cin.clear() ir cin.ignore().

v0.2 dokumentacija

Panaikintas c_masyvas.cpp bei visos funkcijos susijusios su masyvais.
Dabar generuojama 20 pazymiu.
Galimybe nuskaityti info is failo bei irasyti rezultata i faila.

Testavimas:
Su 10000: nuskaitymo vidurkis 0.379853 s (DEBUG); 0.03973865 (RELEASE);

SU 100000: nuskaitymo vidurkis 4.678703 s (DEBUG); 0.4749995 (RELEASE);

Su 1000000: nuskaitymo vidurkis 24.250467 s (DEBUG); 2.099945 (RELEASE);

Kiti testavimo duomenys:

Testavimas vyksta iprastomis salygomis. Tai yra, kompiuteryje atidarytas tik visual studio, notepad++, o fone veikia windows defender ir AMD software.
studentai10000.txt:
	Nuskaitymas		Rusiavimas	Spausdinimas
	
	1. 0.381866 s	0.0522 s	0.0661 s  
	2. 0.379624 s	0.0525 s	0.0675 s	( 14.2212 s (spausdinimas i konsole))
	3. 0.379853 s	0.0513 s	0.0653 s
	4. 0.0397989 s	0.0015 s	0.0264 s (RELEASE)
	5. 0.0396784 s	0.0015 s	0.0269 s (RELEASE)
	
studentai100000.txt:
	Nuskaitymas		Rusiavimas	Spausdinimas
	
	1. 4.66092 s	0.6027 s	0.6351 s
	2. 4.67711 s	0.5977 s	0.6459 s
	3. 4.69808 s	0.5925 s	0.6422 s	( 136.9455 s (spausdinimas i konsole))
	4. 0.476265 s	0.0133 s	0.2574 s (RELEASE)
	5. 0.473734 s	0.0187 s	0.2581 s (RELEASE)	125.4006 s (spausdinimas i konsole)
	
studentai1000000.txt:
	Nuskaitymas		Rusiavimas	Spausdinimas
	
	1. 24.2544 s	5.9000 s	6.1552 s
	2. 24.2507 s	10.6223 s	6.1837 s
	3. 24.2463 s	10.6634 s	6.9418 s	( 1306.3533 s (spausdinimas i konsole))
	4. 2.09501 s	0.2144 s	2.4617 s (RELEASE)
	5. 2.10488 s	0.0860 s	2.4743 s (RELEASE)