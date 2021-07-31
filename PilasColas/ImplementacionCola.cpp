#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptr NULL
using namespace std;

class Cola{
public:
    Cola(int n){
        C = new int[n];
        prim = ulti = -1;
    }

    int primero(){
        return C[prim];
    }
    int ultimo(){
        return C[ulti];
    }

    bool vacio(){
        return prim == -1;
    }

    void insertar(int dato){
        if(vacio())
            prim = 0;
        C[++ulti] = dato;
    }

    int sacar(){
        int d = C[prim];
        if(prim == ulti)
            prim = ulti = -1;
        else
            prim++;
        return d;
    }

    void vaciar(){
        while(!vacio()){
            sacar();
        }
    }

    ~Cola(){}

private:
    int prim;
    int ulti;
    int *C;
};


int main(int argc,char *argv[],char **env){



    Cola cola(5);

    cout<<boolalpha<<cola.vacio()<<endl;

    cola.insertar(1);
    cola.insertar(4);
    cola.insertar(42);
    cola.insertar(141);

    cout<<"primero: "<<cola.primero()<<endl;
    cout<<"ultimo: "<<cola.ultimo()<<endl;

    while(!cola.vacio()){
        cout<<cola.sacar()<<" ";
    }

    cout<<endl;

    cout<<boolalpha<<cola.vacio()<<endl;











    return EXIT_SUCCESS;
}
