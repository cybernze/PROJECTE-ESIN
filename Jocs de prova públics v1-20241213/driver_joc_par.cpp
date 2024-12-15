#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include <esin/error>
#include <esin/gen_driver>
#include <esin/util>

#include "anagrames.hpp"
#include "diccionari.hpp"
#include "iter_subset.hpp"
#include "obte_paraules.hpp"
#include "word_toolkit.hpp"

using util::nat;
using util::byte;
using namespace std;

// funcions d'utilitat

// imprimeix un booleà
ostream& operator<=(ostream& os, const bool b) {
  os << (b ? "true" : "false");
  return os;
}

int get_next_param(char* line, int& pos, string& s, char sep) {
  char c = line[pos]; 
  bool something_read = false;

  s = "";
  while (c != '\0' and c == sep) c = line[++pos];

  if (c != '\"') {
    while (c != '\0' and c != sep) { 
      s += c; 
      c = line[++pos]; 
    }
    something_read = (s != "");
  }
  else {
    bool fin = false;
    something_read = true;
    pos++; 
    c = line[pos];
    do {
      char slash = '\\';
      while (c != '\0' and c != '\"' and c != slash) {
        s += c; 
        c = line[++pos];
      }
      if (c != slash) { 
        fin = true; 
        if (c != '\0') pos++; 
      } else {
        if (c == slash and line[pos + 1] == '\"') { 
          s += '\"'; 
          pos += 2; 
          c = line[pos]; 
        } else { 
          s += slash; 
          pos++; 
          c = line[pos]; 
        }
      }
    }
    while (!fin);
  }
  return ((c == '\0' and !something_read) ? -1 : pos);
}

void split(const string& s, vector<string>& x, char c) throw() {
  int pos = 0; 
  char *tmp_buf = new char[s.length()+1];

  for (nat i = 0; i < s.length(); ++i) 
    tmp_buf[i] = s[i];
  tmp_buf[s.length()] = '\0';

  string field = ""; 
  while (get_next_param(tmp_buf, pos, field, c) > 0) {
    x.push_back(field);
  }
  delete[] tmp_buf;
}

// imprimeix una llista de T's
template <typename T>
ostream& operator<<(ostream& os, const list<T>& L) {
  typename list<T>::const_iterator it = L.begin();
  if (it == L.end()) { 
    os << "[]";  
  }
  else {
    T prev = *it;
    os << "[";
    ++it;
    while (it != L.end()) {
      os << prev << ", ";
      prev = *it;
      ++it;
    }
    os << prev << "]";
  }
  return os;
}

// user init
void* user_init(gen_driver& dr) {
  string id = dr.args(1);
  string tid = dr.args(2);
  
  if (tid == "anagrames") {
    if (dr.nargs() == 2) {
      return static_cast<void*>(new anagrames);
    }
    else
      throw error(gen_driver::WrongNumArgs,gen_driver::nom_mod,
		  gen_driver::WrongNumArgsMsg);
  }
  else if (tid == "dicc") {
    if (dr.nargs() == 2) {
      return static_cast<void*>(new diccionari);
    }
    else
      throw error(gen_driver::WrongNumArgs,gen_driver::nom_mod,
		  gen_driver::WrongNumArgsMsg);
  }
  else if (tid == "iter_subset") {
    if (dr.nargs() == 4) {
      if ((util::toint(dr.args(3)) < 0) || (util::toint(dr.args(4)) < 0))
        throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
		    gen_driver::WrongTypeArgsMsg);
      nat n = static_cast<nat> (util::toint(dr.args(3)));
      nat k = static_cast<nat> (util::toint(dr.args(4)));
      return static_cast<void*>(new iter_subset(n, k));
    }
    else
      throw error(gen_driver::WrongNumArgs,gen_driver::nom_mod,
		  gen_driver::WrongNumArgsMsg);
  }
  else if (tid == "vector<nat>") {
    vector<nat>* v = new vector<nat>(dr.nargs() - 2);
    for (nat i = 3; i <= dr.nargs(); ++i) {
      if (util::toint(dr.args(i)) < 0)
        throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
		    gen_driver::WrongTypeArgsMsg);
      (*v)[i - 3] = util::toint(dr.args(i));
    }
    return static_cast<void*>(v);
  }
  else if (tid == "vector<string>") {
    vector<string>* v = new vector<string>(dr.nargs() - 2);
    for (nat i = 3; i <= dr.nargs(); ++i) {
      (*v)[i - 3] = dr.args(i);
    }
    return static_cast<void*>(v);
  }
  else if (tid == "list<string>") {
    if (dr.nargs() == 2) 
      return static_cast<void*>(new list<string>);
    else
      throw error(gen_driver::WrongNumArgs,gen_driver::nom_mod,
		  gen_driver::WrongNumArgsMsg);
  }
  throw error(gen_driver::WrongTypeArgs,gen_driver::nom_mod,
	      gen_driver::WrongTypeArgsMsg);
}

/* TypeTraits */

template <> const char* TypeTraits<anagrames>::name = "anagrames";
template <> const char* TypeTraits<diccionari>::name = "dicc";
template <> const char* TypeTraits<iter_subset>::name = "iter_subset";
template <> const char* TypeTraits<vector<nat> >::name = "vector<nat>";
template <> const char* TypeTraits<vector<string> >::name = "vector<string>";
template <> const char* TypeTraits<list<string> >::name = "list<string>";

/*-------------------------< ANAGRAMES >---------------------------*/
void tracta_anagrama_insereix(gen_driver& dr) {
  anagrames* A = dr.object<anagrames>();
  A -> insereix(dr.args(1));
}

void tracta_anagrama_prefix(gen_driver& dr) {
  anagrames* A = dr.object<anagrames>();
  string s = dr.args(1);
  dr.get_ostream() << A -> prefix(s) << endl;
}

void tracta_mateix_anagrama(gen_driver& dr) {
  list<string> l;
  anagrames* A = dr.object<anagrames>();
  string s = dr.args(1);
  A -> mateix_anagrama_canonic(s, l);
  dr.get_ostream() << l << endl;
}

/*--------------------< DICCIONARI >-------------------*/
void tracta_insereix(gen_driver& dr) {
  diccionari* D = dr.object<diccionari>();
  D -> insereix(dr.args(1));
}

void tracta_prefix(gen_driver& dr) {
  diccionari* D = dr.object<diccionari>();
  string s = dr.args(1);
  dr.get_ostream() << D -> prefix(s) << endl;
}

void tracta_satisfan_patro(gen_driver& dr) {
  diccionari* D = dr.object<diccionari>();
  vector<string>* q = dr.object<vector<string> >(1);
  list<string>* l = dr.object<list<string> >(2);
  D -> satisfan_patro(*q, *l);
}

void tracta_satisfan_patro_pantalla(gen_driver& dr) {
  diccionari* D = dr.object<diccionari>();
  vector<string>* q = dr.object<vector<string> >(1);
  list<string> l;
  D -> satisfan_patro(*q, l);
  dr.get_ostream() << l << endl;
}

void tracta_satisfan_patro_simple(gen_driver& dr) {
  diccionari* D = dr.object<diccionari>();
  string s = dr.args(1);
  if (s.length()<2 or s[0] != '[' or s[s.length()-1]!=']') {
    throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod,
		gen_driver::WrongTypeArgsMsg);
  }
  vector<string> v;
  split(s.substr(1, s.length()-2), v, ',');

  for (nat i=0; i<v.size(); ++i) {
    if (v[i] == "*") {
      v[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
  }

  list<string> l;
  D -> satisfan_patro(v, l);
  dr.get_ostream() << l << endl;
}

void tracta_llista_paraules(gen_driver& dr) {
  diccionari* D = dr.object<diccionari>();
  int k;
  if ((k = util::toint(dr.args(1))) < 0)
    throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
		gen_driver::WrongTypeArgsMsg);
  list<string>* l = dr.object<list<string> >(2);
  D -> llista_paraules(static_cast<nat>(k), *l);
}

void tracta_llista_paraules_pantalla(gen_driver& dr) {
  diccionari* D = dr.object<diccionari>();
  int k;
  if ((k = util::toint(dr.args(1))) < 0)
    throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod, 
		gen_driver::WrongTypeArgsMsg);
  list<string> l;
  D -> llista_paraules(static_cast<nat>(k), l);
  dr.get_ostream() << l << endl;
}

void tracta_num_par(gen_driver& dr) {
  dr.get_ostream() << dr.object<diccionari>() -> num_pal() << endl;
}

	
/*------------------------------< ITER_SUBSET >-----------------------*/
void tracta_all_subsets(gen_driver& dr) {
  nat n = util::toint(dr.args(1));
  nat k = util::toint(dr.args(2));
  iter_subset s(n,k);
  int nsets = 0;
  do {
    if (nsets != 0) 
      dr.get_ostream() << ", ";
    ++nsets;
    vector<nat> v = *s;
    if (v.size() > 0) {
      dr.get_ostream() << '{'; 
      for (nat i = 0; i < v.size() - 1; ++i) 
        dr.get_ostream() << v[i] << ',';
      dr.get_ostream() << v[v.size() - 1];
      dr.get_ostream() << '}';
    } else {
      dr.get_ostream() << "{}";
    } 
    ++s;
  } while (!s.end());
  cout << endl;
}

void tracta_end(gen_driver& dr) {
  (dr.get_ostream() <= dr.object<iter_subset>() -> end()) << endl;
}

void tracta_dereference(gen_driver& dr) {
  iter_subset it = *(dr.object<iter_subset>());
  vector<nat> v = *it; 
  dr.get_ostream() << '{'; 
  for (int i = 0; i < ((int)v.size() - 1); ++i) {
    dr.get_ostream() << v[i] << ',';    
  }
  if (v.size() > 0) {
    dr.get_ostream() << v[v.size() - 1];
  }
  dr.get_ostream() << '}' << endl;
}

void tracta_preincr(gen_driver& dr) {
  iter_subset* pit = dr.object<iter_subset>();
  ++(*pit);
}

void tracta_postincr(gen_driver& dr) {
  iter_subset* pit = dr.object<iter_subset>();
  (*pit)++;
}

void tracta_igual(gen_driver& dr) {
  iter_subset* pit1 = dr.object<iter_subset>();
  iter_subset* pit2 = dr.object<iter_subset>(1);
  (dr.get_ostream() <= (*pit1 == *pit2)) << endl;
}

void tracta_diferent(gen_driver& dr) {
  iter_subset* pit1 = dr.object<iter_subset>();
  iter_subset* pit2 = dr.object<iter_subset>(1);
  (dr.get_ostream() <= (*pit1 != *pit2)) << endl;
}

/*------------------------------< OBTE_PARAULES >-----------------------*/
void tracta_obte_paraules_fix_len(gen_driver& dr) {
  nat k = util::toint(dr.args(1));
  string s = dr.args(2);
  anagrames* A = dr.object<anagrames>(3);
  list<string> l;
  obte_paraules::obte_paraules(k, s, *A, l);
  dr.get_ostream() << l << endl;
}

void tracta_obte_paraules_all_len(gen_driver& dr) {
  string s = dr.args(1);
  anagrames* A = dr.object<anagrames>(2);
  list<string> l;
  obte_paraules::obte_paraules(s, *A, l);
  dr.get_ostream() << l << endl;
}

void joc_wordchallenge(gen_driver& dr) {
  string s = dr.args(1);
  anagrames* A = dr.object<anagrames>(2);
  list<string> l;
  obte_paraules::obte_paraules(s, *A, l);
  dr.get_ostream() << l << endl;
}

/*------------------------------< WORD_TOOLKIT >-----------------------*/
void tracta_es_canonic(gen_driver& dr) {
  (dr.get_ostream() <= word_toolkit::es_canonic(dr.args(1))) << endl;
}

void tracta_canonic(gen_driver& dr) {
  dr.get_ostream() << word_toolkit::anagrama_canonic(dr.args(1)) << endl;
}

void tracta_mes_frequent(gen_driver& dr) {
  //string excl = dr.args(1);
  //list<string>* l = dr.object<list<string> >(2);
  //dr.get_ostream() << word_toolkit::mes_frequent(excl, *l) << endl;

  string excl = dr.args(1);
  string s = dr.args(2);
  if (s.length()<2 or s[0] != '[' or s[s.length()-1]!=']') {
    throw error(gen_driver::WrongTypeArgs, gen_driver::nom_mod,
                gen_driver::WrongTypeArgsMsg);
  }
  vector<string> v;
  split(s.substr(1, s.length()-2), v, ',');

  list<string> l;
  for (nat i=0; i<v.size(); ++i) {
    l.push_back(v[i]);
  }
  // dr.get_ostream() << "excl = " << excl << endl;
  char c = word_toolkit::mes_frequent(excl, l);
  if (c != '\0') {
     dr.get_ostream() << c << endl;
  }
  else {
     dr.get_ostream() << endl;
  }
}

/*------------------------------< MAIN >-----------------------*/

int main(){  
  gen_driver d("errors_joc_par.txt");

  // anagrames
  d.add_call("a_insereix", tracta_anagrama_insereix, "anagrames", "string", 
             "[<anagrames>] a_(ins)ereix <string>");
  d.add_call("a_ins", tracta_anagrama_insereix, "anagrames", "string", 
             "[<anagrames>] a_(ins)ereix <string>");
  d.add_call("a_prefix", tracta_anagrama_prefix, "anagrames", "string",
             "[<anagrames>] a_(pre)fix <string>");
  d.add_call("a_pre", tracta_anagrama_prefix, "anagrames", "string",
             "[<anagrames>] a_(pre)fix <string>");
  d.add_call("mateix_anagrama_canonic", tracta_mateix_anagrama, 
             "anagrames", "string", 
             "[<anagrames>] (m)ateix_(a)nagrama_(c)anonic <string>");
  d.add_call("mac", tracta_mateix_anagrama, 
             "anagrames", "string",
             "[<anagrames>] (m)ateix_(a)nagrama_(c)anonic <string>");

  // diccionari
  d.add_call("insereix", tracta_insereix, "dicc", "string", 
             "[<dicc>] (ins)ereix <string>");
  d.add_call("ins", tracta_insereix, "dicc", "string",
             "[<dicc>] (ins)ereix <string>");
  d.add_call("prefix", tracta_prefix, "dicc", "string",
             "[<dicc>] (pre)fix <string>");
  d.add_call("pre", tracta_prefix, "dicc", "string",
             "[<dicc>] (pre)fix <string>");
  d.add_call("satisfan_patro_s", tracta_satisfan_patro_simple,
             "dicc", "string",
	          "[<dicc>] (s)atisfan_(pat)ro_(s) <string>");
  d.add_call("spats",  tracta_satisfan_patro_simple, 
             "dicc", "string",
	           "[<dicc>] (s)atisfan_(pat)ro_(s) <string>");
  d.add_call("satisfan_patron_p", tracta_satisfan_patro_pantalla, 
             "dicc", "vector<string>", 
             "[<dicc>] (s)atisfan_(pat)ro_(p) vector<string>");
  d.add_call("spatp",  tracta_satisfan_patro_pantalla, 
             "dicc", "vector<string>",
             "[<dicc>] (s)atisfan_(pat)ro_(p) vector<string>");
  d.add_call("satisfan_patro", tracta_satisfan_patro,
             "dicc", "vector<string> list<string>",
	           "[<dicc>] (s)atisfan_(pat)ro vector<string> list<string>");
  d.add_call("spat",  tracta_satisfan_patro, 
             "dicc", "vector<string> list<string>",
	           "[<dicc>] (s)atisfan_(pat)ro vector<string> list<string>");
  d.add_call("llista_paraules_p", tracta_llista_paraules_pantalla, 
             "dicc", "nat", 
             "[<diccionari>] (l)lista_(pa)raules_(p) nat");
  d.add_call("lpap", tracta_llista_paraules_pantalla, 
             "dicc", "nat",
             "[<diccionari>] (l)lista_(pa)raules_(p) nat");
  d.add_call("llista_paraules", tracta_llista_paraules, 
             "dicc", "nat list<string>", 
             "[<diccionari>] (l)lista_(pa)raules nat list<string>");
  d.add_call("lpa", tracta_llista_paraules, 
             "dicc", "nat list<string>",
             "[<diccionari>] (l)lista_(pa)raules nat list<string>");
  d.add_call("num_par", tracta_num_par,
             "dicc");

  // iter_subset
  d.add_call("end", tracta_end, "iter_subset");
  d.add_call("*", tracta_dereference, "iter_subset");
  d.add_call("++", tracta_preincr, "iter_subset", "", 
             "[<iter_subset>] [preincr|++]");
  d.add_call("preincr", tracta_preincr, "iter_subset", "",
             "[<iter_subset>] [preincr|++]");
  d.add_call("postincr", tracta_postincr, "iter_subset");
  d.add_call("==", tracta_igual, "iter_subset", "iter_subset");
  d.add_call("!=", tracta_diferent, "iter_subset", "iter_subset");
  d.add_call("all_subsets", tracta_all_subsets, "*", "nat nat");

  // obte_paraules
  d.add_call("obte_paraules_lon_fixa", tracta_obte_paraules_fix_len, 
             "*", "nat string anagrames", 
             "(o)bte_(p)araules_lon_(f)ixa <nat> <string> <anagrames>");
  d.add_call("spf", tracta_obte_paraules_fix_len, 
             "*", "nat string anagrames", 
             "(o)bte_(p)araules_lon_(f)ixa <nat> <string> <anagrames>");
  d.add_call("obte_paraules_lon_totes", tracta_obte_paraules_all_len, 
             "*", "string anagrames", 
             "(o)bte_(p)araules_lon_(t)otes <string> <anagrames>");
  d.add_call("spt", tracta_obte_paraules_all_len, 
             "*", "string anagrames", 
             "(o)bte_(p)araules_lon_(t)otes <string> <anagrames>");
  d.add_call("wordchallenge", joc_wordchallenge, "*", "string dicc");

  // word_toolkit
  d.add_call("es_canonic", tracta_es_canonic, "*", "string");
  d.add_call("canonic", tracta_canonic, "*", "string");
  d.add_call("mes_frequent", tracta_mes_frequent, "*", "string string");

  // instal·lació de tipus
  d.install_type<anagrames>();
  d.install_type<diccionari>();
  d.install_type<iter_subset>();

  d.install_std_type<vector<nat> >("vector<nat>");
  d.install_std_type<vector<string> >("vector<string>");
  d.install_std_type<list<string> >("list<string>");
  d.go();
}
