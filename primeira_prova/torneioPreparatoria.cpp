#include <iostream>

using namespace std;

typedef int dado;
const int INVALIDO = -1;

class Torneio{
    private:
        dado* heap;
        int capacidade;
        int tamanho;
        int inicioDados;
        int retornaPai(int n){
            return (n-1)/2;
        }
        int filhoEsquerda(int n){
            return n*2 + 1;
        }
        int filhoDireita(int n){
            return n*2 + 2;
        }
    public:
        Torneio(int tam){
            capacidade = 1;
            while(capacidade < tam){
                capacidade *= 2;
            }
            capacidade = capacidade -1 + tam;
            heap = new dado[capacidade];
            inicioDados = capacidade - tam;
            cout << "inicioDados: " << inicioDados << endl;
            cout << "capacidade: " << capacidade << endl;
            for(int i = 0; i < tam; i++){
                heap[i] = INVALIDO;
            }
            tamanho = 0;
        }
        ~Torneio(){
            delete[] heap;
        }
        void arruma(){
            cout<<"arruma: " << inicioDados-1 << endl;
            for(int i = inicioDados-1; i >= 0; i--){
                copiaMaior();
            }
        }
        void copiaMaior(int i){
            int esq = filhoEsquerda(i);
            int dir = filhoDireita(i);
            int maior = -1;
            if(esq < capacidade){
                if((dir<capacidade) && (heap[dir] > heap[esq])){
                    maior = dir;
                }else{
                    maior = esq;
                }
                heap[i] = heap[maior];
            }else{
                heap[i] = INVALIDO;
            }
        }
        void copiaSubindo(int i){
            int pai = retornaPai(i);
            if(heap[i] > heap[pai]){
                heap[pai] = heap[i];
                copiaSubindo(pai);
            }
        }
        void insere(dado d){
            if(tamanho == capacidade) throw runtime_error("Erro ao inserir");
            heap[tamanho+inicioDados] = d;
            copiaSubindo(tamanho+inicioDados);
            tamanho++;
        }
}