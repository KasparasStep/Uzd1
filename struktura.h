#pragma once
// struktura.h
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <limits>
#include <fstream>
#include <sstream>
#include <list>
#include <deque>
#include <iterator>


//using outline
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::left;
using std::right;
using std::setw;
using std::endl;
using std::sort;
using std::fixed;
using std::setprecision;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::cerr;
using std::stringstream;
using std::move;
using std::ostream;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::numeric_limits;
using std::mt19937;
using std::chrono::steady_clock;
using std::invalid_argument;
using std::out_of_range;
using std::exception;
using std::runtime_error;
using std::streamsize;
using std::to_string;
using std::mt19937;
using std::pair;


// paliktas tik vektorinis variantas
struct Studentas {
    string vardas, pavarde;
    vector<int> paz;
    int egz;
    double gal_vid;
    double gal_med;
};

// Funkcijų prototipai
template <typename Container>
void skaitytiIsFailo_T(const string& failas, Container& grupe, int metodas) {
    ifstream in(failas);
    if (!in) { cout << "Failas nerastas: " << failas << "\n"; return; }

    string line;
    getline(in, line); // Praleidžiame antraštę

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
            grupe.push_back(std::move(st)); // push_back tinka visiems trims tipams
        }
    }
}

int gautiSkaiciu(string info, int min, int max);
string genVarda();
string genPavarde(string vardas);
void genPazymius(vector<int>& paz, int& egz);

double skaiciuotiVidurki(const vector<int>& paz);
double skaiciuotiMediana(vector<int> paz);
void apskaiciuotiPagalMetoda(Studentas& st, int metodas);

//void skaitytiIsFailo(const string& failas, vector<Studentas>& grupe, int metodas);
void spausdintiRezultatus(const vector<Studentas>& grupe, int rodyti, const string& failas);
void vykdytiVector();

void genFaila(const string& failas, int kiek);
//void splitStudents(const vector<Studentas>& visi, vector<Studentas>& kieti,
//	vector <Studentas>& tiniginiai, int metodas);

void test1();
void test2(const string& failas, int metodas);


// STRATEGIJA 1

template <typename Container>
void split_Strategy1(const Container& visi, Container& kieti, Container& tinginiai, int metodas) {
    auto galutinis = [&](const Studentas& st) { return (metodas == 2) ? st.gal_med : st.gal_vid; };

    std::copy_if(visi.begin(), visi.end(), std::back_inserter(kieti), [&](const Studentas& st) { return galutinis(st) >= 5.0; });
    std::copy_if(visi.begin(), visi.end(), std::back_inserter(tinginiai), [&](const Studentas& st) { return galutinis(st) < 5.0; });
}

// STRATEGIJA 3 (std::vector ir std::deque)
// Naudoja partition ir erase

template <typename Container>
void split_Strategy3_VD(Container& visi, Container& tinginiai, int metodas) {
    auto galutinis = [&](const Studentas& st) { return (metodas == 2) ? st.gal_med : st.gal_vid; };

    // stable_partition sustumia visus kietus į priekį, o tinginius į galą.
    // 'it' yra riba, nuo kurios prasideda tinginiai.
    auto it = std::stable_partition(visi.begin(), visi.end(), [&](const Studentas& st) { return galutinis(st) >= 5.0; });

    // Perkeliam tinginius į naują konteinerį greituoju (move) būdu
    tinginiai.insert(tinginiai.end(), std::make_move_iterator(it), std::make_move_iterator(visi.end()));

    // Ištriname tinginius iš originalaus konteinerio (jame lieka tik kieti)
    visi.erase(it, visi.end());
}