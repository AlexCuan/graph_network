#include <iostream>
#include "Graph.h"
#include <limits.h>
#include <vector>
//#include "db_utils.h"


using namespace std;

template<typename T>
T &validateInput(T &val) {
    while (true) {

        if (cin >> val && val > 0 ) {
            break;
        } else {
            cout << "Enter a valid integer value!: ";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return val;
}


void add_vertex_m() {
    string name;
    cout << "Ingrese el nombre del vertice: ";
    cin >> name;
    if (!get_vertex_by_name(name, *G).found) {
        add_node(name, *G);
        save_vertex_to_db(name);
    } else {
        cout << "Vertice ya existente" << endl;
    }
}

void add_edge_m() {
    string from, to;

    cout << "Ingrese el nombre del vertice de origen: ";
    cin >> from;

    if (!get_vertex_by_name(from, *G).found) {
        cout << "Vertice no existente, desea añadirlo? [Yes/No]" << endl;
        string answ;
        cin >> answ;
        if ((answ == "yes")&&(answ == "Yes")) {
            add_vertex_m();
        } else {
            cout << "Añadir vertice no se llevo a cabo. No se puede crear arco" << endl;
            return;
        }

    }
    cout << "Ingrese el nombre del vertice de destino: ";
    cin >> to;

    if (!get_vertex_by_name(to, *G).found) {
        cout << "Vertice no existente, desea añadirlo?" << endl;
        string answ;
        cin >> answ;
        if (answ == "yes") {
            add_vertex_m();
        } else {
            cout << "Añadir vertice no se llevo a cabo. No se puede crear arco" << endl;
            return;
        }
    }

    Edge temp = make_pair(vertex_i[get_vertex_by_name(from, *G).vertex], vertex_i[get_vertex_by_name(to, *G).vertex]);

    if (get_edge(from, to, *G).found) {
        cout << "Arista ya existente" << endl;
    } else {
        add_edge(temp.first, temp.second, *G);
        save_edge_to_db(from, to);
    }
}

void update_vertex_m() {
    string actual_name;
    string new_name;
    cout << "Ingrese el nombre actual del vertice: ";
    getline(cin, actual_name, '\n');

    cout << "Ingrese el nombre nuevo del vertice: ";
    getline(cin, new_name, '\n');

    vertex_struct a = get_vertex_by_name(actual_name, *G);

    if (a.found) {
        modify_vertex_name(a.vertex, new_name);
        update_vertex_db(actual_name, new_name);
    } else {
        cout << "No existe el nodo" << endl;
    }
}

void update_edge_m() {
    int weight;

    string temp_answ, from_old, to_old, from_new, to_new;
    cout << "Introduzca el arco viejo: ";
    cin >> from_old >> to_old;

//    Edge temp = make_pair(vertex_i[get_vertex_by_name(from_old, *G).vertex], vertex_i[get_vertex_by_name(to_old, *G).vertex]);
    edge_struct a = get_edge(from_old, to_old, *G);

    if (a.found) {
        cout << "Introduzca el arco nuevo: ";
        cin >> from_new >> to_new;

        cout << "Desea cambiar el peso?" << endl;
        cin >> temp_answ;

        if (temp_answ == "si") {
            cout << "Ingrese el peso: " << endl;
            cin >> weight;
        }

        Edge actual_edge = make_pair(vertex_i[get_vertex_by_name(from_old, *G).vertex], vertex_i[get_vertex_by_name(to_old, *G).vertex]);
        Edge new_edge = make_pair(vertex_i[get_vertex_by_name(from_new, *G).vertex], vertex_i[get_vertex_by_name(to_new, *G).vertex]);

        modify_weight(a.edge, weight);
        update_edge(actual_edge, new_edge);
        update_edge_db(from_old, to_old, from_new, to_new, weight);
    } else {
        cout << "No existe el arco" << endl;
    }
}

void delete_vertex_m() {
    string name;
    cout << "Ingrese el nombre del vertice: ";
    cin >> name;
    vertex_struct a = get_vertex_by_name(name, *G);
    if (a.found) {
        clear_node(a.vertex, *G);
        remove_vertex(a.vertex, *G);
        delete_vertex_from_db(name);
    } else {
        cout << "No existe el vertice" << endl;
    }
}

void delete_edge_m() {
    string from;
    string to;
    cout << "Introduzca el vertice de origen: ";
    cin >> from;
    cout << "Introduzca el vertice de destino: ";
    cin >> to;

//    Edge temp = make_pair(vertex_i[get_vertex_by_name(from, *G).vertex], vertex_i[get_vertex_by_name(to, *G).vertex]);
    edge_struct a = get_edge(from, to, *G);

    if (a.found) {
        remove_edge(a.edge, *G);
        delete_edge_from_db(from, to);
        clog << "Edge deleted successfully";
    } else {
        cout << "Edge doesn't exists" << endl;
    }

}


void get_shortest_path() {
    string from, to;
    cout << "Ingrese el nombre del vertice de origen: ";
    cin >> from;
    cout << "Ingrese el nombre del vertice de destino: ";
    cin >> to;
    vertex_struct a = get_vertex_by_name(from, *G);
    vertex_struct b = get_vertex_by_name(to, *G);
    if (a.found && b.found) {
        path_and_dist dist = shortest_path(a.vertex, b.vertex);

        for (std::size_t i = 0; i < dist.path.size(); i++) {
            cout << vertex_i(dist.path[i]) << " --> ";
        }
        cout << endl;
    } else {
        cout << "No existe uno de los vertices" << endl;
    }
}

void get_adjacent_vertices() {
    string name;
    cout << "Ingrese el nombre del vertice: ";
    cin >> name;
    vertex_struct a = get_vertex_by_name(name, *G);
    if (a.found) {
        cout << "Vertices adyacentes: " << endl;
        retrieve_adjacent_vertices(a.vertex, *G);
        cout << endl;
    } else {
        cout << "No existe el vertice" << endl;
    }
}

void print_vertices() {
    for (vp = vertices(*G); vp.first != vp.second; ++vp.first) {
        cout << "Vertex: " << vertex_i[*vp.first] << " Name: " << name_node[*vp.first] << endl;
    }
}

void print_edges() {
    int i = 0;
    for (tie(ei, ei_end) = edges(*G); ei != ei_end; ++ei) {
        cout << "Edge #" << i << " from: " << vertex_i[source(*ei, *G)] << " to: " << vertex_i[target(*ei, *G)] <<", weight: "<<
        edge_weight_map[*ei]<< endl;
        i++;
    }
}


