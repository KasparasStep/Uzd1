#include "struktura.h"


// Atsitiktinių skaičių generatorius
static std::mt19937 mt(steady_clock::now().time_since_epoch().count());


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
    if (n % 2 == 0) return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
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
        cerr << "Klaida skaitant failą: " << e.what() << endl;
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
    // testavimo meniu
    cout << "\nAr norite paleisti greičio tyrimus?\n";
    cout << "1 - Tyrimas 1 (failų kūrimas)\n";
    cout << "2 - Tyrimas 2 (duomenų apdorojimas)\n";
    cout << "3 - Abu tyrimai\n";
    cout << "0 - Praleisti\n";
    int tPas = gautiSkaiciu("Pasirinkimas: ", 0, 3);

    if (tPas == 1 || tPas == 3) test1();
    //if (tPas == 2 || tPas == 3) 

    
    //meniu
    while (true) {
        cout << "\n--- MENIU ---\n";
        cout << "1 - Įrašyti viską ranka\n";
        cout << "2 - Įrašyti vardus ranka, generuoti tik pažymius\n";
        cout << "3 - Generuoti viską (vardus/pavardes ir pažymius)\n";
        cout << "4 - Nuskaityti iš failo\n";
		cout << "5 - Generuoti studentų failus (1 tūkst. / 10 tūkst. / 100 tūkst. / 1 M / 10 M)\n";
        cout << "0 - Baigti duomenų suvedimą ir rikiuoti\n";
        int pas = gautiSkaiciu("Pasirinkimas: ", 0, 5);

		// 0 variantas: baigti įvedimą
        if (pas == 0) break;

		// 1 ir 2 variantai: rankinis įvedimas
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

        // 3 variantas: Generuoti viska
        else if (pas == 3) {
            
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

		// 4 variantas: Iš failo
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

		// 5 variantas: Generuoti failus
        else if (pas == 5) {
            cout << "\nKurį failą generuoti?\n";
            cout << "1 -      1 000 įrašų\n";
            cout << "2 -     10 000 įrašų\n";
            cout << "3 -    100 000 įrašų\n";
            cout << "4 -  1 000 000 įrašų\n";
            cout << "5 - 10 000 000 įrašų\n";
            cout << "6 - Visus iš karto\n";
            int fPas = gautiSkaiciu("Pasirinkimas: ", 1, 6);

            vector<pair<string, int>> failai = {
                {"studentai1k.txt",  1000},
                {"studentai10k.txt", 10000},
                {"studentai100k.txt",100000},
                {"studentai1M.txt",  1000000},
                {"studentai10M.txt", 10000000}
            };
            // jei tik vieną failą
            if (fPas >= 1 && fPas <= 5) {
                auto& [vardas, kiek] = failai[fPas - 1];
                cout << "Generuojama: " << vardas << "...\n";
                auto t1 = high_resolution_clock::now();
                genFaila(vardas, kiek);
                auto t2 = high_resolution_clock::now();
                cout << "Sugeneruota per: "
                    << fixed << setprecision(4)
                    << duration<double>(t2 - t1).count() << " s\n";
            }
            // jei visi iš karto
            else {
                for (auto& [vardas, kiek] : failai) {
                    cout << "Generuojama: " << vardas << " (" << kiek << " įrašų)...\n";
                    auto t1 = high_resolution_clock::now();
                    genFaila(vardas, kiek);
                    auto t2 = high_resolution_clock::now();
                    cout << "Sugeneruota per: "
                        << fixed << setprecision(4)
                        << duration<double>(t2 - t1).count() << " s\n";
                }
                cout << "\nVisi failai sugeneruoti.\n";
            }
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

    //skirtsymas į dvi dalis
    cout << "\nAr skirstyti studentus į dvi grupes (kieti / tinginiai)?\n";
    cout << "1 - Taip\n2 - Ne\n";
    int skPas = gautiSkaiciu("Pasirinkimas: ", 1, 2);

    if (skPas == 1) {
        vector<Studentas> kieti, tinginiai;

        auto t1 = high_resolution_clock::now();
        splitStudents(grupe, kieti, tinginiai, metodas);
        auto t2 = high_resolution_clock::now();

        cout << "\nKieti (>= 5.0): " << kieti.size() << " studentų\n";
        cout << "Tinginiai  (< 5.0): " << tinginiai.size() << " studentų\n";
        cout << "Skirstymas užtruko:  " << fixed << setprecision(4)
            << duration<double>(t2 - t1).count() << " s\n";

        // Failų pavadinimai
        string kietuFailas, tinginiuFailas;
        cout << "\nKietų failo pavadinimas (pvz. kieti.txt): ";
        cin >> kietuFailas;
        cout << "Tinginių failo pavadinimas (pvz. tinginiai.txt): ";
        cin >> tinginiuFailas;

        auto t3 = high_resolution_clock::now();
        spausdintiRezultatus(kieti, metodas, kietuFailas);
        spausdintiRezultatus(tinginiai, metodas, tinginiuFailas);
        auto t4 = high_resolution_clock::now();

        cout << "Išvedimas užtruko: " << fixed << setprecision(4)
            << duration<double>(t4 - t3).count() << " s\n";

        cout << "\nFailai sukurti:\n";
        cout << "  " << kietuFailas << " (" << kieti.size() << " įrašų)\n";
        cout << "  " << tinginiuFailas << " (" << tinginiai.size() << " įrašų)\n";
    }
}

void splitStudents(const vector<Studentas>& visi, vector<Studentas>& kieti,
    vector <Studentas>& tiniginiai, int metodas) {
    auto galutinis = [&](const Studentas& st) {
        return (metodas == 2) ? st.gal_med : st.gal_vid;
        };

    //copy if kopijuoja tik tuos elementus, kurie atitinka salyga
    copy_if(visi.begin(), visi.end(), back_inserter(kieti), [&](const Studentas& st)
        {
            return galutinis(st) >= 5.0;
        });
    copy_if(visi.begin(), visi.end(), back_inserter(tiniginiai), [&](const Studentas& st)
        {
            return galutinis(st) < 5.0;
        });
}
