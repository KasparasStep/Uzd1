#include "struktura.h"
string genVarda() {
    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    string vardai[] = { "Jonas", "Petras", "Simas", "Povilas", "Mykolas", "Tomas", "Dovydas", "Matas", "Lukas", "Rokas",
                        "Evelina", "Gabija", "Ieva", "Greta", "Sandra", "Egle", "Viktorija", "Kamile", "Vilte", "Vejune" };
    return vardai[mt() % 20];
}

string genPavarde(string vardas) {
    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    string Vpavardes[] = { "Kazlauskas", "Jankauskas", "Petrauskas", "Stankevicius", "Vasiliauskas", "Butkus", "Zukauskas", "Paulauskas", "Urbonas", "Kavaliauskas" };
    string Mpavardes[] = { "Kazlauskaite", "Jankauskaite", "Petrauskaite", "Stankeviciute", "Vasiliauskaite", "Butkute", "Zukauskaite", "Paulauskaite", "Urbonaite", "Kavaliauskaite" };
    if (!vardas.empty() && vardas.back() == 's') {
        return Vpavardes[mt() % 10];
    }
    return Mpavardes[mt() % 10];
}
// klaidu valymas
int gautiSkaiciu(string info, int min, int max) {
    int sk;
    while (true) {
        cout << info;
        try {
            // 1. Bandome nuskaityti skaičių
            if (!(cin >> sk)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Ivestas ne skaicius!");
            }

            // 2. TIKRINIMAS: Ar po skaičiaus seka nepageidaujami simboliai (pvz. taškas ar kablelis)?
            // cin.peek() pažiūri į kitą simbolį buferyje
            if (cin.peek() != '\n' && cin.peek() != ' ' && cin.peek() != '\t' && cin.peek() != EOF) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Skaicius negali tureti kablelio ar papildomu simboliu!");
            }

            // 3. Diapazono tikrinimas
            if (sk < min || sk > max) {
                throw out_of_range("Tokio pasirinkimo nera!");
            }

            // Viskas gerai - išvalome buferį iki galo ir grąžiname reikšmę
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return sk;

        }
        catch (const exception& e) {
            cout << "Klaida: " << e.what() << " Bandykite dar karta.\n";
        }
    }
}