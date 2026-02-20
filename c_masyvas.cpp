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
void genPazymius(int*& paz, int& kiekis, int& egz) {
	static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
	kiekis = mt() % 5 + 1; // Generuoja nuo 1 iki 5 pazymiu
	paz = new int[kiekis];
	for (int i = 0; i < kiekis; i++) paz[i] = mt() % 10 + 1; // Pazymiai nuo 1 iki 10
	egz = mt() % 10 + 1; // Egzamino balas nuo 1 iki 10
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
	int talpa = 30;
	int n = 0; // pradine masyvo talpa - 30
	StudentasArray* grupe = new StudentasArray[talpa];
	int metodas = gautiSkaiciu("Pasirinkite, kaip skaiciuoti galutini pazymi (1 - Vidurkis, 2 - Mediana): ", 1, 2);

	while (true) {
		cout << "\n1-Irasyti viska ranka\n2-Generuoti tik pazymius\n3-Generuoti viska\n4-Baigti darba\n";
		int pasirinkimas = gautiSkaiciu("Pasirinkimas: ", 1, 4);
		if (pasirinkimas == 4) break; // tas pats kaip ir vektoriuje

		StudentasArray st;
		if (pasirinkimas == 3) {
			int kiek = gautiSkaiciu("Kiek studentu sugeneruoti? ", 1, 100000000);
			for (int i = 0; i < kiek; i++) {
				StudentasArray st;
				st.vardas = genVarda();
				st.pavarde = genPavarde(st.vardas);
				genPazymius(st.paz, st.kiekis, st.egz);
				st.rez = skaiciuotiGalutini(st.paz, st.kiekis, st.egz, metodas);
				if (n == talpa) {
					talpa *= 2;
					StudentasArray* naujaGrupe = new StudentasArray[talpa];
					for (int j = 0; j < n; j++) naujaGrupe[j] = grupe[j];
					delete[] grupe;
					grupe = naujaGrupe;
				}
				grupe[n++] = st;
			}
			cout << "Sugeneruota: " << kiek << " studentu." << endl;
		}
		else {
			cout << "Iveskite studento varda (arba 'stop',jei norite uzbaigti studentu irasyma): ";
			cin >> st.vardas;
			if (st.vardas == "stop" || st.vardas == "Stop" || st.vardas == "STOP") break;
			cout << "Iveskite studento pavarde: ";
			cin >> st.pavarde;
			if (pasirinkimas == 1) {
				cout << "Iveskite namu darbu pazymius (1 - 10) (arba 'stop', jei norite uzbaigti namu darbu pazymiu irasyma): \n";
				while (true) {
					string input;
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
			}
			else genPazymius(st.paz, st.kiekis, st.egz);
		}

		st.rez = skaiciuotiGalutini(st.paz, st.kiekis, st.egz, metodas);

		if (n == talpa) {
			talpa *= 30;
			StudentasArray* naujaGrupe = new StudentasArray[talpa];
			for (int i = 0; i < n; i++) naujaGrupe[i] = grupe[i];
			delete[] grupe;
			grupe = naujaGrupe;
		}
		grupe[n++] = st;
	}
	cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis pazymys\n";
	for (int i = 0; i < n; i++) {
		cout << left << setw(15) << grupe[i].vardas << setw(15) << grupe[i].pavarde << setw(20) << fixed << setprecision(2) << grupe[i].rez << endl;
		delete[] grupe[i].paz; // Atlaisviname kiekvieno studento pazymiu masyva
	}
	delete[] grupe; // Atlaisviname studentu masyva
}