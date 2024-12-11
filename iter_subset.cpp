#include "iter_subset.hpp"

/* Pre:  Cert
   Post: Construeix un iterador sobre els subconjunts de k elements
   de {1, ..., n}; si k > n no hi ha res a recórrer. */
iter_subset::iter_subset(nat n, nat k) throw(error) {
    this->n = n;
    this->k = k;
    if (k <= n) {
        termina = false; // pot generar més subconjunts
        sub_actual.resize(k);
        for (nat i = 0; i < k; ++i) {
            sub_actual[i]=i+1;
        }
    }
    else { //no es pot generar subconjunts
        termina = true;
    }
    return;
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
iter_subset::iter_subset(const iter_subset& its) throw(error) {
    this->n = its.n;
    this->k = its.k;
    this->termina = its.termina;
    this->sub_actual = its.sub_actual;
}
iter_subset& iter_subset::operator=(const iter_subset& its) throw(error){
    if (this != &its) {
        this->n = its.n;
        this->k = its.k;
        this->termina = its.termina;
        this->sub_actual = its.sub_actual;
    }
    return *this;
}
iter_subset::~iter_subset() throw(){}

/* Pre:  Cert
   Post: Retorna cert si l'iterador ja ha visitat tots els subconjunts
   de k elements presos d'entre n; o dit d'una altra forma, retorna
   cert quan l'iterador apunta a un subconjunt sentinella fictici
   que queda a continuació de l'últim subconjunt vàlid. */
bool iter_subset::end() const throw() {
    return termina;
}

/* Operador de desreferència.
   Pre:  Cert
   Post: Retorna el subconjunt apuntat per l'iterador;
   llança un error si l'iterador apunta al sentinella. */
subset iter_subset::operator*() const throw(error){
    if (!termina) return sub_actual;
    throw error(IterSubsetIncorr);
}

/* Operador de preincrement.
   Pre:  Cert
   Post: Avança l'iterador al següent subconjunt en la seqüència i el retorna;
   no es produeix l'avançament si l'iterador ja apuntava al sentinella. */
iter_subset& iter_subset::operator++() throw() {
    if (!termina) {
        termina = !combina(); //Generació de la següent combinació/subconjunt.
                            //Si és true vol dir que s'ha pogut generar un subconjunt més , per tant, el genera i confirma que no ha terminat de moment.
    }
    return *this; //el subconjunt ja s'ha generat per la funció 'combina'
}

/* Operador de postincrement.
   Pre:  Cert
   Post: Avança l'iterador al següent subconjunt en la seqüència i retorna el seu valor
   previ; no es produeix l'avançament si l'iterador ja apuntava al sentinella. */
iter_subset iter_subset::operator++(int) throw(){
    iter_subset aux = *this;
    if (!termina) {
        ++(*this);
    }
    return aux;
}

/* Operadors relacionals. */
bool iter_subset::operator==(const iter_subset& c) const throw(){
    if(k==0 && c.k==0 && n!=0 && c.n!=0 && termina==c.termina) return true;
    return (termina == c.termina && sub_actual == c.sub_actual && n == c.n && k == c.k);
}

bool iter_subset::operator!=(const iter_subset& c) const throw(){
	return !(*this==c);
}

bool iter_subset::combina() {
    for (nat i = k - 1; i >= 0 && i < sub_actual.size(); --i) {
        // Comprobamos que el índice 'i' esté dentro de los límites de sub_actual
        if (sub_actual[i] < n - (k - 1 - i)) {
            ++sub_actual[i];
            for (nat j = i + 1; j < k; ++j) {
                sub_actual[j] = sub_actual[j - 1] + 1;
            }
            return true; // Hemos generado una nueva combinación
        }
    }
    termina = true; // No hay más combinaciones
    return false;
}
