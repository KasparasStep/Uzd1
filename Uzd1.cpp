#include "struktura.h"

int main() {
    int pasirinkimas;
    std::cout << "Pasirinkite duomenu saugojimo buda:\n";
    std::cout << "1 - Naudoti std::vector\n";
    std::cout << "2 - Naudoti C masyvus (dinamine atmintis)\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> pasirinkimas;

    if (pasirinkimas == 1) {
        vykdytiVectorVersija();
    }
    else if (pasirinkimas == 2) {
        vykdytiArrayVersija();
    }
    else {
        std::cout << "Neteisingas pasirinkimas. Bandyti dar karta.\n";
        cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> pasirinkimas;
    }

    return 0;
}