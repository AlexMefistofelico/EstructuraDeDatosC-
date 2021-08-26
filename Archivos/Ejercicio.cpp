#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptr NULL
using namespace std;
/*
Se tiene datos de personas (nombre,edad,sexo) de la Ciudad
de Oruro en un archivo, se desea realizar un pseudocódigo para:

a: Crear 2 archivos , uno de menores de 18 años y con
    sexo femenino y otro de mayores o iguales a 18 años
    con sexo masculino.
b:  Eliinar logicamente, a las personas de sexo femenino
    menores a 18 años.
c:  Eliminar fisicamente, a las personas que fueron eliminadas
    logicamente

*/

class Registro{
public:
    char nombre[15];
    int edad;
    char sexo;

    bool estado;

    Registro(char *nom,int ed,char sex){
        strcpy(nombre,nom);
        edad = ed;
        sexo = sex;
        estado = true;
    }

    Registro(){
        estado = true;
    }

    ~Registro(){

    }

    void llenar(){
        cout<<"Nombre: ";
        fflush(stdin);
        gets(nombre);
        cout<<"Edad: ";
        cin>>edad;
        cout<<"Sexo: ";
        cin>>sexo;
    }

    void mostrar(){
        cout<<nombre<<"\t"<<edad<<"\t"<<sexo<<endl;
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


    void eliminarLog(){
        Registro reg;

        abrir("r+");

        fread(&reg,sizeof(Registro),1,arch);

        while(!feof(arch)){

            if(reg.edad < 18 && reg.sexo == 'f' && reg.estado){
                reg.estado = false;
                fseek(arch,ftell(arch)-sizeof(Registro),SEEK_SET);
                fwrite(&reg,sizeof(Registro),1,arch);
                fseek(arch,ftell(arch)-sizeof(Registro),SEEK_SET);
            }
            fread(&reg,sizeof(Registro),1,arch);
        }
        fclose(arch);
    }



    void partir(const char *na,const char *nb){
        abrir("rb");

        FILE *a = fopen(na,"a+b");
        FILE *b = fopen(nb,"a+b");
        Registro reg;


        while(!feof(arch)){
            if(reg.edad<18 && reg.sexo == 'f')
                fwrite(&reg,sizeof(Registro),1,a);
            else if(reg.edad>=18 && reg.sexo == 'm')
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


    Archivo a("Archivo.dat");


    a.crear();

    a.agregar(Registro("Maria",14,'f'));
    a.agregar(Registro("Mario",24,'m'));
    a.agregar(Registro("Oscar",34,'m'));
    a.agregar(Registro("Jhoselin",17,'f'));
    a.agregar(Registro("Faviola",15,'f'));
    a.agregar(Registro("Galilea",4,'f'));
    a.agregar(Registro("Fabricio",54,'m'));


    cout<<"reporte gral."<<endl;
    a.reporte();


    a.partir("Menores.dat","Mayores.dat");
    cout<<"reporte Señoritas Menores."<<endl;
    a.reporte("Menores.dat");
    cout<<"reporte Jovenes Mayores."<<endl;
    a.reporte("Mayores.dat");


    a.eliminarLog();
    cout<<"reporte gral eliminacion logica ."<<endl;
    a.reporte();

    a.eliminar();
    return 0;
}


