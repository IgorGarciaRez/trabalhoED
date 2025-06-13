#include <iostream>
using namespace std;

struct Dado
{
    string nome = "vazio";
    string tipo;
    Dado *proximo;
};

class Noh{
    friend class Fila;
    private:
        Dado dado;
        Noh *prox;
    public:
        Noh(Dado d){
            dado = d;
            prox = NULL;
        }
};

class Fila{
    private:
        Noh *primeiro;
        Noh *ultimo;
        Fila *normal, *prioridade;
        int tamanho;
        bool arrumada;
    public:
        Fila(){
            primeiro = NULL;
            ultimo = NULL;
            tamanho = 0;
            arrumada = false;
        }
        ~Fila(){
            while(!vazia()){
                desenfileirar();
            }
        }
        bool vazia(){
            return (primeiro == NULL && ultimo == NULL);
        }
        void enfileirar(Dado d){
            Noh *novo = new Noh(d);
            if (vazia()) {
                primeiro = novo;
                ultimo = novo;
            } else {
                ultimo->prox = novo;
                ultimo = novo;
            }
            tamanho++;
            arrumada = false;
        }
        Dado desenfileirar(){
            if(vazia()) throw runtime_error("Erro");
            Noh *aux = primeiro;
            Dado d = aux->dado;
            primeiro = aux->prox;
            delete aux;
            tamanho--;
            return d;
        }
        void arrumaPrioridade(){
            if(this->tamanho == 0) throw runtime_error("Erro");
            int qtd = tamanho;
            int ind = 0;
            for(int i = 0; i < qtd; i++){
                Dado d = this->desenfileirar();
                if(d.tipo == "prioridade"){
                    prioridade->enfileirar(d);
                }else{
                    normal->enfileirar(d);
                }
            }
            while(this->tamanho != qtd){
                if(prioridade->vazia() || ind==3){
                    this->enfileirar(prioridade->desenfileirar());
                    ind = 0;
                }else{
                    this->enfileirar(normal->desenfileirar());
                    ind++;
                }
            }
            arrumada = true;
        }
        Dado atendimento(){
            if(this->tamanho == 0) throw runtime_error("Aguarde");
            if(arrumada){
                return desenfileirar();
            }else{
                arrumaPrioridade();
                return desenfileirar();
            }
        }
};

int main()
    {
        Fila banco;
        string comando, tipo;
        Dado entrada, atendido;
        cin >> comando;
        while (comando != "fim")
        {
            if (comando == "normal")
            {
                cin >> entrada.nome;
                entrada.tipo = "normal";
                banco.enfileirar(entrada);
            }
            else if (comando == "prioridade")
            {
                cin >> entrada.nome;
                entrada.tipo = "prioridade";
                banco.enfileirar(entrada);
            }
            else if (comando == "atender")
            {
                cout<<banco.atendimento().nome;
            }
            cin >> comando;
        }
        return 0;
}