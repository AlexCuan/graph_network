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

    vertex_struct a = get_vertex_by_name(actual_name, *G);
    
    if (a.found) {
        modify_vertex_name(a.vertex, new_name);
        update_vertex_db(actual_name, new_name);
    }
    else{
        cout<<"No existe el nodo"<<endl;
    }
}