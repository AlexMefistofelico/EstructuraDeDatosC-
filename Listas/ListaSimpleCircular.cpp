#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptr NULL
using namespace std;


class Nodo{
    public:
    int info;
	Nodo *sig;
	Nodo(int info) {
		this->info = info;
		sig = nullptr;
	}
};

class ListaCircular {
	public:
	Nodo *raiz;

	ListaCircular() {
		raiz = new Nodo(INT_MIN);
		raiz->sig = raiz;
	}

	bool esvacio() {
		return raiz->sig == raiz;
	}

	void agregar(int info){
		Nodo *nuevo = new Nodo(info);
		nuevo->sig = raiz->sig;
		raiz->sig = nuevo;
	}

	string f(int n){
        string cad="";
        while(n--)
            cad+='_';
        return cad;
	}
	void mostrar() {
        string cad = "|______";
		Nodo *aux = raiz->sig;
		cout<<("raiz -> ");

		while(aux!=raiz) {
			cout<<aux->info<<" -> ";
			aux = aux->sig;
			cad += f(to_string(aux->info).size()+3);
		}
		cad+='|';
		cout<<endl<<cad<<endl;
	}

	void agregarf(int info){
		Nodo *nuevo = new Nodo(info);
		Nodo *aux = raiz->sig;
		while(aux->sig != raiz)
			aux = aux->sig;

		aux->sig = nuevo;
		nuevo->sig = raiz;
	}


	void agregarO(int dato){
		Nodo *pt=raiz,*pt1=raiz->sig,*nuevo = new Nodo(dato);
		while (pt1!=raiz && dato>pt1->info){
			pt=pt1;
			pt1=pt1->sig;
		}
		nuevo->sig=pt1;
		pt->sig=nuevo;
	}

	int eliminarP(){
		Nodo *pt = raiz->sig;
	  	int dato = pt->info;
	    raiz->sig = pt->sig;
	    return dato;
	}

	int eliminarU(){
		Nodo *pt=raiz,*pt1=raiz->sig;
		while (pt1->sig!=raiz){
			pt=pt1;
			pt1=pt1->sig;
		}
		int dato = pt1->info;
		pt->sig = pt1->sig;
		return dato;
	}

	void eliminar(int dato){
		Nodo *pt=raiz,*pt1=raiz->sig;
		while (pt1!=raiz&&dato!=pt1->info){
		  		pt=pt1;
		  		pt1=pt1->sig;
		}
		if (pt1!=raiz)
			 pt->sig=pt1->sig;
	}

	bool buscar(int info) {
		Nodo *aux = raiz->sig;
		while(aux!=raiz) {
			if(aux->info == info)
				return true;
			aux = aux->sig;
		}
		return false;
	}


};

int main(int argc,char *argv[],char **env){

    ListaCircular listC;

    listC.agregarO(4);
    listC.agregarO(5);
    listC.agregarO(6);
    listC.agregarO(1);
    listC.agregarO(2);
    listC.agregarO(3);
    listC.agregarO(4);
    listC.agregarO(5);
    listC.agregarO(6);
    listC.agregarO(1);
    listC.agregarO(2);
    listC.agregarf(3);

    listC.agregarf(3);
    listC.agregarf(3);

    listC.agregar(13);
    listC.agregar(31);

    listC.mostrar();

    cout<<listC.eliminarP()<<endl;
    cout<<listC.eliminarP()<<endl;
    cout<<listC.eliminarU()<<endl;
    cout<<listC.eliminarU()<<endl;

    listC.mostrar();



    return EXIT_SUCCESS;
}
