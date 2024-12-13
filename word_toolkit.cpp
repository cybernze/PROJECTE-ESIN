#include "word_toolkit.hpp"
#include <algorithm>

namespace word_toolkit {
    /* Pre:  Cert
    Post: Retorna cert si i només si les lletres de l'string s estan
    en ordre lexicogràfic ascendent. */
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

    /* Pre:  Cert
    Post: Retorna l'anagrama canònic (ordenar de menor a major les lletres de l'string) de l'string s.*/
    string anagrama_canonic(const string& s) throw() {
        string res = s; //no modifiquem l'string original
        sort(res.begin(),res.end());
        return res;
    }

    /* Pre: L és una llista no buida de paraules formades exclusivament
    amb lletres majúscules de la 'A' a la 'Z' (excloses la 'Ñ', 'Ç',
    majúscules accentuades, ...).
    Post: Retorna el caràcter que no apareix a l'string excl i és
    el més freqüent en la llista de paraules L.
    En cas d'empat, es retornaria el caràcter alfabèticament menor.
    Si l'string excl inclou totes les lletres de la 'A' a la 'Z' es
    retorna el caràcter '\0', és a dir, el caràcter de codi ASCII 0. */
    char mes_frequent(const string& excl, const list<string>& L) throw() {

        // Pas 1: Creem vector per comptar freqüències de totes les lletres de 'A - 'Z
        vector<int> freq(25, 0);

        // Pas 2: Utilitzem un vector bool per saber l'aparició de les lletres ('A - 'Z) que conté l'string execl
        vector<bool> apareix(25, false);
        for (char c : excl) { //
            if (c >= 'A' and c <= 'Z') {
                apareix[c - 'A'] = true;
            }
        }

        // Pas 3: Comptem únicament la freqüència dels caràcters de cada string de la llista L però que no apareixen a l'string execl
        for (const string& paraula : L) {
            for (char c : paraula) {
                if (c >= 'A' and c <= 'Z' and !apareix[c - 'A']) {
                    ++freq[c - 'A'];
                }
            }
        }

        // Pas 4: Determinar el caràcter més freqúent (alfabéticament menor en cas d'empat)
        char res = '\0'; //En cas extrem (execl conté totes les lletres A-Z) retornem 0 en codi ASCII
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
