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


//ESTRUCTURA DE DATOS ESTATICA GENERICA PILA Y COLA AUXILIARES PARA RECORRIDOS NO RECURISVOS
template<class T>
class Nodo{
public:
    Nodo *HijoIzq;
	Nodo *HijoDer;
	T dato;
	int rep;
	Nodo(T d){
		dato = d;
		HijoIzq = HijoDer = nullptr;
		rep = 1;
	}
	~Nodo(){}
	Nodo(Nodo* n){
		dato = n->dato;
		HijoDer = n->HijoDer;
		HijoIzq = n->HijoIzq;
		rep = 1;
	}
};

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
		else
			r->rep++;
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
			cout<<r->dato<<" rep: "<<r->rep<<endl;
			inOrden(r->HijoDer);
	}

	void postOrden(Nodo<T>* r){
		if(r==nullptr)return;
		postOrden(r->HijoIzq);
		postOrden(r->HijoDer);
		cout<<r->dato<<" ";
	}
};



int main(int argc,char *argv[],char **env){

	Arbol<string> arbol;

	string cad = "esto solo es una prueba prueva prueba funciones anonimas sis2310a cualquir texto texto texto texto texto texto texto texto texto texto texto ";
	string aux="";

	O(log n)
	n = la cantidad de palabras 

	for(int i=0;i<cad.size();i++){
		if(i==cad.size()-1){
			aux += cad[i];
			arbol.agregar(aux);
		}else if(cad[i]==' '){
			arbol.agregar(aux);
			aux = "";
		}else{
			aux+=cad[i];
		}
	}	

	arbol.inOrden(arbol.raiz);

	

    return 0;
}

