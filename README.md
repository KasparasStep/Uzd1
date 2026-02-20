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