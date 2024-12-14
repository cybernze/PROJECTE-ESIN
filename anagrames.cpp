#include "anagrames.hpp"
#include "anagrames.rep"
#include "word_toolkit.hpp" // Funciones de ayuda para anagramas

const float anagrames::LOAD_FACTOR = 0.75;

anagrames::anagrames() throw(error) : _M(16), _quants(0){
  _taula= new node_hash*[_M]();
}

anagrames::anagrames(const anagrames& A) throw(error)
: _M(A._M), _quants(A._quants) {
  _taula= new node_hash *[_M]();
  for(nat i=0; i<_M; i++){
    if(A._taula[i]){
      _taula[i] = new node_hash(*A._taula[i]);
      node_hash* actual = _taula[i];
      node_hash* original = A._taula[i]->_seg;
      while(original){
        actual->_seg = new node_hash(*original);
        actual = actual->_seg;
        original = original->_seg;
      }
    }
  }
}

anagrames& anagrames::operator=(const anagrames& A) throw(error) {
  if (this != &A) {
    this->~anagrames();
    _M = A._M;
    _quants = A._quants;
    _taula= new node_hash *[_M]();
    for(nat i=0; i<_M; i++){
      if(A._taula[i]){
        _taula[i] = new node_hash(*A._taula[i]);
        node_hash* actual = _taula[i];
        node_hash* original = A._taula[i]->_seg;
        while(original){
          actual->_seg = new node_hash(*original);
          actual = actual->_seg;
          original = original->_seg;
        }
      }
    }
  }
  return *this;
}

anagrames::~anagrames() throw() {
  for (nat i = 0; i < _M; ++i) {
    node_hash* actual = _taula[i];
    while (actual) {
      node_hash* temp = actual;
      actual = actual->_seg;
      delete temp;
    }
  }
  delete[] _taula;
}

void anagrames::insereix(const string& paraula) throw(error) {
  string clau = word_toolkit::anagrama_canonic(paraula);
  int pos = fhash(clau);

  node_hash* actual = _taula[pos];
  while (actual) {
    if (actual->_clau == clau) {
      // Insertar la palabra en orden en la lista
      auto it = actual->_valors.begin();
      while (it != actual->_valors.end() && *it < paraula) {
        ++it;
      }

      if (it == actual->_valors.end() || *it != paraula) {
        actual->_valors.insert(it, paraula);
      }
      return;
    }
    actual = actual->_seg;
  }

  _taula[pos] = new node_hash;
  _taula[pos]->_clau = clau;
  _taula[pos]->_valors = {paraula};
  _taula[pos]->_seg = _taula[pos];
  ++_quants;

  if (static_cast<float>(_quants) / _M > LOAD_FACTOR) {
    rehash();
  }
}

void anagrames::mateix_anagrama_canonic(const string& a, list<string>& L) const throw(error) {
  if (!word_toolkit::es_canonic(a)) {
    throw error(NoEsCanonic);
  }

  int pos = fhash(a);
  node_hash* actual = _taula[pos];
  while (actual) {
    if (actual->_clau == a) {
      L = actual->_valors;
      return;
    }
    actual = actual->_seg;
  }

  L.clear();
}

nat anagrames::fhash(const string& clau){
  int hashValue=0;
  nat p=31;
  nat power=1;

  for (char c : clau) {
    hashValue = (hashValue + (c * power)) % _M;
    power = (power * p) % _M;
  }

  return hashValue;

}

void anagrames::() {
  nat nuevoTamano = _M * 2;
  node_hash** nuevaTabla = new node_hash*[nuevoTamano]();

  // Reinsertar elementos de la tabla antigua en la nueva tabla
  for (nat i = 0; i < _M; ++i) {
    node_hash* actual = _taula[i];
    while (actual != nullptr) {
      nat nuevaPos = fhash(actual->_clau) % nuevoTamano;
      node_hash* siguiente = actual->_seg;
      actual->_seg = nuevaTabla[nuevaPos];
      nuevaTabla[nuevaPos] = actual;
      actual = siguiente;
    }
  }

  delete[] _taula; // Liberar la tabla antigua
  _taula = nuevaTabla;
  _M = nuevoTamano;
}
