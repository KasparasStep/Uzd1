#include "struktura.h"

int main() {
    string failas = "studentai10000.txt";
    deque<Studentas> visi, kieti, tinginiai;

    auto t1 = high_resolution_clock::now();
    skaitytiDuomenis(failas, visi, 1);
    auto t2 = high_resolution_clock::now();

    // DEQUE taip pat naudoja std::sort
    sort(visi.begin(), visi.end(), [](const Studentas& a, const Studentas& b) {
        return a.gal_vid < b.gal_vid;
        });
    auto t3 = high_resolution_clock::now();

    for (const auto& s : visi) {
        if (s.gal_vid < 5.0) tinginiai.push_back(s);
        else kieti.push_back(s);
    }
    auto t4 = high_resolution_clock::now();

    cout << "DEQUE - Skaitymas: " << duration<double>(t2 - t1).count() << "s, "
        << "Rusiavimas: " << duration<double>(t3 - t2).count() << "s, "
        << "Skirstymas: " << duration<double>(t4 - t3).count() << "s\n";
    return 0;
}