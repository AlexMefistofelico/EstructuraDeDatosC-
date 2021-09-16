#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptrptr NULL
using namespace std;

class Nodo{
public:
    Nodo *sig;
	int dato;

	Nodo(int d){
		dato = d;
		sig = nullptr;
	}

};

class Lista{
public:
    Nodo *raiz;

	Lista(){
		raiz = nullptr;
	}

	void add(int d){
		Nodo *nuevo = new Nodo(d);
		nuevo->sig = raiz;
		raiz = nuevo;
	}

	void addFinal(int d){
		Nodo *aux = raiz;
		if(aux==nullptr){
			raiz  = new Nodo(d);
		}else{
			while(aux->sig != nullptr)
			aux = aux->sig;
			aux->sig = new Nodo(d);
		}
	}

	void addOrden(int d){
		Nodo *nuevo = new Nodo(d);
		Nodo *pt = nullptr;
		Nodo *pt1 = raiz;

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

	void eliminar(int d){
		Nodo *pt = nullptr;
		Nodo *pt1 = raiz;
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

	void modificar(int da,int dn){
		Nodo *aux = raiz;
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
		for(Nodo *i = raiz;i->sig!=nullptr;i=i->sig){
			for(Nodo *j=i->sig;j!=nullptr;j=j->sig){
				if(i->dato > j->dato){
                    int tmp = i->dato;
                    i->dato = j->dato;
                    j->dato = tmp;
				}
			}
		}
	}

	void mostrar(){
		cout<< "raiz->";
		Nodo *aux = raiz;

		while(aux!=nullptr){
			cout<<aux->dato<<"->";
			aux = aux->sig;
		}

		cout<<"nullptr"<<endl;
	}


};



int main(int argc,char *argv[],char **env){

    Lista l;
/*
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
*/
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


    return EXIT_SUCCESS;
}
