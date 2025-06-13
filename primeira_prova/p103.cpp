#include <iostream>

using namespace std;

struct Processo{
    int id;
    string nome;
};

class Noh{
    friend class Fila;
    private:
        Processo proc;
        Noh *prox;
    public:
        Noh(Processo p){
            proc = p;
            prox = NULL;
        }
};

class Fila{
    private:
        Noh *primeiro;
        Noh *ultimo;
    public:
        Fila(){
            primeiro = NULL;
            ultimo = NULL;
        }
        ~Fila(){
            while(!vazia()){
                desenfileirar();
            }
        }
        bool vazia(){
            return (primeiro == NULL && ultimo == NULL);
        }
        void enfileirar(Processo p){
            Noh *novo = new Noh(p);
            ultimo->prox = novo;
        }
        Processo desenfileirar(){
            if(vazia()) throw runtime_error("Erro");
            Noh *aux = primeiro;
            primeiro = aux->prox;
            delete aux;
            return primeiro->proc;
        }
};