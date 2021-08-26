#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptr NULL
using namespace std;
/*
Las Presente Clase Registro es una clase que se almacenara en un archivo de acceso
Cod:	código del producto
Precio: precio del producto
Nombre: nombre del producto
Fecha vencimiento: la fecha vencimiento del producto
Estado: estado del producto para ver si un producto estar dado de alta o eliminado.
*/

class Registro{
public:
    int cod;
    double precio;
    char nombre[15];
    char fechaV[15];
    bool estado ;

    Registro(int num,double pre,char *nom,char *fec){
        estado = true;
        cod = num;
        precio = pre;
        strcpy(nombre,nom);
        strcpy(fechaV,fec);
    }

    Registro(){
        estado = true;
    }

    ~Registro(){

    }

    void llenar(){
        cout<<"cod: ";
        cin>>cod;
        cout<<"precio: ";
        cin>>precio;
        cout<<"Nombre: ";
        fflush(stdin);
        gets(nombre);
        cout<<"fechaVec: ";
        fflush(stdin);
        gets(nombre);
    }

    void mostrar(){
        cout<<cod<<"\t"<<precio<<"\t"<<nombre<<"\t"<<fechaV<<endl;
    }

};



class Archivo{
public:
     char nombre[20];
     FILE *arch;

     Archivo(char*n){
        strcpy(nombre,n);
        arch = new FILE;
    }

    ~Archivo(){
        delete arch;
    }

    void abrir(char*m){
        arch = fopen(nombre,m);
    }

    void crear(){
        abrir("wb");
        cout<<((arch!=nullptr)?"Creado Con Exito":"NO se pudo Crear")<<endl;
        fclose(arch);
    }

    void agregar(Registro reg){
        abrir("a+b");
        fwrite(&reg,sizeof(Registro),1,arch);
        fclose(arch);
    }

    void reporte(){
        abrir("rb");
        Registro reg;

        fread(&reg,sizeof(Registro),1,arch);
        while(!feof(arch)){
            if(reg.estado)
                reg.mostrar();
            fread(&reg,sizeof(Registro),1,arch);
        }
        fclose(arch);
    }

    void reporte(char const *nom){
        arch = fopen(nom,"rb");
        Registro reg;

        fread(&reg,sizeof(Registro),1,arch);
        while(!feof(arch)){
            if(reg.estado)
                reg.mostrar();

            fread(&reg,sizeof(Registro),1,arch);
        }
        fclose(arch);
    }


    long buscar(int cod){
        abrir("rb");
        Registro reg;

        long indice = -1;
        bool sw=true;

        fread(&reg,sizeof(Registro),1,arch);

        while(!feof(arch) && sw){
            if(reg.cod==cod){
                sw = false;
                break;
            }
            fread(&reg,sizeof(Registro),1,arch);
        }

        if(!sw)indice = ftell(arch)-sizeof(Registro);

        fclose(arch);
        return indice;
    }

    void modificar(int cod,Registro reg){
        ///NECESITAMOS ARCHIVO AXUILIAR PARA LA MODIFICACION
        long index = buscar(cod);
        abrir("r+");

        if(index >= 0){
            fseek(arch,index,SEEK_SET);
            fwrite(&reg,sizeof(Registro),1,arch);
        }else
            cerr<<"Registro no ha sido encontrado"<<endl;
        fclose(arch);
    }

    void eliminar(int cod){
        Registro reg;

        long index = buscar(cod);

        abrir("r+");

        if(index>=0){
            fseek(arch,index,SEEK_SET);
            fread(&reg,sizeof(Registro),1,arch);
            reg.estado = false;
            fseek(arch,index,SEEK_SET);
            fwrite(&reg,sizeof(Registro),1,arch);
        }else
            cerr<<"Registro no ha sido encontrado"<<endl;
        fclose(arch);
    }

    void partir(const char *na,const char *nb){
        abrir("rb");

        FILE *a = fopen(na,"a+b");
        FILE *b = fopen(nb,"a+b");
        Registro reg;


        while(!feof(arch)){
            if(reg.cod%2==0)
                fwrite(&reg,sizeof(Registro),1,a);
            else
                fwrite(&reg,sizeof(Registro),1,b);

            fread(&reg,sizeof(Registro),1,arch);
        }

        fclose(a);
        fclose(b);
        fclose(arch);
    }

     void eliminar(){
        abrir("rb");
        FILE *tmp = fopen("tmp.dat","a+b");

        Registro reg;

        fread(&reg,sizeof(Registro),1,arch);
        while(!feof(arch)){
            if(reg.estado)
                fwrite(&reg,sizeof(Registro),1,tmp);
            fread(&reg,sizeof(Registro),1,arch);
        }
        fclose(tmp);
        fclose(arch);

        remove(nombre);
        rename("tmp.dat",nombre);
    }

    long tamArch(){
        abrir("rb");

        fseek(arch,0,SEEK_END);
        long t = ftell(arch);

        fclose(arch);
        return t;
    }

    int numReg(){
        return tamArch()/sizeof(Registro);
    }
};



int main(int argc,char *argv[],char **env){


    cout<<sizeof(Registro)<<endl;

    Archivo a("Archivo.dat");
/*
    a.crear();

    a.agregar(Registro(43,15.55,"jabon","01/01/2010"));
    a.agregar(Registro(15,53.3,"jamon","12/12/2011"));
    a.agregar(Registro(49,15.55,"leche","01/06/2010"));
    a.agregar(Registro(55,65.3,"ace","12/12/2011"));
    a.agregar(Registro(40,5.455,"tody","01/01/2010"));
    a.agregar(Registro(59,65.3,"salmon","12/12/2011"));
    a.agregar(Registro(41,15.55,"atum","01/11/2020"));
    a.agregar(Registro(51,10.3,"fideo","12/12/2021"));
    a.agregar(Registro(13,115,"arroz","01/05/1992"));
    a.agregar(Registro(75,655,"arroz","12/02/2011"));
*/

    cout<<a.buscar(43)<<endl;
    cout<<a.buscar(15)<<endl;

    a.reporte();

    a.eliminar(41);
    a.eliminar(51);
    a.eliminar(13);


    a.eliminar();


    return 0;
}


