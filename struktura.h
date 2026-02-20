#pragma once
#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::left;
using std::right;
using std::setw;
using std::endl;

// Struct vektoriu versijai
struct StudentasVector {
    std::string vardas, pavarde;
    std::vector<int> paz;
    int egz;
    double rez;
};

// Struct masyvo versijai
struct StudentasArray {
    std::string vardas, pavarde;
    int* paz;
    int kiekis;
    int egz;
    double rez;
};

// Prototipai
void vykdytiVectorVersija();
void vykdytiArrayVersija();
double skaiciuotiGalutini(double vidurkis_ar_mediana, int egz);
