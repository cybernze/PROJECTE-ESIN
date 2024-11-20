#ifndef _WORD_TOOLKIT_HPP
#define _WORD_TOOLKIT_HPP
#include <string>
#include <list>
#include <esin/error>

using namespace std;

namespace word_toolkit {

  /* Pre:  Cert 
     Post: Retorna cert si i només si les lletres de l'string s estan 
     en ordre lexicogràfic ascendent. */
  bool es_canonic(const string& s) throw();

  /* Pre:  Cert 
     Post: Retorna l'anagrama canònic de l'string s. 
     Veure la classe anagrames per saber la definició d'anagrama canònic. */
  string anagrama_canonic(const string& s) throw();

  /* Pre: L és una llista no buida de paraules formades exclusivament
     amb lletres majúscules de la 'A' a la 'Z' (excloses la 'Ñ', 'Ç',
     majúscules accentuades, ...). 
     Post: Retorna el caràcter que no apareix a l'string excl i és
     el més freqüent en la llista de paraules L.
     En cas d'empat, es retornaria el caràcter alfabèticament menor.
     Si l'string excl inclou totes les lletres de la 'A' a la 'Z' es 
     retorna el caràcter '\0', és a dir, el caràcter de codi ASCII 0. */
  char mes_frequent(const string& excl, const list<string>& L) throw();
};
#endif
