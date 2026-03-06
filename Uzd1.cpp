#include "struktura.h"
int main() {
    try {
        vykdytiVector();
    }
    catch (const std::exception& e) {
        cerr << "Programos veikimo klaida: " << e.what() << endl;
        return 1;
	}
    return 0;
        
}
string genVarda() {
    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    string vardai[] = { "Jonas", "Petras", "Simas", "Povilas", "Mykolas", "Tomas", "Dovydas", "Matas", "Lukas", "Rokas",
                        "Evelina", "Gabija", "Ieva", "Greta", "Sandra", "Egle", "Viktorija", "Kamile", "Vilte", "Vejune" };
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
        try {
            if (!(cin >> sk)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("KLAIDA: ivestas ne skaicius.");
            }
            if (cin >> sk && sk >= min && sk <= max) {
                return sk;
            }
            else if (sk < min || sk > max) {
                throw std::out_of_range("KLAIDA: ivestas skaicius uz leistinu ribu.");
                cout << "Klaida: iveskite tinkama skaiciu (" << min << " - " << max << ").\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        catch (const std::exception& e) {
            cout << "Klaida: " << e.what() << " Bandykite dar karta." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}