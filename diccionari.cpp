#include "diccionari.hpp"

// Cost: O(1)
diccionari::diccionari() throw(error){
  _arrel = new node;
  num_paraules = 0;
}


// Cost: O(n), on n és el nombre de paraules al diccionari.
diccionari::diccionari(const diccionari& D) throw(error){
  _arrel = new node;
  this->num_paraules = D.num_paraules;
  copia(_arrel, D._arrel);
}


// Cost: O(n), on n és el nombre de paraules al diccionari.
diccionari& diccionari::operator=(const diccionari& D) throw(error){
  if(this != &D){
    neteja(_arrel);
    _arrel = new node;
    this->num_paraules = D.num_paraules;
    copia(_arrel, D._arrel);
  }
  return *this;
}


// Cost: O(n), on n és el nombre de paraules al diccionari.
diccionari::~diccionari() throw(){
  neteja(_arrel);
}


// Pre: cert
// Post: Allibera tota la memòria dels nodes a partir de p.
// Cost: O(n), on n és el nombre de nodes a partir de p.
void diccionari::neteja(node* p) {
  if (p == nullptr) return;
  for (node* fill : p->fills) {
    neteja(fill);
  }
  delete p;
}


// Pre: cert
// Post: dest és una còpia exacta de src.
// Cost: O(n), on n és el nombre de nodes a partir de src.
void diccionari::copia(node*& dest, node* src) {
  if (src == nullptr) return;

  for (int i = 0; i < 26; ++i) {
    if (src->fills[i] != nullptr) {
      dest->fills[i] = new node;
      copia(dest->fills[i], src->fills[i]);
    }
  }
}


// Cost: O(L), on L és la longitud de la paraula.
void diccionari::insereix(const string& p) throw(error) {
  node* current = _arrel;
  for (char c : p) {
    int index = c - 'A';
    if (current->fills[index] == nullptr) {
      current->fills[index] = new node;
    }
    current = current->fills[index];
  }

  int end_index = 26;  // Índice per al caràcter final '#'
  if (current->fills[end_index] == nullptr) {
    current->fills[end_index] = new node;
    ++num_paraules;
  }
}


// Cost: O(L), on L és la longitud de p.
string diccionari::prefix(const string& p) const throw(error){
  if (_arrel == nullptr) return "";

  node *current = _arrel;
  string result = "";
  string temp = "";

  for (char c : p) {
    int index = c - 'A';
    if (current->fills[index] == nullptr) break;
    temp += c;
    current = current->fills[index];

    if (current->fills[26] != nullptr) result = temp;
  }
  return result;
}


// Cost: O(n * k), on n és el nombre de paraules i k la longitud màxima de q.
void diccionari::satisfan_patro(const vector<string>& q, list<string>& L) const throw(error) {
  L.clear();
  string current_word;
  satisfan_patro_recursive(_arrel, q, 0, current_word, L);
}

// Funció recursiva per trobar paraules que satisfan un patró
// Pre:  Cert
// Post: Retorna la llista de paraules del diccionari que satisfan el patró especificat en el vector d'strings q, en ordre alfabètic ascendent.
// Cost: O(n * k), on n és el nombre de paraules i k la longitud màxima de q.
void diccionari::satisfan_patro_recursive(node* p, const vector<string>& q, unsigned long pos, string& current_word, list<string>& L) const {
  if (p == nullptr) return;

  // Cas base: Hem processat tot el patró
  if (pos == q.size()) {
    if (p->fills[26] != nullptr) {
      list<string>::iterator it = L.begin();
      while (it != L.end() && *it < current_word) {
        ++it;
      }
      L.insert(it, current_word);
    }
    return;
  }

  // Cas recursiu: Processem el patró actual
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


// Cost: O(n), on n és el nombre de paraules.
void diccionari::llista_paraules(nat k, list<string>& L) const throw(error) {
  if (_arrel == nullptr) return;

  string current_word;
  dfs_llista_paraules(_arrel, current_word, k, L);
}

// Funció recursiva per trobar paraules amb longitud >= k
// Pre: cert
// Post: L conté totes les paraules amb longitud >= k.
// Cost: O(n), on n és el nombre de paraules.
void diccionari::dfs_llista_paraules(node* n, string& current_word, nat k, list<string>& L) const {
  if (current_word.length() >= k) {
    L.push_back(current_word);
  }

  for (nat i = 0; i < 26; ++i) {
    if (n->fills[i] != nullptr) {
      char next_char = 'A' + i;
      current_word.push_back(next_char);

      dfs_llista_paraules(n->fills[i], current_word, k, L);

      current_word.pop_back();
    }
  }
}

// Cost: O(1)
nat diccionari::num_pal() const throw(){
  return num_paraules;
}
