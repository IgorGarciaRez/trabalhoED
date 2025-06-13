#include <iostream>

using namespace std;

struct Item{
    string name;
    int value;
};

class Noh{
    friend class Inventory;
    private:
        Item item;
        Noh *proximo;
    public:
        Noh(Item it){
            item = it;
            proximo = NULL;
        }
};

class Inventory{
    private:
        Noh *topo;
        int tamanho;
    public:
        Inventory(){
            topo = NULL;
            tamanho = 0;
        }
        ~Inventory(){
            if(tamanho<1) throw runtime_error("Erro");
            while(tamanho>0){
                desenfileira();
            }
        }
        Item desenfileira(){
            if(tamanho<1) throw runtime_error("Erro");
            Noh *aux = topo;
            Item removido = aux->item;
            delete aux;
            topo = topo->proximo;
            tamanho--;
            return removido;
        }
        void enfileira(Item it){
            Noh *novo = new Noh(it);
            novo->proximo = topo;
            topo = novo;
            tamanho++;
        }
};