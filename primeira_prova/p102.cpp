#include <iostream>

using namespace std;

const int CAPACIDADE = 5;

struct Item{
    string nome;
    int valor;
};

class Inventario{
    private:
        Item inventario[CAPACIDADE];
        int tamanho, topo;
    public:
        Inventario(){
            tamanho = 0;
            topo = 0;
        }
        ~Inventario(){
            while(topo>0){
                desempilhar();
            }
        }
        Item desempilhar(){
            if(tamanho==0) throw runtime_error("Erro");
            Item aux = inventario[tamanho-1];
            tamanho--;
            return aux;
        }
        void empilhar(Item it){
            if(tamanho<CAPACIDADE){
                inventario[tamanho-1] = it;
                tamanho++;
            }
        }
};