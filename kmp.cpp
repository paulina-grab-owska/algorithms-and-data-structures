#include <iostream>
#include <vector>

using namespace std;

//funkcja pomocnicza do obliczania tablicy najdłuższych prefiksów-sufiksów (LPS)
//gdzie zacząć porównywać wzorzec z tekstem w przypadku niezgodności
void LPS(const string& pattern, vector<int>& lps) {
    int len = 0;  //długość aktualnego prefiksu-sufiksu

    //pierwszy element zawsze 0, bo prefiks o długości 1 nie może być sufiksem
    lps[0] = 0;

    int i = 1;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}


void KMP(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    //tablica najdłuższych prefiksów-sufiksów (LPS)
    vector<int> lps(m, 0);
    LPS(pattern, lps);

    int i = 0;  //indeks dla tekstu
    int j = 0;  //indeks dla wzorca

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            //znaleziono wzorzec, wypisz indeks początkowy
            cout << "znaleziono wzorzec na indeksie " << i - j + 1 << endl;
            j = lps[j - 1];
        } 
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text, pattern;

    cout << "podaj tekst: ";
    getline(cin, text);

    cout << "podaj wzorzec: ";
    getline(cin, pattern);

    KMP(text, pattern);

    return 0;
}



