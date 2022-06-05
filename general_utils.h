#include <iostream>
#include "Graph.h"
#include "db_utils.h"

using namespace std;

void update_vertex_m(){
    string actual_name;
    string new_name;
    cout<<"Ingrese el nombre actual del vertice: ";
    getline(cin, actual_name, '\n');

    cout<<"Ingrese el nombre nuevo del vertice: ";
    getline(cin, new_name, '\n');

    Vertex a = get_vertex_by_name(actual_name, *G);

//To-Do: Arreglar esto
//Esto es una chapuceria. Hubiese puesto if(a) pero no funciona
    if (name_node[a] == actual_name) {
        modify_vertex_name(a, new_name);
        update_vertex_db(actual_name, new_name);
    }
    else{
        cout<<"No existe el nodo"<<endl;
    }
}