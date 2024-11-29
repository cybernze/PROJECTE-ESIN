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

  dest->es_final = src->es_final;

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
    int index = c - 'a';  // Calculem l'index del caràcter
    if (current->fills[index] == nullptr) {
      current->fills[index] = new node;
    }
    current = current->fills[index];
  }

  if (!current->es_final) {
    current->es_final = true;  // Marquem com final de paraula
    ++num_paraules;  // Incrementem el comptador de paraules
  }
}

string diccionari::prefix(const string& p) const throw(error){
    node* current = _arrel;
    string result;
    for (char c : p) {
        int index = c - 'a';
        if (current->fills[index] == nullptr) break; // Si no hi ha camí termina
        result += c;
        current = current->fills[index];
    }
    return result;
}

nat diccionari::num_pal()const throw(){
    return num_paraules;
}

void diccionari::satisfan_patro(const vector<string>& q, list<string>& L)const throw(error) {
    L.clear(); //Nos aseguramos que la lista esté vacia
    string current_word;
    satisfan_patro_recursive(_arrel, q, 0, current_word, L);  // Llamada al método auxiliar
    L.sort();  // Ordenar alfabéticamente
}

void diccionari::satisfan_patro_recursive(node* node, const vector<string>& q, unsigned long pos, string& current_word, list<string>& L) {
    if (node == nullptr) return;

    // CB: Hem processat tot el patró
    if (pos == q.size()) {
        if (node->es_final) {
            L.push_back(current_word);  // Agregar la palabra si es válida
        }
        return;
    }

    // CR: Procesar el patró actual (caràcters válids per posició actual)
    const string& valid_chars = q[pos];
    string new_word = current_word;
    for (unsigned long i = 0; i < valid_chars.length(); i++) {
        char c = valid_chars[i];
        int index = c - 'a';
        if (node->fills[index] != nullptr) {
            new_word = current_word + c;
            satisfan_patro_recursive(node->fills[index], q, pos + 1, new_word, L);
        }
    }
}
