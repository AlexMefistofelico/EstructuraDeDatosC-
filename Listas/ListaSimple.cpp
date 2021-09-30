#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptrptr NULL
using namespace std;

template<class T>
class Nodo{
public:
    Nodo *sig;
	T dato;

	Nodo(T d){
		dato = d;
		sig = nullptr;
	}

};

template<class T>
class Lista{
public:
    Nodo<T> *raiz;

	Lista(){
		raiz = nullptr;
	}

	void add(T d){
		Nodo<T> *nuevo = new Nodo<T>(d);
		nuevo->sig = raiz;
		raiz = nuevo;
	}

	void addFinal(T d){
		Nodo<T> *aux = raiz;
		if(aux==nullptr){
			raiz  = new Nodo<T>(d);
		}else{
			while(aux->sig != nullptr)
			aux = aux->sig;
			aux->sig = new Nodo<T>(d);
		}
	}

	void addOrden(T d){
		Nodo<T> *nuevo = new Nodo<T>(d);
		Nodo<T> *pt = nullptr;
		Nodo<T> *pt1 = raiz;

		while(pt1!=nullptr&&d>pt1->dato){//solo cambiar <
			pt = pt1;
			pt1 = pt1->sig;
		}
//*************************
		if(pt1!=nullptr)
			nuevo->sig = (d==pt1->dato)?pt1->sig:pt1;
//*************************
		if(pt==nullptr)
			raiz = nuevo;
		else
			pt->sig = nuevo;
	}

	void eliminar(T d){
		Nodo<T> *pt = nullptr;
		Nodo<T> *pt1 = raiz;
		while(pt1!=nullptr&&d!=pt1->dato){
			pt = pt1;
			pt1 = pt1->sig;
		}
		if(pt1==nullptr)
			cout<<"El dato no existe"<<endl;
		else if(pt==nullptr)
			raiz = pt1->sig;
		else
			pt->sig = pt1->sig;
	}

	void modificar(T da,T dn){
		Nodo<T> *aux = raiz;
		while(aux!=nullptr){
			if(aux->dato==da){
				aux->dato = dn;
				cout<<"dato modificado"<<endl;
				return;
			}
			aux=aux->sig;
		}
		cout<<"No se encontro "<<da<<endl;
	}

	void ordenar(){
		for(Nodo<T> *i = raiz;i->sig!=nullptr;i=i->sig){
			for(Nodo<T> *j=i->sig;j!=nullptr;j=j->sig){
				if(i->dato > j->dato){
                    T tmp = i->dato;
                    i->dato = j->dato;
                    j->dato = tmp;
				}
			}
		}
	}

	void mostrar(){
		cout<< "raiz->";
		Nodo<T> *aux = raiz;

		while(aux!=nullptr){
			cout<<aux->dato<<"->";
			aux = aux->sig;
		}

		cout<<"nullptr"<<endl;
	}


};

/**
Dadas 2 listas Simplemente Enlazadas con "N" y "M" datos
en orden , realizar un Pseudo Código que una ambas listas
en una lista ordenada.

Lista unirListas(Lista l1 ,Lista l2){
    Lista listaResul;

    Nodo<T> aux1 =>l1.raiz;
    Nodo<T> aux2 =>l2.raiz;

    MIENTRAS(aux1!=NULO && aux2!=NULO){
        SI(aux1->dato < aux2->dato){
            listaResul.addFinal(aux1->dato);
            aux1 =>aux1->sig;
        }CASO_CONTRARIO{//si es mayor o igual
            listaResul.addFinal(aux2->dato);
            aux2 =>aux2->sig;
        }
    }
    MIENTRAS(aux1!=NULO ){
        listaResul.addFinal(aux1->dato);
        aux1 =>aux1->sig;
    }
    MIENTRAS(aux2!=NULO){
        listaResul.addFinal(aux2->dato);
        aux2 =>aux2->sig;
    }
    RETORNAR listaResul;
}
*/
//addFinal(T) : funcion que agrega datos al final de mi lista(listaResul)....


template <class T>
Lista<T> unirListas(Lista<T> l1/*l1 ordenada*/,Lista<T> l2/*l1 ordenada*/){
    Lista<T> listaResul;
    Nodo<T> *aux1 = l1.raiz;
    Nodo<T> *aux2 = l2.raiz;

    while(aux1!=nullptr && aux2!=nullptr){
        if(aux1->dato < aux2->dato){
            listaResul.addFinal(aux1->dato);
            aux1 = aux1->sig;
        }else{//si es mayor o igual
            listaResul.addFinal(aux2->dato);
            aux2 = aux2->sig;
        }
    }
    while(aux1!=nullptr ){
        listaResul.addFinal(aux1->dato);
        aux1 = aux1->sig;
    }
    while(aux2!=nullptr){
        listaResul.addFinal(aux2->dato);
        aux2 = aux2->sig;
    }
    return listaResul;
}

int main(int argc,char *argv[],char **env){

    /*
    lista en 1000 segundos
    raiz->1->2->3...............->1000->nullptr"

    arbols en ln(1000) segundos 7seg.

    raiz->1->6->10->nullptr
*/
    Lista<string> l1;
    Lista<string> l2;


    l1.addFinal("andrea");
    l1.addFinal("beronica");
    l1.addFinal("selena");
    l1.addFinal("miguel");
    l1.addFinal("neyser");

    l2.addFinal("alex");
    l2.addFinal("belen");
    l2.addFinal("boris");
    l2.addFinal("jose");
    l2.addFinal("maria");
    l2.addFinal("zulema");

/*
    l1.addFinal(1.33321);
    l1.addFinal(4.33321);
    l1.addFinal(6.33321);
    l1.addFinal(7.33321);
    l1.addFinal(17.33321);
    l1.addFinal(72.33321);

    l2.addFinal(-11.33321);
    l2.addFinal(-1.33321);
    l2.addFinal(1.33321);
    l2.addFinal(1.33321);
    l2.addFinal(6.33321);
    l2.addFinal(10.33321);
*/
    l1.mostrar();
    l2.mostrar();

    Lista<string> l3 = unirListas(l1,l2);
    l3.mostrar();
/*
    Lista l;

		l.add(19);
		l.add(1);
		l.add(17);
		l.add(20);
		l.add(7);
		l.add(8);
		l.add(9);
		l.add(10);
		l.add(11);
		l.add(3);
		l.add(4);
		l.add(5);
		l.add(6);
		l.add(15);
		l.add(16);
		l.add(13);
		l.add(12);
		l.add(2);
		l.add(18);
		l.add(14);

		l.addOrden(19);
		l.addOrden(1);
		l.addOrden(17);
		l.addOrden(20);
		l.addOrden(7);
		l.addOrden(8);
		l.addOrden(9);
		l.addOrden(10);
		l.addOrden(10);
		l.addOrden(11);
		l.addOrden(3);
		l.addOrden(4);
		l.addOrden(5);
		l.addOrden(6);
		l.addOrden(15);
		l.addOrden(16);
		l.addOrden(13);
		l.addOrden(12);
		l.addOrden(2);
		l.addOrden(18);
		l.addOrden(14);

		l.addOrden(0);
		l.addOrden(10);
		l.addOrden(21);
        l.eliminar(111);

		l.add(3);
		l.add(2);
		l.add(5);
		l.add(4);
		l.add(1);
       l.modificar(1,11111);
		l.mostrar();
		l.ordenar();
		l.mostrar();

		//l.ordenar();
		l.mostrar();

*/
    return EXIT_SUCCESS;
}
