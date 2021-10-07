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

template<class T>
class Nodo{
public:
    T dato;
	Nodo *HijoIzq;
	Nodo *HijoDer;
	Nodo(T d){
		dato = d;
        HijoDer = HijoIzq = nullptr;
	}
};

template<class T>
class Arbol{
public:
    Nodo<T>* raiz;
	Arbol(){
		raiz = nullptr;
	}
    void preOrden(Nodo<T>* r){
		if(r==nullptr)return;
		cout<<r->dato<<ESP;
		preOrden(r->HijoIzq);
		preOrden(r->HijoDer);
	}
	void inOrden(Nodo<T>* r){
		if(r==nullptr)return;
		inOrden(r->HijoIzq);
		cout<<r->dato<<ESP;
		inOrden(r->HijoDer);
	}
	void postOrden(Nodo<T>* r){
		if(r==nullptr)return;
		postOrden(r->HijoIzq);
		postOrden(r->HijoDer);
		cout<<r->dato<<ESP;
	}
};

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

class ImplementacionArbolBinarioExpreciones{
public:
	Cola<string> aCola(string cad){
		Cola<string> c;
		string aux = "";
		int i=0;
		while(i<cad.length()){
			if(isdigit(cad[i])||cad[i]=='.'){
				aux+=cad[i];
				if(i==cad.length()-1)
					c.insertar(aux);
			}else{
				if(aux!="")
					c.insertar(aux);
				c.insertar(string(1,cad[i]));//usando contructor
				aux="";
			}
			i++;
		}
		return c;
	}
    int prioriadad(string o){
		if(o=="+"||o=="-")return 1;
		if(o=="*"||o=="/")return 2;
		if(o=="^")return 3;
		return 0;
	}

	Arbol<string> aArbolExp(Cola<string> colainf){
		Pila<string> pilaO;
		Pila<Nodo<string>*> pilaN;
		Arbol<string> a;
		string x,aux;
		Nodo<string> *nodo;
		while(!colainf.vacio()){
			x = colainf.sacar();
				if(x=="(")/////////////////////////////////////
					pilaO.push(x);
				else if(x==")"){/////////////////////////////////////
					while(!(pilaO.EnTope()=="(")){
						nodo = new Nodo<string>(pilaO.pop());
						nodo->HijoDer = pilaN.pop();
						nodo->HijoIzq = pilaN.pop();
						pilaN.push(nodo);
					}
					pilaO.pop();//sacando "parentecis"
				}else if(x=="^"||x=="/"||x=="*"||x=="-"||x=="+"){/////////////////////////////////////
					while(!pilaO.vacio()&&prioriadad(x)<=prioriadad(pilaO.EnTope())){
						nodo = new Nodo<string>(pilaO.pop());
						nodo->HijoDer = pilaN.pop();
						nodo->HijoIzq = pilaN.pop();
						pilaN.push(nodo);
					}
					pilaO.push(x);
				}else/////////////////////////////////////
                    pilaN.push(new Nodo<string>(x));
		}
		while(!pilaO.vacio()){
			nodo = new Nodo<string>(pilaO.pop());
			nodo->HijoDer = pilaN.pop();
			nodo->HijoIzq = pilaN.pop();
			pilaN.push(nodo);
		}
		a.raiz = pilaN.pop();
		return a;
	}
};

int main(int argc,char *argv[],char **env){
		ImplementacionArbolBinarioExpreciones ex;
//		string exp = "((123/(15.15+1.123*4))/((15.15*1.123)/(123+1.123*15.15-1.123)))+15.15-4";
//		string exp = "((4-1)*5)+(64/(2^5))";
//		string exp = "((b+((b^2-a*c)^(1/2)))/(d*a))/((b+a)/(c+b*d))";
		string exp = "((3.0+((3.0^2-1.6*5)^(1/2)))/(15.15*1.6))/((3.0+5)/(5+3.0*15.15))";
		Cola<string> colaexp = ex.aCola(exp);
//		while(!colaexp.vacio()){
//            cout<<colaexp.sacar()<<endl;
//		}
        Arbol<string> arbol = ex.aArbolExp(colaexp);
		arbol.preOrden(arbol.raiz);
		cout<<endl;
		arbol.inOrden(arbol.raiz);
		cout<<endl;
		arbol.postOrden(arbol.raiz);
		cout<<endl;
    return 0;
}
