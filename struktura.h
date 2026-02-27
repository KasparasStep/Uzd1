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

// paliktas tik vektorinis variantas
struct Studentas {
    string vardas, pavarde;
    vector<int> paz;
    int egz;
    double gal_vid;
    double gal_med;
};


// Prototipai
int gautiSkaiciu(string info, int min, int max);

int skaitytiIsFailo(const string& failoVardas, vector<Studentas>& studentai);

string genVarda();
string genPavarde(string vardas);

void genPazymius(vector<int>& paz, int& egz); // vektoriui

void vykdytiVector();

double skaiciuotiVidurki(const vector<int>& paz); //uztenka suskaiciuoti ir nereikia kopijuoti
double skaiciuotiMediana(vector<int> paz); //reikia rusiuoti, tai perduodam be const
