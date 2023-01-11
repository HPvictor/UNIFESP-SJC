#include<bits/stdc++.h>
using namespace std;
 
class Hash {
        int BUCKET; 
        list<int> *tabela;
    public:
//funcao constroi a tabela
        Hash(int elemento) {
            this->BUCKET = elemento;
            tabela = new list<int>[BUCKET];
        }; 
//funcao insere elemento na tabela
        void insereItem(int elemento) {
            int index = FuncaoHash(elemento);
            tabela[index].push_back(elemento);
        };
//funcao deleta  elemento da tabela
        void deletaItem(int elemento) {
            int index = FuncaoHash(elemento);
//encontra elemento indicado na lista(usando index)
            list <int> :: iterator i;
            for (i = tabela[index].begin();
                    i != tabela[index].end(); i++) {
                if (*i == elemento)
                    break;
            }
//caso elemento seja encontrado, remova-o
            if (i != tabela[index].end())
                tabela[index].erase(i);
        };
//Funcao hash que encontra o valor do elemento
        int FuncaoHash(int x) {
            return (x % BUCKET);
        };
//Funcao para mostra qual o index
        void mostraIndex( int IN ) {
            int i = FuncaoHash(IN);
            cout << "[" << i << "] ";
            list <int> :: iterator k;
            for (k = tabela[i].begin();
                k != tabela[i].end(); k++) {
                cout << *k << " ";
            }
        };
//encontra o index do proximo elemento
        int encontra(int elemento) {
            int index = FuncaoHash(elemento);
//encontra onde esse index se encontra na lista
            list <int> :: iterator i;
            for (i = tabela[index].begin();
                    i != tabela[index].end(); i++) {
                if (*i == elemento)
                    break;
            }
            if (i == tabela[index].end())
                if (*i != elemento)
                    return -1;
            return *i;
        };
};
//inicio da funcao main
int main() {
    int tamanho;    
    cin >> tamanho;
    Hash h(tamanho);
    int n;
    while (n > -1) {
        cin >> n;
        if (n < 0)
            break;
        h.insereItem(n);
    }
    int s = 0;
    cin >> s;
    if (h.encontra(s) > -1)
        h.deletaItem(s);
    else
        cout << "Valor nao encontrado" << endl;
    int c = 0, ch = 0;
    cin >> c;
    h.mostraIndex(c);
    cout << endl;
    return 0;
}