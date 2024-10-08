#include <iostream>
using namespace std;

// Struktura reprezentująca węzeł drzewa binarnego
struct node {
	int val;
	struct node* parent;	//wskażnik na rodzica
	struct node* l_son;	    //wskażnik na lewe poddrzewo
	struct node* r_son;	    //wskaźnik na prawe poddrzewo
};

struct node* root;

//WSTAW
void put(int n, struct node* start) {
	if (root == NULL) {
		root = new node;
		root->val = n;
		root->l_son = NULL;
		root->r_son = NULL;
		root->parent = NULL;
	}
	else {
		if (n < start->val) put(n, start->l_son);
	
		else put(n, start->r_son);
	}
}


//NAJMNIESZY
struct node* min(struct node* start) {  // Przechodzenie w lewo -> doście do najmniejszej wartości
	if (start->l_son != NULL)           // Sprawdzenie, czy lewe poddrzewo jest puste
	    { return min(start->l_son);}    // Zwrócenie najmniejszej wartości
	else return start;
}

//NAJWIĘKSZY
struct node* max(struct node* start) {  // Przechodzenie w prawo -> doście do największej wartości
	if (start->r_son != NULL)           // Sprawdzenie, czy prawe poddrzewo jest puste
	    {return max(start->r_son);}     // Zwrócenie największej wartości
	else return start;                     
}


//INORDER
void in_order(struct node* start) {
	if (start->l_son != NULL) in_order(start->l_son);
	cout << start->val << endl;

	if(start->r_son != NULL) in_order(start->r_son);
}


//NASTĘPNIK
node* findnext(node* root, node* noode) {
    if (noode == NULL) // Sprawdzenie, czy węzeł nie istnieje
        return 0;

    node* next = NULL;

    while (root != NULL) {
        if (noode->val < root->val) { // Jeśli wartość węzła jest mniejsza, idź w lewo
            next = root;
            root = root->l_son;
        }
        else if (noode->val > root->val) { // Jeśli wartość węzła jest większa, idź w prawo
            root = root->r_son;
        }
        else {              // Jeśli wartość węzła jest równa, znajdź następnik
            if (noode->r_son != NULL) {
                next = noode->r_son;
                while (next->l_son != NULL)
                    next = next->l_son;
            }
            break;
        }
    }

    return next;           // Zwrócenie następnika
}

// Funkcja do znajdowania poprzednika danego węzła
node* before(node* root, node* noode) {
    if (noode == NULL) // Sprawdzenie, czy węzeł nie istnieje
        return 0;

    node* before = NULL;

    while (root != NULL) {
        if (noode->val < root->val) { // Jeśli wartość węzła jest mniejsza, idź w lewo
            root = root->l_son;
        }
        else if (noode->val > root->val) { // Jeśli wartość węzła jest większa, idź w prawo
            before = root;
            root = root->r_son;
        }
        else { // Jeśli wartość węzła jest równa, znajdź poprzednika
            if (noode->l_son != NULL) {
                before = noode->l_son;
                while (before->r_son != NULL)
                    before = before->r_son;
            }
            break;
        }
    }

    return before; // Zwrócenie poprzednika
}




int main() {
    
    node* Drzewo = NULL;
    
    
    
	return(0);
}




