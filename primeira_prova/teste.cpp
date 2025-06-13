#include <iostream>
using namespace std;

struct dado {
    string nome = "vazio";
    string tipo;
    dado* proximo = NULL;
};

class fila {
private:
    dado* inicio;
    dado* fim;
    int tamanho;

public:
    fila() {
        inicio = NULL;
        fim = NULL;
        tamanho = 0;
    }

    bool vazia() {
        return tamanho == 0;
    }

    void enfileirar(dado entrada) {
        dado* novo = new dado;
        *novo = entrada;
        novo->proximo = NULL;
        if (fim != NULL)
            fim->proximo = novo;
        else
            inicio = novo;
        fim = novo;
        tamanho++;
    }

    dado desenfileirar() {
        if (inicio == NULL)
            throw runtime_error("Fila vazia!");
        dado retorno = *inicio;
        dado* removido = inicio;
        inicio = inicio->proximo;
        if (inicio == NULL)
            fim = NULL;
        delete removido;
        tamanho--;
        return retorno;
    }

    ~fila() {
        while (!vazia()) {
            desenfileirar();
        }
    }
};

int main() {
    fila filaNormal, filaPrioridade;
    string comando;
    dado entrada;
    int contador = 0;

    cin >> comando;
    while (comando != "fim") {
        if (comando == "normal") {
            cin >> entrada.nome;
            entrada.tipo = "normal";
            filaNormal.enfileirar(entrada);
        } else if (comando == "prioridade") {
            cin >> entrada.nome;
            entrada.tipo = "prioridade";
            filaPrioridade.enfileirar(entrada);
        } else if (comando == "atender") {
            if (contador < 3 && !filaPrioridade.vazia()) {
                dado atendido = filaPrioridade.desenfileirar();
                cout << atendido.nome << endl;
                contador++;
            } else if (!filaNormal.vazia()) {
                dado atendido = filaNormal.desenfileirar();
                cout << atendido.nome << endl;
                contador = 0; // Reseta após atendimento normal
            } else if (!filaPrioridade.vazia()) {
                dado atendido = filaPrioridade.desenfileirar();
                cout << atendido.nome << endl;
                contador++;
            } else {
                cout << "AGUARDE" << endl;
            }
        }

        cin >> comando;
    }

    return 0;
}
