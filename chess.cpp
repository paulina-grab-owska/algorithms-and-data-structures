#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node {                           //zawartość jednego węzła (node)
    string name;
    string surname;
    string country;
    int points;
    int year;
    node* next;
};


// FUNCJE UŻYTKU GLOBALNEGO 
void Pointer(node*& head, string Name, string Surname, string Country, int Points, int Year) {
    node* helper = new node;

    helper->name = Name;
    helper->surname = Surname;
    helper->country = Country;
    helper->points = Points;
    helper->year = Year;
    helper->next = head;
    head = helper;
}


//FUNKCJE DO ZADANIA 1
node* f_task1(node* LIST, int rank) {
    node* x = LIST; node* rank_up = NULL;
    
    while (x != NULL) {
        if (x->points >= rank) { Pointer(rank_up, x->name, x->surname, x->country, x->points, x->year); 
        cout << "points: " << x->points << "; player: " << x->name << " " << x->surname << " (" << x->country << ") " << endl;
        }
        x = x->next;
    }
    return rank_up;
}


//FUNKCJE DO ZADANIA 2
node* f_task2(node* LIST) {
    node* national_champion = NULL; node* x1 = LIST;
    while (x1 != NULL) {
        node* x2 = national_champion;
        
        bool nationality = false;
        while (x2 != NULL) { 
            if (x2->country == x1->country) { nationality = true; break; }
            x2 = x2->next;
        } 
        if (nationality != false) { x1 = x1->next; continue; } 
        
        x2 = x1; node* champion = x1;
        while (x2 != NULL) {
            if (champion->points < x1->points){ champion = x1; }
            x2 = x2->next;
        }
        Pointer(national_champion, champion->name, champion->surname, champion->country, champion->points, champion->year);
        cout << "country: " << x1->country << "; player: " << x1->name << " " << x1->surname << " (" << x1->year << ") " << endl;
        x1 = x1->next;
    }
    return national_champion;
}


//FUNKCJE DO ZADANIA 3

void f_task3(node*& LIST) {
    node* bellow_30 = NULL;
    node* x2 = LIST;
    while (LIST != NULL && LIST->year <= 1993 && x2->next != NULL) {
        if (x2->next->year <= 1993) {
            node* x1 = x2->next; x2->next = x2->next->next;
            delete x1;
            continue;
        }
        Pointer(bellow_30, x2->name, x2->surname, x2->country, x2->points, x2->year); 
        cout << "year: " << x2->year << "; player: " << x2->name << " " << x2->surname << " (" << x2->country << ") " << endl;
        x2 = x2->next;
    }
}




//GŁÓWNA FUNKCJA
int main() {       
    
    //pobieranie danych z pliku
    fstream file;
    file.open("chess.txt", ios::in);
    string line;  
    
    if(!file.is_open()){ cout << "no data found" << endl; exit(0); }
    
    node* LIST = NULL;

    string name, surname, country, Ppoints, Pyear;

    int number = 0;
    while(!file.eof())
    {
        getline(file, surname, ' ' );
        getline(file, name, ' ' );
        getline(file, country, ' ' );
        getline(file, Ppoints, ' ' );
        getline(file, Pyear, '\n' );
        
        int points = stoi(Ppoints);
        int year = stoi(Pyear);
        
        Pointer(LIST, name, surname, country, points, year);
   
        number++;
    }
    
    
    file.close();
    
    cout << "the best 50 chess players according to FIDE ranking" << endl;
 
    // 1
    cout << "enter a number of rank points: ";
    int rank; cin >> rank;
    cout << "chess players that achieved the entered rank: " << endl; 
    f_task1(LIST, rank); 
    cout << endl << endl << endl << endl;
  
    
    // 2
    cout << "the list of the best players of their countries: " << endl;
    f_task2(LIST);
    cout << endl << endl << endl << endl;
    
   
    // 3
    cout << "the list of players under 30 years old: " << endl;
    f_task3(LIST);
    cout << endl << endl << endl << endl;


    return 0;
}


