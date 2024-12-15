#include <iostream>
#include <cassert>
#include "anagrames.hpp" // Incluye tu implementación aquí
using namespace std;

// Función para imprimir el contenido de la tabla hash (para depuración)
void imprimirTabla(const anagrames& tabla) {
    cout << "Tabla hash:" << endl;
    tabla.imprimirTabla(); // Asegúrate de implementar esta función en tu clase
    cout << "-----------------------------" << endl;
}

// Pruebas básicas de inserción y búsqueda
void pruebasBasicas() {
    anagrames tabla;

    // Insertar palabras y verificar que estén organizadas por clave
    tabla.insereix("roma");
    tabla.insereix("amor");
    tabla.insereix("mora");
    tabla.insereix("mar");

    list<string> resultados;
    tabla.mateix_anagrama_canonic("amor", resultados);

    // Verificar que se hayan agrupado correctamente
    list<string> esperado = {"amor", "mora", "roma"};
    assert(resultados == esperado);
    cout << "Pruebas básicas PASADAS" << endl;
}

// Pruebas con colisiones
void pruebasColisiones() {
    anagrames tabla;

    // Insertar palabras con claves diferentes pero que podrían causar colisiones
    tabla.insereix("roma");
    tabla.insereix("amor");
    tabla.insereix("carro");
    tabla.insereix("rocar");

    list<string> resultados;

    // Verificar anagramas para "amor"
    tabla.mateix_anagrama_canonic("amor", resultados);
    list<string> esperadoAmor = {"amor", "roma"};
    assert(resultados == esperadoAmor);

    // Verificar anagramas para "rocar"
    tabla.mateix_anagrama_canonic("rocar", resultados);
    list<string> esperadoRocar = {"carro", "rocar"};
    assert(resultados == esperadoRocar);

    cout << "Pruebas de colisiones PASADAS" << endl;
}

// Pruebas de redimensionamiento
void pruebasRedimensionamiento() {
    anagrames tabla;

    // Insertar más palabras para forzar el redimensionamiento
    vector<string> palabras = {
        "abc", "bca", "cab", "dog", "god", "odg", "tree", "eert",
        "reed", "deer", "roma", "amor", "mora", "tar", "rat", "art"
    };

    for (const auto& palabra : palabras) {
        tabla.insereix(palabra);
    }

    // Verificar que las claves y valores sigan siendo correctos
    list<string> resultados;
    tabla.mateix_anagrama_canonic("abc", resultados);
    list<string> esperadoAbc = {"abc", "bca", "cab"};
    assert(resultados == esperadoAbc);

    tabla.mateix_anagrama_canonic("dog", resultados);
    list<string> esperadoDog = {"dog", "god", "odg"};
    assert(resultados == esperadoDog);

    cout << "Pruebas de redimensionamiento PASADAS" << endl;
}

// Pruebas con casos límites
void pruebasLimites() {
    anagrames tabla;

    // Caso vacío
    list<string> resultados;
    tabla.mateix_anagrama_canonic("abc", resultados);
    assert(resultados.empty());

    // Insertar una palabra vacía
    tabla.insereix("");
    tabla.mateix_anagrama_canonic("", resultados);
    list<string> esperadoVacio = {""};
    assert(resultados == esperadoVacio);

    // Insertar palabras muy largas
    string larga1(1000, 'a'); // "aaaa...aaaa" (1000 'a')
    string larga2(999, 'a');  // "aaaa...aaa" (999 'a') + 'b'
    larga2 += 'b';
    tabla.insereix(larga1);
    tabla.insereix(larga2);

    tabla.mateix_anagrama_canonic(larga1, resultados);
    list<string> esperadoLarga1 = {larga1};
    assert(resultados == esperadoLarga1);

    cout << "Pruebas límites PASADAS" << endl;
}

// Pruebas con palabras que no son canónicas
void pruebasCanonicidad() {
    anagrames tabla;

    // Insertar palabras
    tabla.insereix("roma");
    tabla.insereix("amor");

    // Probar con una clave no canónica
    list<string> resultados;
    try {
        tabla.mateix_anagrama_canonic("maro", resultados); // Esto debería lanzar error
        assert(false); // No deberíamos llegar aquí
    } catch (const error& e) {
        cout << "Error correctamente lanzado para palabra no canónica" << endl;
    }

    cout << "Pruebas de canonicidad PASADAS" << endl;
}

int main() {
    cout << "Iniciando pruebas..." << endl;

    pruebasBasicas();
    pruebasColisiones();
    pruebasRedimensionamiento();
    pruebasLimites();
    pruebasCanonicidad();

    cout << "¡Todas las pruebas PASARON!" << endl;
    return 0;
}
