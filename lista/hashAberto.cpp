#include <iostream>

using namespace std;

struct Dado{
    int chave;
    int valor;
    int estado; // 0 - vazio; 1 - ocupado; 2 - removido
};

class HashAberto{
    private:
        Dado *tabela;
        int capacidade;
        int tamanho;
        int calculaHash(int chave){
            return chave % capacidade;
        }
        int buscaChave(int chave){
            int pos = calculaHash(chave);
            int inicio = pos;
            do {
                if(tabela[pos].estado == 0) return -1;
                if(tabela[pos].estado == 1 && tabela[pos].chave == chave) return pos;
                pos = (pos+1) % capacidade;
            } while(pos != inicio);
            return -1;
        }
    public:
        HashAberto(int cap){
            capacidade = cap;
            tamanho = 0;
            tabela = new Dado[cap];
            for(int i = 0; i < capacidade; i++){
                tabela[i].estado = 0;
            }
        }
        ~HashAberto(){
            delete[] tabela;
        }
        void inserir(int chave, int valor){
            if(tamanho == capacidade) throw runtime_error("Erro tabela cheia");
            if(buscaChave(chave) != -1) throw runtime_error("Item ja existe");
            int pos = calculaHash(chave);
            while(tabela[pos].estado == 1){
                pos = (pos+1) % capacidade;
            }
            tabela[pos].chave = chave;
            tabela[pos].valor = valor;
            tabela[pos].estado = 1;
            tamanho++;
        }
        void remover(int chave){
            if(tamanho == 0) throw runtime_error("Hash vazia");
            int pos = buscaChave(chave);
            if(pos == -1) throw runtime_error("Chave nao encontrada");
            tabela[pos].estado = 2;
            tamanho--;
        }
};
