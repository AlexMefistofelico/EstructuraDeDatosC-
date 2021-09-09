#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define nullptr NULL
using namespace std;
/*
1. Una clinica necesita guardar información de sus pacientes, para lo cual requiere los siguientes datos:
 Sexo (char)
 Vacunado (bool)
 Edad (int)
 Nombre (char*)
 celular (int)
 fechaConsulta (defina una estructura para manejar la fecha)
*/
class Registro{
 public:
    char sexo;
    bool vacunado ;
    int edad;
    char nombre[15];
    int celular;
    char fechaConsulta[15];

    Registro(char c,bool v,int e,char *n,int ce,char* f){
        sexo = c;
        vacunado = v;
        edad = e;
        strcpy(nombre,n);
        celular = ce;
        strcpy(fechaConsulta,f);
    }


    ~Registro(){

    }

    Registro(){
        sexo = nullptr;
        vacunado = false;
        edad = 0;
        strcpy(nombre,"");
        celular = 0;
        strcpy(fechaConsulta,"");
    }
    void mostrar(){
        cout<<(sexo=='M'?"Masculino":"Femenino")<<"\t"<<(vacunado?"":"NO ")<<"vacunado"<<"\t"<<edad<<"\t"<<nombre<<"\t"<<celular<<"\t"<<fechaConsulta<<endl;
    }

};



class Archivo{
public:
     char nombre[20];
     FILE *arch;                            //archivo principal
    //para el primer metodo de orden...
    FILE *a,*b;                             //archivos auxiliares
    char *nomA="auxA.dat",*nomB="auxB.dat"; //nombres de archivos auxiliares
    int p;                                  //para las secuencias...

    FILE *aux[10];                          //para el segundo metodo de orden
    int digito=0;                           //contador.

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
                reg.mostrar();
            fread(&reg,sizeof(Registro),1,arch);
        }
        fclose(arch);
    }
/*
2. Seleccionar en un archivo de texto llamado “contacto.txt”, el nombre y celular de los pacientes cuya
Sexo sea ‘M’ masculino, el nombre y celular estarán separados por “,” y cada registro estará separado
por “;”
*/
    void generaContacto(){
        abrir("rb");
        Registro reg;

        FILE *aux = fopen("contacto.txt","a+b");

        fread(&reg,sizeof(Registro),1,arch);

        while(!feof(arch)){
            if(reg.sexo=='M')
                fprintf(aux,"%s,%d,%c;",reg.nombre,reg.celular,reg.sexo);
            fread(&reg,sizeof(Registro),1,arch);
        }

        fclose(aux);
        fclose(arch);
    }
/*
3. Seleccionar en un archivo binario el nombre y Sexo de las pacientes que aún no se encuentren
vacunadas
*/
    void sinVacuna(){
        abrir("rb");
        FILE *aux = fopen("noVacunados.dat","wb");
        Registro reg;

        fread(&reg,sizeof(Registro),1,arch);
        while(!feof(arch)){
            if(!reg.vacunado){
                fwrite(&reg.nombre,sizeof(char[15]),1,aux);
                fwrite(&reg.sexo,sizeof(reg.sexo),1,aux);
            }
            fread(&reg,sizeof(Registro),1,arch);
        }
        fclose(arch);
        fclose(aux);
    }

    void sinVacunaReporte(){
        FILE *arch = fopen("noVacunados.dat","rb");
        Registro reg;

        fread(&reg.nombre,sizeof(reg.nombre),1,arch);
        fread(&reg.sexo,sizeof(reg.sexo),1,arch);

        while(!feof(arch)){
            fread(&reg.nombre,sizeof(reg.nombre),1,arch);
            fread(&reg.sexo,sizeof(reg.sexo),1,arch);
            reg.mostrar();
        }
        fclose(arch);

    }

/*
4. Eliminar físicamente los registros del archivo cuyos celulares de los dueños no sea un número correcto
de celular (un número correcto de celular debe constar de 8 dígitos y el primer número debe estar entre
6 y 8)
*/
    bool esValido(int cel){
        return cel>=60000000 && cel<90000000;
    }

     void eliminar(){
        abrir("rb");
        FILE *tmp = fopen("tmp.dat","a+b");

        Registro reg;

        fread(&reg,sizeof(Registro),1,arch);
        while(!feof(arch)){
            if(esValido(reg.celular))
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
/*
5. Ordenar el archivo “clinica.dat” en base al campo “edad”, utilizando el algoritmo de “Mezcla Natural”
o “Mezcla Equilibrada”
*/
    /*desde aqui es el ORDEN 1.*/
    /*desde aqui es el ORDEN 1.*/
    /*desde aqui es el ORDEN 1.*/

    void copiarSecP(FILE*x,FILE*y,int p){
        int cont=1;
        Registro reg;

        while(cont<=p && !feof(x)){
            fread(&reg, sizeof(Registro),1,x);
            if(!feof(x))
                fwrite(&reg, sizeof(Registro),1,y);
            cont++;
        }
    }

    void particion(){
        while(!feof(arch)){
            copiarSecP(arch,a,p);
            if(!feof(arch))
                copiarSecP(arch,b,p);
        }
    }

    void mezclarSecP(int p){
        int seca=0,secb=0,posa,posb;
        Registro rega,regb;
        do{
            posa=ftell(a);
            fread(&rega,sizeof(Registro),1,a);
            fseek(a,posa,0);
            posb=ftell(b);
            fread(&regb,sizeof(Registro),1,b);
            fseek(b,posb,0);
            if(rega.edad<regb.edad){
                copiarSecP(a,arch,1);
                seca++;
                if(seca==p){
                    copiarSecP(b,arch,p-secb);
                    secb=p;
                }
            }else{
                copiarSecP(b,arch,1);
                secb++;
                if(secb==p){
                    copiarSecP(a,arch,p-seca);
                    seca=p;
                }
            }
        }while(seca!=p && secb!=p);
    }

    void mezclar(){
        while(!feof(a) && !feof(b)){
            mezclarSecP(p);
        }
    }

    void ordenar(){
        int mitad;
        abrir("rb+");
        fseek(arch,0,SEEK_END);
        mitad= (ftell(arch)/sizeof(Registro))/2;
        p=1;
        do{
            a=fopen(nomA,"wb+");
            b=fopen(nomB,"wb+");
            rewind(arch);
            particion();
            rewind(a);
            rewind(b);

            rewind(arch);
            mezclar();
            fclose(b);
            fclose(a);
            p=p*2;
        } while( p<=mitad);
        fclose(arch);
    }
/*
6. Ordenar el archivo “clinica.dat” en base al campo “celular”, utilizando el algoritmo de “Inspección de
Dígitos”
*/
    /*desde aqui es el ORDEN 2.*/
    /*desde aqui es el ORDEN 2.*/
    /*desde aqui es el ORDEN 2.*/

    void particionar(){
        Registro reg;
        int posaux;

        while(!feof(arch)){
            fread(&reg,sizeof(Registro),1,arch);
            if(!feof(arch)){
                posaux=(reg.celular/(int)pow(10,digito))%10;
                fwrite(&reg,sizeof(Registro),1,aux[posaux]);
            }
        }
    }

    void mezclar2(){
        Registro reg;
        for(int i=0;i<10;i++)
            while(!feof(aux[i])){
                fread(&reg,sizeof(Registro),1,aux[i]);
                if(!feof(aux[i]))
                    fwrite(&reg,sizeof(Registro),1,arch);
            }
    }

    void ordenarDigito(){
        int i;
        char nombre[11]="arch0.dat";

        abrir("rb+");

        do{
            rewind(arch);
            for(i=0;i<10;i++){
                nombre[4]='0'+i;
                aux[i]=fopen(nombre,"wb+");
            }

            particionar();

            rewind(arch);
            for(i=0;i<10;i++)
                rewind(aux[i]);

            mezclar2();
            for(i=0;i<10;i++)
                fclose(aux[i]);

            digito++;
        }while(digito<=8/*num digitos del numero mas largo*/);

        fclose(arch);
    }

};




int main(int argc,char *argv[],char **env){


    cout<<"tama"<<((char)164)<<"o de cada registro: "<<sizeof(Registro)<<endl;

    Archivo a("Archivo.dat");

    a.crear();

    /*
    1. Una clinica necesita guardar información de sus pacientes, para lo cual requiere los siguientes datos:
         Sexo (char)
         Vacunado (bool)
         Edad (int)
         Nombre (char*)
         celular (int)
         fechaConsulta (defina una estructura para manejar la fecha)
    */

    a.agregar(Registro('M',true,12,"asdf",60202021,"01/01/2010"));
    a.agregar(Registro('F',true,21,"asdf",70202021,"01/01/2010"));
    a.agregar(Registro('M',false,11,"asdf",80202021,"01/01/2010"));
    a.agregar(Registro('F',false,1,"asdf",20210000,"01/01/2010"));
    a.agregar(Registro('M',true,2,"asdf",60202021,"01/01/2010"));
    a.agregar(Registro('F',true,1,"asdf",10000000,"01/01/2010"));
    a.agregar(Registro('M',true,1,"asdf",60202021,"01/01/2010"));
    a.agregar(Registro('F',false,31,"asdf",70202021,"01/01/2010"));
    a.agregar(Registro('M',true,42,"asdf",60202021,"01/01/2010"));
    a.agregar(Registro('F',true,42,"asdf",70202021,"01/01/2010"));
    a.agregar(Registro('M',false,41,"asdf",60202021,"01/01/2010"));
    a.agregar(Registro('F',false,21,"asdf",70202021,"01/01/2010"));
    a.agregar(Registro('M',true,62,"asdf",60202021,"01/01/2010"));
    a.agregar(Registro('F',true,28,"asdf",70202021,"01/01/2010"));
    a.agregar(Registro('M',false,101,"asdf",60202021,"01/01/2010"));
    a.agregar(Registro('F',false,91,"asdf",50002021,"01/01/2010"));

    puts("\nANTES DEL ORDEN");
    a.reporte();


/*
2. Seleccionar en un archivo de texto llamado “contacto.txt”, el nombre y celular de los pacientes cuya
Sexo sea ‘M’ masculino, el nombre y celular estarán separados por “,” y cada registro estará separado
por “;”
*/
    puts("\nGenerando Archivo *.txt Contactos");
    a.generaContacto();




/*
3. Seleccionar en un archivo binario el nombre y Sexo de las pacientes que aún no se encuentren
vacunadas
*/
    puts("\nGenera Archivo Binario NOmbre Sexo");
    a.sinVacuna();
    a.sinVacunaReporte();




/*
4. Eliminar físicamente los registros del archivo cuyos celulares de los dueños no sea un número correcto
de celular (un número correcto de celular debe constar de 8 dígitos y el primer número debe estar entre
6 y 8)
*/
    puts("\nEliminacion Fisica (Presione Tecla Para Continuar:)");
    getchar();
    a.eliminar();



/*
5. Ordenar el archivo “clinica.dat” en base al campo “edad”, utilizando el algoritmo de “Mezcla Natural”
o “Mezcla Equilibrada”
*/
    a.ordenar();
    puts("\nDESPUES DEL ORDEN POR EDAD");
    a.reporte();



/*
6. Ordenar el archivo “clinica.dat” en base al campo “celular”, utilizando el algoritmo de “Inspección de
Dígitos”
*/
    a.ordenarDigito();
    puts("\nDESPUES DEL ORDEN POR TELEFONO");
    a.reporte();





    return 0;
}


