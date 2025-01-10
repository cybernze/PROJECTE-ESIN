#include "iter_subset.hpp"

// Cost: O(k)
iter_subset::iter_subset(nat n, nat k) throw(error) {
    this->n = n;
    this->k = k;
    if (k <= n) {
        termina = false;
        sub_actual.resize(k);
        for (nat i = 0; i < k; ++i) {
            sub_actual[i] = i + 1;
        }
    } else {
        termina = true;
    }
    return;
}

// Cost: O(k)
iter_subset::iter_subset(const iter_subset& its) throw(error) {
    this->n = its.n;
    this->k = its.k;
    this->termina = its.termina;
    this->sub_actual = its.sub_actual;
}

// Cost: O(k)
iter_subset& iter_subset::operator=(const iter_subset& its) throw(error) {
    if (this != &its) {
        this->n = its.n;
        this->k = its.k;
        this->termina = its.termina;
        this->sub_actual = its.sub_actual; // Assignació del subconjunt actual.
    }
    return *this;
}

// Cost: O(1)
iter_subset::~iter_subset() throw() {}

// Cost: O(1)
bool iter_subset::end() const throw() {
    return termina;
}

// Cost: O(k)
subset iter_subset::operator*() const throw(error) {
    if (!termina) return sub_actual;
    throw error(IterSubsetIncorr);
}

// Cost: O(k)
iter_subset& iter_subset::operator++() throw() {
    if (!termina) {
        termina = !combina();
    }
    return *this;
}

// Cost: O(k)
iter_subset iter_subset::operator++(int) throw() {
    iter_subset aux = *this;
    if (!termina) {
        ++(*this);
    }
    return aux;
}

// Cost: O(k)
bool iter_subset::operator==(const iter_subset& c) const throw() {
    if (k == 0 && c.k == 0 && n != 0 && c.n != 0 && termina == c.termina) return true; // Cas especial.
    return (termina == c.termina && sub_actual == c.sub_actual && n == c.n && k == c.k);
}

// Cost: O(k)
bool iter_subset::operator!=(const iter_subset& c) const throw() {
    return !(*this == c);
}

// Cost: O(k)
bool iter_subset::combina() {
    for (nat i = k - 1; i >= 0 && i < sub_actual.size(); --i){

        if (sub_actual[i] < n - (k - 1 - i)) {
            ++sub_actual[i];

            for (nat j = i + 1; j < k; ++j) {
                sub_actual[j] = sub_actual[j - 1] + 1;
            }
            return true;
        }
    }
    termina = true;
    return false;
}
