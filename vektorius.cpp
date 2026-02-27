#include "struktura.h"

// f-ja duomenu generavimui
void genPazymius(vector<int>& paz, int& egz) {
	static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
	int kiekPaz = 5; // Generuoja 5 pazymius
	for (int i = 0; i < kiekPaz; i++) paz.push_back(mt() % 10 + 1); // Pazymiai nuo 1 iki 10
	egz = mt() % 10 + 1; // Egzamino balas nuo 1 iki 10
}

double skaiciuotiVidurki(const vector<int>& paz) {
	if (paz.empty()) return 0.0; // Apsauga nuo dalybos iš nulio, jei nera pazymiu uz N.D.
	double suma = 0;
	for (int p : paz) {
		suma += p;
	}
	return suma / paz.size();
}

double skaiciuotiMediana(vector<int> paz) {
	if (paz.empty()) return 0.0;
	sort(paz.begin(), paz.end());
	size_t n = paz.size();
	if (n % 2 == 0) {
		return paz[n / 2 - 1] + paz[n / 2] / 2.0; // Lyginis skaičius elementų, grąžina vidurki dviejų vidurinių
	}
	else {
		return paz[n / 2]; // Nelyginis skaičius elementų, grąžina vidurki dviejų vidurinių
	}
}

void apskaiciuotiPagalMetoda(Studentas& st, int metodas) {
	if (metodas == 1 || metodas == 3)
		st.gal_vid = skaiciuotiVidurki(st.paz) * 0.4 + st.egz * 0.6;
	if (metodas == 2 || metodas == 3)
		st.gal_med = skaiciuotiMediana(st.paz) * 0.4 + st.egz * 0.6;
}
void skaitytiIsFailo(const string& failas, vector<Studentas>& grupe, int metodas) {
	ifstream in(failas);
	if (!in) {
		cerr << "Klaida: nepavyko atidaryti failo " << failas << endl;
		return;
	}
	string line;
	getline(in, line); // Praleidžiame antraštę
	while (getline(in, line)) {
		if (line.empty()) continue;
		stringstream ss(line);
		Studentas st;
		ss >> st.vardas >> st.pavarde;
		int p; // pazymys
		vector<int> visi; //visi pazymiai
		while (ss >> p) { visi.push_back(p); } // skaitome visus pazymius
		if (!visi.empty()) {
			st.egz = visi.back(); // paskutinis skaicius yra egzaminas
			visi.pop_back(); // pašaliname egzaminą iš pazymiu vektoriaus
			st.paz = move(visi); // perkeliam pazymius i studento struktura
			apskaiciuotiPagalMetoda(st, metodas); // skaiciuojame
			grupe.push_back(move(st)); // perkeliam studento struktura i grupe
		}
	}
	in.close();
	cout << "Duomenys nuskaityti." << endl;
}

void vykdytiVector() {
	vector<Studentas> grupe;

	int metodas = gautiSkaiciu("Pasirinkite, kaip skaiciuoti galutini pazymi (1 - Vidurkis, 2 - Mediana): \nPasirinkimas: ", 1, 2);

	cout << "\n1-Irasyti viska ranka\n2-Generuoti tik pazymius\n3-Generuoti viska\n4-Nuskaityti is failo\n0-Baigti darba\n";

	while (true) {
		int pasirinkimas = gautiSkaiciu("Pasirinkimas: ", 0, 4);
		if (pasirinkimas == 0) break;

		if (pasirinkimas == 4) {
			string failas;
			cout << "Iveskite failo pavadinima: ";
			cin >> failas;
			skaitytiIsFailo(failas, grupe, metodas);
			continue;
		}

		Studentas st;
		if (pasirinkimas == 1 || pasirinkimas == 2) {
			cout << "Iveskite studento varda (arba 'stop',jei norite uzbaigti studentu irasyma): \n";
			cin >> st.vardas;
			if (st.vardas == "stop" || st.vardas == "Stop" || st.vardas == "STOP") break;
			cout << "Iveskite studento pavarde: ";
			cin >> st.pavarde;
		}
		else if (pasirinkimas == 3) {
			int kiek = gautiSkaiciu("Kiek studentu generuoti? ", 1, 1000000);
			for (int i = 0; i < kiek; i++) {
				Studentas st;
				st.vardas = genVarda();
				st.pavarde = genPavarde(st.vardas);
				genPazymius(st.paz, st.egz);
				apskaiciuotiPagalMetoda(st, metodas);
				grupe.push_back(st);
			}

			cout << "Sugeneruota: " << kiek << " studentu." << endl;
			cout << "\n1-Irasyti viska ranka\n2-Generuoti tik pazymius\n3-Generuoti viska\n4-Baigti darba\n";
			continue;
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

		apskaiciuotiPagalMetoda(st, metodas);
		grupe.push_back(move(st));
	}

	if (grupe.empty()) {
		cout << "Nera studentu duomenu." << endl;
		return;
	}

	//rusiavimo kriterijus

	cout << "Rikiuoti pagal: 1 - Varda, 2 - Pavarde, 3 - Rezultata\n";
	int rusiuoti = gautiSkaiciu("Pasirinkimas: ", 1, 3);

	// rusiuoti

	auto startRusiuoti = high_resolution_clock::now();
	sort(grupe.begin(), grupe.end(), [rusiuoti, metodas](const Studentas& a, const Studentas& b) {
		if (rusiuoti == 1) return a.vardas < b.vardas;
		else if (rusiuoti == 2) return a.pavarde < b.pavarde;
		else if (metodas == 2) return a.gal_med > b.gal_med;
		else return a.gal_vid > b.gal_vid;
		});
	auto endRikiuoti = high_resolution_clock::now();
	cout << "Rikiavimo laikas: " << duration_cast<std::chrono::seconds>(endRikiuoti - startRusiuoti).count() << " s" << endl;

	// isvedimo vietos pasirinkimas

	cout << "\nKur isvesti rezultatus?\n1 - I ekrana\n2 - I faila\n";
	int isvestis = gautiSkaiciu("Pasirinkimas: ", 1, 2);

	string failas = "";
	if (isvestis == 2) {
		cout<< "Iveskite failo pavadinima: ";
		cin >> failas;
	}

	auto startIsvesti = high_resolution_clock::now();
	spausdintiRezultatus(grupe, metodas, failas);
	auto endIsvesti = high_resolution_clock::now();
	cout << "Isvedimo laikas: " << duration_cast<std::chrono::seconds>(endIsvesti - startIsvesti).count() << " s" << endl;
}
	// isvedimas su funkcija

void spausdintiRezultatus(const std::vector<Studentas>&grupe, int rodyti, const std::string & failas) {
		ostream* out = &cout;//spausdiname i ekrana
			ofstream fout;

		// jei failas nurodytas, spausdiname i faila
		if (!failas.empty()) {
			fout.open(failas);
			if (!fout) {
				cerr << "Klaida: nepavyko atidaryti failo " << failas << " rasymui." << endl;
				return;
			}
			out = &fout; //nukreipiame i faila

		}

		(*out) << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
		if (rodyti == 1 || rodyti == 3) (*out) << setw(20) << "Galutinis (Vid.)";
		if (rodyti == 2 || rodyti == 3) (*out) << setw(20) << "Galutinis (Med.)";
		(*out) << endl << string(70, '-') << endl;

		for (const auto& st : grupe) {
			(*out) << left << setw(15) << st.vardas << setw(15) << st.pavarde;
			if (rodyti == 1 || rodyti == 3) (*out) << fixed << setprecision(2) << setw(20) << st.gal_vid;
			if (rodyti == 2 || rodyti == 3) (*out) << fixed << setprecision(2) << setw(20) << st.gal_med;
			(*out) << endl;
		}

		if (!failas.empty()){
			fout.close();
			cout << "Rezultatai issaugoti faile: " << failas << endl;
		}
}
	
	
	