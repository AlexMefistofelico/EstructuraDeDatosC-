
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptr NULL
using namespace std;

class Nodo{
public:
    Nodo *ant;
	Nodo *sig;
	int dato;

	Nodo(int d){
		dato = d;
		ant = sig = this;
	}
};

class Lista{
public:

   	Nodo *raiz;
	Lista(){
		raiz = new Nodo(INT_MIN);
	}

	bool vacio(){
//		raiz->sig == raiz->ant podria estar apuntando a un mismo nodo
		return raiz==raiz->ant&&raiz==raiz->sig;
	}

	void addI(int d){
		Nodo *nuevo = new Nodo(d);
		raiz->sig->ant = nuevo;
		nuevo->sig = raiz->sig;
		nuevo->ant = raiz;
		raiz->sig = nuevo;
	}

	void addF(int d){
		Nodo *nuevo = new Nodo(d);
		Nodo *pt = raiz->sig;
		while(pt->sig!=raiz)
			pt = pt->sig;

		pt->sig = nuevo;
		nuevo->ant = pt;
		nuevo->sig = raiz;
		raiz->ant = nuevo;
	}


	void addOrden(int d){
		Nodo *nuevo = new Nodo(d);
		Nodo *pt = raiz,*pt1 = raiz->sig;
		while(pt1!=raiz && d>pt1->dato){
			pt = pt1;
			pt1 = pt1->sig;
		}
		pt->sig = nuevo;
		nuevo->ant = pt;
		pt1->ant = nuevo;
		nuevo->sig = pt1;
	}

	int eliPrimero(){
		int dt = raiz->sig->dato;
		Nodo *pt = raiz->sig;
		raiz->sig = pt->sig;
		pt->sig->ant = pt->ant;
		return dt;
	}

	void eliminar(int d){
		Nodo *pt = raiz->sig;
		while(pt!=raiz&&d!=pt->dato)
			pt = pt->sig;
		pt->ant->sig = pt->sig;
		pt->sig->ant = pt->ant;
	}

	void mostrar(){
		Nodo *aux = raiz->sig;
		cout<< ("raiz <-> ");
		string cad = "|_______";

		while(aux!=raiz){
			cout<<aux->dato<<" <-> ";
			cad+=s(to_string(aux->dato).size()+5);
			aux = aux->sig;
		}
		cout<<'\n'<<cad<<'|'<<endl;
	}

	string s(int n){
		string cad = "";
		while(n-->0)
			cad+='_';
		return cad;
	}
};


int main(int argc,char *argv[],char **env){

        Lista l;


        cout<<boolalpha<<l.vacio()<<endl;


		l.addF(1);
		l.addF(22);
		l.addF(300);
		l.addF(4);
		l.addF(5);
		l.addF(5);


		/**
		 *true
			raiz <-> 1 <-> 22 <-> 300 <-> 4 <-> 5 <-> 5 <->
			|______________________________________________|
			false
		 **/

		l.eliminar(1);
		l.eliminar(5);
		//l.eliminar(15);//precondicion para eliminar debe exister el elemento a eliminar.
		/*
		l.eliminar(300);
		l.eliminar(4);
		l.eliminar(22);
		*/
		l.mostrar();
		cout<<l.vacio()<<endl;
//		l.eliminar(1);
//		l.mostrar();
//
//		l.eliminar(300);
//		l.mostrar();
//
//		l.eliminar(22);
//		l.mostrar();

    return EXIT_SUCCESS;
}
