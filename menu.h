#include <iostream>
#include "general_utils.h"

using namespace std;

void introduction();

void main_menu();

void vertices_menu();

void edges_menu();


void introduction() {
    clean_console();
    cout << "=================================================================================================== \n\n\n";
    cout << "Bienvenido al sistema de administracion de red\n\n";
    cout << "Mediante este programa ud puede gestionar los nodos de una red de manera limitada, pero eficiente. \n"
            "Se encuentran disponibles las siguientes opciones:\n\n"
            "- Trabajo con nodos de una red (CRUD)\n"
            "- Trabajo con enlaces entre nodos (CRUD)\n"
            "- Persistencia de datos en bases de datos SQL\n"
            "- Implementacion del algoritmo de djikstra (camino mas cercano) para grandes volumenes de datos\n\n";
    cout << "=================================================================================================== \n\n";
    cout <<"Presione cualquier tecla para comenzar";
    getchar();

}

void main_menu() {

    while (true) {
        clean_console();
        cout << "============================================================================== \n\n";
        cout << "                           Sistema de administracion de red                                \n\n";
        cout << "==============================================================================\n\n";

        cout << "1 -> Gestionar nodos" << endl;
        cout << "2 -> Gestionar arcos" << endl;
        cout << "3 -> Hallar ruta mas cercana" << endl;
        cout << "4 -> Crear db" << endl;
        cout << "5 -> Salir" << endl;
        cout <<"\n\nIntroduzca su seleccion: ";


        int option;

        option = validateInput(option);
        switch (option) {
            case 1:
                vertices_menu();
                break;
            case 2:
                edges_menu();
                break;
            case 3:
                get_shortest_path();
                break;
            case 4:
                create_tables();
                break;
            case 5:
                return;

            default:
                cout << "Por favor inserte un numero entre 1 y 4." << endl;
                break;
        }
    }
}

void vertices_menu() {
    while (true) {
        clean_console();

        cout << "============================================================================== \n\n";
        cout << "                            Sistema de administracion de red                                 \n\n";
        cout << "==============================================================================\n\n";

        cout << "1 -> Añadir vertice" << endl;
        cout << "2 -> Modificar vertice" << endl;
        cout << "3 -> Eliminar vertice" << endl;
        cout << "4 -> Listar vertices" << endl;
        cout << "5 -> Obtener nodos adyacentes" << endl;
        cout << "6 -> Volver" << endl;
        cout <<"\n\nIntroduzca su seleccion: ";


        int option;

        option = validateInput(option);
        switch (option) {
            case 1:
                clean_console();
                add_vertex_m();
                break;
            case 2:
                clean_console();
                update_vertex_m();
                break;
            case 3:
                clean_console();
                delete_vertex_m();
                break;
            case 4:
                clean_console();
                print_vertices();
                break;
            case 5:
                clean_console();
                get_adjacent_vertices();
                break;
            case 6:
                return;
            default:
                cout << "Por favor inserte un numero entre 1 y 5." << endl;
                break;
        }
    }
}

void edges_menu() {
    while (true) {
        clean_console();

        cout << "============================================================================== \n\n";
        cout << "                            Sistema de administracion de red                                 \n\n";
        cout << "==============================================================================\n\n";

        cout << "1 -> Añadir arco" << endl;
        cout << "2 -> Modificar arco" << endl;
        cout << "3 -> Eliminar arco" << endl;
        cout << "4 -> Listar arcos" << endl;
        cout << "5 -> Regresar" << endl;
        cout <<"\n\nIntroduzca su seleccion: ";

        int option;
        validateInput(option);
        switch (option) {
            case 1:
                clean_console();
                add_edge_m();
                break;
            case 2:
                clean_console();
                update_edge_m();
                break;
            case 3:
                clean_console();
                delete_edge_m();
                break;
            case 4:
                clean_console();
                print_edges();
                break;
            case 5:
                return;
            default:
                cout << "Por favor inserte un numero entre 1 y 5." << endl;
                break;
        }
    }
}

