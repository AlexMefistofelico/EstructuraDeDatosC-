#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>

using namespace std;

class Nodo{
public:
    Nodo *ant;
	Nodo *sig;
	int dato;

	Nodo(int d){
		dato = d;
		ant = sig = nullptr;
	}
};

class Lista{
    public:
	Nodo *raizi,*raizd;
	Lista(){
		raizi = raizd = nullptr;
	}

	void addI(int d){
		Nodo *nuevo = new Nodo(d);
		if(vacio())
			raizi = raizd = nuevo;
		else{
			nuevo->sig = raizi;
			raizi->ant = nuevo;
			raizi = nuevo;
		}
	}

	void addD(int d){
		Nodo *nuevo = new Nodo(d);
		if(vacio())
			raizi = raizd = nuevo;
		else{
			nuevo->ant = raizd;
			raizd->sig = nuevo;
			raizd = nuevo;
		}
	}

	void addOrden(int d){
		Nodo *nuevo = new Nodo(d);
		if(vacio())
			raizi = raizd = nuevo;
		else{
			Nodo *pt = nullptr,*pt1 = raizi;
			while(pt1!=nullptr && d>pt1->dato){
				pt = pt1;
				pt1 = pt1->sig;
			}
			if(pt==nullptr){
				nuevo->sig = raizi;
				raizi->ant = nuevo;
				raizi = nuevo;
			}else if(pt1==nullptr){
				nuevo->ant = raizd;
				raizd->sig  = nuevo;
				raizd = nuevo;
			}else{
				nuevo->sig = pt1;
				nuevo->ant = pt;
				pt1->ant = nuevo;
				pt->sig = nuevo;
			}
		}
	}

	int eliPrimero(){
		int dt = raizi->dato;
		if(raizd==raizi)
			raizi = raizd = nullptr;
		else{
			raizi = raizi->sig;
			raizi->ant = nullptr;
		}
		return dt;
	}

	int eliUltimo(){
		int dt = raizd->dato;
		if(raizd==raizi)
			raizi = raizd = nullptr;
		else{
			raizd = raizd->ant;
			raizd->sig = nullptr;
		}
		return dt;
	}

	void eliminar(int d){
		Nodo *pt = raizi;
		while(pt!=nullptr&&d!=pt->dato)
			pt = pt->sig;
		if(pt==nullptr)
			cout<<"El dato es inexistente"<<endl;
		else if(raizd==raizi)
			raizi = raizd = nullptr;
		else{
			Nodo *pta = pt->ant,*pts = pt->sig;
			if(pta==nullptr){
				raizi = pts;
				pts->ant = nullptr;
			}else if(pts==nullptr){
				raizd = pta;
				pta->sig = nullptr;
			}else{
				pta->sig = pts;
				pts->ant = pta;
			}
		}
	}

	void mostrarI(){
		Nodo *aux = raizi;
		cout<< ("raizi -> ");
		while(aux!=nullptr){
			cout<<aux->dato<<" -> ";
			aux = aux->sig;
		}
		cout<<"nullptr"<<endl;
	}

	void mostrarD(){
		Nodo *aux = raizd;
		cout<< ("raizd -> ");
		while(aux!=nullptr){
			cout<<aux->dato<<" -> ";
			aux = aux->ant;
		}
		cout<<"nullptr"<<endl;
	}


	bool vacio(){
		return raizi==nullptr;
	}
};

int main(int argc,char *argv[],char **env){


    Lista l;

    l.addOrden(1);
    l.addOrden(22);
    l.addOrden(300);
    l.addOrden(4);
    l.addOrden(5);
    l.addOrden(5);

    l.mostrarI();
    l.mostrarD();

    l.eliminar(1);
    l.mostrarI();
    l.mostrarD();

    l.eliminar(300);
    l.mostrarI();
    l.mostrarD();

    l.eliminar(22);
    l.mostrarI();
    l.mostrarD();

    l.eliPrimero();
    l.eliUltimo();
    l.mostrarI();
    l.mostrarD();


    l.addD(1110);
    l.addD(1220);
    l.addD(1320);
    l.addD(1430);
    l.addI(100);
    l.addI(200);
    l.addI(300);
    l.addI(400);

  //  l.eliUltimo();
    l.mostrarI();
    l.mostrarD();

    return EXIT_SUCCESS;
}
