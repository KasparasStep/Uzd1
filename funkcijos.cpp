#include "struktura.h"
string genVarda() {
    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    string vardai[] = { "Jonas", "Petras", "Simas", "Povilas", "Mykolas", "Tomas", "Dovydas", "Matas", "Lukas", "Rokas",
                        "Evelina", "Gabija", "Ieva", "Greta", "Sandra", "Eglė", "Viktorija", "Kamilė", "Viltė", "Vėjūnė" };
    return vardai[mt() % 20];
}

string genPavarde(string vardas) {
    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    string Vpavardes[] = { "Kazlauskas", "Jankauskas", "Petrauskas", "Stankevičius", "Vasiliauskas", "Butkus", "Žukauskas", "Paulauskas", "Urbonas", "Kavaliauskas" };
    string Mpavardes[] = { "Kazlauskaitė", "Jankauskaitė", "Petrauskaitė", "Stankevičiūtė", "Vasiliauskaitė", "Butkutė", "Žukauskaitė", "Paulauskaitė", "Urbonaitė", "Kavaliauskaite" };
    if (!vardas.empty() && vardas.back() == 's') {
        return Vpavardes[mt() % 10];
    }
    return Mpavardes[mt() % 10];
}

// klaidu valymas skaiciu irasyme
int gautiSkaiciu(string info, int min, int max) {
    int sk;
    while (true) {
        cout << info;
        try {
            // 1. Bandome nuskaityti skaičių
            if (!(cin >> sk)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Įvestas ne skaičius!");
            }

            // 2. TIKRINIMAS: Ar po skaičiaus seka nepageidaujami simboliai (pvz. taškas ar kablelis)?
            // cin.peek() pažiūri į kitą simbolį buferyje
            if (cin.peek() != '\n' && cin.peek() != ' ' && cin.peek() != '\t' && cin.peek() != EOF) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Skaičius negali turėti kablelio ar papildomų simbolių!");
            }

            // 3. Diapazono tikrinimas
            if (sk < min || sk > max) {
                throw out_of_range("Tokio pasirinkimo nėra!");
            }

            // Viskas gerai - išvalome buferį iki galo ir grąžiname reikšmę
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return sk;

        }
        catch (const exception& e) {
            cout << "Klaida: " << e.what() << " Bandykite dar kartą.\n";
        }
    }
}