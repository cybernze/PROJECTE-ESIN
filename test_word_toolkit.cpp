#include <iostream>
#include <string>
#include <list>
#include "word_toolkit.hpp"

int main() {
    using namespace std;

    // Prueba de es_canonic
    string test1 = "AABCD";
    string test2 = "DCBAA";
    string test3 = "A";

    cout << "¿Es '" << test1 << "' canónico? " << (word_toolkit::es_canonic(test1) ? "Sí" : "No") << endl;
    cout << "¿Es '" << test2 << "' canónico? " << (word_toolkit::es_canonic(test2) ? "Sí" : "No") << endl;
    cout << "¿Es '" << test3 << "' canónico? " << (word_toolkit::es_canonic(test3) ? "Sí" : "No") << endl;


    // Prueba de anagrama_canonic
    string test4 = "COCINA";
    cout << "Anagrama canónico de '" << test4 << "': "
         << word_toolkit::anagrama_canonic(test4) << endl;

    // Prueba de mes_frequent
    list<string> palabras = {"COCHE", "CASA", "CAMA", "CABEZA"};
    string excl = "ABCDE";
    cout << "Letra más frecuente que no está en '" << excl << "': "
         << word_toolkit::mes_frequent(excl, palabras) << endl;

    return 0;
}
