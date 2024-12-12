
#include <list>
#include <string>
#include "anagrames.hpp"
#include "iter_subset.hpp"
#include "obte_paraules.hpp"

using namespace std;
using util::nat;

namespace obte_paraules {

/* Pre: Cert
   Post: Retorna la lista de palabras que se pueden formar usando k letras
   de la palabra s. Lanza error si k es mayor que la longitud de s o k < 3. */
void obte_paraules(nat k, const string& s, const anagrames& A, list<string>& paraules) throw(error) {
    if (k < 3 || k > s.size()) {
        throw error(LongitudInvalida); // Lanza error si k es inválido
    }

    paraules.clear(); // Aseguramos que la lista está vacía

    // Generar todas las combinaciones de k letras de s usando iter_subset
    iter_subset comb(s.size(), k);
    while (!comb.end()) {
        const subset& indices = *comb;
        string combinacion;

        // Crear la combinación de letras usando los índices generados
        for (nat index : indices) {
            combinacion.push_back(s[index - 1]); // Los índices son 1-based
        }

        // Obtener las palabras válidas del objeto anagrames
        list<string> palabras_validas;
        A.mateix_anagrama_canonic(word_toolkit::anagrama_canonic(combinacion), palabras_validas);

        // Añadir las palabras válidas a la lista final
        paraules.insert(paraules.end(), palabras_validas.begin(), palabras_validas.end());

        ++comb; // Avanzar al siguiente subconjunto
    }
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

    // Generar palabras para cada longitud k (de 3 a s.size())
    for (nat k = 3; k <= s.size(); ++k) {
        list<string> palabras_k;
        obte_paraules(k, s, A, palabras_k);

        // Añadir las palabras a la lista final
        paraules.insert(paraules.end(), palabras_k.begin(), palabras_k.end());
    }

    // Ordenar la lista: longitud ascendente y alfabéticamente
    paraules.sort([](const string& a, const string& b) {
        if (a.size() != b.size()) return a.size() < b.size(); // Ordenar por longitud
        return a < b; // Ordenar alfabéticamente
    });
}

} // namespace obte_paraules
