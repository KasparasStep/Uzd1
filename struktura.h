#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

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

// Struct vektoriu versijai
struct StudentasVector {
    string vardas, pavarde;
    vector<int> paz;
    int egz;
    double rez;
};

// Struct masyvo versijai
struct StudentasArray {
    string vardas, pavarde;
    int* paz = nullptr;
    int kiekis = 0;
    int egz;
    double rez;
};

// Prototipai
int gautiSkaiciu(string info, int min = 1, int max = 10);

void vykdytiVector();
void vykdytiArray();

double skaiciuotiGalutini(vector<int> v, int egz, int metodas);
double skaiciuotiGalutini(int* arr, int n, int egz, int metodas);
