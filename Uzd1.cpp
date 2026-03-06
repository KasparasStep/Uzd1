#include "struktura.h"
#include <windows.h>
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    try {
        vykdytiVector();
    }
    catch (const std::exception& e) {
        cerr << "Programos veikimo klaida: " << e.what() << endl;
        return 1;
	}
    return 0;
        
}
