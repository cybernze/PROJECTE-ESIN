#include <iostream>
#include "iter_subset.hpp"

using namespace std;

int main() {
    // Probar iterador con diferentes valores de n y k
    nat n = 5;
    nat k = 4;

    cout << "Subconjuntos de " << k << " elementos de {1, ..., " << n << "}:" << endl;

    iter_subset it(n, k);

    while (!it.end()) {
        subset s = *it; // Obtener el subconjunto actual
        cout << "{ ";
        for (nat elem : s) {
            cout << elem << " ";
        }
        cout << "}" << endl;
        ++it; // Avanzar al siguiente subconjunto
    }

    // Probar casos límite
    cout << "\nProbar caso límite k > n:" << endl;
    iter_subset it_invalid(4, 6);

    if (it_invalid.end()) {
        cout << "Correcto: No hay subconjuntos posibles cuando k > n." << endl;
    }
    return 0;
}
