#include <iostream>
#include <list>
using namespace std;

template <typename T>
class AVLArbre {
private:
    struct Node {
        T clau;
        Node* esquerra;
        Node* dreta;
        int altura;

        Node(const T& c) : clau(c), esquerra(nullptr), dreta(nullptr), altura(1) {}
    };

    Node* arrel;

    // Retorna l'altura d'un node
    // Cost temporal: O(1)
    int obtenirAltura(Node* node) {
        return node ? node->altura : 0;
    }

    // Calcula el factor d'equilibri
    // Cost temporal: O(1)
    int obtenirFactorEquilibri(Node* node) {
        return node ? obtenirAltura(node->esquerra) - obtenirAltura(node->dreta) : 0;
    }

    // Realitza una rotació cap a la dreta
    // Cost temporal: O(1)
    Node* rotacioDreta(Node* y) {
        Node* x = y->esquerra;
        Node* T2 = x->dreta;

        x->dreta = y;
        y->esquerra = T2;

        y->altura = max(obtenirAltura(y->esquerra), obtenirAltura(y->dreta)) + 1;
        x->altura = max(obtenirAltura(x->esquerra), obtenirAltura(x->dreta)) + 1;

        return x;
    }

    // Realitza una rotació cap a l'esquerra
    // Cost temporal: O(1)
    Node* rotacioEsquerra(Node* x) {
        Node* y = x->dreta;
        Node* T2 = y->esquerra;

        y->esquerra = x;
        x->dreta = T2;

        x->altura = max(obtenirAltura(x->esquerra), obtenirAltura(x->dreta)) + 1;
        y->altura = max(obtenirAltura(y->esquerra), obtenirAltura(y->dreta)) + 1;

        return y;
    }

    // Insereix un valor de manera recursiva
    // Cost temporal: O(log n), perquè el màxim de comparacions i rotacions és proporcional a l'altura de l'arbre.
    Node* inserir(Node* node, const T& clau) {
        if (!node) {
            return new Node(clau);
        }

        if (clau < node->clau) {
            node->esquerra = inserir(node->esquerra, clau);
        } else if (clau > node->clau) {
            node->dreta = inserir(node->dreta, clau);
        } else {
            // Clau duplicada, no es permet
            return node;
        }

        node->altura = 1 + max(obtenirAltura(node->esquerra), obtenirAltura(node->dreta));

        int equilibri = obtenirFactorEquilibri(node);

        // Casos de rotació
        if (equilibri > 1 && clau < node->esquerra->clau) {
            return rotacioDreta(node);
        }
        if (equilibri < -1 && clau > node->dreta->clau) {
            return rotacioEsquerra(node);
        }
        if (equilibri > 1 && clau > node->esquerra->clau) {
            node->esquerra = rotacioEsquerra(node->esquerra);
            return rotacioDreta(node);
        }
        if (equilibri < -1 && clau < node->dreta->clau) {
            node->dreta = rotacioDreta(node->dreta);
            return rotacioEsquerra(node);
        }

        return node;
    }

    // Cerca un valor a l'arbre
    // Cost temporal: O(log n), perquè només cal recórrer l'altura de l'arbre.
    bool cerca(Node* node, const T& clau) {
        if (!node) {
            return false;
        }

        if (clau == node->clau) {
            return true;
        } else if (clau < node->clau) {
            return cerca(node->esquerra, clau);
        } else {
            return cerca(node->dreta, clau);
        }
    }

    // Recorre l'arbre en ordre i emmagatzema els valors en una llista
    // Cost temporal: O(n), perquè es visiten tots els nodes exactament una vegada.
    void recorregutInordre(Node* node, list<T>& valors) {
        if (node) {
            recorregutInordre(node->esquerra, valors);
            valors.push_back(node->clau);
            recorregutInordre(node->dreta, valors);
        }
    }

    // Allibera la memòria dels nodes
    // Cost temporal: O(n), perquè cal visitar tots els nodes per eliminar-los.
    void eliminarArbre(Node* node) {
        if (node) {
            eliminarArbre(node->esquerra);
            eliminarArbre(node->dreta);
            delete node;
        }
    }

public:
    AVLArbre() : arrel(nullptr) {}

    ~AVLArbre() {
        eliminarArbre(arrel);
    }

    // **Precondició**: cap.
    // **Postcondició**: Insereix una clau a l'arbre AVL.
    // Cost temporal: O(log n)
    void inserir(const T& clau) {
        arrel = inserir(arrel, clau);
    }

    // **Precondició**: cap.
    // **Postcondició**: Retorna cert si la clau existeix a l'arbre; altrament, fals.
    // Cost temporal: O(log n)
    bool cerca(const T& clau) {
        return cerca(arrel, clau);
    }

    // **Precondició**: cap.
    // **Postcondició**: Insereix una llista de valors a l'arbre AVL.
    // Cost temporal: O(m log n), on \(m\) és la mida de la llista i \(n\) el nombre de nodes actuals de l'arbre.
    void inserirLlista(const list<T>& valors) {
        for (const auto& valor : valors) {
            inserir(valor);
        }
    }

    // **Precondició**: cap.
    // **Postcondició**: Retorna una llista dels elements en ordre ascendent.
    // Cost temporal: O(n)
    list<T> obtenirEnOrdre() {
        list<T> valors;
        recorregutInordre(arrel, valors);
        return valors;
    }

    // **Precondició**: cap.
    // **Postcondició**: Imprimeix els elements en ordre ascendent.
    // Cost temporal: O(n)
    void imprimeix() {
        list<T> valors = obtenirEnOrdre();
        for (const auto& valor : valors) {
            cout << valor << " ";
        }
        cout << endl;
    }
};
