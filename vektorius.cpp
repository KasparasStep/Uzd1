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
    if (n % 2 == 0) return paz[n / 2 - 1] + paz[n / 2] / 2.0;
    else return paz[n / 2];
}

void apskaiciuotiPagalMetoda(Studentas& st, int metodas) {
    if (metodas == 1 || metodas == 3)
        st.gal_vid = skaiciuotiVidurki(st.paz) * 0.4 + st.egz * 0.6;
    if (metodas == 2 || metodas == 3)
        st.gal_med = skaiciuotiMediana(st.paz) * 0.4 + st.egz * 0.6;
}

void skaitytiIsFailo(const string& failas, vector<Studentas>& grupe, int metodas) {
    ifstream in(failas);
    try {
        if (!in) throw std::runtime_error("Failas nerastas: " + failas);

        string line;
        getline(in, line); // Praleisti antrastę

        while (getline(in, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
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
        cout << "Duomenys nuskaityti sėkmingai.\n";
    }
    catch (const std::exception& e) {
        cerr << "Klaida skaitant faila: " << e.what() << endl;
    }
}

void spausdintiRezultatus(const vector<Studentas>& grupe, int rodyti, const string& failas) {
    ostream* out = &cout;
    ofstream fout;
	auto startSpausd = high_resolution_clock::now();
    if (!failas.empty()) {
        fout.open(failas);
        if (fout) out = &fout;
    }

    (*out) << left << setw(15) << "Vardas" << setw(15) << "Pavardė";
    if (rodyti == 1 || rodyti == 3) (*out) << setw(20) << "Galutinis (Vid.)";
    if (rodyti == 2 || rodyti == 3) (*out) << setw(20) << "Galutinis (Med.)";
    (*out) << endl << string(70, '-') << endl;

    for (const auto& st : grupe) {
        (*out) << left << setw(15) << st.vardas << setw(15) << st.pavarde;
        if (rodyti == 1 || rodyti == 3) (*out) << fixed << setprecision(2) << setw(20) << st.gal_vid;
        if (rodyti == 2 || rodyti == 3) (*out) << fixed << setprecision(2) << setw(20) << st.gal_med;
        (*out) << endl;
    }
	auto endSpausd = high_resolution_clock::now();
	cout << "\nSpausdinimas užtruko: " << fixed << setprecision(4) << duration<double>(endSpausd - startSpausd).count() << " s\n";
}

void vykdytiVector() {
    vector<Studentas> grupe;
    int metodas = gautiSkaiciu("Skaičiavimo metodas:\n1 - Vidurkis\n2 - Mediana\n3 - Abu.\nPasirinkimas: ", 1, 3);

    while (true) {
        cout << "\n--- MENIU ---\n";
        cout << "1 - Įrašyti viską ranka\n";
        cout << "2 - Įrašyti vardus ranka, generuoti tik pažymius\n";
        cout << "3 - Generuoti viską (vardus/pavardes ir pažymius)\n";
        cout << "4 - Nuskaityti iš failo\n";
        cout << "0 - Baigti duomenų suvedimą ir rikiuoti\n";
        int pas = gautiSkaiciu("Pasirinkimas: ", 0, 4);

        if (pas == 0) break;

        if (pas == 1 || pas == 2) {
            Studentas st;
            cout << "Įveskite vardą: "; cin >> st.vardas;
            cout << "Įveskite pavardę: "; cin >> st.pavarde;

            if (pas == 1) {
                // 1 variantas: Viskas ranka
                string input;
                cout << "Įveskite N.D. pažymius (1-10). 'stop' - baigti: \n";
                while (cin >> input && input != "stop") {
                    try {
                        int p = stoi(input);
                        if (p >= 1 && p <= 10) st.paz.push_back(p);
                        else cout << "Tik 1-10!\n";
                    }
                    catch (...) { cout << "Neteisingas skaičius!\n"; }
                }
                st.egz = gautiSkaiciu("Įveskite egzamino balą (1-10): ", 1, 10);
            }
            else {
                // 2 variantas: generuojami tik pazymiai
                genPazymius(st.paz, st.egz);
                cout << "Sugeneruoti " << st.paz.size() << " pažymiai ir egzaminas.\n";
            }
            apskaiciuotiPagalMetoda(st, metodas);
            grupe.push_back(move(st));

        }
        else if (pas == 3) {
            // 3 variantas: Generuoti viska
            int kiek = gautiSkaiciu("Kiek studentų generuoti? ", 1, 1000000);
            for (int i = 0; i < kiek; i++) {
                Studentas st;
                st.vardas = genVarda();
                st.pavarde = genPavarde(st.vardas);
                genPazymius(st.paz, st.egz);
                apskaiciuotiPagalMetoda(st, metodas);
                grupe.push_back(move(st));
            }
            cout << "Sugeneruota.\n";

        }
        else if (pas == 4) {
            // 4 variantas: Iš failo
            string f;
            cout << "Įveskite failo pavadinimą (pvz. studentai10000.txt): ";
            cin >> f;
            auto s = high_resolution_clock::now();
            skaitytiIsFailo(f, grupe, metodas);
            auto e = high_resolution_clock::now();
            cout << "Nuskaityta per: " << duration<double>(e - s).count() << " s\n";
        }
    }

    if (grupe.empty()) {
        cout << "Sąrašas tuščias.\n";
        return;
    }

    // rusiavimas

    cout << "\nKaip rūšiuoti duomenis?\n";
    cout << "1 - Pagal Vardą\n2 - Pagal pavardę\n3 - Pagal galutinį pažymį\n";
    int rPasirinkimas = gautiSkaiciu("Pasirinkimas: ", 1, 3);

    auto startRusiuoti = high_resolution_clock::now();

    sort(grupe.begin(), grupe.end(), [rPasirinkimas, metodas](const Studentas& a, const Studentas& b) {
        switch (rPasirinkimas) {
            case 1: return a.vardas < b.vardas;
            case 2: return a.pavarde < b.pavarde;
            case 3: {
                double galA = (metodas == 2) ? a.gal_med : a.gal_vid;
                double galB = (metodas == 2) ? b.gal_med : b.gal_vid;
                return galA > galB;// mazejimo tvarka
            }
            default: return a.pavarde < b.pavarde;
        }
        });

    auto endRusiuoti = high_resolution_clock::now();
    double rTrukme = duration<double>(endRusiuoti - startRusiuoti).count();
    cout << "\nRūšiavimas užtruko: " << fixed << setprecision(4) << rTrukme << " s\n";

    cout << "Kur išvesti?\n1 - Ekranas\n2 - Failas.\nPasirinkimas: ";
    int kur = gautiSkaiciu("", 1, 2);
    string fVardas = "";
    if (kur == 2) { cout << "\nFailo pavadinimas(pvz.: rezultatai.txt): "; cin >> fVardas; }

    spausdintiRezultatus(grupe, metodas, fVardas);
}