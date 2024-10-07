#include <iostream>
using namespace std;

struct node {
	int val;
	node* next;
};


void show(node* H) {
	cout << "h -> ";
	if (H != NULL) {                            
		node* p = H;                           
		while ( p != NULL ) {					
			cout << p->val << " -> ";          
			p = p->next;         
		}
	}
	cout << "NULL" << endl << endl;
}

void AddH(node* &H, int x) {				
	node* p = new node;						
	p->val = x;								
	p->next = H;				           
	H = p;						           
}

void DelH(node* &H) {					
	if (H != NULL) {
		node* p = H;
		H = p->next;						
		delete p;                           
	}

}


//zamiana 1 z 3; 2 z 4 
void Changex2(node *& H){
    
    int size = 0;                               //tak dla formalności
	node* p = H;
	while (p != NULL) { p = p->next; size++; }
    if (size < 4) { return; }       

    //zamiana 1 z 3
    p = H;
    node *e = p->next->next;     
    swap(p->val, e->val);
    
    //zamiana 2 z 4
    p = H->next;
    e = p->next->next;
    swap(p->val, e->val);
   
}

//funkcja zamieniająca wartości, które nie są obok siebie 
void SwapWhatever(node* &H, int x, int y){
    
    for (node* p = H; p != NULL; p = p->next) {
        if (p->val == x) {
            for (node* e = H; e != NULL; e=e->next) {
                if (e->val == y) {
                    swap(e->val, p->val);
                    return;                             //zamiana zrobiona, kończymy
                }
            }
        }
    }
}



int main()
{
    node* H1 = NULL;
    AddH(H1, 6); AddH(H1, 5); AddH(H1, 4); AddH(H1, 3); AddH(H1, 2);	AddH(H1, 1);
	show(H1);
	Changex2(H1);
	show(H1);
	
	cout << endl << endl;
	
	node* H2 = NULL;
    AddH(H2, 6); AddH(H2, 5); AddH(H2, 4); AddH(H2, 3); AddH(H2, 2); AddH(H2, 1);
	show(H2);
	SwapWhatever(H2, 5, 1);
	show(H2);

    return 0;
}
