
#include <list>
#include <string>
#include "AVL.cpp"
#include "anagrames.hpp"
#include "iter_subset.hpp"
#include "obte_paraules.hpp"
#include "word_toolkit.hpp"

using namespace std;
using util::nat;

/*EXPLICACIÓ DETALLADA DELS ALGORISMES UTILITZATS:

1.void obte_paraules(nat k, const string& s, const anagrames& A, list<string>& paraules):

-   Estructura escalable i eficient:
AVLTree garanteix un cost eficient O(logn) en insercions i cercas.

-   Eficàcia en la generació de combinacions:
iter_subset permet generar combinacions de manera òptima, reduint la memòria necessària ja que no cal generar totes les combinacions alhora.

-   Normalització amb anagrames canònics:
anagrama_canonic és una solució senzilla i efectiva per comparar i agrupar anagrames.

-   Gestió de paraules en estructures adequades:
std::list i l’ús d’AVL combinen una gestió eficient de les dades amb flexibilitat en el seu processament.

2.void obte_paraules(const string& s, const anagrames& A, list<string>& paraules):

-   Estructura modular i reutilització:
Aquesta funció reutilitza la funcionalitat de la primera funció obte_paraules(nat k, ...), que ja està optimitzada per generar paraules d’una longitud fixa.

-   Eficiència:
Generar paraules per cada longitud k separadament permet treballar de manera ordenada i clara, a més d’assegurar que es compleix el requisit d’ordenació per longitud ascendent.
Les insercions es fan directament al final de la llista, mantenint l’eficiència.

-Alternatives pensades abans d'arribar a la solució final:
1. Crear una nova llista en lloc de netejar-la/assegurar-nos de que sigui buida amb 'paraules.clear()',seria menys eficients si la llista ja conté espai reservat per a elements
2. Utilització de set: No utilitzem set perquè no ens interessa l'ordre general, sinó l'ordre en els diferents subconjunts.
*/

namespace obte_paraules {

// Cost: O(n^k * (k log k + p log m)), on:
// - n^k: Nombre de subconjunts de mida k d’un conjunt de mida n.
// - k log k: Càlcul de l’anagrama canònic.
// - p log m: Inserció de p paraules vàlides a l’arbre balancejat (m paraules úniques).
void obte_paraules(nat k, const string& s, const anagrames& A, list<string>& paraules) throw(error) {
    if (k < 3 || k > s.size()) {
        throw error(LongitudInvalida);
    }

    paraules.clear();
    AVLTree<string> paraules_unicas;

    iter_subset comb(s.size(), k);
    while (!comb.end()) {
        const subset& indices = *comb;
        string combinacion;

        // Crear la combinació
        for (nat index : indices) {
            combinacion.push_back(s[index - 1]);
        }

        list<string> palabras_validas;
        A.mateix_anagrama_canonic(word_toolkit::anagrama_canonic(combinacion), palabras_validas);

        // Inserir les paraules al conjunt per evitar duplicats
        paraules_unicas.inserirLlista(palabras_validas);

        ++comb;
    }

    // Passar les paraules úniques al resultat final en ordre lexicogràfic
    paraules = paraules_unicas.obtenirEnOrdre();
}

// Cost: O(∑(k=3 to n) n^k * (k log k + p log m)), on:
// - n^k: Nombre de subconjunts de mida k d’un conjunt de mida n.
// - k log k: Càlcul de l’anagrama canònic per cada subconjunt.
// - p log m: Inserció de p paraules vàlides a l’arbre balancejat (m paraules úniques).
// La complexitat és la suma dels costos per a tots els valors de k (de 3 a n).
void obte_paraules(const string& s, const anagrames& A, list<string>& paraules) throw(error) {
    if (s.size() < 3) {
        throw error(LongitudInvalida);
    }

    paraules.clear(); // Ens assegurem que la llista està buida.

    // Generar paraules per a cada longitud k (de 3 a s.size())
    for (nat k = 3; k <= s.size(); ++k) {
        list<string> palabras_k;
        obte_paraules(k, s, A, palabras_k);

        paraules.insert(paraules.end(), palabras_k.begin(), palabras_k.end());
    }

}

}
