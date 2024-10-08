#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;



//------------------------------MACIERZ SĄSIEDZCTWA (Z PLIKU)-------------------------------------
void macierz() {
    int** macierzz;

    fstream file("graf.txt");

    if (!file.is_open()) {
        cout << "nie można otworzyć pliku." << endl;
        exit(1);
    }

    int rozmiar;
    file >> rozmiar;
    
    macierzz = new int*[rozmiar];                          //alokacja pamięci dla macierzy
    for (int i = 0; i < rozmiar; ++i) {
        macierzz[i] = new int[rozmiar];
    }

  
    for (int i = 0; i < rozmiar; ++i) {                     //wczytanie danych z pliku do macierzy
        for (int j = 0; j < rozmiar; ++j) {
            file >> macierzz[i][j];
        }
    }


    cout << "wczytana macierz sąsiedztwa:" << endl;
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            cout << macierzz[i][j] << " ";
        }
        cout << endl;
    }


    file.close();

}



//----------------------------MACIERZ --> LISTA SĄSIEDZCTWA--------------------------------------
void macierz_do_listaS() {
    fstream file("graf.txt");

    if (!file.is_open()) {
        cout << "nie można otworzyć pliku." << endl;
        return;
    }

    int rozmiar;
    file >> rozmiar;

    vector<vector<pair<int, int>>> listaS(rozmiar); //element zewnętrznego wektora odpowiada jednemu wierzchołkowi grafu.

    int value;
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            file >> value;

            if (value != 0) {
                listaS[i].emplace_back(j, value);
            }
        }
    }

    file.close();

    // Wypisz listę sąsiedztwa
    for (int i = 0; i < rozmiar; ++i) {
        cout << i+1 << " -> ";
        for (const auto& cel : listaS[i]) {
            cout << cel.first + 1 << " / " << cel.second << " -> ";
        }
        cout << "NULL" << endl;
    }
}



//-------------------------LISTA SĄSIEDZCTWA --> LISTA KRAWĘDZI---------------------------
struct Krawedz {
    int start;
    int koniec;
    int odleglosc;
};

void listaS_do_listaK() {
    fstream file("graf.txt");

    if (!file.is_open()) {
        cout << "nie można otworzyć pliku." << endl;
        return;
    }

    int rozmiar;
    file >> rozmiar;

    vector<vector<pair<int, int>>> listaS(rozmiar);

    int value;
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            file >> value;

            if (value != 0) {
                listaS[i].emplace_back(j, value);
            }
        }
    }

    file.close();


    //konwercja listę sąsiedztwa na listę krawędzi
    vector<Krawedz> listaK;
    for (int i = 0; i < listaS.size(); ++i) {
        for (const auto& cel : listaS[i]) {
            Krawedz krawedz;                //tworzenie obiektu krawędzi i przypisanie mu wartości
            krawedz.start = i;
            krawedz.koniec = cel.first;
            krawedz.odleglosc = cel.second;

            listaK.push_back(krawedz);
        }
    }

    //wypisanie listę krawędzi
    for (const auto& krawedz : listaK) {
        cout << krawedz.start +1 << " -> " << krawedz.koniec +1 << " / " << krawedz.odleglosc << endl;
    }

}



//---------------------LISTA KRAWĘDZI --> LISTA SĄSIEDZCTWA---------------------------------
vector<Krawedz> macierz_do_listaK() {
    ifstream file("graf.txt");

    if (!file.is_open()) {
        cout << "nie można otworzyć pliku." << endl;
        return {};
    }

    int rozmiar;
    file >> rozmiar;

    vector<Krawedz> listaK;

    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            int value;
            file >> value;

            if (value != 0) {
                Krawedz krawedz;
                krawedz.start = i;
                krawedz.koniec = j;
                krawedz.odleglosc = value;
                listaK.push_back(krawedz);
            }
        }
    }

    file.close();

    return listaK;
}

void listaK_do_listaS(const vector<Krawedz>& listaK) {
    //znajdź liczbę wierzchołków
    int rozmiar = 0;
    for (const auto& krawedz : listaK) {
        rozmiar = max(rozmiar, max(krawedz.start, krawedz.koniec) + 1);
    }

    //inicjalizuj listę sąsiedztwa
    vector<vector<pair<int, int>>> listaS(rozmiar);

    //dodaj krawędzie do listy sąsiedztwa
    for (const auto& krawedz : listaK) {
        listaS[krawedz.start].emplace_back(krawedz.koniec, krawedz.odleglosc);
    }

    //wypisanie
    for (int i = 0; i < rozmiar; ++i) {
        cout << i +1 << " -> ";
        for (const auto& cel : listaS[i]) {
            cout << cel.first +1 << " / " << cel.second << " -> ";
        }
        cout << "NULL" << endl;
    }
}



int main() {
    

    //macierz();
    
    //macierz_do_listaS();
    
    //listaS_do_listaK();
    
    vector<Krawedz> listaK = macierz_do_listaK();
    listaK_do_listaS(listaK);

    return 0;
}

 
    
