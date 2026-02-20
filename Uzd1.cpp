#include "struktura.h"

int main() {
    int pasirinkimas;
    while (true) {
        cout << "\n===========================================\n";
        cout << "Pasirinkite duomenu saugojimo buda: \n";
        cout << "1 - Naudoti std::vector\n";
        cout << "2 - Naudoti C masyvus (dinamine atmintis)\n";
		cout << "0 - Baigti programa";
        cout << "\n===========================================\n";
        cout << "Pasirinkimas: ";

        if (cin >> pasirinkimas) {
            if (pasirinkimas == 0) {
                cout << "Programa baigta.\n";
                break;
            }
            if (pasirinkimas == 1) vykdytiVector();
            else if (pasirinkimas == 2) vykdytiArray();
            else cout << "Neteisingas pasirinkimas.\n";
        }
        else {
		    cout << "Klaida: iveskite tinkama skaiciu.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    return 0;
        
}

string genVarda() {
	static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
	string vardai[] = { "Jonas", "Petras", "Simas", "Povilas", "Mykolas", "Tomas", "Dovydas", "Matas", "Lukas", "Rokas",
                        "Evelina", "Gabija", "Ieva", "Greta", "Sandra", "Egle", "Viktorija", "Kamile", "Vilte", "Vejune"};
	return vardai[mt() % 20];
}

string genPavarde(string vardas) {
    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    string Vpavardes[] = { "Kazlauskas", "Jankauskas", "Petrauskas", "Stankevicius", "Vasiliauskas", "Butkus", "Zukauskas", "Paulauskas", "Urbonas", "Kavaliauskas" };
    string Mpavardes[] = { "Kazlauskaite", "Jankauskaite", "Petrauskaite", "Stankeviciute", "Vasiliauskaite", "Butkute", "Zukauskaite", "Paulauskaite", "Urbonaite", "Kavaliauskaite" };
    if (!vardas.empty() && vardas.back() == 's') {
        return Vpavardes[mt() % 10];
    }
        return Mpavardes[mt() % 10];
}
    // klaidu valymas
    int gautiSkaiciu(string info, int min, int max) {
        int sk;
        while (true) {
            cout << info;
            if (cin >> sk && sk >= min && sk <= max) {
                return sk;
            }
            else {
                cout << "Klaida: iveskite tinkama skaiciu (" << min << " - " << max << ").\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }