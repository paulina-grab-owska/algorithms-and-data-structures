#include <iostream>
using namespace std;

struct Node {
    char data;
    int nb;
    Node* L, *R;

    Node(char data, int nb) : data(data), nb(nb), L(NULL), R(NULL) {}
};

void codeit(Node* root, string xd, string huff[]) {
    if (root == NULL) return;

    if (!root->L && !root->R) {  huff[root->data] = xd;  }

    codeit(root->L, xd + "0", huff);
    codeit(root->R, xd + "1", huff);
}

void huffdrzew(string text) {
    const int ascii = 256;
    unsigned nb[ascii] = {0};

    for (char c : text) { nb[static_cast<unsigned char>(c)]++; }

    int n = 0;
    for (int i = 0; i < ascii; ++i) {
        if (nb[i] > 0) { ++n; }
    }

    Node* noode[ascii];
    int dx = 0;
    for (int i = 0; i < ascii; ++i) {
        if (nb[i] > 0) {
            noode[dx++] = new Node(static_cast<char>(i), nb[i]);
        }
    }

    while (n > 1) {
        int i = 0, j = 1;
        for (int k = 2; k < n; ++k) {
            if (noode[k]->nb < noode[i]->nb) {
                j = i;
                i = k;
            } 
            else if (noode[k]->nb < noode[j]->nb) { j = k; }
        }

        Node* nooode = new Node('\0', noode[i]->nb + noode[j]->nb);
        nooode->L = noode[i];
        nooode->R = noode[j];

        noode[j] = nooode;
        noode[i] = noode[--n];
    }

    Node* root = noode[0];

    string huff[ascii];
    codeit(root, "", huff);

    cout << "literki, częstość bycia i kodzik: " << endl;
    for (int i = 0; i < ascii; ++i) {
        if (!huff[i].empty()) {
            cout << static_cast<char>(i) << " (" << nb[i] << ") : " << huff[i] << endl;
        }
    }

    cout << endl << "zakodzikowane:" << endl;
    for (char c : text) {
        cout << huff[static_cast<unsigned char>(c)];
    }

    cout << endl;
}

int main() {
    string text = "sdjksfhaweieaasdklaeskaskaejfaweenvkvnokglwhgkewjbkfalksjdlajsdlaakakakdcaas";
    huffdrzew(text);

    return 0;
}
