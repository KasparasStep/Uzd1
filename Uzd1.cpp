#include "struktura.h"

int main() {
    int pasirinkimas;
        cout << "Pasirinkite duomenu saugojimo buda: \n";
        cout << "1 - Naudoti std::vector\n";
        cout << "2 - Naudoti C masyvus (dinamine atmintis)\n";
		cout << "0 - Baigti programa\n";
        cout << "Pasirinkimas: ";
    while (true) {
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