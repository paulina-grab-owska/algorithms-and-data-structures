/* 
dla danego ciągu liczb sprawdź czy istnieje możliwość stworzenia permutacji tego ciągu w taki sposób by każde 2 sąsiednie elementy były parą kolejnych liczb o różniczy N
*/

#include <vector>
#include <algorithm>
using namespace std;

bool canCreatePermutation(vector<int>& numbers, int n) {
    sort(numbers.begin(), numbers.end()); 
    
    int i = 0;
    while (i < numbers.size() - 1) {
        if (numbers[i+1] - numbers[i] != n) { return false; }
        i += 2;
    }
    return true;
}

int main() {
    vector<int> numbers1 = {2, 6, 4, 8, 10, 12};
    vector<int> numbers2 = {3, 7, 14, 9, 8, 20};
    vector<int> numbers3 = {5, 30, 10, 25, 15, 20};
    int n1 = 2, n2 = 3, n3 = 5;
    
    cout << endl << "dla ciągu nr 1" << endl;
    if (canCreatePermutation(numbers1, n1)) { cout << "     istnieje możliwość stworzenia permutacji ciągu o stałej różnicy. " << endl; }
    else { cout << "    nie ma możliwości stworzenia permutacji" << endl; }
    
    cout << endl << "dla ciągu nr 2" << endl;
    if (canCreatePermutation(numbers2, n2)) { cout << "     istnieje możliwość stworzenia permutacji ciągu o stałej różnicy. " << endl; }
    else { cout << "    nie ma możliwości stworzenia permutacji" << endl; }
    
    cout << endl << "dla ciągu nr 3" << endl;
    if (canCreatePermutation(numbers3, n3)) { cout << "     istnieje możliwość stworzenia permutacji ciągu o różnicy. " << endl; }
    else { cout << "    nie ma możliwości stworzenia permutacji" << endl; }

    return 0;
}
