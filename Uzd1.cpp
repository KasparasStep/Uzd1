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
using std::nth_element;

struct Studentas {
	std::string vardas = "A", pavarde = "BB";
	//int *paz jei dinaminis masyvas
	std::vector <int> paz;
	int egz;
	double rez;
};
void inputas(vector<Studentas>& grupe, int P);
void outputas(vector<Studentas>& grupe);
int pasirinkimas();
double median(vector<int> paz);

int main() {
	int P = pasirinkimas();
	vector<Studentas>grupe;
	inputas(grupe, P);
	outputas(grupe);

}
void inputas(vector<Studentas>& grupe, int P) {
	for (int ii = 0; ii < 2; ii++) {
		Studentas A;
		cout << "Iveskite varda ir pavarde: ";
		cin >> A.vardas >> A.pavarde;
		cout << "Iveskite semestro ivertinimus. Kiek ju bus? ";
		int n, sum = 0;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int temp;
			cout << "Iveskite " << i + 1 << " pazymi is " << n << ":";
			cin >> temp;
			A.paz.push_back(temp); sum += temp;
		}
		cout << "Iveskite egzamino iverti: "; cin >> A.egz;
		if (P == 1) {
		A.rez = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;
		}
		else {
		A.rez = median(A.paz) * 0.4 + A.egz * 0.6;
		}
		

		
		grupe.push_back(A);
		A.paz.clear();
		
		
	}// galima priskirti grupej, kai turime A.rez; pushbackinam studento pavadinima
}
void outputas(vector<Studentas>& grupe) {
	cout << left << setw(15) << "Vardas"
		 << left << setw(20) << "Pavarde"
		<< right << setw(15) << "Galutinis (Vid.)/"
		<< right << setw(20) << "Galutinis (Med.)" << endl;
	cout <<string(70, '-') << endl;

	for (auto A : grupe) {
		cout << left << setw(15) << A.vardas << left << setw(20) << A.pavarde
			<< right << setw(15)
			<< right << setw(20) << std::fixed<<std::setprecision(2)<< A.rez << endl;
		//for (auto k : A.paz) cout << setw(3) << k;
		//cout << setw(5) << A.egz;
	
	}
}

double median(vector<int> paz)
{
	size_t n = paz.size();
	if (n == 0) return 0; //jei nera pazymiu

	size_t mid = n / 2; 

	nth_element(paz.begin(), paz.begin() + mid, paz.end());
	double m1 = paz[mid];

	if (n % 2 == 1) return m1;

	nth_element(paz.begin(), paz.begin() + mid - 1, paz.end());
	double m2 = paz[mid - 1];

	return (m1 + m2) / 2.0;
}

int pasirinkimas() {
		int P;
		cout << "Pasirinkiti galutinio balo skaiciavimo metoda\n";
		cout << "1 - Vidurkis\n";
		cout << "2 - Mediana\n";
		cout << "Iveskite pasirinkima: ";
		cin >> P;
		while (P != 1 && P != 2) {
			cout << "Klaida: neteisingas pasirikinimas. Bandykite dar karta\n";
			cin >> P;
		}
		return P;
}