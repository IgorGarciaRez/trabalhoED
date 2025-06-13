#include <iostream>

using namespace std;

struct Dado{
    int valor;
    string nome;
};

class MaxHeap{
    private:
        Dado *heap;
        int capacidade, tamanho;
        int retornaPai(int i){
            return (i-1)/2;
        }
        int retornaEsquerdo(int i){
            return 2*i+1;
        }
        int retornaDireito(int i){
            return 2*i+2;
        }
        void arruma(){

        }
    public:
        MaxHeap(int cap){
            capacidade = cap;
            heap = new Dado[cap];
            tamanho = 0;
        }
        ~MaxHeap(){
            delete[] heap;
        }
        void arruma(){
            for(int i=(tamanho/2-1); i>=0; i++){
                corrigeDescendo(i);
            }
        }
        void corrigeDescendo(int i){
            int esq = retornaEsquerdo(i);
            int dir = retornaDireito(i);
            int maior;
            Dado aux;
            if(esq <= tamanho && heap[esq].valor > heap[i].valor){
                maior = esq;
            }else{
                maior = i;
            }
            if(dir <= tamanho && heap[dir].valor > heap[maior].valor){
                maior = dir;
            }
            if(maior!=i){
                aux = heap[maior];
                heap[maior] = heap[i];
                heap[i] = aux;
                corrigeDescendo(maior);
            }
        }
        void corrigeSubindo(int i){
            int pai = retornaPai(i);
            if(heap[i].valor > heap[pai].valor){
                Dado aux = heap[i];
                heap[i] = heap[pai];
                heap[pai] = aux;
                corrigeSubindo(pai);
            }
        }
        Dado retiraRaiz(){
            if(tamanho==0) throw runtime_error("Erro");
            Dado aux = heap[0];
            heap[0] = heap[tamanho-1];
            tamanho--;
            corrigeDescendo(0);
            return aux;
        }
        void insere(Dado d){
            if(tamanho==capacidade) throw runtime_error("Erro");
            heap[tamanho] = d;
            corrigeSubindo(tamanho);
            tamanho++;
        }
};