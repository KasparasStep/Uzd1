#include "struktura.h"

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
	int metodas = gautiSkaiciu("Pasirinkite, kaip skaiciuoti galutini pazymi (1 - Vidurkis, 2 - Mediana): ", 1, 2);
	cin >> metodas;

	while (true) {
		StudentasVector st;
		cout << "Iveskite studento varda (arba 'stop',jei norite uzbaigti studentu irasyma): ";
		cin >> st.vardas;
		if (st.vardas == "stop") break;
		cout << "Iveskite studento pavarde: ";
		cin >> st.pavarde;

		string input;
		cout << "Iveskite namu darbu pazymius (1 - 10) (arba 'stop', jei norite uzbaigti namu darbu pazymiu irasyma): ";
		while (true) {
			cout << "Iveskite namu darbu pazymius (1 - 10) (arba 'stop', jei norite uzbaigti namu darbu pazymiu irasyma): ";
			cin >> input;
			if (input == "stop") break;
			try { int paz = std::stoi(input); //keiciam string i int
			if (paz >= 1 && paz<= 10) st.paz.push_back(paz);
			else cout << "Pazymys turi buti tarp 1 ir 10, bandykite dar karta: ";
			} 
			catch (...) { cout << "Neteisingas pazymys, bandykite dar karta: "; }
			}
		cout << "Iveskite egzamino bala (1 - 10): ";
		cin >> st.egz;
		st.rez = skaiciuotiGalutini(st.paz, st.egz, metodas);
		grupe.push_back(st);
		}
	cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis Pazymys" << endl;
	for (const auto& st : grupe) {
		cout << left << setw(15) << st.vardas << setw(15) << st.pavarde << setw(20) << fixed << setprecision(2) << st.rez << endl;
	}
}
	