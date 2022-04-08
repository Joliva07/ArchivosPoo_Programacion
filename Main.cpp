#include "Estudiante.cpp"
#include <iostream>
#include <stdio.h>
using namespace std;

const char *nom_arch="archivo.dat";
const char *temp="temporal.dat";


main(){
	estudiante es;
	int n=0;
	char con;
	do{
		system("cls");
		cout<<"Escriba el numero de la opcio que desea realizar:\n1.Ver listado de estudiantes\n2.Agregar estudiantes al listado\n3.Actualizar listado de estudiantes\n4.Eliminar un estudiante del listado\n";
		cin>>n;
		switch(n){
			case 1:
				es.leer(); break;
			case 2:
				es.crear(); break;
			case 3:
				es.leer();
				es.actualizar(); break;
			case 4:
				es.leer();
				es.eliminar(); break;
			default:
			cout<<"El numero seleccionado no es una opcion, vuelva a intentarlo";			
		}
		cout<<"\nDesea Realizar otra accion? (s/n): ";
		cin>>con;
	}while(con=='s'||con=='S');
}

void estudiante::leer(){
	system("cls");
	FILE* archivo=fopen(nom_arch,"rb");
	if(!archivo){
		archivo=fopen(nom_arch,"w+b");
	}
	Estud estud;
	int id=0;
	fread(&estud,sizeof(Estud),1,archivo);
	
	cout<<"id"<<"|"<<"codigo"<<"|"<<"Nombres"<<"|"<<"Apellidos"<<"|"<<"Direccion"<<"|"<<"Telefono"<<endl;
	do{
		cout<<"__________________________________________________________\n";
		cout<<id<<" | "<<estud.codigo<<" | "<<estud.nombres<<" | "<< estud.apellidos <<" | "<<estud.direccion<<" | "<<estud.telefono<<endl;
		fread(&estud,sizeof(Estud),1,archivo);
		id=id+1;
	}while(feof(archivo)==0);
	fclose(archivo);
}

void estudiante::crear(){
	FILE* archivo=fopen(nom_arch,"ab");
	char con;
	Estud estud;
	do{
		fflush(stdin);
		cout<<"Ingrese el codigo: ";
		cin>>estud.codigo;
		cin.ignore();
		cout<<"Ingrese el nombre: ";
		getline(cin,estud.nombres);
		cout<<"Ingrese el apellido: ";
		getline(cin,estud.apellidos);
		cout<<"Ingrese la direccion: ";
		getline(cin,estud.direccion);
		cout<<"Ingrese el telefono: ";
		cin>>estud.telefono;
		fwrite(&estud,sizeof(Estud),1,archivo);
		cout<<"\nDesea ingresar datos de otro estudiante (s/n): ";
		cin>>con;
		cout<<endl;
	}while(con=='s'||con=='S');
	fclose(archivo);
}

void estudiante::actualizar(){
	FILE* archivo=fopen(nom_arch,"r+b");
	int id;
	Estud estud;
	cout<<"Ingrese el id a modificar: ";
	cin>>id;
	fseek(archivo, id *sizeof(Estud),SEEK_SET);
	cout<<"Ingrese el codigo: ";
	cin>>estud.codigo;
	cin.ignore();
	cout<<"Ingrese el nombre: ";
	getline(cin,estud.nombres);
	cout<<"Ingrese el apellido: ";
	getline(cin,estud.apellidos);
	cout<<"Ingrese la direccion: ";
	getline(cin,estud.direccion);
	cout<<"Ingrese el telefono: ";
	cin>>estud.telefono;
	fwrite(&estud,sizeof(Estud),1,archivo);
	fclose(archivo);
}

void estudiante::eliminar(){
	int id=0,i=0;
	FILE *archivo, *arch_tem;
	Estud estud;
	archivo=fopen(nom_arch,"rb");
	arch_tem=fopen(temp,"w+b");
	
	cout<<"Ingrese el id eliminar: ";
	cin>>id;
	
	while(fread(&estud,sizeof(Estud),1,archivo)){
		if(i!=id){
			fwrite(&estud,sizeof(Estud),1,arch_tem);
		}
		i++;
	}
	fclose(archivo);
	fclose(arch_tem);
	
	archivo=fopen(nom_arch,"wb");
	arch_tem=fopen(temp,"rb");
	while(fread(&estud,sizeof(Estud),1,arch_tem)){
		fwrite(&estud,sizeof(Estud),1,archivo);
	}
	fclose(archivo);
	fclose(arch_tem);
}










