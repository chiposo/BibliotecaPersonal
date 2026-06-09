#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<iomanip>
using namespace std;

struct items{
    int id=0;
    char titulo[100];
    char autor[100];
    int anio=0;
    char genero[10];
    int estado;

};

enum estado{
    DISPONIBLE,
    PRESTADO,
    SIN_EXISTENCIA
};
items* biblioteca = NULL;
int cantidad=0;
int ultimoid=1;
//funcion para incluir el paso por referencia
void aumentarc(int &c);
void aumentarc(int &c){
    c++;
}

//declaracion: prototipos
void generarreporte();
void menu();
void agregar();
void buscaritem();
void mostrartodo();
void modificar();
void eliminar();
void guardar();
void cargar();
void barraprogreso();
void barraprogreso(char mensaje[]){
    cout << "\n\n" << mensaje << "\n";
    cout << "[";
    for(int i=0; i<30; i++)
    {
        cout << (char)219;
        Sleep(10);
    }
    cout << "] 100%\n";
}
void pausa();
void pausa(){
    cout << "\n\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}
void portada();
void portada(){
    system("cls");
    cout << "\n";
    cout << "///////////////////////////////////////////////////////\n";
    cout << "//                                                  //\n";
    cout << "//       SISTEMA DE BIBLIOTECA PERSONAL            //\n";
    cout << "//             PROGRAMACION I                     //\n";
    cout << "///////////////////////////////////////////////////\n";
    barraprogreso("Iniciando....");
    Sleep(500);
}
void rapido();
void rapido(){
    barraprogreso("Cargando....");
    Sleep(50);
    system("cls");
};
int buscarid(int id);
int main(){
    system("color 0B");
    portada();
    cargar();
    menu();
    return 0;
}

void menu(){
     int opc = 0;
    do{
            system("cls");
            cout << "+-----------------------------------+\n";
            cout << "|             BIBLIOTECA            |\n";
            cout << "|-----------------------------------|\n";
            cout << "  Libros registrados:"<<cantidad<<"\n";
            cout << "|-----------------------------------|\n";
            cout << "|Agregar nuevo item................1|\n";
            cout << "|Buscar Item.......................2|\n";
            cout << "|Mostrar Todos.....................3|\n";
            cout << "|Modificar Item....................4|\n";
            cout << "|Eliminar Item.....................5|\n";
            cout << "|Guardar y salir...................6|\n";
            cout << "+-----------------------------------+\n";
            cout << "Selecciona una opcion: ";
            cin >> opc;
            system("cls");
            switch(opc){
                case 1: agregar(); break;
                case 2: buscaritem(); break;
                case 3: mostrartodo(); break;
                case 4: modificar(); break;
                case 5: eliminar(); break;
                case 6: guardar(); free(biblioteca); break;
            }
    }while(opc!=6);
}

void agregar(){
    //aumentar la cantidad de los elementos almacenados
    aumentarc(cantidad);
    //crear el espacio de memoria para biblioteca
    biblioteca=(items*)realloc(biblioteca,cantidad * sizeof(items));

    //obtiene la direccion del ultimo espacio disponible
    items* nuevo= &biblioteca[cantidad - 1];
    nuevo->id = ultimoid++;
    cin.ignore();

    //llenado de datos
    cout <<"\nTitulo: ";
    cin.getline(nuevo->titulo,100);
    rapido();
    cout<<"\nAutor: ";
    cin.getline(nuevo->autor,100);
    rapido();
    cout<<"\nAnio: ";
    cin >> nuevo->anio;
    rapido();
    cin.ignore();
    cout <<"\nGenero: ";
    cin.getline(nuevo->genero,10);
    rapido();
    nuevo->estado=DISPONIBLE;
    guardar();
    cout << "\n El libro fue agregado correctamente \n";
    cin.ignore();
    pausa();



}

//funcion auxiliar para buscar
int buscarid(int id){
    //recorrer los elementos
    for(int i=0; i< cantidad; i++){
        if(biblioteca[i].id==id){
            return i;
        }
    }
    //retornar -1 si no encuentra el id
    return -1;
}

//funcion para buscar 
void buscaritem(){
    //verificar si existen registros
    if(cantidad == 0){
        cout << "\n No existen libros \n";
        return;
    }
    int id=-1;
    int posicion=-1;
    char titulob[100];
    cout << "\n Ingresa el titulo del libro a buscar: \n";
    cin.ignore();
    cin.getline(titulob,100);
    rapido();
    for(int i=0; i<cantidad; i++){
        if(strcmp(biblioteca[i].titulo,titulob)==0){
            id=biblioteca[i].id;
            posicion=i;
            break;
        }
    }
    if(id==-1){
        cout << "\n **No se encontro el libro por el titulo pero puedes intentar por id** \n";
        cout << "\n Ingresa el id: \n";
        cin >> id;
        rapido();
        posicion=buscarid(id);
    }
    if(posicion == -1){
        cout << "\n Libro no encontrado \n";
  
    }else{
        cout << "\n+------------------------------------------------+\n";
        cout << "|                LIBRO ENCONTRADO                |\n";
        cout << "+------------------------------------------------+\n";
        cout << "| ID      : " << biblioteca[posicion].id << endl;
        cout << "| Titulo  : " << biblioteca[posicion].titulo << endl;
        cout << "| Autor   : " << biblioteca[posicion].autor << endl;
        cout << "| Anio    : " << biblioteca[posicion].anio << endl;
        cout << "| Genero  : " << biblioteca[posicion].genero << endl;
        cout << "| Estado  : ";
        if(biblioteca[posicion].estado==DISPONIBLE)
            cout << "Disponible";
        else if(biblioteca[posicion].estado==PRESTADO)
            cout << "Prestado";
        else
            cout << "Sin existencia";

        cout << "\n+------------------------------------------------+\n";
    }
    cout << endl;
    pausa();


}

//mostrar todos los registros al momento
void mostrartodo()
{
    if(cantidad == 0)
    {
        cout << "\nNo existen libros registrados.\n";
        pausa();
        return;
    }
    cout << "\n========================================================================================================\n";
    cout << left
         << setw(5)  << "ID"
         << setw(25) << "TITULO"
         << setw(20) << "AUTOR"
         << setw(8)  << "ANIO"
         << setw(15) << "GENERO"
         << setw(15) << "ESTADO"
         << endl;
    cout << "========================================================================================================\n";
    for(int i=0; i<cantidad; i++)
    {
        cout << left
             << setw(5)  << biblioteca[i].id
             << setw(25) << biblioteca[i].titulo
             << setw(20) << biblioteca[i].autor
             << setw(8)  << biblioteca[i].anio
             << setw(15) << biblioteca[i].genero;

        if(biblioteca[i].estado == DISPONIBLE)
            cout << setw(15) << "Disponible";
        else if(biblioteca[i].estado == PRESTADO)
            cout << setw(15) << "Prestado";
        else
            cout << setw(15) << "Sin existencia";

        cout << endl;
    }
    cout << "========================================================================================================\n";
    pausa();
}

void modificar(){
    if(cantidad == 0){
        cout << "\n No existen registros \n";
        pausa();
        return;
    }

    char titulob[100];
    int posicion=-1;
    int opc=0;
    cout << "\n Ingresa el titulo del libro a modificar: \n";
    cin.ignore();
    cin.getline(titulob,100);
    rapido();
    for(int i=0; i<cantidad; i++){
        if(strcmp(biblioteca[i].titulo,titulob)==0){
            posicion=i;
            break;
        }
    }

    if(posicion == -1){
        cout << "\n Libro no encontrado \n";
        pausa();
        return;
    }

     
    cout << "\n";
    cout << "============================================================\n";
    cout << "                  MODIFICAR LIBRO\n";
    cout << "============================================================\n";
    cout << " ID      : " << biblioteca[posicion].id << endl;
    cout << " TITULO  : " << biblioteca[posicion].titulo << endl;
    cout << " AUTOR   : " << biblioteca[posicion].autor << endl;
    cout << " ANIO    : " << biblioteca[posicion].anio << endl;
    cout << " GENERO  : " << biblioteca[posicion].genero << endl;
    cout << " ESTADO  : ";
    if(biblioteca[posicion].estado == DISPONIBLE)
    {
        cout << "Disponible";
    }
    else if(biblioteca[posicion].estado == PRESTADO)
    {
        cout << "Prestado";
    }
    else
    {
        cout << "Sin existencia";
    }
    cout << "\n============================================================\n";
    cout << "\n ¿Que deseas modificar?\n\n";
    cout << " [1] Solo estado\n";
    cout << " [2] Todos los datos\n";
    cout << " [0] Cancelar\n";
    cout << "\n Opcion: ";
    cin >> opc;
    rapido();
    switch(opc){
        case 1: 
                cout << "\n";
                cout << "================ SELECCIONAR ESTADO ================\n";
                cout << " [0] Disponible\n";
                cout << " [1] Prestado\n";
                cout << " [2] Sin existencia\n";
                cout << "====================================================\n";
                cout << " Seleccione: ";
                cin >> biblioteca[posicion].estado;
                rapido();
                cout << "\n";
                cout << "************************************************************\n";
                cout << "*                                                          *\n";
                cout << "*          ESTADO MODIFICADO CORRECTAMENTE                 *\n";
                cout << "*                                                          *\n";
                cout << "************************************************************\n";
                pausa();

                break;
        case 2:     
                           

                cout << "\n";
                cout << "============================================================\n";
                cout << "              INGRESE LOS NUEVOS DATOS\n";
                cout << "============================================================\n";
                cout << "\nNuevo titulo: ";
                cin.ignore();
                cin.getline(biblioteca[posicion].titulo,100);
                rapido();
                cout << "Nuevo autor: ";
                cin.getline(biblioteca[posicion].autor,100);
                rapido();
                cout << "Nuevo anio: ";
                cin >> biblioteca[posicion].anio;
                cin.ignore();
                rapido();
                cout << "Nuevo genero: ";
                cin.getline(biblioteca[posicion].genero,10);
                rapido();
                cout << "\n";
                cout << "================ SELECCIONAR ESTADO ================\n";
                cout << " [0] Disponible\n";
                cout << " [1] Prestado\n";
                cout << " [2] Sin existencia\n";
                cout << "====================================================\n";
                cout << " Seleccione: ";
                cin >> biblioteca[posicion].estado;
                rapido();
                cout << "\n";
                cout << "************************************************************\n";
                cout << "*                                                          *\n";
                cout << "*          LIBRO MODIFICADO CORRECTAMENTE                  *\n";
                cout << "*                                                          *\n";
                cout << "************************************************************\n";
                pausa();
                
                break;
        default: return;
                    

    }
    guardar();
}

void eliminar(){
    if(cantidad == 0){
        cout << "\n No existen registros \n";
        pausa();
        return;
    }

    char titulob[100];
    int posicion=-1;
    cout << "\n Ingresa el titulo del libro a eliminar: \n";
    cin.ignore();
    cin.getline(titulob,100);
    rapido();
    for(int i=0; i<cantidad; i++){
        if(strcmp(biblioteca[i].titulo,titulob)==0){
            posicion=i;
            break;
        }
    }

    if(posicion == -1){
        cout << "\n Libro no encontrado \n";
        pausa();
        return;
    }   

    //para eliminar tenemos que recorrer los elementos hacia atras en base a lo encontrado
    for(int i=posicion; i<cantidad-1; i++){
        biblioteca[i]=biblioteca[i+1];
    }

    cantidad --;
    //aqui redimencionamos la memoria para ajusntar a la cantidad de registros
    biblioteca = (items*)realloc(biblioteca,cantidad * sizeof(items));
    rapido();
    cout << "\n";
    cout << "************************************************************\n";
    cout << "*                                                          *\n";
    cout << "*           LIBRO ELIMINADO CORRECTAMENTE                  *\n";
    cout << "*                                                          *\n";
    cout << "************************************************************\n";
    pausa();
    guardar();
}

void guardar(){
    FILE *archivo;
    archivo = fopen("biblioteca.dat","wb");
    if(archivo == NULL){
        cout << "\nERROR\n";
        return;
    }

    fwrite(&cantidad,sizeof(int),1,archivo);
    fwrite(biblioteca,sizeof(items),cantidad,archivo);
    fclose(archivo);
    rapido();
    cout << "\n";
    cout << "************************************************************\n";
    cout << "*                                                          *\n";
    cout << "*           DATOS GUARDADOS CORRECTAMENTE                  *\n";
    cout << "*                                                          *\n";
    cout << "************************************************************\n";
    pausa();
    system("cls");
    generarreporte();
}

void cargar(){
    FILE *archivo;
    archivo=fopen("biblioteca.dat","rb");
    if(archivo == NULL){
        return;
    }

    fread(&cantidad,sizeof(int),1,archivo);
    biblioteca=(items*)malloc(cantidad * sizeof(items));
    fread(biblioteca,sizeof(items),cantidad,archivo);
    fclose(archivo);
    ultimoid=cantidad+1;
}

void generarreporte(){
    FILE *reporte;
    reporte = fopen("reporte.txt","w");
    if(reporte == NULL){
        cout << "\n Error \n";
        return;
    }

    fprintf(reporte,"=========== REPORTE DE BIBLIOTECA ===========\n\n");
    for(int i=0; i<cantidad; i++){
        fprintf(reporte,"ID: %d\n",biblioteca[i].id);
        fprintf(reporte,"Titulo: %s\n",biblioteca[i].titulo);
        fprintf(reporte,"Autor: %s\n",biblioteca[i].autor);
        fprintf(reporte,"Anio: %d\n",biblioteca[i].anio);
        fprintf(reporte,"Genero: %s\n",biblioteca[i].genero);
        if(biblioteca[i].estado == DISPONIBLE)
            fprintf(reporte,"Estado: Disponible\n");
        else if(biblioteca[i].estado == PRESTADO)
            fprintf(reporte,"Estado: Prestado\n");
        else
            fprintf(reporte,"Estado: Sin existencia\n");

        fprintf(reporte,
                "-----------------------------------------\n");
    }
    fclose(reporte);
    cout << "\nReporte TXT generado \n";
    pausa();
}