#include <iostream>
using namespace std;

struct node {
	int val;
	node* next;
};

//------------------------------------------funkcja wypisująca----------------------------------------------------
void show(node* H) {
	cout << "h -> ";
	if (H != NULL) {                            //jeśli wgl jakaś lista jest
		node* p = H;                            //ustawiamy wskaźnik pomocniczy, który będzie chodził
		while ( p != NULL ) {					//dopóki wskaźnik pomocniczy nie trafi na koniec listy
			cout << p->val << " -> ";            //można zrobić też pętlą do{} while(p->next !=NULL)
			p = p->next;                        //przesuń wskaźnik pomocniczy
		}
	}
	cout << "NULL" << endl << endl;
}


//-----------------------------------dodanie wskaźnika przed header---------------------------------------------
void AddH(node* &H, int x) {				//H->NULL
	node* p = new node;						//stworzenie nowego wskaźnika - rezerwacja pamięci
	p->val = x;								//nadanie wartości
	p->next = H;				            //przesunięcie H o jedno dalej - p nowy header
	H = p;						            //cofnięcie headera o jedno w tył
}


//---------------------------------------usuwanie elementów---------------------------------------------------

//usuwanie elementu za header
void DelH(node* &H) {						//H jest wskaźnikiem na pierwszy obiekt w liście
	if (H != NULL) {
		node* p = H;
		H = p->next;						//H = H->next; przesunięcie headera, p nowy header
		delete p;                           //usunięcie elementu przed headerem
	}

}

//usuwanie elementu z końca listy
void DelEND(node* &H) {
	if (H != NULL) {
		if(H->next == NULL) {	            //czy mamy tylko jeden element?
			DelH(H);                        // jak tak - to jest on jednocześnie pierwy i ostatni więc usuń
		}

		else {
			node* p = H;
			while (p->next->next != NULL)  {    //dopóki nie mamy końca za dwa pola, przesuń wskażnik
			    p = p->next;  
			}
			DelH(p->next);                      //jeśli za dwa pola koniec, to usuń następne
			
		}
	}
}



//-------------------------------------ZAMIANA MIEJSCAMI ELEMENTÓW LISTY----------------------------------------

//zamiana pierwszego z drugim elementem
void ChangeOrder1(node*& H) {
	node* p = H;
	H = p->next;                            // lub H=H->next
	p->next = p->next->next;                //wtedy następny jest równy temu za dwa
	H->next = p;
}

//zamiana elementów w środku - zamiana elementu x z następnikiem
void ChangeOrder2(node*& H, int x) {

	node* p = H;
	while (p->next != NULL && p->next->val != x) {  p = p->next; }       //dopóki nie ma końca listy i wartość nie jest szukana przesuwaj	p = p->next;

    if (p->next != NULL && p->next->next != NULL) {         //jeśli istnieje ten węzeł x i jego następnik to
	    node* e = p->next;                                  //utówrz pomocniczy wskaźnik
		p->next = e->next;                                  //ustaw je na to samo pole
		e->next = p->next->next;                            //przesuń
		p->next->next = e;                                  //zamień wartości
	}
	
}



//jedna funkcja, bez rozważania dwóch przypdaków
void ChangeOrder00(node*& H, int x) {

	AddH(H, 0);                                             //dodajemy na początek pomocnicze pole

	node* p = H->next;			                            //tu zmiana (bo mamy pomocnicze pole)
	while (p->next != NULL && p->next->val != x) {          //dopóki istnieje następny element i jest różny od x przesuwaj
		p = p->next;
	}

		if (p->next != NULL && p->next->next != NULL) {     //jak wyżej - pozbywliśmy się tutaj pierwszej syutyacji 
			node* e = p->next;                              //(zamiana pierwszego elementu z drugim)
			p->next = e->next;                              //bo dodaliśmy pomocnicze pole
			e->next = p->next->next;                        //jak wyżej
			p->next->next = e;
		}

	DelH(H);                                                //usuwamy pomocnicze pole
}


//------------------------------------------DZIELENIE LISTY------------------------------------------------

void split(node*& H, node*& H1, node*& H2) {	//H!=NULL; H1=H2=NULL ----> H=NULL; H1&H2 mają po 1/2 H

	int size = 0;                   //sprawdzamy rozmiar, bo będziemy dzielić na dwie częście
	node* p = H;
	while (p != NULL) {
		p = p->next;
		size++;
	}

	size = size / 2;            //dzielimy otrzymany rozmiar na dwa, bo dwie listy
	p = H;                      //musimy znowy przyrównać p do H, bo w pętli warunek się zgubił

	for(int i = 1; i < size; i++) {     //dopóki nie dojdziesz do połowy size przesuwaj
		p = p->next;
	}

	H1 = H;                         //to co przeszliśmy do jest nowa lista
	H = NULL;                       //zerujemy H, bo tej listy ma już nie być
	H2 = p->next;                   //H2 to jest druga lista, która zaczyna się tam, gdzie H1 się skończyło
	p->next = NULL;                 //zerujemy p->next, bo on nie jest już potrzebny na nowych listach


}

//------------------------------------------ŁĄCZENIE LIST----------------------------------------------

//funkcja łącząca dwie listy sotując jej wartości parami

void merge(node*& H, node*& H1, node*& H2) {    //zakładamy, że wartości na tych funkcjach są posortowane - bez tego założenia lepiej byłoby najpierw scalić listy i ją potem posortować

    while (H1 != NULL && H2 != NULL) {   //dopóki chociaż jedna lista się nie wyczerpie
        if (H1->val > H2->val) {        //wybierz większą
            AddH(H, H1->val);           //dodaj ją do H - ta funkcja wraz z sukcesywnym dodawaniem
            H1 = H1->next;              //spycha następne w stronę końca listy
        } 
        else {
            AddH(H, H2->val);
            H2 = H2->next;
        }
    }

    while (H1 != NULL ) {               //te dwie ostatnie pętle służą do dodania pozostałych elementów
        AddH(H, H1->val);               //jeśli wprowadzone listy nie mają takiej samej ilości elementów
        H1 = H1->next;
    }

    while (H2 != NULL) {
        AddH(H, H2->val);
        H2 = H2->next;
    }


}



//---------------------------------------------ZADANIA--------------------------------------------------

// Zadanie 1: Usuń co drugi element z listy 
void DelHx2(node*& H) {
	if (H != NULL && H->next != NULL) {				//czy lista nie jest pusta i ma conajmniej dwa elementy
		node* p = H;
		 
		while (p != NULL && p->next !=NULL)  {      //jeśli nie mamy NULLa teraz, ani na następnym
            DelH(p->next);                          //to usuń następny
            p = p->next;                            //i przenieś wskaźnik na ten za 2 (czyli teraz już następny)
        }
		
	}

}

// Zadanie 2: Zamień element o wartości x z następnikiem - ZDEFINIOWANA WYŻEJ
/*
void ChangeOrder2(node*& H, int x) {

	node* p = H;
	while (p->next != NULL && p->next->val != x) { p = p->next;}

	if (p->next != NULL && p->next->next != NULL) {
		node* e = p->next;
		p->next = e->next;
		e->next = p->next->next;
		p->next->next = e;
	}

}
*/

// Zadanie 3: Usuń elementy parzyste z listy
void DelHZ2(node*& H){
    node* p = H;
    node* e = H;
  
    while(H != NULL && H->val % 2 == 0) {        //jeśli mamy parzystą wartość na początku listy   
        p = H;                                  //tworzymy wskaźnik pomocniczy na header, który będziemy usuwać
        H = H->next;                            //przesuwamy header
        delete p;
    }
    
    p = H;                                      //w poprzedniej pętli warunek się zgubił

    while( p != NULL && p->next != NULL) {      //sprawdzamy, czy istnieje następnik
        if((p->next->val) % 2 == 0) {           //sprawdzamy główny warunek
        e = p->next;                            //nowa zmienna pomocnicza, którą usuniemy - przesuwamy żeby wskazywała na następny element
        p->next = e->next;                      
        delete e;
        }
        
        else { p = p->next; }                    //jak się nie dzieli, to przesuń
    }
    
 
    
    
    
}

// Zadanie 4: Zamień pierwszy element z ostatnim
void ChangeF_L(node*& H) {
    
    int size = 0;                //sprawdzamy rozmiar, bo jak nie ma co najmniej 2 elementów to nie zacyka
	node* p = H;
	while (p != NULL) {
		p = p->next;
		size++;
	}
    
    if(size < 2) { return; }        //jeśli za mało to nawet nie rób dalej
    
    node* e = H;                //wskaźnik na pierwszy
    node* g = H;                //wskaźnik na ostatni
    
    while (g->next != NULL) { g = g->next; }    //robimy g ostatnim wskaźnikiem
    
    swap(e->val, g->val);       //zamieniamy ich wartości
    
    
}




// Zadanie 5: Kopia listy H->1->2->3 na H->1->2->3->1->2->3 
void Kopia_1(node*& H) {
    
    if (H != NULL) {                        //DOBRZE JEST DAWAĆ TEN WARUNEK ZA KAŻDYM RAZEM
        node* e = H;
    
        while (e->next != NULL) e = e->next;                //dopóki pomocniczy się nie skończy, przesuwaj
    
        node* tail = e;                                     //ustaw tam nowy wskaźnik na koniec
        node* p = H;                                        //ustaw nowy wskaźnik na początek     

        while (p != NULL && p->next != NULL && tail->next != p) { //dopóki dwa następne elementy istnieją i trzeci warunek jest po to, żeby kopia się w dobrym miejscu pojawiała
            AddH(e->next, p->val);                               //dodaj do elementu następnego od końca wartość z p
            p = p->next;                                        //przesuń oba wskaźniki o 1 do przodu
            e = e->next;
        }
    }
}




// Zadanie 6: Kopia listy H->1->2->3 na H->1->1->2->2->3->3
void Kopia_2(node*& H) {
    if (H == NULL) { return; }                  // nie można skopiować pustej listy, dla formalności
  
    node *p = H;
    while (p != NULL) {                   
        node* e = new node;                     // tworzy nowy element z danymi - alokacja pamięci
        e->next = p->next;                      // ustawia wskaźnik next nowego elementu
        p->next = e;                            // dodaje nowy element za obecnym
        e->val = p->val;
        p = e->next;                            // przechodzi do następnego oryginalnego elementu
        
    }
    
}



// Zadanie 7: Kopia listy H->1->3->5 na H->1->3->3->3->5->5->5->5->5 
void Kopia_3(node*& H) {
    node* p = H;
    while (p != NULL) {                             //dopóki nie ma końca
        for (int i = 0; i < p->val - 1; i++) {      //to powtarzaj tą pętlę, tyle razy ile wartość p
            AddH(p->next, p->val);                  //korzystamy w funkcji add - do p->next dodajemy p->val i przesuwamy
            p = p->next;                            //przesuwamy dalej, żeby dodać
        }
        p = p->next;                                //przesuwamy dalej, żeby zmienić nazwę
    }
}



int main() {
	
	node* H = NULL;
	
	cout << "dodawnie wartości do listy: " << endl;
	AddH(H, 1);	AddH(H, 2);	AddH(H, 3);	AddH(H, 4);	AddH(H, 5);	AddH(H, 6);
	show(H);
	cout << endl << endl;
	
	cout << "usuwanie wartości z headera: " << endl;
	DelH(H);
	show(H);
	cout << endl << endl;
	
	cout << "usuwanie wartości z końca listy: " << endl;
	DelEND(H);
	show(H);
	cout << endl << endl;
	
	
	
	node* H1 = NULL;
	AddH(H1, 1); AddH(H1, 2); AddH(H1, 3); AddH(H1, 4);	AddH(H1, 5); AddH(H1, 6);
	
	cout << "zamiana elementów: " << endl;
	        show(H1);
	cout << "   zamiana pierwszego i drugeigo elementu: " << endl;
	        ChangeOrder1(H1);
	        show(H1);
	cout << "   zamiana elementu o wartości x (4) z następnikiem: " << endl;
	        ChangeOrder2(H1, 4);
	        show(H1);
	cout << "   zamiana elementu o wartości x (4) z następnikiem (z użyciem jednej fucnkji - bez rozważania dwóch przypadków): " << endl;
	        ChangeOrder00(H1, 4);
	        show(H1);
	cout << endl << endl;
	
	
	
	node* H2 = NULL;  AddH(H2, 1); AddH(H2, 2); AddH(H2, 3); AddH(H2, 4);	AddH(H2, 5); AddH(H2, 6);
	node* Ha = NULL; node* Hb = NULL;
	
	cout << "dzielenie jednej listy na dwie:  " << endl;
	    cout << "   lista wyjściowa: "; show(H2);
	    split(H2, Ha, Hb);
	    cout << "   lista wyjściowa po dzieleniu:  "; show(H2);
	    cout << "   lista a:  "; show(Ha);
	    cout << "   lista b:  "; show(Hb);
	cout << endl << endl;
	
	
	
	cout << "łączenie dwóch list:  " << endl;
	    cout << "   lista a:  "; show(Ha);
	    cout << "   lista b:  "; show(Hb);
	    cout << "   lista wynikowa:  "; show(H2);
	    cout << endl; 
	    merge(H2, Ha, Hb);
	    cout << "   lista a po łączeniu:  "; show(Ha);
	    cout << "   lista b po łączeniu  "; show(Hb);
	    cout << "   lista wynikowa po łączeniu:  "; show(H2);
	cout << endl << endl;
	
	
	
	node* H3 = NULL;  AddH(H3, 1); AddH(H3, 2); AddH(H3, 3); AddH(H3, 4);	AddH(H3, 5); AddH(H3, 6);
	
	cout <<"usuwanie co drugiego elemntu z listy:" << endl;
	    cout << "   lista wyjściowa:  "; show(H3); 
	    DelHx2(H3);
	    cout << "   lista po usuwaniu:  "; show(H3);
	cout << endl << endl;
	
	
	node* H4 = NULL;  AddH(H4, 1); AddH(H4, 2); AddH(H4, 3); AddH(H4, 4);	AddH(H4, 5); AddH(H4, 6);
	
	cout <<"usuwanie parzystych elementów z listy:" << endl;
	    cout << "   lista wyjściowa:  "; show(H4); 
	    DelHZ2(H4);
	    cout << "   lista po usuwaniu:  "; show(H4);
	cout << endl << endl;
	
	

	cout <<"zamiana pierwszego elementu z ostatnim:" << endl;
	    cout << "   lista wyjściowa:  "; show(H4); 
	    ChangeF_L(H4);
	    cout << "   lista po zamianie:  "; show(H4);
	cout << endl << endl;
	
	

	
	cout << "kopiowania:  " << endl;
	    node* H5 = NULL;  AddH(H5, 1); AddH(H5, 2); AddH(H5, 3); AddH(H5, 4);
	    cout << "       wg zasady  H->1->2->3 na H->1->2->3->1->2->3:" << endl;
	        cout << "       lista przed kopiowaniem:  "; show(H5);
	        Kopia_1(H5);
	        cout << "       lista po kopiowaniu:  "; show(H5);
	        cout << endl; 
	   
	   node* H6 = NULL;  AddH(H6, 1); AddH(H6, 2); AddH(H6, 3); AddH(H6, 4);
	   cout << "    wg zasady  H->1->2->3 na H->1->1->2->2->3->3:" << endl;
	        cout << "       lista przed kopiowaniem:  "; show(H6);
	        Kopia_2(H6);
	        cout << "       lista po kopiowaniu:  "; show(H6);
	        cout << endl; 
	        
	  node* H7 = NULL;  AddH(H7, 1); AddH(H7, 2); AddH(H7, 3); AddH(H7, 4);
	  cout << "wg zasady  H->1->3->5 na H->1->3->3->3->5->5->5->5->5 :" << endl;
	        cout << "   lista przed kopiowaniem:  "; show(H7);
	        Kopia_3(H7);
	        cout << "   lista po kopiowaniu:  "; show(H7);
	        cout << endl; 
	cout << endl << endl;

	

	
	return 0;
}






