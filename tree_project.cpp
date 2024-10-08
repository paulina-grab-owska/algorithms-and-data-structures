#include <iostream>
#include <string>

using namespace std;

//struktura węzła drzewa BST
struct ProductNode {
    string name;                    //nazwa produktu
    int quantity;                   //ilość produktu
    int purchased;                  //ilość zakupionych wcześniej produktów
    int frequency;                  //częstość wyszukiwań produktu
    ProductNode* left;              //lewy potomek
    ProductNode* right;             //prawy potomek

    //konstruktor węzła
    ProductNode(string name, int quantity, int purchased, int frequency) {
        this->name = name;
        this->quantity = quantity;
        this->purchased = purchased;
        this->frequency = frequency;
        this->left = nullptr;
        this->right = nullptr;
    }
};

//klasa drzewa BST
class ProductBST {
    public:
            //konstruktor drzewa
            ProductBST() { root = nullptr; }

            //wyszukiwanie produktu po nazwie
            ProductNode* search(const string& name) { return searchHelper(root, name); }

            //dodawanie produktu
            void add(const string& name, int quantity, int purchased, int frequency) {
                root = addHelper(root, name, quantity, purchased, frequency);
            }

            //zakup produktu
            void purchase(const string& name, int quantity) { purchaseHelper(root, name, quantity); }

            // aktualizacja drzewa
            void update(int threshold) { updateHelper(root, threshold); }

    private:
            ProductNode* root;     // Korzeń drzewa

            //wyszukiwanie produktu po nazwie HELPER
            ProductNode* searchHelper(ProductNode* node, const string& name) {
                if (node == nullptr || node->name == name) {
                    if (node != nullptr) { node->frequency++;  }
                    return node;
                }

                if (name < node->name) { return searchHelper(node->left, name);} 
                else { return searchHelper(node->right, name); }
            }

            //dodawanie produktu po nazwie HELPER
            ProductNode* addHelper(ProductNode* node, const string& name, int quantity, int purchased, int frequency) {
                if (node == nullptr) { return new ProductNode(name, quantity, purchased, frequency); }

                if (name < node->name) { node->left = addHelper(node->left, name, quantity, purchased, frequency); } 
                else if (name > node->name) { node->right = addHelper(node->right, name, quantity, purchased, frequency); } 
                else { node->quantity += quantity; }

                return node;
            }

            //zakup produkty HELPER
            void purchaseHelper(ProductNode* node, const string& name, int quantity) {
                if (node == nullptr) { return; }

                 if (name < node->name) { purchaseHelper(node->left, name, quantity); } 
                 else if (name > node->name) { purchaseHelper(node->right, name, quantity); } 
                 else { 
                    node->quantity -= quantity; 
                    if (node->quantity < 0) { node->quantity = 0; }
                }
            }

            //aktualizacja drzewa HELPER
            void updateHelper(ProductNode*& node, int threshold) {
                if (node == nullptr) { return; }

                 //lewa
                updateHelper(node->left, threshold);

                //węzeł
                if (node->quantity < 1 || node->frequency < threshold) { node = removeHelper(node, node->name); }

                //prawa
                updateHelper(node->right, threshold);
            }

            //usuwanie węzła HELPER
            ProductNode* removeHelper(ProductNode*& node, const string& name) {
                if (node == nullptr) { return nullptr; }

                if (name < node->name) { node->left = removeHelper(node->left, name); } 
                else if (name > node->name) { node->right = removeHelper(node->right, name); } 
                else {
                    if (node->left == nullptr && node->right == nullptr) { delete node; node = nullptr; } 
                    else if (node->left == nullptr) {                      
                        ProductNode* temp = node;
                        node = node->right;
                        delete temp;
                    } 
                    else if (node->right == nullptr) {                    
                        ProductNode* temp = node;
                        node = node->left;
                        delete temp;
                    } 
                    else {                                                 
                        ProductNode* temp = findMin(node->right);            
                        node->name = temp->name;                             
                        node->quantity = temp->quantity;
                        node->purchased = temp->purchased;
                        node->frequency = temp->frequency;
                        node->right = removeHelper(node->right, temp->name); 
                    }
                }

                return node;
            }

            //wyszukiwanie węzła min HELPER
            ProductNode* findMin(ProductNode* node) {
                while (node->left != nullptr) { node = node->left; }

                return node;
            }

    public:
    
        //dodawanie produktu
        void addProduct(const string& name, int quantity, int purchased, int frequency) {
            addHelper(root, name, quantity, purchased, frequency);
        }

        //wyszukiwanie produktu
        void searchProduct(const string& name) {
            ProductNode* node = searchHelper(root, name);
            if (node != nullptr) {
                node->frequency++;
                cout << "Product found: " << node->name << ", quantity: " << node->quantity << ", purchased: " << node->purchased << ", frequency: " << node->frequency << endl;
            } 
            else { cout << "Product not found" << endl; }
        }

        //zakup produktu
        void purchaseProduct(const string& name, int quantity) { purchaseHelper(root, name, quantity); }

        //aktualizacja drzewa
        void updateTree(int threshold) { updateHelper(root, threshold); }
};

int main() {

    ProductBST productTree;

    productTree.addProduct("mleko", 10, 5, 2);
    productTree.addProduct("chleb", 20, 10, 5);
    productTree.addProduct("jajka", 30, 15, 7);
    productTree.addProduct("masło", 40, 20, 10);
    
    productTree.searchProduct("mleko");

    productTree.purchaseProduct("mleko", 3);

    productTree.updateTree(3);

    return 0;
}

