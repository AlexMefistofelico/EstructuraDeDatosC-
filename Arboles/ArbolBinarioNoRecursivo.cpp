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
class Pila{
private:
    int tope;
	T p[MAX];

public:
    Pila(){
        tope = -1;
	}
	~Pila(){}
	bool vacio(){
		return tope == -1;
	}
	T EnTope(){
		return p[tope];
	}
	void push(T dato){
		p[++tope]=dato;
	}
	T pop(){
		return p[tope--];
	}
	void Elimina(){
		while(!vacio())
			pop();
	}
};

template<class T>
class Cola{
private:
    int primero_;
	int ultimo_;
	T C[MAX];
public:
	Cola(){
		primero_ = -1;
		ultimo_ = primero_;
	}
	~Cola(){}
	bool vacio(){
		return primero_ == -1;
	}
	T primero(){
		return C[primero_];
	}
	T ultimo(){
		return C[ultimo_];
	}
	void insertar(T d){
		if(vacio())
			primero_ = 0;
		C[++ultimo_]=d;
	}
	T sacar(){
		T dato = C[primero_];
		if(primero_==ultimo_){
			primero_ = -1;
			ultimo_ = -1;
		}else
			primero_++;
		return dato;
	}
	void vaciar(){
		while(!vacio())
			sacar();
	}
};
//DESDE AQUI LA ESTRUCUTA DE DATOS ARBOL BINARIO DE BUSQUEDA

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
			cout<<r->dato<<" ";
			inOrden(r->HijoDer);
	}

	void postOrden(Nodo<T>* r){
		if(r==nullptr)return;
		postOrden(r->HijoIzq);
		postOrden(r->HijoDer);
		cout<<r->dato<<" ";
	}

	// que es esbirros
// ALGORITMO RECORRIDO EN  AMPLITUD NO RECURSIVO
/**
	PROCEDIMIENTO amplitud(Nodo r) INICIO
		Cola<Nodo> cola
		Nodo aux
		cola.insertar(r)

		MIENTRAS(NO cola.vacio()) INICIO

			aux = cola.sacar()
			SI(aux->HijoIzq <> NULO)
				cola.insertar(aux->HijoIzq)
			SI(aux->HijoDer <> NULO)
				cola.insertar(aux->HijoDer)
			MOSTRAR [aux->dato, " "]

		FIN
	FIN
*/

// ALGORITMO RECORRIDO EN  PREORDEN NO RECURSIVO
/**
	PROCEDIMIENTO preOrden_(Nodo r)INICIO
		Pila<Nodo> pila
		Nodo ptr = r
		pila.push(ptr)

		MIENTRAS(!pila.vacio())INICIO

			MOSTRAR [ptr->dato, " "]

			SI(ptr->HijoDer <> NULO)
				pila.push(ptr->HijoDer)
			SI(ptr->HijoIzq <> NULO)
				ptr = ptr->HijoIzq
			SINO
				ptr = pila.pop()
		FIN
	FIN
*/

// ALGORITMO RECORRIDO EN  ENORDEN NO RECURSIVO
/**
	PROCEDIMIENTO inOrden_(Nodo r)INICIO
		Pila<Nodo> pila
		pila.push(NULO)
		Nodo ptr = r

		MIENTRAS(ptr <> NULO)INICIO
			MIENTRAS(ptr <> NULO)INICIO
				pila.push(ptr)
                ptr = ptr->HijoIzq
			FIN

			ptr = pila.pop()
			BOLEANO tieneDer = FALSO

			MIENTRAS(ptr <> NULO&&NO tieneDer)INICIO
				MOSTRAR [ptr->dato, " "]
				SI(ptr->HijoDer <> NULO)INICIO
					ptr = ptr->HijoDer
					tieneDer = VERDADERO
				FINSINO
					ptr = pila.pop()
			FIN

		FIN
	FIN
*/

// ALGORITMO RECORRIDO EN  POSTORDEN NO RECURSIVO
/**
PROCEDIMIENTO postOrden_(Nodo ptr)INICIO
    Pila<Nodo> pila
    Pila<BOLEANO> pilaSW
    BOLEANO sw

    pila.push(NULO)
    pilaSW.push(FALSO)

    MIENTRAS(ptr  <>  NULO)INICIO

        MIENTRAS(ptr  <>  NULO)INICIO
            pila.push(ptr)
            pilaSW.push(VERDADERO)

            SI(ptr->HijoDer  <>  NULO)INICIO
                pila.push(ptr->HijoDer)
                pilaSW.push(FALSO)
            FIN

            ptr=ptr->HijoIzq
        FIN

        ptr=pila.pop()
        sw=pilaSW.pop()

        MIENTRAS(ptr  <>  NULO && sw)INICIO

            MOSTRAR [ptr->dato, " "]
            ptr=pila.pop()
            sw=pilaSW.pop()
        FIN

    FIN
FIN
*/

	void amplitud(Nodo<T>* r) {
		Cola<Nodo<T>*> cola;
		Nodo<T>* aux;
		cola.insertar(r);
		while(!cola.vacio()) {
			aux = cola.sacar();
			if(aux->HijoIzq!=nullptr)
				cola.insertar(aux->HijoIzq);
			if(aux->HijoDer!=nullptr)
				cola.insertar(aux->HijoDer);
			cout<<aux->dato<<" ";
		}
	}

	void preOrden_(Nodo<T>* r){
		Pila<Nodo<T>*> pila;
		Nodo<T>* ptr = r;
		pila.push(ptr);
		while(!pila.vacio()){
			cout<<ptr->dato<<" ";
			if(ptr->HijoDer!=nullptr)
				pila.push(ptr->HijoDer);
			if(ptr->HijoIzq!=nullptr)
				ptr = ptr->HijoIzq;
			else
				ptr = pila.pop();
		}
	}

	void inOrden_(Nodo<T>* r){
		Pila<Nodo<T>*> pila;
		pila.push(nullptr);
		Nodo<T>* ptr = r;
		while(ptr!=nullptr){
			while(ptr!=nullptr){
				pila.push(ptr);
                ptr = ptr->HijoIzq;
			}
			ptr = pila.pop();
			bool tieneDer = false;
			while(ptr!=nullptr&&!tieneDer){
				cout<<ptr->dato<<" ";
				if(ptr->HijoDer!=nullptr){
					ptr = ptr->HijoDer;
					tieneDer = true;
				}else
					ptr = pila.pop();
			}
		}
	}
//Recorrido PostOrden no recursivo
void postOrden_(Nodo<T> *ptr){
    Pila<Nodo<T>*> pila;
    Pila<bool> pilaSW;
    bool sw;

    pila.push(nullptr);
    pilaSW.push(false);

    while(ptr != nullptr){
        while(ptr != nullptr){
            pila.push(ptr);
            pilaSW.push(true);
            if(ptr->HijoDer != nullptr){
                pila.push(ptr->HijoDer);
                pilaSW.push(false);
            }
            ptr=ptr->HijoIzq;
        }
        ptr=pila.pop();
        sw=pilaSW.pop();

        while(ptr != nullptr && sw){
            cout<<ptr->dato<<" ";
            ptr=pila.pop();
            sw=pilaSW.pop();
        }
    }
}

};

int main(int argc,char *argv[],char **env){
    	Arbol<int> a;
        //10,9,8,17,15,20,18,30,11,19,28,71,51,12,81,13
		a.agregar(10);
		a.agregar(9);
		a.agregar(8);
		a.agregar(17);
		a.agregar(15);
		a.agregar(20);
		a.agregar(18);
		a.agregar(30);

/*
		a.agregar(11);
		a.agregar(19);
		a.agregar(28);
		a.agregar(71);
		a.agregar(51);
		a.agregar(12);
		a.agregar(81);
		a.agregar(13);
*/
		cout<<"*menor *"<<a.menmay(a.raiz)<<endl;

        puts("\nRecorrido En Amplitud...");
		a.amplitud(a.raiz);
		cout<<endl;


        puts("\nRecorrido En PreOrden(RID)...");
		a.preOrden(a.raiz);
		cout<<endl;
		a.preOrden_(a.raiz);
		cout<<endl;
//		a.eliminar(10);
//		a.eliminar(30);


        puts("\nRecorrido En InOrden(IRD)...");
		a.inOrden(a.raiz);
		cout<<endl;
		a.inOrden_(a.raiz);
		cout<<endl;


        puts("\nRecorrido En PostOrden(IDR)...");
		a.postOrden(a.raiz);
		cout<<endl;
		a.postOrden_(a.raiz);
		cout<<endl;

        cout<<"\nAltura: "<<a.altura(a.raiz)<<endl;

        cout<<"\nSin Hijos: "<<a.sinhijos(a.raiz)<<endl;

        cout<<"\nNiveles\n";
        a.niveles(a.raiz);

    return 0;
}

