
#include "struktura.h"
int main() {
    string failas = "studentai10000.txt"; // Testuojamas failas
    vector<Studentas> visi, kieti, vargsiukai;

    cout << "Testuojamas VECTOR su " << failas << endl;

    auto t1 = high_resolution_clock::now();
    skaitytiVector(failas, visi, 1);
    auto t2 = high_resolution_clock::now();

    auto t3 = high_resolution_clock::now();
    sort(visi.begin(), visi.end(), [](const Studentas& a, const Studentas& b) {
        return a.gal_vid < b.gal_vid;
        });
    auto t4 = high_resolution_clock::now();

    auto t5 = high_resolution_clock::now();
    skirstytiVector(visi, kieti, vargsiukai);
    auto t6 = high_resolution_clock::now();

    cout << "Skaitymas: " << duration<double>(t2 - t1).count() << "s" << endl;
    cout << "Rusiavimas: " << duration<double>(t4 - t3).count() << "s" << endl;
    cout << "Skirstymas (S1): " << duration<double>(t6 - t5).count() << "s" << endl;

    return 0;
}