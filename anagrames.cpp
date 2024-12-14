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

  // Buscar clave en la lista enlazada de la posición actual
  while (actual) {
    if (actual->_clau == clau) {
      // Insertar palabra en orden
      auto it = actual->_valors.begin();
      while (it != actual->_valors.end() && *it < paraula) {
        ++it;
      }

      // Insertar solo si no existe
      if (it == actual->_valors.end() || *it != paraula) {
        actual->_valors.insert(it, paraula);
      }
      return; // Clave encontrada y actualizada, terminamos
    }
    actual = actual->_seg;
  }

  // Crear un nuevo nodo en la lista enlazada
  node_hash* nuevoNodo = new node_hash;
  nuevoNodo->_clau = clau;
  nuevoNodo->_valors = {paraula};
  nuevoNodo->_seg = _taula[pos]; // Enlazar con el resto de la lista
  _taula[pos] = nuevoNodo;       // Actualizar la cabecera de la lista
  ++_quants;

  // Verificar el factor de carga y redimensionar si es necesario
  if (static_cast<float>(_quants) / _M > LOAD_FACTOR) {
    rehash();
  }
}


void anagrames::mateix_anagrama_canonic(const string& a, list<string>& L) const throw(error) {
  if (!word_toolkit::es_canonic(a)) {
    throw error(NoEsCanonic);
  }

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

int anagrames::fhash(const string& clau)const{
  int hashValue=0;
  nat p=31;
  nat power=1;

  for (char c : clau) {
    hashValue = (hashValue + (c * power)) % _M;
    power = (power * p) % _M;
  }

  return hashValue;

}

void anagrames::rehash() {
  nat nuevoTamano = _M * 2; // Duplicar el tamaño de la tabla
  node_hash** nuevaTabla = new node_hash*[nuevoTamano](); // Nueva tabla inicializada a nullptr

  // Reinsertar elementos de la tabla antigua en la nueva tabla
  for (nat i = 0; i < _M; ++i) {
    node_hash* actual = _taula[i];
    while (actual != nullptr) {
      node_hash* siguiente = actual->_seg; // Guardar el siguiente nodo antes de modificar _seg

      // Recalcular la nueva posición en la tabla ampliada
      nat nuevaPos = fhash(actual->_clau) % nuevoTamano;

      // Insertar el nodo al inicio de la lista en la nueva posición
      actual->_seg = nuevaTabla[nuevaPos];
      nuevaTabla[nuevaPos] = actual;

      actual = siguiente; // Avanzar al siguiente nodo en la vieja tabla
    }
  }

  delete[] _taula; // Liberar la memoria de la tabla antigua
  _taula = nuevaTabla; // Actualizar la tabla
  _M = nuevoTamano; // Actualizar el tamaño
}
