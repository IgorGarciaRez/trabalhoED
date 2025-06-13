#include <iostream>
using namespace std;

struct Node {
    int valor;
    Node* proximo;

    Node(int v) : valor(v), proximo(nullptr) {}
};

class Lista {
private:
    Node* cabeca;

    // Função auxiliar para imprimir em ordem reversa (recursiva)
    void imprimeReversoAux(Node* no) {
        if (no == nullptr) return;
        imprimeReversoAux(no->proximo);
        cout << no->valor << " -> ";
    }

public:
    Lista() : cabeca(nullptr) {}

    ~Lista() {
        while (cabeca != nullptr) {
            Node* temp = cabeca;
            cabeca = cabeca->proximo;
            delete temp;
        }
    }

    void insereNoInicio(int valor) {
        Node* novo = new Node(valor);
        novo->proximo = cabeca;
        cabeca = novo;
    }

    void insereNoFim(int valor) {
        Node* novo = new Node(valor);
        if (cabeca == nullptr) {
            cabeca = novo;
        } else {
            Node* atual = cabeca;
            while (atual->proximo != nullptr) {
                atual = atual->proximo;
            }
            atual->proximo = novo;
        }
    }

    void insereNaPosicao(int valor, int posicao) {
        if (posicao <= 0 || cabeca == nullptr) {
            insereNoInicio(valor);
            return;
        }

        Node* atual = cabeca;
        int contador = 0;

        while (atual != nullptr && contador < posicao - 1) {
            atual = atual->proximo;
            contador++;
        }

        if (atual == nullptr) {
            insereNoFim(valor);
        } else {
            Node* novo = new Node(valor);
            novo->proximo = atual->proximo;
            atual->proximo = novo;
        }
    }

    bool procura(int valor) {
        Node* atual = cabeca;
        while (atual != nullptr) {
            if (atual->valor == valor) return true;
            atual = atual->proximo;
        }
        return false;
    }

    void imprime() {
        Node* atual = cabeca;
        while (atual != nullptr) {
            cout << atual->valor << " -> ";
            atual = atual->proximo;
        }
        cout << "NULL" << endl;
    }

    void imprimeReverso() {
        imprimeReversoAux(cabeca);
        cout << "NULL" << endl;
    }
};

int main() {
    Lista lista;

    lista.insereNoInicio(10);
    lista.insereNoFim(20);
    lista.insereNaPosicao(15, 1); // entre 10 e 20
    lista.insereNaPosicao(5, 0);  // no início
    lista.insereNaPosicao(100, 10); // no fim

    cout << "Lista normal: ";
    lista.imprime();

    cout << "Lista reversa: ";
    lista.imprimeReverso();

    cout << "Procurando 15: " << (lista.procura(15) ? "Encontrado" : "Não encontrado") << endl;
    cout << "Procurando 99: " << (lista.procura(99) ? "Encontrado" : "Não encontrado") << endl;

    return 0;
}
