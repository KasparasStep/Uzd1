CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall

# Visi keturi tikslai
TARGETS := Uzd1 vector list deque

.PHONY: all clean

all: $(TARGETS)

# ---- Uzd1 (pagrindinis projektas) ----
Uzd1: Uzd1.cpp vektorius.cpp testavimas.cpp funkcijos.cpp struktura.h
	$(CXX) $(CXXFLAGS) Uzd1.cpp vektorius.cpp testavimas.cpp funkcijos.cpp -o Uzd1

# ---- Tyrimo projektai ----
vector: vector.cpp funkcijos.cpp struktura.h
	$(CXX) $(CXXFLAGS) vector.cpp funkcijos.cpp -o vector

list: list.cpp funkcijos.cpp struktura.h
	$(CXX) $(CXXFLAGS) list.cpp funkcijos.cpp -o list

deque: deque.cpp funkcijos.cpp struktura.h
	$(CXX) $(CXXFLAGS) deque.cpp funkcijos.cpp -o deque

# Vykdomieji failai ištrinami, o ne .o — kompiliuojame vienu žingsniu
clean:
	rm -f $(TARGETS)
