#include <iostream>

using namespace std;

typedef int Dado;

class Noh{
    friend class Lista;
    private:
        Dado dado;
        Noh *proximo;
    public:
        Noh(Dado d){
            dado = d;
            proximo = NULL;
        }
};

class Lista{
    private:
        Noh *primeiro;
        Noh *ultimo;
        int tamanho;
    public:
        Lista(){
            tamanho = 0;
            primeiro = NULL;
            ultimo = NULL;
        }
        void removeTodos(){
            Noh *aux = primeiro;
            Noh *temp = NULL;
            while(aux != NULL){
                temp = aux;
                aux = aux->proximo;
                delete temp;
            }
            tamanho = 0;
            primeiro = NULL;
            ultimo = NULL;
        }
        bool vazia(){
            return (tamanho = 0);
        }
        void insereFim(Dado d){
            Noh *novo = new Noh(d);
            if(vazia()){
                primeiro = novo;
                ultimo = novo;
            }else{
                ultimo->proximo = novo;
                ultimo = novo;
            }
            tamanho++;
        }
        void insereInicio(Dado d){
            Noh *novo = new Noh(d);
            if(vazia()){
                primeiro = novo;
                ultimo = novo;
            }else{
                novo->proximo = primeiro;
                primeiro = novo;
            }
            tamanho++;
        }
        void inserePosicao(Dado d, int pos){
            Noh *novo = new Noh(d);
            if(vazia()){
                primeiro = novo;
                ultimo = novo;
            }else if(pos == 0){
                novo->proximo = primeiro;
                primeiro = novo;
            }else if(pos == tamanho){
                ultimo->proximo = novo;
                ultimo = novo;
            }else{
                Noh *aux = primeiro;
                int ind = 0;
                while(ind < (pos-1)){
                    aux = aux->proximo;
                    ind++;
                }
                novo->proximo = aux->proximo;
                aux->proximo = novo;
            }
            tamanho++; 
        }
        void removeInicio(){
            if(vazia()) throw runtime_error("Lista vazia");
            Noh *aux = primeiro;
            primeiro = primeiro->proximo;
            delete aux;
            tamanho--;
            if(vazia()) ultimo = NULL;
        }
        void removeFim(){
            if(vazia()) throw runtime_error("Lista vazia");
            Noh *aux = primeiro;
            Noh *anterior;
            while(aux->proximo != NULL){
                anterior = aux;
                aux = aux->proximo;
            }
            delete aux;
            anterior->proximo = NULL;
            ultimo = anterior;
            tamanho--;
            if(vazia()) primeiro = NULL;
        }
        void removeNoh(Dado d){
            if(vazia()) throw runtime_error("Lista vazia");
            Noh *aux = primeiro;
            Noh *anterior;
            while((aux != NULL) && (aux->dado != d)){
                anterior = aux;
                aux = aux->proximo;
            }
            if(aux != NULL){
                if(aux == primeiro){
                    removeInicio();
                }else if(aux == ultimo){
                    removeFim();
                }else{
                    anterior->proximo = aux->proximo;
                    delete aux;
                    tamanho--;
                }
            }else throw runtime_error("Não encontrado");
        }
};