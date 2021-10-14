#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
/**
    @AlexAriel
    Thursday
    2021-10-07-14.51.58
    NOTAS.-

*/
#define MAX 100
#define ESP ""

class Persona{
public:
	int ci;
	string nombre;
	double sueldo;

	Persona(int c,string n,double s){
		ci = c;
		nombre = n;
		sueldo = s;
	}
	void mostrar(){
		cout<<nombre<<"\t"<<ci<<"\t"<<sueldo<<endl;
	}
/*
	Persona(){
	}
*/
	~Persona(){}
};

//ESTRUCTURA DE DATOS ESTATICA GENERICA PILA Y COLA AUXILIARES PARA RECORRIDOS NO RECURISVOS
template<class T>
class Nodo{
public:
    Nodo *HijoIzq;
	Nodo *HijoDer;
	T dato;
	Nodo(T d){
		dato = d;
		HijoIzq = HijoDer = nullptr;

	}
	~Nodo(){}
	Nodo(Nodo* n){
		dato = n->dato;
		HijoDer = n->HijoDer;
		HijoIzq = n->HijoIzq;
	}
};

//darle una nueva funcionalidad a el ""> <""
bool operator > (Persona a,Persona b){
	return a.nombre > b.nombre;
}

bool operator < (Persona a,Persona b){
	return a.nombre < b.nombre;
}


template<class T>
class Arbol{
public:
    Nodo<T>* raiz;

	Arbol(){
		raiz = nullptr;
	}
	~Arbol(){}

	Nodo<T>* agregar(Nodo<T>* r,T d){
		if (r==nullptr)
		     r = new Nodo<T>(d);
		else if (d>r->dato)
		     r->HijoDer=agregar(r->HijoDer,d);
		else if (d<r->dato)
		     r->HijoIzq=agregar(r->HijoIzq,d);
		return r;
	}

	void agregar(T d){
		raiz=agregar(raiz,d);
	}

	Nodo<T>* buscar(Nodo<T>* r, T clave){
		if (clave==r->dato)
		    r=elinodo(r);
		else if(clave>r->dato)
			r->HijoDer=buscar(r->HijoDer,clave);
		else
			r->HijoIzq=buscar(r->HijoIzq,clave);
		return r;
	}

	Nodo<T>* elinodo(Nodo<T>* r){
		if (r->HijoIzq==nullptr && r->HijoDer==nullptr)
			return nullptr;
		else if(r->HijoIzq!=nullptr && r->HijoDer==nullptr)
		    return r->HijoIzq;
		else if(r->HijoIzq==nullptr && r->HijoDer!=nullptr)
		    return r->HijoDer;
		else{
	    	r->HijoDer=buscar(r->HijoDer,r->dato = menmay(r->HijoDer)/*mm*/);
	    	return r;
		}
	}

	int menmay(Nodo<T>* r){
		if(r->HijoIzq==nullptr)
		    return r->dato;
	    return menmay(r->HijoIzq);
	}

	void eliminar(int clave){
		raiz=buscar(raiz,clave);
	}

    //ALTURA
	int altura(Nodo<T>* r){
		if(r==nullptr)
		    return 0;
	    return (1+max(altura(r->HijoIzq),altura(r->HijoDer)));
	}

	//NODOS QUE NO TIENEN HIJOS
	int sinhijos(Nodo<T>* r){
		if (r==nullptr)
			return 0;
		else if(r->HijoIzq==nullptr && r->HijoDer==nullptr)
		    return 1;
		else return (sinhijos(r->HijoIzq)+sinhijos(r->HijoDer));
	}

	//NIVELES
	void niveles(Nodo<T>* r){
		if(r!=nullptr){
			niveles(r->HijoIzq);
			cout<<"\nNodo = "<<r->dato<<"\taltura = "<<altura(r)<<endl;
			niveles(r->HijoDer);
		}
	}

	void preOrden(Nodo<T>* r){
		if(r==nullptr)return;
		cout<<r->dato<<" ";
		preOrden(r->HijoIzq);
		preOrden(r->HijoDer);
	}

	void inOrden(Nodo<T>* r){
		if(r==nullptr)return;
			inOrden(r->HijoIzq);
			//cout<<r->dato<<" ";
			r->dato.mostrar();
			inOrden(r->HijoDer);
	}

	void postOrden(Nodo<T>* r){
		if(r==nullptr)return;
		postOrden(r->HijoIzq);
		postOrden(r->HijoDer);
		//cout<<r->dato<<" ";
		r->dato.mostrar();
	}
};


//hacer un arbol de personas y reportar en orden por su carnet , por su nombre

int main(int argc,char *argv[],char **env){
	

	Arbol<Persona> arbol;

	arbol.agregar(Persona(23,"alex",1000));
	arbol.agregar(Persona(232,"antonio",1.0000));
	arbol.agregar(Persona(13442,"brayan",1.0000));
	arbol.agregar(Persona(142,"miguel",1.0000));
	arbol.agregar(Persona(1342,"jeanette",1.0000));
	arbol.agregar(Persona(342,"jorge",1.0000));
	arbol.agregar(Persona(1112342,"adriana",1.0000));
	arbol.agregar(Persona(321342,"saul",1.0000));
	arbol.agregar(Persona(62342,"michael",1.0000));
	arbol.agregar(Persona(92342,"karla",1.0000));
	arbol.agregar(Persona(02342,"daleth",1.0000));

	arbol.inOrden(arbol.raiz);


    return 0;
}

