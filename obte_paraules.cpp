//Representació AVL
#include <iostream>
#include <list>
using namespace std;

template <typename T>
class AVLArbre {
private:
    struct Node {
        T clau;
        Node* esquerra;
        Node* dreta;
        int altura;

        Node(const T& c) : clau(c), esquerra(nullptr), dreta(nullptr), altura(1) {}
    };

    Node* arrel;

    // Retorna l'altura d'un node
    // Cost temporal: O(1)
    int obtenirAltura(Node* node) {
        return node ? node->altura : 0;
    }

    // Calcula el factor d'equilibri
    // Cost temporal: O(1)
    int obtenirFactorEquilibri(Node* node) {
        return node ? obtenirAltura(node->esquerra) - obtenirAltura(node->dreta) : 0;
    }

    // Realitza una rotació cap a la dreta
    // Cost temporal: O(1)
    Node* rotacioDreta(Node* y) {
        Node* x = y->esquerra;
        Node* T2 = x->dreta;

        x->dreta = y;
        y->esquerra = T2;

        y->altura = max(obtenirAltura(y->esquerra), obtenirAltura(y->dreta)) + 1;
        x->altura = max(obtenirAltura(x->esquerra), obtenirAltura(x->dreta)) + 1;

        return x;
    }

    // Realitza una rotació cap a l'esquerra
    // Cost temporal: O(1)
    Node* rotacioEsquerra(Node* x) {
        Node* y = x->dreta;
        Node* T2 = y->esquerra;

        y->esquerra = x;
        x->dreta = T2;

        x->altura = max(obtenirAltura(x->esquerra), obtenirAltura(x->dreta)) + 1;
        y->altura = max(obtenirAltura(y->esquerra), obtenirAltura(y->dreta)) + 1;

        return y;
    }

    // Insereix un valor de manera recursiva
    // Cost temporal: O(log n), perquè el màxim de comparacions i rotacions és proporcional a l'altura de l'arbre.
    Node* inserir(Node* node, const T& clau) {
        if (!node) {
            return new Node(clau);
        }

        if (clau < node->clau) {
            node->esquerra = inserir(node->esquerra, clau);
        } else if (clau > node->clau) {
            node->dreta = inserir(node->dreta, clau);
        } else {
            // Clau duplicada, no es permet
            return node;
        }

        node->altura = 1 + max(obtenirAltura(node->esquerra), obtenirAltura(node->dreta));

        int equilibri = obtenirFactorEquilibri(node);

        // Casos de rotació
        if (equilibri > 1 && clau < node->esquerra->clau) {
            return rotacioDreta(node);
        }
        if (equilibri < -1 && clau > node->dreta->clau) {
            return rotacioEsquerra(node);
        }
        if (equilibri > 1 && clau > node->esquerra->clau) {
            node->esquerra = rotacioEsquerra(node->esquerra);
            return rotacioDreta(node);
        }
        if (equilibri < -1 && clau < node->dreta->clau) {
            node->dreta = rotacioDreta(node->dreta);
            return rotacioEsquerra(node);
        }

        return node;
    }

    // Cerca un valor a l'arbre
    // Cost temporal: O(log n), perquè només cal recórrer l'altura de l'arbre.
    bool cerca(Node* node, const T& clau) {
        if (!node) {
            return false;
        }

        if (clau == node->clau) {
            return true;
        } else if (clau < node->clau) {
            return cerca(node->esquerra, clau);
        } else {
            return cerca(node->dreta, clau);
        }
    }

    // Recorre l'arbre en ordre i emmagatzema els valors en una llista
    // Cost temporal: O(n), perquè es visiten tots els nodes exactament una vegada.
    void recorregutInordre(Node* node, list<T>& valors) {
        if (node) {
            recorregutInordre(node->esquerra, valors);
            valors.push_back(node->clau);
            recorregutInordre(node->dreta, valors);
        }
    }

    // Allibera la memòria dels nodes
    // Cost temporal: O(n), perquè cal visitar tots els nodes per eliminar-los.
    void eliminarArbre(Node* node) {
        if (node) {
            eliminarArbre(node->esquerra);
            eliminarArbre(node->dreta);
            delete node;
        }
    }

public:
    AVLArbre() : arrel(nullptr) {}

    ~AVLArbre() {
        eliminarArbre(arrel);
    }

    // **Precondició**: cap.
    // **Postcondició**: Insereix una clau a l'arbre AVL.
    // Cost temporal: O(log n)
    void inserir(const T& clau) {
        arrel = inserir(arrel, clau);
    }

    // **Precondició**: cap.
    // **Postcondició**: Retorna cert si la clau existeix a l'arbre; altrament, fals.
    // Cost temporal: O(log n)
    bool cerca(const T& clau) {
        return cerca(arrel, clau);
    }

    // **Precondició**: cap.
    // **Postcondició**: Insereix una llista de valors a l'arbre AVL.
    // Cost temporal: O(m log n), on \(m\) és la mida de la llista i \(n\) el nombre de nodes actuals de l'arbre.
    void inserirLlista(const list<T>& valors) {
        for (const auto& valor : valors) {
            inserir(valor);
        }
    }

    // **Precondició**: cap.
    // **Postcondició**: Retorna una llista dels elements en ordre ascendent.
    // Cost temporal: O(n)
    list<T> obtenirEnOrdre() {
        list<T> valors;
        recorregutInordre(arrel, valors);
        return valors;
    }

    // **Precondició**: cap.
    // **Postcondició**: Imprimeix els elements en ordre ascendent.
    // Cost temporal: O(n)
    void imprimeix() {
        list<T> valors = obtenirEnOrdre();
        for (const auto& valor : valors) {
            cout << valor << " ";
        }
        cout << endl;
    }
};

#include <string>
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
    AVLArbre<string> paraules_unicas;

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
