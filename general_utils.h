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

void update_edge_m(){
    Edge actual_edge;
    Edge new_edge;
    int weight;
    string temp;
    cout<<"Ingrese el arco actual: "<<endl;
    cin>>actual_edge.first>>actual_edge.second;
    cout<<"Ingrese el arco nuevo: "<<endl;
    cin>>new_edge.first>>new_edge.second;
    cout<<"Desea cambiar el peso?"<<endl;
    cin >> temp;
    if(temp == "si"){
        cout<<"Ingrese el peso: "<<endl;
        cin>>weight;
    }
    edge_struct a = get_edge(actual_edge.first, actual_edge.second, *G);
    if (a.found) {
        update_edge_db(actual_edge.first, actual_edge.second,edge_weight_map[a.edge], new_edge.first, new_edge.second, weight);
        modify_weight(a.edge, weight);
        update_edge(actual_edge, new_edge);
    }
    else{
        cout<<"No existe el arco"<<endl;
    }
}