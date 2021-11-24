#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>

using namespace std;

template<class T>
class Nodo{
public:
    Nodo<T> *ant;
	Nodo<T> *sig;
	T dato;

	Nodo<T>(T d){
		dato = d;
		ant = sig = nullptr;
	}
};

template<class T>
class Lista{
    public:
	Nodo<T>* raizi, *raizd;
	Lista(){
		raizi = raizd = nullptr;
	}

	void addI(T d){
		Nodo<T> *nuevo = new Nodo<T>(d);
		if(vacio())
			raizi = raizd = nuevo;
		else{
			nuevo->sig = raizi;
			raizi->ant = nuevo;
			raizi = nuevo;
		}
	}

	void addD(T d){
		Nodo<T> *nuevo = new Nodo<T>(d);
		if(vacio())
			raizi = raizd = nuevo;
		else{
			nuevo->ant = raizd;
			raizd->sig = nuevo;
			raizd = nuevo;
		}
	}

	void addOrden(T d){
		Nodo<T> *nuevo = new Nodo<T>(d);
		if(vacio())
			raizi = raizd = nuevo;
		else{
			Nodo<T> *pt = nullptr,*pt1 = raizi;
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

	T eliPrimero(){
		T dt = raizi->dato;
		if(raizd==raizi)
			raizi = raizd = nullptr;
		else{
			raizi = raizi->sig;
			raizi->ant = nullptr;
		}
		return dt;
	}

	T eliUltimo(){
		T dt = raizd->dato;
		if(raizd==raizi)
			raizi = raizd = nullptr;
		else{
			raizd = raizd->ant;
			raizd->sig = nullptr;
		}
		return dt;
	}

	void eliminar(T d){
		Nodo<T> *pt = raizi;
		while(pt!=nullptr&&d!=pt->dato)
			pt = pt->sig;
		if(pt==nullptr)
			cout<<"El dato es inexistente"<<endl;
		else if(raizd==raizi)
			raizi = raizd = nullptr;
		else{
			Nodo<T> *pta = pt->ant,*pts = pt->sig;
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
		Nodo<T> *aux = raizi;
		cout<< ("raizi -> ");
		while(aux!=nullptr){
			cout<<aux->dato<<" -> ";
			aux = aux->sig;
		}
		cout<<"nullptr"<<endl;
	}

	void mostrarD(){
		Nodo<T> *aux = raizd;
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
    /**
    Dadso una LIsta Doblemente en lazado con "N" datos, realizar un
    Pseudo Codigo modifique todos los datos a su inmediato valor superior
    de 3 de la lista propocionada
    //SOLUCION
    //resul.addD: agregar al final de mi lista "resul"
    Lista generaMulti3(){
        Lista resul;

        Nodo<T> aux =>raizi;

        MIENTRAS(aux!=NULO){
            resul.addD(REDONDEAR((aux->dato+1)/3.0)*3);
            aux =>aux->sig;
        }
        RETORNAR resul;
    }

    */

    //SOLUCION CODIGO
	Lista generaMulti3(){
		Lista resul;

		Nodo<T> *aux = raizi;

		while(aux!=nullptr){
            resul.addD(round((double)(aux->dato+1)/3.0)*3);
			aux = aux->sig;
		}
        return resul;
    }

};

class Cordenada{
public:
    float x,y;
    int b;

    Cordenada(float x,float y,int b){
        this->x = x;
        this->y = y;
        this->b = b;
    }

    void mostrar(){
//        (x,y,b)
//        (10.1,1.1,0)
//
        cout<<"("<<x<<","<<y<<","<<b<<")";
    }

    Cordenada(){}
    ~Cordenada(){}
protected:
private:
};

/**
//lista es una TDA LIsta doblemente enlazada

ARCHIVO archi = ABRIR_ARCHIVO("DINO.txt","r")
FLOTANTE x,y
INTEGER b

MIENTRAS(fscanf(archi,"%f%f%d",&x,&y,&b))INICIO
    lista.addI(Cordenada(x,y,b))
END

Nodo aux = lista.raizi

MIENTRAS(aux!=NULO)INICIO
    aux->dato.mostrar()
    aux = aux->sig
END
*/

int main(int argc,char *argv[],char **env){

    Lista<Cordenada> lista;
    FILE *archi = fopen("DINO.txt","r");
    float x,y;
    int b;

    while(fscanf(archi,"%f%f%d",&x,&y,&b)!=EOF){
        lista.addI(Cordenada(x,y,b));
    }

    Nodo<Cordenada> *aux = lista.raizi;
    cout<< ("raizi -> ");
    while(aux!=nullptr){
        aux->dato.mostrar();
        aux = aux->sig;
    }
    cout<<"nullptr"<<endl;


//    (11/3) = 3.55

  /*
    round (34.3) = 34
    round (34.53) = 35
    round (4.51) = 5
    */
/*
    Lista<int> l;

    l.addD(5);//1
    l.addD(8);
    l.addD(10);
    l.addD(9);

    l.mostrarI();

    Lista<int> resul = l.generaMulti3();

    resul.mostrarI();
*/
/*
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
*/
    return EXIT_SUCCESS;
}
