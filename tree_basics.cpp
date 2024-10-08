#include <iostream>
using namespace std;


//////////////////////////////////////////////////DRZEWA BST/////////////////////////////////////////////////////

struct node {
	int val;
	node* P;	        //rodzic
	node* L;	        //lewe poddrzewo  
	node* R;	        //prawe poddrzewo  
};


//----------------------------------------------------------FUNKCJA WSTAWIAJĄCA------------------------------
void insert(node*& root, int x, node* parent = NULL) {
	if (root == NULL) {
		node* t = new node;
		t->val = x;
		t->L = NULL;
		t->R = NULL;
		t->P = parent;
		root = t;
	}
	else {
		if (x >= root->val) { insert(root->R, x, root); }

		else insert(root->L, x, root);
	}
}

//--------------------------------------------FUNKCJE WYPISUJĄCO-SORTUJĄCE----------------------------------------

//inorder - wypisuje wartości od najmniejszej do największej
void inorder(struct node* start){
	if (start->L != NULL) inorder(start->L);
	cout << start->val << "  ";

	if (start->R != NULL) inorder(start->R);
}

//preorder - najpierw korzeń poddrzewa, a następnie kolejno lewe i prawe poddrzewa. 
void preorder(struct node* start) {
    if (start != NULL) {
        cout << start->val << " ";
        
        preorder(start->L);                     //rekurencyjnie odwiedź lewe poddrzewo
        preorder(start->R);                     //rekurencyjnie odwiedź prawe poddrzewo
    }
}

//postorder
void postorder(struct node* start) {
    if (start != NULL) {
        postorder(start->L);                    //rekurencyjnie odwiedź lewe poddrzewo
        postorder(start->R);                    //rekurencyjnie odwiedź prawe poddrzewo
        
        cout << start->val << "  ";
    }
}


//------------------------------FUNKCJE SZUKAJĄCE NAJWIĘKSZEJ I NAJMNIEJSZEJ WARTOŚCI W DRZEWIE-----------------   

//najmniejsza
struct node* min(struct node* start) {                       //przechodzenie w lewo -> doście do najmniejszej wartości
	while (start->L != NULL)                       //sprawdzenie, czy lewe poddrzewo jest puste
	    { start = start->L;}                        //zwrócenie najmniejszej wartości
	return start;
}

//największa
struct node* max(struct node* start) {                       //przechodzenie w prawo -> doście do największej wartości
	while (start->R != NULL)                       //sprawdzenie, czy prawe poddrzewo jest puste
	    {start = start->R;}                         //zwrócenie największej wartości
	return start;                     
}


//---------------------------------NASTĘPNIK I POPRZEDNIK-----------------------------------------------

//następnik
struct node* after(node* root, node* noode) {       //noode to węzeł wyjściowy dla którego szukamy
    if (noode == NULL) return 0;

    node* after = NULL;

    while (root != NULL) {
        if (noode->val < root->val) {               //jeśli wartość węzła jest mniejsza, idź w lewo
            after = root;
            root = root->L;
        }
        else if (noode->val > root->val) {          //jeśli wartość węzła jest większa, idź w prawo
            root = root->R;
        }
        else {                                      //jeśli wartość węzła jest równa, znajdź następnik
            if (noode->R != NULL) {
                after = noode->R;
                while (after->L != NULL)
                    after = after->L;
            }
            break;
        }
    }

    return after;                                   //zwrócenie następnika
}

//poprzednik  
struct node* before(node* root, node* noode) {     //noode to węzeł wyjściowy
    if (noode == NULL) return 0;                 //sprawdzenie, czy węzeł nie istnieje

    node* before = NULL;

    while (root != NULL) {
        if (noode->val < root->val) {           //jeśli wartość węzła jest mniejsza, idź w lewo
            root = root->L;
        }
        else if (noode->val > root->val) {      //jeśli wartość węzła jest większa, idź w prawo
            before = root;
            root = root->R;
        }
        else {                                  //jeśli wartość węzła jest równa, znajdź poprzednika
            if (noode->L != NULL) {
                before = noode->L;
                while (before->R != NULL)
                    before = before->R;
            }
            break;
        }
    }   
    return before;                                  //zwrócenie poprzednika
}

//---------------------------USUWANIE ELEMENTU----------------------------------------------    

struct node* removee(node* root, int x) {
    if (root == NULL) { return root; }

    if (x < root->val) {  root->L = removee(root->L, x); }   //szukanie elementu do usunięcia w obu poddrzewach
    else if (x > root->val) { root->R = removee(root->R, x); } 
    else {
        
        //1: bez dzieci lub z jednym dzieckiem
        if (root->L == NULL) {
            node* p = root->R;
            delete root;
            return p;
        } 
        else if (root->R == NULL) {
            node* p = root->L;
            delete root;
            return p;
        }

        //2:dwoje dzieci
        node* p = min(root->R);  //najmniejszy element w prawym poddrzewie

        root->val = p->val; //skopiuj zawartość

        root->R = removee(root->R, p->val); //usuń najmnieszy element
    }
    return root;
}


//-------------------------------------------------ROTACJE-------------------------------------------

//rotacja pojedyncza
struct node* rot_L(node* &root, node* noode){
   
    node* y = noode->R;                                         //zapisanie wskaźników
    noode->R = y->L;                                            //aktualizacja wskaźników
    
    if (y->L != NULL) { y->L->P = noode; }
    
    y->P = noode->P;                                        //przypisanie rodziców
    
    if (noode->P == nullptr) {   root = y; }                //aktualizacja korzenia (jeśli to akurat był korzeń)
    else if (noode == noode->P->L) { noode->P->L = y;} 
    else {  noode->P->R = y;}
    
    y->L = noode;                                           //przeniesienie na lewe poddrzewo
    noode->P = y;
    return root;
    
}

struct node* rot_R(node* &root, node* noode){                   //jak wyżej, tylko na prawo
   
    node* y = noode->L;                                        
    noode->L = y->R;                                            
    
    if (y->R != NULL) { y->R->P = noode; }
    
    y->P = noode->P;                                       
    
    if (noode->P == nullptr) {   root = y; }               
    else if (noode == noode->P->R) { noode->P->R = y;} 
    else {  noode->P->L = y;}
    
    y->R = noode;                                          
    noode->P = y;
    return root;
    
}



////////////////////////////////////////DRZEWA AVL//////////////////////////////////////////

struct AVLNode
{
  AVLNode * P;
  AVLNode * L;
  AVLNode * R;
  int key;                                  //bilansss
  int val;
};

//-------------------------------------------funkcje pomocnicze------------------------

//obliczanie wysokości węzła
int wysokosc(AVLNode* node) {
    return (node != NULL) ? node->key : 0;       //warunek ? dla prawdy : dla fałszu;
}

//oblczanie różnicy wysokości poddrzew prawo lewo
int roznica_wyskosci(AVLNode* node) {
    return (node != NULL) ? wysokosc(node->L) - wysokosc(node->R) : 0;
}

//aktualizacja wysokośc węzła
void aktualizuj_wysokosc(AVLNode* node) {
    if (node != NULL) {
        node->key = 1 + max(wysokosc(node->L), wysokosc(node->R));
    }
}

//preorder
void preorderAVL(AVLNode* root) {
    if (root != NULL) {
        cout << root->val << " ";
        
        preorderAVL(root->L);                     
        preorderAVL(root->R);                    
    }
}

//minimum
struct AVLNode* minAVL(struct AVLNode* root) {                      
	while (root->L != NULL)                       
	    { root = root->L;}                        
	return root;
}


//-------------------------------------rotacje--------------------------------------------------

//R
struct AVLNode* R(AVLNode* root, AVLNode* noode) {
    AVLNode* y = noode->L;
    noode->L = y->R;
    y->R = noode;

    aktualizuj_wysokosc(noode);
    aktualizuj_wysokosc(y);

    return y; 
}

//L
struct AVLNode* L(AVLNode* root, AVLNode* noode) {
    AVLNode* y = noode->R;
    noode->R = y->L;
    y->L = noode;

    aktualizuj_wysokosc(noode);
    aktualizuj_wysokosc(y);

    return y; 
}

//RL 
struct AVLNode* RL(AVLNode* &node, AVLNode* noode){
    R(node, noode);
    L(node, noode);
}

//LR 
struct AVLNode* LR(AVLNode* &node, AVLNode* noode){
    L(node, noode);
    R(node, noode);
}


//--------------------------------------funkcja wstawiająca--------------------------------------- 

struct AVLNode* insertAVL(AVLNode* root, int key) {
    //1: po prostu wstawiamy
    if (root == NULL) {  return root; }

    if (key < root->val) { root->L = insertAVL(root->L, key); } 
    else if (key > root->val) { root->R = insertAVL(root->R, key); } 
    else{  return root;  }

    //2: aktualizacja
    aktualizuj_wysokosc(root);

    //3: sprawdzanie zrównoważenia drzewa
    int bilanss = roznica_wyskosci(root);

    //jeśli coś nie styka to robimy tak:

    //dla L i LR
    if (bilanss > 1) {
        if (key < root->L->val) { return R(root, root->L);  }       //lewe poddrzewo, lewy potomek
        else { return LR(root, root->L); }                        //lewe podrzewo, prawy potomek
    }

    //dla R i RL
    if (bilanss < -1) {
        if (key > root->R->val) { return R(root, root->R); }    //prawe poddrzwo, prawy potomek
        else {  return RL(root, root->R); }                     //prawe poddrzewo, lewy potomek
    }

    return root; 
}

//-------------------------------------funkcja usuwająca------------------------

AVLNode* removeeAVL(AVLNode* root, int key) {
    //1: usuwamy - bardzo analogiczne do wstawiania
    if (root == NULL) {return root; }

    if (key < root->val) { root->L = removeeAVL(root->L, key); } 
    else if (key > root->val) { root->R = removeeAVL(root->R, key); } 
    else {                                                                           //delikwent znaleziony
        //0/1 dzieci
        if (root->L == NULL || root->R == NULL) {
            AVLNode* p = (root->L != NULL) ? root->L : root->R;

            //bezdzietny
            if (p == NULL) {
                p = root;
                root = NULL;
            } 
            //jedno
            else { *root = *p; }                                                //kopiuje do węzła

            delete p;
        } 
        
        //2 dzieci
        else { 
            AVLNode* p = minAVL(root->R);                   //najmniejszy węzeł w prawym poddrzewie
            root->val = p->val;                             //kopiuj val do mniejszego
            root->R = removeeAVL(root->R, p->val);   
        }
    }

    
    //2: aktualizacja wysokości
    aktualizuj_wysokosc(root);

    //3: współczynnika równoważenia węzła i robimy tak, jak przy wstawianiu
    int bilanss = roznica_wyskosci(root);

    //dla L i LR
    if (bilanss > 1) {
        if (roznica_wyskosci(root->L) >= 0) { return L(root, root->L); } 
        else {return LR(root, root->L); }
    }

    //dla R i RL
    if (bilanss < -1) {
        if (roznica_wyskosci(root->R) <= 0) { return R(root, root->R);} 
        else {  return RL(root, root->R); }
    }

    return root; 
}


//------------------------------------------MAIN---------------------------------------
int main()
{
	node* T = NULL;
	
	cout << "DRZEWA BST" << endl << endl;
	
	//funkcja wstawiająca
	insert(T, 20); insert(T, 3); insert(T, 10); insert(T, 40); insert(T, 30);
	insert(T, 25); insert(T, 5); insert(T, 8); insert(T, 50); insert(T, 60);

    //funkcje sortujące
	cout << "funkcje sortujące:" << endl;
	cout << "   inorder: "; inorder(T); 	cout << endl;
	cout << "   preorder: "; preorder(T); 	cout << endl;
	cout << "   postorder: "; postorder(T); 	cout << endl << endl << endl;
	

    //szukanie najmnijeszej i największej wartości
    cout << "szukanie skrajnych wartości: " << endl;
	cout << "   najmniejsza wartość: " << min(T) << endl;
	cout << "   największa wartość: " << max(T) << endl << endl << endl;
	
	
	//szuaknie następnika
	cout << "szukanie następnika: " << endl;
	node* J1 = after(T, T);
	cout << "   dla wartości 20 (T): " << J1->val << endl;
	node* J2 = after(T, T->L);
	cout << "   dla wartości 3 (T->L): " << J2->val << endl;
	node* J3 = after(T, T->R);
	cout << "   dla wartości 40 (T->R): " << J3->val << endl << endl;
	
	//szukanie poprzednika
	cout << "szukanie poprzednika: " << endl;
	node* K1 = before(T, T);
	cout << "   dla wartości 20 (T): " << K1->val << endl;
	node* K2 = before(T, T->L->R);
	cout << "   dla wartości 10 (T->L->R): " << K2->val << endl;
	node* K3 = before(T, T->R);
	cout << "   dla wartości 40 (T->R): " << K3->val << endl << endl << endl;
	
	
	//usuwanie dowolnej wartości
	cout << "usuwanie dowolnej wartości na drzewie: " << endl;
	cout << "   usunięcie wartości 5 (T->L->R->L): " << endl; removee(T, 5); 
	cout << "       drzewo w preorder po usunięciu: "; preorder(T); 	cout << endl;
	cout << "   usunięcie wartości 30 (T->R->L->R): "<< endl; removee(T, 30);
	cout << "       drzewo w preorder po usunięciu: "; preorder(T); 	cout << endl << endl << endl;


    node* T1 = NULL;
    insert(T1, 20); insert(T1, 3); insert(T1, 10); insert(T1, 40); insert(T1, 30);
	insert(T1, 25); insert(T1, 5); insert(T1, 8); insert(T1, 50); insert(T1, 60);
    
	//rotacje
	cout << "rotacje pojedyncze: " << endl;
	cout << "   drzewo przed rotacją (wg funkcji preorder): "; preorder(T1); 	cout << endl;
	cout << "       na lewo: "; rot_L(T1, T1->L); preorder(T1); cout << endl;
	cout << "       na prawo: "; rot_R(T1, T1->R); preorder(T1); cout << endl << endl << endl;
	
	cout << "DRZEWA AVL" << endl << endl;
	
	AVLNode* T2 = NULL;
	insertAVL(T2, 20); insertAVL(T2, 3); insertAVL(T2, 10); insertAVL(T2, 40); insertAVL(T2, 30);
	insertAVL(T2, 25); insertAVL(T2, 5); insertAVL(T2, 8); insertAVL(T2, 50); insertAVL(T2, 60);
	AVLNode* T3 = NULL;
	insertAVL(T3, 20); insertAVL(T3, 3); insertAVL(T3, 10); insertAVL(T3, 40); insertAVL(T3, 30);
	insertAVL(T3, 25); insertAVL(T3, 5); insertAVL(T3, 8); insertAVL(T3, 50); insertAVL(T3, 60);
	AVLNode* T4 = NULL;
	insertAVL(T4, 20); insertAVL(T4, 3); insertAVL(T4, 10); insertAVL(T4, 40); insertAVL(T4, 30);
	insertAVL(T4, 25); insertAVL(T4, 5); insertAVL(T4, 8); insertAVL(T4, 50); insertAVL(T4, 60);
	AVLNode* T5 = NULL;
	insertAVL(T5, 20); insertAVL(T5, 3); insertAVL(T5, 10); insertAVL(T5, 40); insertAVL(T5, 30);
	insertAVL(T5, 25); insertAVL(T5, 5); insertAVL(T5, 8); insertAVL(T5, 50); insertAVL(T5, 60);
	
	cout << "rotacje podwójne: " << endl;
	cout << "   drzewo przed rotacją (wg funkcji preorder): "; preorderAVL(T2); cout << endl;
	cout << "       R: "; R(T2, T2->R); preorderAVL(T2); cout << endl;
	cout << "       L: "; L(T3, T3->L); preorderAVL(T3); cout << endl;
	cout << "       RL: "; RL(T4, T4->R->L); preorderAVL(T4); cout << endl;
	cout << "       LR: "; LR(T5, T5->L->R); preorderAVL(T5); cout << endl;

	
	cout << "usuwanie elementu: " << endl;
	cout << "   przed usunięciem: "; preorderAVL(T4); cout << endl;
	cout << "   po usunięciu 10: "; removeeAVL(T4, 10); preorderAVL(T4); cout << endl;


	return 0;
}

