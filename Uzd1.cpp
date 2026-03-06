#include "struktura.h"
#include "funkcijos.cpp"
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
