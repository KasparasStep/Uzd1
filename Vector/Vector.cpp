// Kompiliavimas:
//   g++ -O2 -std=c++17 studentai_vector.cpp funkcijos.cpp -o studentai_vector
// ============================================================
#include "struktura.h"

#include <windows.h>


// ---- Duomenų skaitymas ----

static void skaityti(const string& failas, vector<Studentas>& grupe, int metodas) {
    ifstream in(failas);
    if (!in) throw runtime_error("Failas nerastas: " + failas);

    string eilute;
    getline(in, eilute); // praleisti antraštę

    while (getline(in, eilute)) {
        if (eilute.empty()) continue;
        stringstream ss(eilute);
        Studentas st;
        if (!(ss >> st.vardas >> st.pavarde)) continue;
        int p;
        while (ss >> p) st.paz.push_back(p);
        if (!st.paz.empty()) {
            st.egz = st.paz.back();
            st.paz.pop_back();
            apskaiciuotiPagalMetoda(st, metodas);
            grupe.push_back(move(st));
        }
    }
}

// ---- Rūšiavimas ----

static void rusiuoti(vector<Studentas>& grupe, int metodas) {
    sort(grupe.begin(), grupe.end(), [&](const Studentas& a, const Studentas& b) {
        double ga = (metodas == 2) ? a.gal_med : a.gal_vid;
        double gb = (metodas == 2) ? b.gal_med : b.gal_vid;
        return ga > gb;
        });
}

// ---- 1 strategija: copy_if į du naujus konteinerius ----
// Originalas nekeičiamas. Studentas saugomas dviejose vietose atmintyje.

static void split_S1(const vector<Studentas>& grupe,
    vector<Studentas>& kieti,
    vector<Studentas>& tinginiai, int metodas) {
    auto galutinis = [&](const Studentas& st) {
        return (metodas == 2) ? st.gal_med : st.gal_vid;
        };
    copy_if(grupe.begin(), grupe.end(), back_inserter(kieti),
        [&](const Studentas& st) { return galutinis(st) >= 5.0; });
    copy_if(grupe.begin(), grupe.end(), back_inserter(tinginiai),
        [&](const Studentas& st) { return galutinis(st) < 5.0; });
}

// ---- 3 strategija: stable_partition + perkėlimas ----
// Grupe tvarkoma vietoje: [kieti | tinginiai].
// tinginiai perkeliami (move) į naują konteinerį ir ištrinami.
// Po funkcijos: grupe = kieti, tinginiai = tinginiai.

static void split_S3(vector<Studentas>& grupe,
    vector<Studentas>& tinginiai, int metodas) {
    auto yraKietas = [&](const Studentas& st) {
        double g = (metodas == 2) ? st.gal_med : st.gal_vid;
        return g >= 5.0;
        };

    // Pertvarko vietoje be papildomos atminties iteracijoms
    auto riba = stable_partition(grupe.begin(), grupe.end(), yraKietas);

    // Move semantics: perkeliame be kopijavimo
    tinginiai.assign(make_move_iterator(riba), make_move_iterator(grupe.end()));
    grupe.erase(riba, grupe.end());
}

// ---- Tyrimo lentelė ----

static void vykdytiTyryma(int metodas) {
    const vector<pair<string, int>> failai = {
        {"Data/studentai1k.txt",    1'000},
        {"Data/studentai10k.txt",   10'000},
        {"Data/studentai100k.txt",  100'000},
        {"Data/studentai1M.txt",    1'000'000},
        {"Data/studentai10M.txt",   10'000'000}
    };

    cout << "\n=== std::vector TYRIMAS ===\n";
    cout << fixed << setprecision(4);
    cout << left
        << setw(22) << "Failas"
        << setw(14) << "Nuskaitymas"
        << setw(14) << "Rūšiavimas"
        << setw(16) << "S1 (copy_if)"
        << setw(16) << "S3 (partition)"
        << "\n" << string(82, '-') << "\n";

    for (const auto& [failas, kiek] : failai) {
        ifstream tikrinimas(failas);
        if (!tikrinimas) {
            cout << setw(22) << failas << "NERASTAS — praleista\n";
            continue;
        }
        tikrinimas.close();

        // 1. Nuskaitymas
        vector<Studentas> originalas;
        originalas.reserve(kiek);
        auto t1 = high_resolution_clock::now();
        skaityti(failas, originalas, metodas);
        auto t2 = high_resolution_clock::now();

        // 2. Rūšiavimas (dirbame su kopija, kad originalas liktų nepakitęs)
        vector<Studentas> rusiotas = originalas;
        auto t3 = high_resolution_clock::now();
        rusiuoti(rusiotas, metodas);
        auto t4 = high_resolution_clock::now();

        // 3. S1 strategija (rusiotas pateikiamas const ref — nekeičiamas)
        vector<Studentas> kieti_s1, tinginiai_s1;
        auto t5 = high_resolution_clock::now();
        split_S1(rusiotas, kieti_s1, tinginiai_s1, metodas);
        auto t6 = high_resolution_clock::now();

        // 4. S3 strategija (dirbame su kopija — S3 keičia konteinerį vietoje)
        vector<Studentas> s3 = rusiotas;
        vector<Studentas> tinginiai_s3;
        auto t7 = high_resolution_clock::now();
        split_S3(s3, tinginiai_s3, metodas);
        auto t8 = high_resolution_clock::now();

        cout << setw(22) << failas
            << setw(14) << duration<double>(t2 - t1).count()
            << setw(14) << duration<double>(t4 - t3).count()
            << setw(16) << duration<double>(t6 - t5).count()
            << setw(16) << duration<double>(t8 - t7).count()
            << "  (kieti: " << s3.size()
            << ", tinginiai: " << tinginiai_s3.size() << ")\n";
    }
}

// ---- Failų generavimas ----

static void generuotiFailus() {
    const vector<pair<string, int>> failai = {
        {"studentai1k.txt",    1'000},
        {"studentai10k.txt",   10'000},
        {"studentai100k.txt",  100'000},
        {"studentai1M.txt",    1'000'000},
        {"studentai10M.txt",   10'000'000}
    };
    for (const auto& [vardas, kiek] : failai) {
        cout << "Generuojama " << vardas << " (" << kiek << " įrašų)...\n";
        auto t1 = high_resolution_clock::now();
        genFaila(vardas, kiek);
        auto t2 = high_resolution_clock::now();
        cout << "  Sugeneruota per " << fixed << setprecision(3)
            << duration<double>(t2 - t1).count() << " s\n";
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    try {
        cout << "Skaičiavimo metodas:\n1 - Vidurkis\n2 - Mediana\n";
        int metodas = gautiSkaiciu("Pasirinkimas: ", 1, 2);

        cout << "\nAr reikia generuoti testavimo failus?\n1 - Taip\n0 - Ne\n";
        if (gautiSkaiciu("Pasirinkimas: ", 0, 1) == 1)
            generuotiFailus();

        vykdytiTyryma(metodas);
    }
    catch (const exception& e) {
        cerr << "Klaida: " << e.what() << "\n";
        return 1;
    }
    return 0;
}