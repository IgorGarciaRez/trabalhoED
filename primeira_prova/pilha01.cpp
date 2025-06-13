#include <iostream>

using namespace std;

struct Item {
    string nome;
    char tipo;
    int valor;
};

class Noh{
    friend class Inventario;
    private:
        Item item;
        Noh *prox;
    public:
        Noh(Item it){
            item = it;
            prox = NULL;
        }
};

class Inventario{
    private:
        Noh* topo;
        int tamanho;
    public:
        Inventario();
        ~Inventario();
        void empilhar(const Item& it);
        Item desempilhar();
		bool vazia();
		void limparInventario();
		int retornaTamanho();
        void espia();
};

void imprimirDado(const Item& umDado) {
    cout<<"Nome: "<<umDado.nome<<" Tipo: "<<umDado.tipo<<" Valor: "<<umDado.valor<<endl;
}

Inventario::Inventario(){
    topo = NULL;
    tamanho = 0;
}

Inventario::~Inventario(){
    limparInventario();
}

void Inventario::empilhar(const Item& it){
    Noh *novo = new Noh(it);
    novo->prox = topo;
    topo = novo;
    tamanho++;
}

Item Inventario::desempilhar(){
    if(this->vazia()) throw runtime_error("Erro: pilha vazia!");
    Noh *auxiliar = topo;
    Item removido = auxiliar->item;
    topo = topo->prox;
    delete auxiliar;
    tamanho--;
    return removido;
}

bool Inventario::vazia(){
    return (topo == NULL);
}

void Inventario::limparInventario(){
    while(!vazia()){
		desempilhar();
	}
}

int Inventario::retornaTamanho(){
    return tamanho;
}

void Inventario::espia(){
    if (this->vazia()) throw runtime_error("Erro: pilha vazia!");
    cout<<"Nome: "<<topo->item.nome<<" Tipo: "<<topo->item.tipo<<" Valor: "<<topo->item.valor<<endl;
}

int main(){
    Inventario inventario;
    Item info;
    char comando;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    inventario.empilhar(info);
                    break;
                case 'r': // remover
                    imprimirDado(inventario.desempilhar());
                    break;
                case 'l': // limpar tudo
                    inventario.limparInventario();
                    break;
                case 'e': // espiar                
                    inventario.espia();
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
    while (!inventario.vazia()) {
        imprimirDado(inventario.desempilhar());
    }
    cout << endl;
    return 0;
}