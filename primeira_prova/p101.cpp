#include <iostream>

using namespace std;

struct Item{
    string nome;
    char tipo;
    int valor;
};

class Noh{
    friend class Inventario;
    private:
        Item item;
        Noh *proximo;
    public:
        Noh(Item it){
            item = it;
            proximo = NULL;
        }
};

class Inventario{
    private:
        Noh *topo;
        int tamanho;
    public:
        Inventario(){
            topo = NULL;
            tamanho = 0;
        }
        ~Inventario(){
            limparInventario();
        }
        void limparInventario(){
            while(tamanho!=0){
                desempilhar();
            }
        }
        Noh desempilhar(){
            if(tamanho==0) throw runtime_error("Erro, pilha vazia");
            Noh *aux = topo;
            Item removido = aux->item;
            delete aux;
            topo = topo->proximo;
            tamanho--;
            return removido;
        }
        void empilhar(Item it){
            Noh *novo = new Noh(it);
            novo->proximo = topo;
            topo = novo;
            tamanho++;
        }
};
