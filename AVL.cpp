#include <iostream>
#include <list>
using namespace std;

template <typename T>
class AVLTree {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        int height;

        Node(const T& k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Devuelve la altura de un nodo
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    // Calcula el factor de equilibrio
    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Realiza una rotación hacia la derecha
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Realiza una rotación hacia la izquierda
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Inserta un valor de forma recursiva
    Node* insert(Node* node, const T& key) {
        if (!node) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            // Clave duplicada, no se permite
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        // Caso de rotación derecha
        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }

        // Caso de rotación izquierda
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }

        // Caso de rotación izquierda-derecha
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Caso de rotación derecha-izquierda
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Busca un valor en el árbol
    bool search(Node* node, const T& key) {
        if (!node) {
            return false;
        }

        if (key == node->key) {
            return true;
        } else if (key < node->key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    // Recorre el árbol en orden y almacena los valores en una lista
    void inorderTraversal(Node* node, list<T>& values) {
        if (node) {
            inorderTraversal(node->left, values);
            values.push_back(node->key);
            inorderTraversal(node->right, values);
        }
    }

    // Libera la memoria de los nodos
    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        deleteTree(root);
    }

    // Inserta una clave en el árbol
    void insert(const T& key) {
        root = insert(root, key);
    }

    // Busca una clave en el árbol
    bool search(const T& key) {
        return search(root, key);
    }

    // Inserta una lista de valores
    void insertList(const list<T>& values) {
        for (const auto& value : values) {
            insert(value);
        }
    }

    // Devuelve una lista de los elementos en orden ascendente
    list<T> getInOrder() {
        list<T> values;
        inorderTraversal(root, values);
        return values;
    }

    // Imprime los elementos en orden ascendente
    void print() {
        list<T> values = getInOrder();
        for (const auto& value : values) {
            cout << value << " ";
        }
        cout << endl;
    }
};
