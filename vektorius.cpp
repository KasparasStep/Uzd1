#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

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

double median(vector<int> paz);

int main() {
	vector<Studentas>grupe;
	int pasirinkimas = 0;
	int metodas = 0;

	
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

	}
	//inputas(grupe, P);
	//outputas(grupe);
}