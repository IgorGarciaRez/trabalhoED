#include <iostream>

using namespace std;

const int CAPACIDADE_FILA = 6;

struct Processo{
    string assunto;
    string nome;
    char tipo;
    int nProcesso;
};

void imprimirDado(const Processo& proc){
    cout << proc.assunto << " " << proc.nome << " " << proc.tipo << " " << proc.nProcesso << endl;
}

class Fila{
    private: 
        Processo fila[CAPACIDADE_FILA]; //precisa ser ponteiro??
        int inicio, fim, tamanho;
    public:
        Fila(){
            inicio = 0;
            fim = -1;
            tamanho = 0;
        }
        ~Fila(){
            while(tamanho > 0){desenfileirar();}
        }
        bool estaVazia(){ return tamanho == 0;}
        bool estaCheia(){ return tamanho == CAPACIDADE_FILA;}
        void enfileirar(const Processo& p){
            if(estaCheia()){ throw runtime_error("Erro: fila cheia!");}
            if(fim < CAPACIDADE_FILA){
                fim = (fim + 1) % CAPACIDADE_FILA;
                fila[fim] = p;
                tamanho++;
            }
        };
        Processo desenfileirar(){
            if(estaVazia()){ throw runtime_error("Erro: fila vazia!");}
            Processo valor = fila[inicio];
            inicio = (inicio + 1) % CAPACIDADE_FILA;
            tamanho--;
            return valor;
        };
        Processo espiar(){
            if(estaVazia()){throw runtime_error("Erro: fila vazia!");}
            return fila[inicio];
        }
        void limpar(){
            while(!estaVazia()){
                desenfileirar();
            }
        }
        void ordenar(){
            Fila temp;
            Processo menor, aux;
            while(!estaVazia()){
                menor = desenfileirar();
                for(int i = 0; i < tamanho; i++){
                    aux = desenfileirar();
                    if(aux.nProcesso > menor.nProcesso){
                        enfileirar(aux);
                    }else{
                        enfileirar(menor);
                        menor = aux;
                    }
                }
                temp.enfileirar(menor);
            }
            while (!temp.estaVazia()) {
                enfileirar(temp.desenfileirar());
                cout<<"desenfileira"<<endl;
            }
        }
};

int main(){
    Fila fila;
    Processo info;
    char comando;
    do
    {
        try
        {
            cin>>comando;
            switch(comando){
                case 'i':
                    cin>>info.assunto>>info.nome>>info.tipo>>info.nProcesso;
                    fila.enfileirar(info);
                    break;
                case 'o':
                    fila.ordenar();
                    break;
                case 'r': // remover
                    imprimirDado(fila.desenfileirar());
                    break;
                case 'l': // limpar tudo
                    fila.limpar();
                    break;
                case 'e': // espiar 
                    if(!fila.estaVazia())               
                        imprimirDado(fila.espiar());
                    else
                        cout << "Erro: fila vazia!"<< endl;
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        }
        catch(runtime_error& e)
        {
            cout<<e.what()<<endl;
        }
        
    } while (comando != 'f');
    while (! fila.estaVazia()) {
        imprimirDado(fila.desenfileirar());
    }
    cout << endl;
    return 0; 
}