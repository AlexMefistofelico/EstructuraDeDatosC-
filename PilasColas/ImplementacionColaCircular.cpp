#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptr NULL
using namespace std;


class ColaCircular{
public:
    size_t N;

    ColaCircular(int n){
        N = n;
        C = new int[N];
        prim = ulti = -1;
    }


    ~ColaCircular(){
        delete C;
    }

    bool vacio(){
        return prim == -1;
    }

    void insertar(int dato){
        if(vacio()){
            prim = 0;
            C[++ulti]=dato;
        }else{
            ulti ++;
            if(ulti == N)
                ulti = 0;
            if(prim == ulti)
                return;
            else
                C[ulti]=dato;
        }
    }

    int sacar(){
        int d = C[prim];
        if(prim==ulti)
            prim = ulti = -1;
        else{
            prim++;
            if(prim==N)
                prim = 0;
        }
        return d;
    }

    int primero(){
        return C[prim];
    }

    int ultimo(){
        return C[ulti];
    }

    void vaciar(){
        while(!vacio())
            sacar();
    }



private:
    int prim;
    int ulti;
    int *C;
};


int main(int argc,char *argv[],char **env){



    ColaCircular cola(5);

    cout<<boolalpha<<cola.vacio()<<endl;
    cola.insertar(4);
    cout<<boolalpha<<cola.vacio()<<endl;

    cola.insertar(4);
    cola.sacar();
    cola.sacar();

    cola.insertar(14);
    cola.insertar(114);
    cola.insertar(34);


    while(!cola.vacio()){

        cout<<cola.sacar()<<endl;

    }








    return EXIT_SUCCESS;
}
