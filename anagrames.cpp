#include "anagrames.hpp"
#include "word_toolkit.hpp"

const float anagrames::LOAD_FACTOR = 0.75;

// Cost: O(M), on M és la mida inicial de la taula hash.
anagrames::anagrames() throw(error) : _M(16), _quants(0){
  _taula= new node_hash*[_M]();
}

// Cost: O(M + n), on M és la mida de la taula i n el nombre total d'elements.
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

// Cost: O(M + n), on M és la mida de la taula i n el nombre total d'elements.
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


// Cost: O(M + n), on M és la mida de la taula i n el nombre total d'elements.
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


// Cost: O(L + k), on L és la longitud de la paraula i k el nombre de col·lisions a la posició.
void anagrames::insereix(const string& paraula) throw(error) {
  diccionari::insereix(paraula);
  string clau = word_toolkit::anagrama_canonic(paraula);
  int pos = fhash(clau) % _M;

  node_hash* actual = _taula[pos];

  while (actual) {
    if (actual->_clau == clau) {
      list<string>::iterator it = actual->_valors.begin();
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


  node_hash* nuevoNodo = new node_hash;
  nuevoNodo->_clau = clau;
  nuevoNodo->_valors = {paraula};
  nuevoNodo->_seg = _taula[pos];
  _taula[pos] = nuevoNodo;
  ++_quants;

  if (static_cast<float>(_quants) / _M > LOAD_FACTOR) rehash();
}

// Cost: O(L + k), on L és la longitud de l'anagrama i k el nombre de col·lisions.
void anagrames::mateix_anagrama_canonic(const string& a, list<string>& L) const throw(error) {
  if (!word_toolkit::es_canonic(a)) throw error(NoEsCanonic);

  int pos = fhash(a)%_M;
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

// Cost: O(L), on L és la longitud de la clau.
nat anagrames::fhash(const string& clau)const{
	nat n = 0;
	for (nat i=0; i < clau.length(); ++i) {
		n = n + clau[i]*(i+1);
	}
	return n;
}

// Redimensionar la taula hash
// Pre: cert
// Post: La taula hash es redimensiona per a acomodar més elements.
// Cost: O(M + n), on M és la mida actual de la taula i n el nombre d'elements.
void anagrames::rehash() {
    nat nouTamany = _M * 2;
    node_hash** novaTaula = new node_hash*[nouTamany]();

    for (nat i = 0; i < _M; ++i) {
        node_hash* actual = _taula[i];

        while (actual) {
            node_hash* seg = actual->_seg;

            nat novaPos = fhash(actual->_clau) % nouTamany;

            actual->_seg = novaTaula[novaPos];
            novaTaula[novaPos] = actual;

            actual = seg;
        }
    }
    delete[] _taula;

    _taula = novaTaula;
    _M = nouTamany;
}
