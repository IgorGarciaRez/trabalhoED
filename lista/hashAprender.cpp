#include <iostream>

using namespace std;

struct Dado{
    int chave;
    int valor;
};

class Noh{
    friend class Lista;
    friend class Hash;
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
    friend class Hash;
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
            while((aux != NULL) && (aux->dado.valor != d.valor)){
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
        Noh* buscar(int chave){
            if(vazia()) throw runtime_error("Lista vazia");
            Noh *aux = primeiro;
            while(aux != NULL){
                if(aux->dado.chave == chave){
                    return aux;
                }
                aux = aux->proximo;
            }
            throw runtime_error("Elemento nao encontrado");
            return NULL;
        }
};

class Hash{
    private:
        int cap;
        Lista *tabela;
        int chaveHash(int chave){
            return chave % cap;
        }
    public:
        Hash(int capacidade){
            cap = capacidade;
            tabela = new Lista[cap];
        }
        ~Hash(){
            delete[] tabela;
        }
        void inserir(int chave, int valor){
            int pos = chaveHash(chave);
            Dado d = Dado{chave, valor};
            Noh *inserido = new Noh(d);
            if(tabela[pos].buscar(chave) == NULL) tabela[pos].insereFim(d);
            else throw runtime_error("Elemento já inserido");
        }
        Noh* recuperar(int chave){
            int pos = chaveHash(chave);
            Noh *n = tabela[pos].buscar(chave);
            if(n == NULL) throw runtime_error("Elemento nao encontrado");
            else return n;
        }
        void alterar(int chave, int novoValor){
            int pos = chaveHash(chave);
            Noh *n = tabela[pos].buscar(chave);
            if(n == NULL) throw runtime_error("Elemento nao encontrado");
            else n->dado.valor = novoValor;
        }
        void apagar(int chave){
            int pos = chaveHash(chave);
            Noh *n = tabela[pos].buscar(chave);
            if(n == NULL) throw runtime_error("Elemento nao encontrado");
            else tabela[pos].removeTodos();
        }
        void redimensionar(int novaCapacidade){
            Lista *tabelaAux = new Lista[novaCapacidade];
            for(int i = 0; i < cap; i++){
                Noh* atual = tabela[i].primeiro;
                while(atual != NULL){
                    int novaPos = atual->dado.chave % novaCapacidade;
                    tabelaAux[novaPos].insereFim(atual->dado);
                    atual = atual->proximo;
                }
            }
            delete[] tabela;
            tabela = tabelaAux;
            cap = novaCapacidade;
        }
};