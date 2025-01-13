#include "word_toolkit.hpp"
#include <algorithm>

/*EXPLICACIÓ DETALLADA DELS ALGORISMES UTILITZATS:
1. bool es_canonic(const string& s):
    -Eficiència: El cost és lineal O(n). És l’opció més eficient, ja que cada lletra només es compara una vegada amb la seva anterior.
    Si es detecta que la cadena no és canònica (ordre incorrecte), l’algorisme s’atura immediatament. Especialment útil si la cadena és llarga.

    -Per què no s’ha utilitzat un altre enfocament? (Possibilitats que vam pensar abans de fer la solució final)
        -   Ordenar la cadena:
        Ordenar s i comparar-la amb la seva versió original tindria una complexitat superior (O(nlogn)).
        A més, requereix memòria addicional per mantenir una còpia de la cadena ordenada.
        -   Recursivitat:
        Un algorisme recursiu seria més complicat i menys eficient, ja que afegiria sobrecàrrega per les crides recursives.

    Ens hem decidit per l’enfocament iteratiu perquè és el més eficient i adequat, ja que maximitza el rendiment i minimitza la complexitat.

2. string anagrama_canonic(const string& s): utilització de std::sort
    -Eficiència: El cost és O(nlogn), algorisme suficientment ràpid per treballar amb cadenes de longitud moderada.

    -Per què no s’ha utilitzat un altre enfocament? (Possibilitats que vam pensar abans de fer la solució final)
        -   Ordenació manual:
        Implementar manualment un algorisme d’ordenació com QuickSort o MergeSort afegiria complexitat innecessària. A més, requeriria memòria addicional per mantenir una còpia de la cadena ordenada.
        -   Taula de freqüències:
        Una alternativa seria utilitzar una taula de freqüències per comptar les aparicions de cada lletra i reconstruir la cadena en ordre. Tot i que això tindria un cost O(n), seria menys flexible i més complicat d’implementar.

    Ens hem decidit per std::sort perquè és una solució òptima per eficiència, simplicitat i suport de la biblioteca estàndard.

3. char mes_frequent(const string& excl, const list<string>& L):
    -Eficiència: tenim costos lineals per

    -Per què no s’ha utilitzat un altre enfocament? (Possibilitats que vam pensar abans de fer la solució final)
        -   std::map:
        Tot i que std::map podria comptar freqüències, afegiria sobrecàrrega temporal (O(log26) per accés) i espacial.
        -   Ordenar al final:
        Comptar les freqüències i després ordenar-les seria més costós O(26log26) que l’enfocament actual.
        -   Taules hash:
        Una estructura com std::unordered_map seria menys adequada perquè no facilita la resolució del desempat alfabètic.

    L’ús de vectors fixos és òptim en aquest cas perquè combina eficiència, simplicitat i una implementació directa.

    */

namespace word_toolkit {
    // Cost temporal: O(n), on n és la longitud de la cadena s.
    // Cost espacial: 0(1). Només utilitza variables auxiliars (prev, canonic i size) per a dur a terme el càlcul.
    bool es_canonic(const string& s) throw() {
        bool canonic = true;
        char prev=s[0];
        int size(s.size());
        for(int i=1; i<size; i++){
            if(prev > s[i]){   /*Ordre estrictament creixent */
                canonic = false;
                break;
            }
            prev = s[i];
        }
        return canonic;
    }

    // Cost temporal: O(n·logn), on n és la longitud de la cadena s.
    // Cost espacial: 0(n). Requereix una còpia de la cadena s per a no modificar-la, per la qual cosa l'espai necessari és proporcional a la longitud de s.
    string anagrama_canonic(const string& s) throw() {
        string res = s; //no modifiquem l'string original
        sort(res.begin(),res.end());
        return res;
    }

    // Cost temporal: O(n⋅k+m), on n és el nombre de paraules a L, k és la longitud mitjana de les paraules i m és la longitud de excl.
    // Cost espacial: 0(1). L'espai requerit per a freq i apareix és constant (independent de l'entrada)
    char mes_frequent(const string& excl, const list<string>& L) throw() {

        // Pas 1: Creem vector per comptar freqüències de totes les lletres de 'A - 'Z
        int freq[25]= {0};

        // Pas 2: Utilitzem un vector bool per saber l'aparició de les lletres ('A - 'Z) que conté l'string excl
        bool apareix[25]= {false};
        for (char c : excl) { //
            if (c >= 'A' and c <= 'Z') {
                apareix[c - 'A'] = true;
            }
        }

        // Pas 3: Comptem únicament la freqüència dels caràcters de cada string de la llista L però que no apareixen a l'string excl
        for (const string& paraula : L) {
            for (char c : paraula) {
                if (c >= 'A' and c <= 'Z' and !apareix[c - 'A']) {
                    ++freq[c - 'A'];
                }
            }
        }

        // Pas 4: Determinar el caràcter més freqúent (alfabéticament menor en cas d'empat)
        char res = '\0'; //En cas extrem (excl conté totes les lletres A-Z) retornem 0 en codi ASCII
        int max = 0;
        for (int i = 0; i < 25; ++i) {
            if (freq[i] > max) {
                max = freq[i];
                res = 'A' + i;
            } else if (freq[i] == max and max > 0) { // Cas empat
                if (res > 'A' + i) {
                    res = 'A' + i;
                }
            }
        }

        return res;
    }

};
