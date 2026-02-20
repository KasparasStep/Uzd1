#include "struktura.h"

// masyvo didinimas
void pridetiPazymi(StudentasArray& st, int paz) {
	int* naujasPaz = new int[st.kiekis + 1];
	for (int i = 0; i < st.kiekis; i++) naujasPaz[i] = st.paz[i];
	
	naujasPaz[st.kiekis] = paz;
	delete[] st.paz;
	st.paz = naujasPaz;
	st.kiekis++;
}

double skaiciuotiGalutini(int* arr, int n, int egz, int metodas) {
	if (n == 0) return 0.6 * egz; // Jei nera pazymiu, galutinis bus 60% egzamino
	double vid_med; // Vidurkis arba mediana
	if (metodas == 1) {
		double suma = 0;
		for (int i = 0; i < n; i++) suma += arr[i];
		vid_med = suma / n;
	}
	else {
		int* temp = new int[n];
		for (int i = 0; i < n; i++) temp[i] = arr[i];
		sort(temp, temp + n);
		vid_med = (n % 2 == 0) ? (temp[n / 2 - 1] + temp[n / 2]) / 2.0 : temp[n / 2];
		delete[] temp;
	}
	return 0.4 * vid_med + 0.6 * egz;
}

void vykdytiArray() {
	int talpa = 30, n = 0;
	StudentasArray* grupe = new StudentasArray[talpa];
	int metodas = gautiSkaiciu("Pasirinkite, kaip skaiciuoti galutini pazymi (1 - Vidurkis, 2 - Mediana): ", 1, 2);

	while (true) {
		StudentasArray st;
		cout << "Iveskite studento varda (arba 'stop',jei norite uzbaigti studentu irasyma): ";
		cin >> st.vardas;
		if (st.vardas == "stop" || st.vardas == "Stop" || st.vardas == "STOP") break;
		cout << "Iveskite studento pavarde: ";
		cin >> st.pavarde;

		string input;
		cout << "Iveskite namu darbu pazymius (1 - 10) (arba 'stop', jei norite uzbaigti namu darbu pazymiu irasyma): \n";
		while (true) {
			cin >> input;
			if (input == "stop" || input == "Stop" || input == "STOP") break;
			try { 
				int paz = std::stoi(input);//keiciam string i int
				if (paz >= 1 && paz <= 10) pridetiPazymi(st, paz);
				else cout << "Pazymys turi buti tarp 1 ir 10.\n";
			} 
			catch (...) { cout << "Klaida, bandykite dar karta: \n"; }
		}
		st.egz = gautiSkaiciu("Iveskite egzamino bala (1 - 10): \n", 1, 10);
		st.rez = skaiciuotiGalutini(st.paz, st.kiekis, st.egz, metodas);

		if (n == talpa) {
			talpa *= 2;
			StudentasArray* naujaGrupe = new StudentasArray[talpa];
			for (int i = 0; i < n; i++) naujaGrupe[i] = grupe[i];
			delete[] grupe;
			grupe = naujaGrupe;
		}
		grupe[n++] = st;
	}
	cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Rezultatas\n";
	for (int i = 0; i < n; i++) {
		cout << left << setw(15) << grupe[i].vardas << setw(15) << grupe[i].pavarde << setw(20) << fixed << setprecision(2) << grupe[i].rez << endl;
		delete[] grupe[i].paz; // Atlaisviname kiekvieno studento pazymiu masyva
	}
	delete[] grupe; // Atlaisviname studentu masyva
}