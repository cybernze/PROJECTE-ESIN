#include "diccionari.cpp"
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

int main() {
    try {
        diccionari d;

        // Insertar palabras
        d.insereix("BB");

        // Verificar número de palabras
        cout << "Número de palabras en el diccionario: " << d.num_pal() << endl;

        // Probar el método prefix
        string prefix = d.prefix("B");
        cout << "Prefijo encontrado para 'B': " << prefix << endl;

        // Probar satisfan_patro
        vector<string> patro = {"H", "E", "L", "P"};
        list<string> palabras_con_patro;
        d.satisfan_patro(patro, palabras_con_patro);
        cout << "Palabras que satisfacen el patrón:" << endl;
        for (const auto& palabra : palabras_con_patro) {
            cout << palabra << endl;
        }

        // Probar llista_paraules
        list<string> palabras_mayores_k;
        nat k = 4;
        d.llista_paraules(k, palabras_mayores_k);
        cout << "Palabras con longitud mayor o igual a " << k << ":" << endl;
        for (const auto& palabra : palabras_mayores_k) {
            cout << palabra << endl;
        }
    } catch (...) {
        cerr << "Se produjo un error inesperado." << endl;
    }

    return 0;
}
