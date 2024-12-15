#include "diccionari.hpp"

/*Utilitzarem un Trie per representar aquesta classe per varies raons:
1. */

diccionari::diccionari() throw(error){
    _arrel = new node;
    num_paraules=0;
}

diccionari::diccionari(const diccionari& D) throw(error){
    _arrel = new node;
    this->num_paraules=D.num_paraules;
    copia(_arrel, D._arrel);
}

diccionari& diccionari::operator=(const diccionari& D) throw(error){
    if(this!=&D){
        neteja(_arrel);
        _arrel = new node;
        this->num_paraules=D.num_paraules;
        copia(_arrel, D._arrel);
    }
    return *this;
}

diccionari::~diccionari() throw(){
    neteja(_arrel);
}

void diccionari::neteja(node* p) {
  if (p == nullptr) return;
  for (node* fill : p->fills) {
    neteja(fill);  // Liberamos los hijos
  }
  delete p;  // Liberamos el nodo actual
}

void diccionari::copia(node*& dest, node* src) {
  if (src == nullptr) return;

  for (int i = 0; i < 26; ++i) {
    if (src->fills[i] != nullptr) {
      dest->fills[i] = new node;
      copia(dest->fills[i], src->fills[i]);
    }
  }
}

void diccionari::insereix(const string& p) throw(error) {
  node* current = _arrel;
  for (char c : p) {
    int index = c - 'A';  // Calculem l'index del caràcter
    if (current->fills[index] == nullptr) {
      current->fills[index] = new node;
    }
    current = current->fills[index];
  }

  int end_index = 26;  // Índice para '#'
  if (current->fills[end_index] == nullptr) {
    current->fills[end_index] = new node;
    ++num_paraules; // Incrementar el contador de palabras solo si es una nueva palabra
  }
}

string diccionari::prefix(const string& p) const throw(error){
    if(_arrel==nullptr) return "";

    node *current = _arrel;
    string result="";
    string temp="";

    for (char c : p) {
        int index = c - 'A';
        if (current->fills[index] == nullptr) break; // Si no hi ha camí termina
        temp += c;
        current = current->fills[index];

        if(current->fills[26]!=nullptr) result=temp;
    }
    return result;
}

void diccionari::satisfan_patro(const vector<string>& q, list<string>& L)const throw(error) {
    L.clear(); //Nos aseguramos que la lista esté vacia
    string current_word;
    satisfan_patro_recursive(_arrel, q, 0, current_word, L);  // Llamada al método auxiliar
    L.sort();  // Ordenar alfabéticamente
}

void diccionari::satisfan_patro_recursive(node* p, const vector<string>& q, unsigned long pos, string& current_word, list<string>& L)const{
    if (p == nullptr) return;

    // CB: Hem processat tot el patró
    if (pos == q.size()) {
        if (p->fills[26] != nullptr) {
            L.push_back(current_word);  // Agregar la palabra si es válida
        }
        return;
    }

    // CR: Procesar el patró actual (caràcters válids per posició actual)
    const string& valid_chars = q[pos];
    string new_word = current_word;
    for (unsigned long i = 0; i < valid_chars.length(); i++) {
        char c = valid_chars[i];
        int index = c - 'A';
        if (p->fills[index] != nullptr) {
            new_word = current_word + c;
            satisfan_patro_recursive(p->fills[index], q, pos + 1, new_word, L);
        }
    }
}

void diccionari::llista_paraules(nat k, list<string>& L) const throw(error) {
  if (_arrel == nullptr) return; // Si el diccionario está vacío, no hay palabras.

  string current_word; // Para construir las palabras actuales durante el recorrido.
  dfs_llista_paraules(_arrel, current_word, k, L);
}

void diccionari::dfs_llista_paraules(node* n, string& current_word, nat k, list<string>& L) const {
  if (current_word.length() >= k) {
    // Si el nodo marca el final de una palabra y su longitud es >= k, la añadimos.
    L.push_back(current_word);
  }

  for (nat i = 0; i < 26; ++i) { // Recorremos todos los hijos (asumiendo alfabeto en inglés).
    if (n->fills[i] != nullptr) {
      char next_char = 'A' + i; // Convertimos el índice al carácter correspondiente.
      current_word.push_back(next_char); // Añadimos el carácter actual a la palabra.

      dfs_llista_paraules(n->fills[i], current_word, k, L); // Recorremos el hijo.

      current_word.pop_back(); // Retrocedemos después del recorrido.
    }
  }
}

nat diccionari::num_pal() const throw(){
  return num_paraules;
}

