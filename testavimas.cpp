#include "struktura.h"

void test1() {
    vector<pair<string, int>> failai = {
        {"studentai1000.txt", 1000},
        {"studentai10000.txt", 10000},
        {"studentai100000.txt", 100000},
        {"studentai500000.txt", 1000000},
        {"studentai1000000.txt", 10000000}
    };

    for (auto& [vardas, kiek] : failai) {
        auto startGen = high_resolution_clock::now();
        genFaila(vardas, kiek);
        auto endGen = high_resolution_clock::now();

        cout << vardas << " (" << kiek << "įrašų): "
            << duration<double>(endGen - startGen).count() << " s\n";
    }
}

void test2(const string& failas, int metodas) {
    vector<Studentas> visi, kieti, tinginiai;

    //nuskaitymas
    auto t1 = high_resolution_clock::now();
    skaitytiIsFailo(failas, visi, metodas);
    auto t2 = high_resolution_clock::now();

    //skirstymas
    splitStudentai(visi, kieti, tinginiai, metodas);
    auto t3 = high_resolution_clock::now();

    //spausdinimas i 2 failus
    spausdintiRezultatus(kieti, metodas, "kieti_" + failas);
    spausdintiRezultatus(tinginiai, metodas, "tinginiai_" + failas);
    auto t4 = high_resolution_clock::now();

    //rezultatai
    cout << "\n=== " << failas << " ===\n";
    cout << "Nuskaitymas:  " << duration<double>(t2 - t1).count() << " s\n";
    cout << "Skirstymas:   " << duration<double>(t3 - t2).count() << " s\n";
    cout << "Išvedimas:    " << duration<double>(t4 - t3).count() << " s\n";
    cout << "IŠ VISO:      " << duration<double>(t4 - t1).count() << " s\n";
}