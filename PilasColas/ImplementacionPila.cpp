#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptr NULL
using namespace std;

class Pila{
public:
    Pila(int n){
        P = new int[n];
        tope = -1;
    }

    bool vacio(){
        return tope == -1;
    }

    void push(int dato){
        P[++tope] = dato;
    }

    int enTope(){
        return P[tope];
    }

    int pop(){
        return P[tope--];
    }

    void elimina(){
        while(!vacio())
            pop();
    }

    ~Pila(){}

private:
    int tope;
    int *P;
};



int main(int argc,char *argv[],char **env){

    Pila pila (4);

    cout<<boolalpha<<pila.vacio()<<endl;

    pila.push(4);
    cout<<boolalpha<<pila.vacio()<<endl;
    pila.push(44);
    pila.push(144);
    pila.push(54);


    cout<<pila.enTope()<<endl;

    while(!pila.vacio()){
        cout<< pila.pop()  <<endl;
    }



    return EXIT_SUCCESS;
}
