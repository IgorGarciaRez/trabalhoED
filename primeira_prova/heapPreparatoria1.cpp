#include <iostream>

using namespace std;

struct dado{
    string nome;
    char tipo;
    int energia;
    int tempo;
    int prioridade;
};

class Heap{
    private:
        dado* heap;
        int capacidade;
        int tamanho;
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
        Heap(int c){
            capacidade = c;
            heap = new dado[c];
            tamanho = 0;
        }
        ~Heap(){
            delete[] heap;
        }
        void arruma(){
            for(int i=tamanho/2-1; i>=0; i--){
                corrigeDescendo(i);
            }
        }
        void corrigeDescendo(int i){
            int esq = filhoEsquerda(i);
            int dir = filhoDireita(i);
            int maior = i;
            if((esq < tamanho) && (heap[esq].energia > heap[maior].energia)){
                maior = esq;
            }
            if((dir < tamanho) && (heap[dir].energia > heap[maior].energia)){
                maior = dir;
            }
            if(maior!=i){
                dado aux = heap[maior];
                heap[maior] = heap[i];
                heap[i] = aux;
                corrigeDescendo(maior);
            }
        }
        void corrigeSubindo(int i){
            int p = retornaPai(i);
            if(heap[i].energia > heap[p].energia){
                dado aux = heap[i];
                heap[i] = heap[p];
                heap[p] = aux;
                corrigeSubindo(p);
            }
        }
        dado retiraRaiz(){
            if(tamanho == 0) throw runtime_error("Erro ao retirar raiz");
            dado aux = heap[0];
            heap[0] = heap[tamanho-1];
            tamanho--;
            corrigeDescendo(0);
            return aux;
        }
        void insere(dado d){
            if(tamanho == capacidade) throw runtime_error("Erro ao inserir");
            heap[tamanho] = d;
            corrigeSubindo(tamanho);
            tamanho++;
        }
        void imprime(){
            if(tamanho == 0) throw runtime_error("Heap vazia!");
            for(int i = 0; i<tamanho; i++){
                cout <<"["<< heap[i].nome << "/" << heap[i].tipo << "/" << heap[i].energia << "/" << heap[i].tempo << "/" << heap[i].prioridade << "] "; 
            }
            cout << endl;
        }
};

int main() {
    int capacidade;
    dado info;
    char comando;

    cin >> capacidade;
    Heap meuHeap(capacidade);

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.energia >> info.tempo >> info.prioridade;
                    meuHeap.insere(info);
                    break;
                case 'r': // remover
                    cout << meuHeap.retiraRaiz().nome << endl;
                    break;
                case 'p': // limpar tudo
                    meuHeap.imprime();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}