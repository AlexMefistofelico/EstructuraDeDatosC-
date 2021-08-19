#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<cstdlib>
#define nullptr NULL
using namespace std;

class Pila{
private:

	int tope;
	string *P;
public:

	Pila(int n){
		tope = -1;
        P = new string[n];
	}

	~Pila(){
		//delete P;
	}

	bool vacio(){
		return tope == -1;
	}

	string enTope(){
		return P[tope];
	}

	void push(string dato){
		P[++tope]=dato;
	}

	string pop(){
		return P[tope--];
	}

	void elimina(){
		while(!vacio())
			pop();
	}
};


class Cola{
private:
    int prim;
	int ulti;
	string *C;

public:
    size_t N;

    Cola(int n){
        N = n;
		prim = -1;
		ulti = prim;
		C = new string[N];
	}

    ~Cola(){
        //delete C;
	}

	bool vacio(){
		return prim == -1;
	}

	string primero(){
		return C[prim];
	}

	string ultimo(){
		return C[ulti];
	}

	void insertar(string d){
		if(vacio())
			prim = 0;
		C[++ulti]=d;
	}

	string sacar(){
		string dato = C[prim];
		if(prim==ulti){
			prim = -1;
			ulti = -1;
		}else
			prim++;
		return dato;
	}

	void vaciar(){
		while(!vacio())
			sacar();
	}
};

class ImplementacionPostfijoEvalucion{
public:

    Cola aCola(string cad){
		Cola col(cad.size()+1);
		string aux = "";

		for(int i=0;i<cad.size();i++){
			if(isdigit(cad[i])||cad[i]=='.'){
				aux+=cad[i];
				if(i == cad.size()-1)
					col.insertar(aux);
			}else{
				if(aux!="")
					col.insertar(aux);

                col.insertar(string(1,cad[i]));
				aux = "";
			}
		}

		return col;
	}

	int prio(char c){
        switch(c){
            case '+':
            case '-':return 1;
            case '*':
            case '/':return 2;
            case '^':return 3;
            default : return 0;
        }
	}

	Cola aPosfijo(Cola colainf){
        Cola cola(colainf.N+1);//posfijo
        Pila pila(colainf.N+1);

        string x;

        while(!colainf.vacio()){
            x = colainf.sacar();

            switch(x[0]){
            case '(':
                pila.push(x);
                break;
            case ')':
                while(pila.enTope()!="(")
                    cola.insertar(pila.pop());
                pila.pop();

                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':

                while(!pila.vacio() && prio(x[0])<=prio(pila.enTope()[0]))
                    cola.insertar(pila.pop());//a posfijo....
                pila.push(x);

                break;
            default:
                cola.insertar(x);//directo a posfijo

            }

        }

        while(!pila.vacio())
            cola.insertar(pila.pop());

        return cola ; /// cola es el posfijo
	}

    double evaluar(Cola colaPosfijo){
        Pila pila (colaPosfijo.N);
        double x,y,z;
        string aux;

        while(!colaPosfijo.vacio()){
            aux = colaPosfijo.sacar();
            switch(aux[0]){
                case '^':
                case '/':
                case '*':
                case '+':
                case '-':
                    y = atof(pila.pop().data());
                    x = atof(pila.pop().data());
                switch(aux[0]){
                    case '^':
                        z = pow(x,y);
                    break;
                    case '/':
                        z = x/y;
                    break;
                    case '*':
                        z = x*y;
                    break;
                    case '+':
                        z = x+y;
                    break;
                    case '-':
                        z = x-y;
                    break;

                }
                char numSTR[50];
                sprintf(numSTR,"%f",z); //11.2 => "11.2"
                pila.push(numSTR /*valor de z*/);

                break;

                default :pila.push(aux);

            }


        }

        return atof(pila.pop().data());//"123.22" => 123.22

    }


};




int main(int argc,char *argv[],char **env){

    string exp ;
    ImplementacionPostfijoEvalucion obj;

//    exp = "((b+((b^2-a*c)^(1/2)))/(d*a))/((b+c)/(c+b*d))";
    exp = "((3.0+((3.0^2-1.6*5)^(1/2)))/(15.15*1.6))/((3.0+5)/(5+3.0*15.15))";

    Cola colainfijo = obj.aCola(exp);
    Cola colaPosfijo = obj.aPosfijo(colainfijo);


    cout<<"Infijo: "<<exp<<endl;
    cout<<"Posfijo: ";

    Cola colaPosfijoEvalua = colaPosfijo;

    while(!colaPosfijo.vacio()){
        cout<<colaPosfijo.sacar()<<" ";
    }



    cout<<endl;

    cout<<"Evaluacion: "<<obj.evaluar(colaPosfijoEvalua)<<endl;


    return EXIT_SUCCESS;
}















//amar y vivir

