#include "anagrames.hpp"
#include "anagrames.rep"
#include "word_toolkit.hpp" // Funciones de ayuda para anagramas

anagrames::anagrames() throw(error) : diccionari(), agrupaments() {}

anagrames::anagrames(const anagrames& other) throw(error)
: diccionari(other), agrupaments(other.agrupaments) {}

anagrames& anagrames::operator=(const anagrames& other) throw(error) {
  if (this != &other) {
    diccionari::operator=(other);
    agrupaments = other.agrupaments;
  }
  return *this;
}

anagrames::~anagrames() throw() {}

void anagrames::insereix(const string& paraula) throw(error) {

  diccionari::insereix(paraula); // Inserta en el diccionario base

  string canonic = word_toolkit::anagrama_canonic(paraula); // Calcula el anagrama canónico

  // Referencia a la lista de palabras asociadas al anagrama canónico
  list<string>& lista_palabras = agrupaments[canonic];

  // Si la lista está vacía, simplemente agrega la palabra
  if (lista_palabras.empty()) {
    lista_palabras.push_back(paraula);
    return;
  }

  // Recorremos la lista para encontrar la posición de inserción correcta
  auto it = lista_palabras.begin();
  while (it != lista_palabras.end() && *it < paraula) {
    ++it;  // Avanzamos hasta encontrar la primera palabra mayor o igual a 'paraula'
  }

  //Se encuentra un duplicado
  if(it!=lista_palabras.end() && *it==paraula) return;

  // Insertamos la palabra en la posición correcta
  lista_palabras.insert(it, paraula);
}


void anagrames::mateix_anagrama_canonic(const string& a, list<string>& L) const throw(error) {
  if (!word_toolkit::es_canonic(a)) {
    throw error(NoEsCanonic);
  }

  auto it = agrupaments.find(a);
  //Cost de find es O(1)
  if (it != agrupaments.end()) {
    L = it->second; // Devuelve las palabras que tienen el mismo anagrama (first es la clave y second el valor, en nuestro caso el valor es la lista)
  } else {
    L.clear(); // Lista vacía si no hay coincidencias
  }
}
