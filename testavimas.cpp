#include "struktura.h"

void test1() {
    vector<pair<string, int>> failai = {
        {"studentai1k.txt", 1000},
        {"studentai10k.txt", 10000},
        {"studentai100k.txt", 100000},
        {"studentai1M.txt", 1000000},
        {"studentai10M.txt", 10000000}
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
    cout << "\n=== TYRIMAS 2: Duomenų apdorojimas ===\n";

    // Tikrina ar failai egzistuoja prieš pradedant
    vector<string> failai = {
        "studentai1k.txt",
        "studentai10k.txt",
        "studentai100k.txt",
        "studentai1M.txt",
        "studentai10M.txt"
    };

    for (auto& failas : failai) {
        // Tikriname ar failas egzistuoja
        ifstream patikrinimas(failas);
        if (!patikrinimas) {
            cout << "\n[!] Failas '" << failas << "' nerastas. "
                << "Pirma paleiskite Tyrimą 1.\n";
            continue;
        }
        patikrinimas.close();

        cout << "\n--- " << failas << " ---\n";
        vector<Studentas> visi, kieti, tinginiai;

        // Bendra pradžia
        auto visoPradzia = high_resolution_clock::now();

        // 1. Nuskaitymas
        auto t1 = high_resolution_clock::now();
        skaitytiIsFailo(failas, visi, metodas);
        auto t2 = high_resolution_clock::now();

        // 2. Skirstymas į dvi grupes
        splitStudents(visi, kieti, tinginiai, metodas);
        auto t3 = high_resolution_clock::now();

        // 3. Išvedimas į du failus
        string bazinis = failas.substr(0, failas.find('.'));
        spausdintiRezultatus(kieti, metodas, "kieti_" + bazinis + ".txt");
        spausdintiRezultatus(tinginiai, metodas, "tinginiai_" + bazinis + ".txt");
        auto t4 = high_resolution_clock::now();

        // Rezultatai pagal užduoties reikalavimus
        cout << "  Nuskaitymas        : "
            << fixed << setprecision(4)
            << duration<double>(t2 - t1).count() << " s\n";
        cout << "  Skirstymas         : "
            << fixed << setprecision(4)
            << duration<double>(t3 - t2).count() << " s\n";
        cout << "  Išvedimas į failus : "
            << fixed << setprecision(4)
            << duration<double>(t4 - t3).count() << " s\n";
        cout << "  IŠ VISO            : "
            << fixed << setprecision(4)
            << duration<double>(t4 - visoPradzia).count() << " s\n";
        cout << "  (Kieti: " << kieti.size()
            << ", Tinginiai: " << tinginiai.size() << ")\n";
    }
}