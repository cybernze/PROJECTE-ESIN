#ifndef _DICCIONARI_HPP
#define _DICCIONARI_HPP
#include <string>
#include <list>
#include <vector>
#include <esin/error>
#include <esin/util>

using namespace std;
using util::nat;

class diccionari {

public:
  /* Pre:  Cert 
     Post: Construeix un diccionari que conté únicament una paraula:
     la paraula buida. */
  diccionari() throw(error);       

  /* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
  diccionari(const diccionari& D) throw(error);        
  diccionari& operator=(const diccionari& D) throw(error); 
  ~diccionari() throw();      

  /* Pre:  Cert 
     Post: Afegeix la paraula p al diccionari; si la paraula p ja
     formava part del diccionari, l'operació no té cap efecte. */
  void insereix(const string& p) throw(error);

  /* Pre:  Cert 
     Post: Retorna el prefix més llarg de p que és una paraula que
     pertany al diccionari, o dit d'una forma més precisa, retorna la
     paraula més llarga del diccionari que és prefix de p. */
  string prefix(const string& p) const throw(error);

  /* Pre:  Cert 
     Post: Retorna la llista de paraules del diccionari que satisfan
     el patró especificat en el vector d'strings q, en ordre
     alfabètic ascendent. */
  void satisfan_patro(const vector<string>& q, 
                      list<string>& L) const throw(error);

  /* Pre:  Cert 
     Post: Retorna una llista amb totes les paraules del diccionari 
     de longitud major o igual a k en ordre alfabètic ascendent. */
  void llista_paraules(nat k, list<string>& L) const throw(error);

  /* Pre:  Cert 
     Post: Retorna el nombre de paraules en el diccionari. */
  nat num_pal() const throw();

private:
  #include "diccionari.rep"
};
#endif
