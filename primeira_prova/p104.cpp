#include <iostream>

using namespace std;

const int CAPACIDADE = 5;

struct Processo{
    int id;
    string nome;
};

class Fila{
    private:
        Processo fila[CAPACIDADE];
        int inicio, fim, tamanho;
    public:
        Fila(){
            inicio = 0;
            fim = -1;
            tamanho = 0;
        }
        ~Fila(){
            while(tamanho>0){
                desenfileira();
            }
        }
        Processo desenfileira(){
            if(tamanho<1) throw runtime_error("Erro");
            Processo aux = fila[inicio];
            inicio = (inicio+1)%CAPACIDADE;
            tamanho--;
            return aux;
        }
        void enfileira(Processo p){
            if(tamanho-1 >= CAPACIDADE) throw runtime_error("Erro");
            fila[fim] = p;
            fim = (fim+1)%CAPACIDADE;
            tamanho++;
        }

};
