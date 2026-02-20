#include "struktura.h"

// f-ja duomenu generavimui
void genPazymius(vector<int>& paz, int& egz) {
	static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
	int kiekPaz = mt() % 5 + 1; // Generuoja nuo 1 iki 5 pazymiu
	for (int i = 0; i < kiekPaz; i++) paz.push_back(mt() % 10 + 1); // Pazymiai nuo 1 iki 10
	egz = mt() % 10 + 1; // Egzamino balas nuo 1 iki 10
}

double skaiciuotiGalutini(vector<int> v, int egz, int metodas) {
	if (v.empty()) return 0.6 * egz; // Jei nera pazymiu, galutinis bus 60% egzamino
	double vid_med; // Vidurkis arba mediana
	if (metodas == 1) {
		double suma = 0;
		for (int p : v) suma += p;
		vid_med = suma / v.size();
	}
	else {
		sort(v.begin(), v.end());
		size_t n = v.size();
		vid_med = (n % 2 == 0) ? (v[n / 2 - 1] + v[n / 2]) / 2.0 : v[n / 2];
	}
	return 0.4 * vid_med + 0.6 * egz;
}

void vykdytiVector() {
	vector<StudentasVector> grupe;
	int metodas = gautiSkaiciu("Pasirinkite, kaip skaiciuoti galutini pazymi (1 - Vidurkis, 2 - Mediana): \n", 1, 2);

	while (true) {
		cout << "\n1-Irasyti viska ranka\n2-Generuoti tik pazymius\n3-Generuoti viska\n4-Baigti darba\n";
		int pasirinkimas = gautiSkaiciu("Pasirinkimas: ", 1, 4);
		if (pasirinkimas == 4) break;

		StudentasVector st;
		if (pasirinkimas == 1 || pasirinkimas == 2) {
			cout << "Iveskite studento varda (arba 'stop',jei norite uzbaigti studentu irasyma): \n";
			cin >> st.vardas;
			if (st.vardas == "stop" || st.vardas == "Stop" || st.vardas == "STOP") break;
			cout << "Iveskite studento pavarde: ";
			cin >> st.pavarde;
		}
		else if (pasirinkimas == 3) {
			int kiek = gautiSkaiciu("Kiek studentu generuoti? ", 1, 1000000000);
			for (int i = 0; i < kiek; i++) {
				StudentasVector st;
				st.vardas = genVarda();
				st.pavarde = genPavarde(st.vardas);
				genPazymius(st.paz, st.egz);
				st.rez = skaiciuotiGalutini(st.paz, st.egz, metodas);
				grupe.push_back(st);
			}
			
			cout << "Sugeneruota: " << kiek << "studentu." << endl;
		}
		if (pasirinkimas == 1) {
			string input;
			cout << "Iveskite namu darbu pazymius (1 - 10) (arba 'stop', jei norite uzbaigti namu darbu pazymiu irasyma): \n";
			while (true) {
				cin >> input;
				if (input == "stop" || input == "Stop" || input == "STOP") break;
				try {
					int paz = std::stoi(input); //keiciam string i int
					if (paz >= 1 && paz <= 10) st.paz.push_back(paz);
					else cout << "Pazymys turi buti tarp 1 ir 10.\n";
				}
				catch (...) { cout << "Neteisingas pazymys, bandykite dar karta: "; }
			}
			cout << "Iveskite egzamino bala (1 - 10): \n";
			cin >> st.egz;
		}
		else genPazymius(st.paz, st.egz);

		st.rez = skaiciuotiGalutini(st.paz, st.egz, metodas);
		grupe.push_back(st);
	}
	
	cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis Pazymys" << endl;
	for (const auto& st : grupe) {
		cout << left << setw(15) << st.vardas << setw(15) << st.pavarde << setw(20) << fixed << setprecision(2) << st.rez << endl;
	}
}
	