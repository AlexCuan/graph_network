#include <iostream>
#include "general_utils.h"

using namespace std;

void main_menu();

void vertices_menu();

void edges_menu();


void main_menu() {

    while (true) {
        clean_console();
        cout << "============================================================================== \n" << endl;
        cout << "                            Titulo de prueba                                 \n" << endl;
        cout << "==============================================================================\n" << endl;

        cout << "1 -> Gestionar nodos" << endl;
        cout << "2 -> Gestionar arcos" << endl;
        cout << "3 -> Hallar ruta mas cercana" << endl;
        cout << "4 -> Crear db" << endl;
        cout << "5 -> Salir" << endl;


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

        cout << "============================================================================== \n" << endl;
        cout << "                            Titulo de prueba                                 \n" << endl;
        cout << "==============================================================================\n" << endl;

        cout << "1 -> Añadir vertice" << endl;
        cout << "2 -> Modificar vertice" << endl;
        cout << "3 -> Eliminar vertice" << endl;
        cout << "4 -> Listar vertices" << endl;
        cout << "5 -> " << endl;


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

        cout << "============================================================================== \n" << endl;
        cout << "                            Titulo de prueba                                 \n" << endl;
        cout << "==============================================================================\n" << endl;

        cout << "1 -> Añadir arco" << endl;
        cout << "2 -> Modificar arco" << endl;
        cout << "3 -> Eliminar arco" << endl;
        cout << "4 -> Listar arcos" << endl;
        cout << "5 -> " << endl;

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

