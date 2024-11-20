#ifndef _ANAGRAMES_HPP
#define _ANAGRAMES_HPP
#include <string>
#include <list>
#include <esin/error>
#include "diccionari.hpp"

using namespace std;

class anagrames : public diccionari {

public:
  /* Pre:  Cert
     Post: Construeix un anagrama buit. */
  anagrames() throw(error);

  /* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
  anagrames(const anagrames& A) throw(error);
  anagrames& operator=(const anagrames& A) throw(error);
  ~anagrames() throw();

  /* Pre:  Cert
     Post: Afegeix la paraula p a l'anagrama; si la paraula p ja
     formava part de l'anagrama, l'operació no té cap efecte. */
  void insereix(const string& p) throw(error);

  /* Pre:  Cert
     Post: Retorna la llista de paraules p tals que anagrama_canonic(p)=a.
     Llança un error si les lletres de a no estan en ordre ascendent. */
  void mateix_anagrama_canonic(const string& a, list<string>& L) const throw(error);

  /* Gestió d'errors. */
  static const int NoEsCanonic = 21;

private:
  #include "anagrames.rep"
};
#endif
