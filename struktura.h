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
using std::list;
using std::deque;


// paliktas tik vektorinis variantas
struct Studentas {
    string vardas, pavarde;
    vector<int> paz;
    int egz;
    double gal_vid;
    double gal_med;
};

// Funkcijų prototipai
int gautiSkaiciu(string info, int min, int max);
string genVarda();
string genPavarde(string vardas);
void genPazymius(vector<int>& paz, int& egz);

double skaiciuotiVidurki(const vector<int>& paz);
double skaiciuotiMediana(vector<int> paz);
void apskaiciuotiPagalMetoda(Studentas& st, int metodas);

void skaitytiIsFailo(const string& failas, vector<Studentas>& grupe, int metodas);
void spausdintiRezultatus(const vector<Studentas>& grupe, int rodyti, const string& failas);
void vykdytiVector();

void genFaila(const string& failas, int kiek);
void splitStudents(const vector<Studentas>& visi, vector<Studentas>& kieti,
	vector <Studentas>& tiniginiai, int metodas);

void test1();
void test2(const string& failas, int metodas);

void skaitytiVector(string failas, vector<Studentas>& grupe, int metodas);
void skaitytiList(string failas, list<Studentas>& grupe, int metodas);
void skaitytiDeque(string failas, deque<Studentas>& grupe, int metodas);

void skirstytiVector(const vector<Studentas>& visi, vector<Studentas>& kieti, vector<Studentas>& tinginiai);
void skirstytiList(const list<Studentas>& visi, list<Studentas>& kieti, list<Studentas>& tinginiai);
void skirstytiDeque(const deque<Studentas>& visi, deque<Studentas>& kieti, deque<Studentas>& tinginiai);