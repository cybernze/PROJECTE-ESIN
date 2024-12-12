#include <set>
#include <list>
#include <string>
#include "anagrames.hpp"
#include "iter_subset.hpp"
#include "obte_paraules.hpp"
#include "word_toolkit.hpp"

using namespace std;
using util::nat;

namespace obte_paraules {

/* Pre: Cert
   Post: Retorna la lista de palabras que se pueden formar usando k letras
   de la palabra s. Lanza error si k es mayor que la longitud de s o k < 3. */
void obte_paraules(nat k, const string& s, const anagrames& A, list<string>& paraules) throw(error) {
    if (k < 3 || k > s.size()) {
        throw error(LongitudInvalida);
    }

    paraules.clear();
    set<string> paraules_unicas;
    /*Utilizamos set frente a unordered_set ya que tiene coste de insercion de O(log n)
     vs O(1)+ordenacion O(n log n), (set introduce los valores en orden)*/

    // Iterar sobre los subconjuntos de k elementos
    iter_subset comb(s.size(), k);
    while (!comb.end()) {
        const subset& indices = *comb;
        string combinacion;

        // Crear la combinación
        for (nat index : indices) {
            combinacion.push_back(s[index - 1]);
        }

        // Obtener las palabras válidas
        list<string> palabras_validas;
        A.mateix_anagrama_canonic(word_toolkit::anagrama_canonic(combinacion), palabras_validas);

        // Insertar las palabras en el conjunto para evitar duplicados
        paraules_unicas.insert(palabras_validas.begin(), palabras_validas.end());

        ++comb; // Avanzar al siguiente subconjunto
    }

    // Pasar las palabras únicas al resultado final en orden lexicográfico
    paraules.assign(paraules_unicas.begin(), paraules_unicas.end());
}

/* Pre: Cert
   Post: Retorna la lista de palabras que se pueden formar usando 3 o más letras
   de la palabra s. La lista estará ordenada por longitud ascendente y, a igual longitud,
   alfabéticamente. Lanza error si s tiene menos de 3 letras. */
void obte_paraules(const string& s, const anagrames& A, list<string>& paraules) throw(error) {
    if (s.size() < 3) {
        throw error(LongitudInvalida); // Lanza error si s tiene menos de 3 letras
    }

    paraules.clear(); // Aseguramos que la lista está vacía

    //No utilizamos set porque no nos interesa el orden general, sino el orden en los diferentes subconjuntos

    // Generar palabras para cada longitud k (de 3 a s.size())
    for (nat k = 3; k <= s.size(); ++k) {
        list<string> palabras_k;
        obte_paraules(k, s, A, palabras_k);

        // Añadir las palabras a la lista final
        paraules.insert(paraules.end(), palabras_k.begin(), palabras_k.end());
    }

    // Ordenar la lista: longitud ascendente y alfabéticamente
}

} // namespace obte_paraules
