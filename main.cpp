#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int maximo2(int x, int y){
    return x>=y ? x : y;
}

int maximo3(int x, int y, int z){
    return maximo2(maximo2(x,y), z);
}


int minimo2(int x, int y){
    return x<y ? x : y;
}

int minimo3(int x, int y, int z){
    return minimo2(minimo2(x,y), z);
}

class Intervalo {
private:
    vector<int> numerosIntervalo;
    int limiteSuperior;
    int limiteInferior;

public:
    Intervalo(){
        limiteInferior = 0;
        limiteSuperior = 0;
    }
    Intervalo(char abertura, int inicio, int fim, char fechamento) {
        // Verifica se o intervalo é válido
        if ((abertura == '(' || abertura == '[') && (fechamento == ')' || fechamento == ']') && inicio <= fim) {
            limiteSuperior = fim;
            limiteInferior = inicio;

            int i = (abertura == '[') ? limiteInferior : limiteInferior+1;
            const int maiorNumeroIntervalo = (fechamento == ']') ? limiteSuperior : limiteSuperior - 1;

            for (i; i <= maiorNumeroIntervalo; i += 1) {
                numerosIntervalo.push_back(i);
            }
        } else {
            cout << "Erro: Intervalo inválido." << endl;
        }
    }

    vector<int> getIntervalo(){
        return numerosIntervalo;
    }

    void setIntervalo(vector<int> x){
        numerosIntervalo = x;
    }

    int getLimiteSuperior(){
        return limiteSuperior;
    }

    int getLimiteInferior(){
        return limiteInferior;
    }

    void imprimirIntervalo() const {
        for (const auto& numero : numerosIntervalo) {
            cout << numero << " ";
        }
        cout << endl;
    }

    //Questão a - Contém

    bool contem(int valor){
        for(const auto& numero : numerosIntervalo){
            if(numero == valor)
                return true;           
        }
        return false;
    }

    //Questao b - Interseção entre dois intervalor

    bool intercepta(Intervalo x){
        for(const auto& elemA: numerosIntervalo){
            for(const auto& elemB : x.getIntervalo()){
                if(elemA == elemB)
                    return true;
            }
        }
        return false;
    }

    //Questão c - Média de um intervalo

    double media(){
        int soma = 0;
        for(const auto& numero : numerosIntervalo)
            soma = soma+numero;
        return ((double)soma/numerosIntervalo.size());
    }

    //Questão d - produto entre limites  
    //[min (infa*infb, infa*supb, supa*infb, supa*supb), 
    //max (infa*infb, infa*supb,supa*infb, supa*supb)]   

    Intervalo produto(Intervalo x){
        int n1 = this->limiteInferior*x.getLimiteInferior();
        int n2 = this->limiteInferior*x.getLimiteSuperior();
        int n3 = this->limiteSuperior*x.getLimiteSuperior();

        Intervalo c('[', minimo3(n1,n2,n3), maximo3(n1,n2,n3), ']');
        
        return c;
    }            

    Intervalo uniao(Intervalo x) {
        vector<int> numerosUniao;

        for (int i = this->limiteInferior; i <= this->limiteSuperior; i++) {
            numerosUniao.push_back(i);
        }

        for (int i = x.getLimiteInferior(); i <= x.getLimiteSuperior(); i++) {
            if (!this->contem(i)) {
                numerosUniao.push_back(i);
            }
        }

        Intervalo uniaoIntervalo('[', minimo2(this->limiteInferior, x.getLimiteInferior()), maximo2(this->limiteSuperior, x.getLimiteSuperior()), ']');
        uniaoIntervalo.setIntervalo(numerosUniao);
        
        return uniaoIntervalo;
    }
         
};

int main() {
    Intervalo a('[', -3, 2, ']');
    Intervalo b('[', 10, 15, ')');
    Intervalo c;
    Intervalo d;
    int numero = 2;

    cout << "intervalo a: ";
    a.imprimirIntervalo();
    cout << "intervalo b: ";
    b.imprimirIntervalo();
    cout << "Contém o número " << numero << "? " << (a.contem(numero) ? "Sim" : "Não") << endl;
    cout << "o a tem interseção com b? " << (a.intercepta(b) ? "Sim" : "Não") << endl;
    c = a.produto(b);
    cout << "intervalo c: ";
    c.imprimirIntervalo();
    d = a.uniao(b);
    cout << "União de a e b: ";
    d.imprimirIntervalo();
    
    return 0;
}
