#include <iostream>
#include <string>
#include <iomanip>              //do mierzenia czasu
#include <time.h>               //do mierzenia czasu
using namespace std;


//ALGORYTM NAIWNY
void naiwny(string& text, string& pattern) {
    int text_size = text.length();
    int pattern_size = pattern.length();

    for (int i = 0; i <= text_size - pattern_size; ++i) {           //iteracja po tekście
        int j;                                                      
        for (j = 0; j < pattern_size; ++j) {                        //porównywanie znaków wzorca z tekstem
            if (text[i + j] != pattern[j]) { break; }               //przerwanie pętli dla niezgodności
        }

        if (j == pattern_size) { cout << "  wzorzec znaleziono na miejscy nr: " << i << endl; }
    }
}



//ALGORYTM RABINA-KARPA
const int PRIME_BASE = 31;              //stała dla funkcji haszującej
const int MODULO = 1e9 + 9;             //limit, żeby nie wylecieć i nie stracić dokłądności

int licz_hasz(const string& s) {
    //nie udało się
}

//napisany na podstawie prezentacji prof. Szeligi
void rabinKarp(const string& pattern, const string& text) {
    int pattern_size = pattern.size();
    int text_size = text.size();

    int pattern_hasz = licz_hasz(pattern);
    int text_hasz = licz_hasz(text.substr(0, pattern_size));            //substr zwraca podciąg tekstu długości wzorca

    for (int i = 0; i <= text_size - pattern_size; ++i) {
        if (pattern_hasz == text_hasz) {
            if (pattern == text.substr(i, pattern_size)) {  cout << "  wzorzec znaleziono na miejscy nr: " << i << endl; }
        }
    
        
        if (i < text_size - pattern_size) {                             //obliczamy hasz dla kolejnego okan tekstu
            text_hasz = (text_hasz * PRIME_BASE % MODULO + text[i + pattern_size] - 'a' + 1 - (text[i] - 'a' + 1) + MODULO) % MODULO; 
            //uaktualniamy hasz usuwając poprzedni znak i dając nowy
        }
    }
}


int main() {
    string text, pattern;
    
    clock_t start1, start2;
    clock_t stop1, stop2;
    double czas1, czas2;

    cout << "podaj tekst: ";
    getline(cin, text);
    cout << "podaj wzorzec: ";
    getline(cin, pattern);

    cout << "algorytm naiwny: " << endl;
    start1 = clock();
    naiwny(text, pattern);
    stop1 = clock();
    czas1 = (double)(stop1-start1) / CLOCKS_PER_SEC;
    cout << "   czas wykonania: " << czas1 << endl << endl;
  
    cout << "algorytm rabina-karpa: " << endl;
    start2 = clock();
    rabinKarp(text, pattern);
    stop2 = clock();
    czas2 = (double)(stop2-start2) / CLOCKS_PER_SEC;
    cout << "   czas wykonania: " << czas2 << endl << endl;







    return 0;
}
