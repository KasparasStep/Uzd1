#include "struktura.h"


// Atsitiktinių skaičių generatorius
static std::mt19937 mt(steady_clock::now().time_since_epoch().count());

void genPazymius(vector<int>& paz, int& egz) {
    paz.clear();
    for (int i = 0; i < 20; i++) paz.push_back(mt() % 10 + 1);
    egz = mt() % 10 + 1;
}

double skaiciuotiVidurki(const vector<int>& paz) {
    if (paz.empty()) return 0.0;
    double suma = 0.0;
    for (int p : paz) suma += p;
    return suma / paz.size();
}

double skaiciuotiMediana(vector<int> paz) {
    if (paz.empty()) return 0.0;
    sort(paz.begin(), paz.end());
    size_t n = paz.size();
    if (n % 2 == 0) return (static_cast<double>(paz[n / 2 - 1]) + static_cast<double>(paz[n / 2] / 2.0));
    else return static_cast<double>(paz[n / 2]);
}

void apskaiciuotiPagalMetoda(Studentas& st, int metodas) {
    if (metodas == 1 || metodas == 3)
        st.gal_vid = skaiciuotiVidurki(st.paz) * 0.4 + st.egz * 0.6;
    if (metodas == 2 || metodas == 3)
        st.gal_med = skaiciuotiMediana(st.paz) * 0.4 + st.egz * 0.6;
}

void skaitytiIsFailo(const string& failas, vector<Studentas>& grupe, int metodas) {
    ifstream in(failas);
    if (!in) {
        cout << "KLAIDA: Failas '" << failas << "' nerastas!\n";
        cout << "Isitikinkite, kad failas yra ten pat, kur .cpp failai.\n";
        return;
    }

    string line;
    getline(in, line); // Antraštė praleidžiama

    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Studentas st;

        // Nuskaitome vardą ir pavardę
        if (!(ss >> st.vardas >> st.pavarde)) continue;

        int p;
        while (ss >> p) {
            st.paz.push_back(p);
        }

        if (!st.paz.empty()) {
            st.egz = st.paz.back();
            st.paz.pop_back();
            apskaiciuotiPagalMetoda(st, metodas);
            grupe.push_back(move(st));
        }
    }
    in.close();
}

void spausdintiRezultatus(const vector<Studentas>& grupe, int rodyti, const string& failas) {
    ostream* out = &cout;
    ofstream fout;

    if (!failas.empty()) {
        fout.open(failas);
        if (fout) out = &fout;
    }

    (*out) << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
    if (rodyti == 1 || rodyti == 3) (*out) << setw(20) << "Galutinis (Vid.)";
    if (rodyti == 2 || rodyti == 3) (*out) << setw(20) << "Galutinis (Med.)";
    (*out) << endl << string(70, '-') << endl;

    for (const auto& st : grupe) {
        (*out) << left << setw(15) << st.vardas << setw(15) << st.pavarde;
        if (rodyti == 1 || rodyti == 3) (*out) << fixed << setprecision(2) << setw(20) << st.gal_vid;
        if (rodyti == 2 || rodyti == 3) (*out) << fixed << setprecision(2) << setw(20) << st.gal_med;
        (*out) << endl;
    }
}

void vykdytiVector() {
    vector<Studentas> grupe;
    int metodas = gautiSkaiciu("Skaiciavimo metodas:\n1 - Vidurkis\n2 - Mediana\n3 - Abu.\nPasirinkimas: ", 1, 3);

    while (true) {
        cout << "\n1 - Ranka\n2 - Generuoti tik pazymius\n3 - Generuoti viska\n4 - Skaityti is failo\n0 - Rodyti rezultata ir baigti\n";
        int pas = gautiSkaiciu("Pasirinkimas: ", 0, 4);
        if (pas == 0) break;

        if (pas == 4) {
            string f; cout << "Failo vardas (.txt failas turi buti .cpp failu aplanke): "; cin >> f;
            auto s = high_resolution_clock::now();
            skaitytiIsFailo(f, grupe, metodas);
            auto e = high_resolution_clock::now();
            cout << "\nNuskaityta per: " << duration<double>(e - s).count() << " s\n";
        }
        else if (pas == 3) {
            int kiek = gautiSkaiciu("Kiek studentu generuoti? ", 1, 1000000);
            for (int i = 0; i < kiek; i++) {
                Studentas st; st.vardas = genVarda(); st.pavarde = genPavarde(st.vardas);
                genPazymius(st.paz, st.egz);
                apskaiciuotiPagalMetoda(st, metodas);
                grupe.push_back(move(st));
            }
        }
    }

    if (grupe.empty()) return;

    // rusiavimas

    cout << "\nKaip rusiuoti duomenis?\n";
    cout << "1 - Pagal Varda\n2 - Pagal pavarde\n3 - Pagal galutini pazymi\n";
    int rPasirinkimas = gautiSkaiciu("Pasirinkimas: ", 1, 3);

    auto startRusiuoti = high_resolution_clock::now();

    sort(grupe.begin(), grupe.end(), [rPasirinkimas, metodas](const Studentas& a, const Studentas& b) {
        if (rPasirinkimas == 1) return a.vardas < b.vardas;
        else if (rPasirinkimas == 2) return a.pavarde < b.pavarde;
        else {
            double galA = (metodas == 1 || metodas == 3) ? a.gal_vid : a.gal_med;
            double galB = (metodas == 1 || metodas == 3) ? b.gal_vid : b.gal_med;
            return galA > galB; // Didesni pazymiai pirmiau
        }
        });

    auto endRusiuoti = high_resolution_clock::now();
    double rTrukme = duration<double>(endRusiuoti - startRusiuoti).count();
    cout << "\nRusiavimas uztruko: " << fixed << setprecision(4) << rTrukme << " s\n";

    cout << "Kur isvesti?\n1 - Ekranas\n2 - Failas.\nPasirinkimas: ";
    int kur = gautiSkaiciu("", 1, 2);
    string fVardas = "";
    if (kur == 2) { cout << "\nFailo pavadinimas: "; cin >> fVardas; }

    spausdintiRezultatus(grupe, metodas, fVardas);
}