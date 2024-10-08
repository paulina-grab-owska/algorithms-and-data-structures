/*
Dana jest tablica elementów reprezentujących elementy do budowy wierzy. Każdy element ma swoją wysokość h. 
Twoim celem jest sprawdzenie czy z danych elementów można zbudować T wierz tak by każda miała wysokość minimum K. Oczywiście każdy element może zostać użytu przy budowie tylko jeden raz
*/

#include <iostream>
#include <vector>
using namespace std;

bool canBuildTowers(vector<int>& elements, int K, int T) {
    if (T == 0) { return true; }

    for (int i = 0; i < elements.size(); i++) {
        if (elements[i] >= K) {                     
            int height = elements[i];
            elements.erase(elements.begin() + i);   // usuwamy element z tablicy, żeby nie użyć go ponownie

            // rekurencyjnie próbujemy zbudować resztę wież
            if (canBuildTowers(elements, K, T-1)) {  return true; }
               
            // jeśli nie udało się zbudować wieży, dodajemy element z powrotem do tablicy
            elements.insert(elements.begin() + i, height);
        }
    }

    // nie udało się zbudować
    return false; 
}

int main() {
    vector<int> elements1 = {2, 3, 5, 6, 8, 10, 12};
    vector<int> elements2 = {1, 3, 5, 7, 9, 10, 11};
    int K1 = 6, K2 = 5;
    int T1 = 3, T2 = 10;

    cout << endl << "w przypadku 1:" << endl;
        if (canBuildTowers(elements1, K1, T1)) { cout << "  idzie zbudować " << T1 << " wieże o wysokości co najmniej " << K1 << endl; }
        else { cout << "    nie idzie zbudować " << T1 << " wież o wysokości co najmniej " << K1 << endl; }
        
    cout << endl << "w przypadku 2:" << endl; 
        if (canBuildTowers(elements2, K2, T2)) { cout << "  idzie zbudować " << T2 << " wieże o wysokości co najmniej " << K2 << endl; }
        else { cout << "    nie idzie zbudować " << T2 << " wież o wysokości co najmniej " << K2 << endl; }

    return 0;
}
