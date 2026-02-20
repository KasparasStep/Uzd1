#include "struktura.h"
#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::left;
using std::right;
using std::setw;
using std::endl;


struct Studentas {
	string vardas, pavarde;
	vector <int> paz;
	int egz;
	double rez;
};

/*funkciju prototipai
double apskaiciuotiRez(vector<int> paz, int egz, int metodas);
Studentas genStudentas();*/

double median(vector<int> paz);

int main() {
	vector<Studentas>grupe;
	int pasirinkimas = 0;
	int metodas;


	cout << "Pasirinkite galutinio balo skaiciavimo metoda (1 - Vidurkis, 2 - Mediana):  ";
	while (!(cin >> metodas) || (metodas != 1 && metodas != 2)) {
		cout << "Neteisingas pasirinkimas. Iveskite 1 arba 2: ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Išvalome klaidingą įvestį
	}

	while (pasirinkimas != 4) {
		cout << "\n--- MENIU ---\n";
		cout << "1. Ivesti studentus rankiniu budu\n";
		cout << "2. Generuoti tik pazymius, o vardai ivedavi rankiniu budu\n";
		cout << "3. Generuoti visus duomenis\n";
		cout << "4. Baigti ir isvesti rezultatus\n";
		cout << "Pasirinkimas: "; cin >> pasirinkimas;

		if (pasirinkimas == 1 || pasirinkimas == 2) {
			while (true) {
				Studentas st; // studentas
				cout << "Iveskite studento varda (arba 'stop' kad baigti): ";
				cin >> st.vardas;
				if (st.vardas == "stop") break;
				cout << "Iveskite studento pavarde: ";
				cin >> st.pavarde;

				if (pasirinkimas == 1) {
					string input; //teksto ivedimas
					cout << "Iveskite namu darbu pazymius (arba iveskite 'stop', kad uzbaigti ivedima): \n";
					while (true) {
						cin >> input;
						// tikriname ar ivedimas yra "stop"
						if (input == "stop" || input == "STOP" || input == "Stop") break;
						// verciame teksta i skaiciu
						try {
							int pazymys = std::stoi(input); // string to int

							if (pazymys >= 1 && pazymys <= 10) {
								st.paz.push_back(pazymys);
							}
							else {
								cout << "Klaida: Pazymys gali buti tik tarp 1 ir 10. Bandykite dar karta.\n";
							}
						}
						catch (std::invalid_argument) {
							cout << "Klaida: iveskite skaiciu arba rasykite 'stop'.\n"; // jei ivedamas ne skaicius arba netinkamas 'stop' variantas
						}
					}
					cout << "Iveskite egzamino bala: ";
					cin >> st.egz;
				}
				else {
					int k = rand() % 10 + 1; // atsitiktinis pazymys nuo 1 iki 10
					for (int i = 0; i < k; i++) st.paz.push_back(rand() % 10 + 1);
					st.egz = rand() % 10 + 1;
				}
				//st.rez = apskaiciuotiRez(st.paz, st.egz, metodas);
				grupe.push_back(st);
			}
		}
		else if (pasirinkimas == 3) {
			int n; cout << "Kiek studentu generuoti? "; cin >> n;
			for (int i = 0; i < n; i++) {
				//Studentas st = genStudentas();
				//st.rez = apskaiciuotiRez(st.paz, st.egz, metodas);
				//grupe.push_back(st);
			}
		}
	}
}