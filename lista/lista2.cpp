#include <iostream>
#include <cstdlib>

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
        void removeTodos(){
            Noh *aux = primeiro;
            Noh *temp;
            while(aux != NULL){
                temp = aux;
                aux =  aux->proximo;
                delete temp;
            }
            tamanho = 0;
            primeiro = NULL;
            ultimo = NULL;
        }
    public:
        Lista(){
            tamanho = 0;
            primeiro = NULL;
            ultimo = NULL;
        }
        Lista(const Lista& umaLista){
            tamanho = 0;
            primeiro = NULL;
            ultimo = NULL;
            Noh *aux = umaLista.primeiro;
            while(aux != NULL){
                insereFim(aux->dado);
                aux = aux->proximo;
            }
        }
        ~Lista(){
            removeTodos();
        }
        Lista& operator=(const Lista& umaLista){
            removeTodos();
            Noh* aux = umaLista.primeiro;
            while (aux != NULL){
                insereFim(aux->dado);
                aux = aux->proximo;
            }
            return *this;
        }
        void insereFim(Dado dado){
            Noh *novo = new Noh(dado);
            if(vazia()){
                primeiro = novo;
                ultimo = novo;
            }else{
                ultimo->proximo = novo;
                ultimo = novo;
            }
            tamanho++;
        }
        void insereInicio(Dado dado){
            Noh *novo = new Noh(dado);
            if(vazia()){
                primeiro = novo;
                ultimo = novo;
            }else{
                novo->proximo = primeiro;
                primeiro = novo;
            }
            tamanho++;
        }
        void inserePosicao(int pos, Dado dado){
            Noh *novo = new Noh(dado);
            if((pos <= tamanho) && (pos >= 0)){
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
                    int posAux = 0;
                    while(posAux < (pos-1)){
                        aux = aux->proximo;
                        posAux++;
                    }
                    novo->proximo = aux->proximo;
                    aux->proximo = novo;    
                }
            }
            tamanho++;
        }
        int procura(Dado valor){

        }
        void imprime(){

        }
        void imprimeReverso(){

        }
        bool vazia(){

        }
};