#include <iostream>
#include "Graph.h"
#include <limits.h>
#include <vector>


using namespace std;

void add_vertex_m() {
    string name;
    cout << "> Ingrese el nombre del vertice: ";
    cin.ignore();
    getline(cin, name, '\n');

    if (!get_vertex_by_name(name, *G).found) {
        add_node(name, *G);
        save_vertex_to_db(name);
        pause_f();
        return;
    } else {
        cout << "XX - No se pudo añadir el vertice - XX" << endl;
        pause_f();
        return;
    }
}

void add_edge_m() {
    string from, to;

    cout << "> Ingrese el nombre del vertice de origen: ";
    cin.ignore();
    getline(cin, from, '\n');

    if (!get_vertex_by_name(from, *G).found) {
        cout << "> Vertice no existente, desea añadirlo? [yes/no]" << endl;
        string answ;
        getline(cin, answ, '\n');

        if (answ == "yes") {
            add_vertex_m();
            cout << "** Vertice añadido **" << endl;
        } else {
            cout << "XX - Añadir vertice no se llevo a cabo. No se puede crear arco - XX" << endl;
            pause_f();
            return;
        }

    }
    cout << "> Ingrese el nombre del vertice de destino: ";
    getline(cin, to, '\n');

    if (!get_vertex_by_name(to, *G).found) {
        cout << "> Vertice no existente, desea añadirlo?" << endl;

        string answ;
        getline(cin, answ, '\n');

        if (answ == "yes") {
            add_vertex_m();
            cout << "** Vertice añadido ** " << endl;
        } else {
            cout << "> XX - Añadir vertice no se llevo a cabo. No se puede crear arco - XX" << endl;
            return;
        }
    }

    Edge temp = make_pair(vertex_i[get_vertex_by_name(from, *G).vertex], vertex_i[get_vertex_by_name(to, *G).vertex]);

    if (get_edge(from, to, *G).found) {
        cout << "XX - Arista ya existente - XX" << endl;
        pause_f();
        return;
    } else {
        add_edge(temp.first, temp.second, *G);
        save_edge_to_db(from, to);
        pause_f();
        return;
    }
}

void update_vertex_m() {
    string actual_name;
    string new_name;
    cout << "> Ingrese el nombre actual del vertice: ";
    cin.ignore();
    getline(cin, actual_name, '\n');

    cout << "> Ingrese el nombre nuevo del vertice: ";
    getline(cin, new_name, '\n');

    vertex_struct a = get_vertex_by_name(actual_name, *G);

    if (a.found) {
        modify_vertex_name(a.vertex, new_name);
        update_vertex_db(actual_name, new_name);
        cout << "** Vertice actualizado **" << endl;
        pause_f();
        return;
    } else {
        cout << "XX - No existe el nodo - XX" << endl;
        pause_f();
        return;
    }
}

void update_edge_m() {
    int weight;

    string temp_answ, from_old, to_old, from_new, to_new;
    cout << "> Introduzca el arco actual: " << endl;
    cout << "> Vertice de origen: ";
    cin.ignore();
    getline(cin, from_old, '\n');
    cout << "> Vertice de destino: ";
    getline(cin, to_old, '\n');

    edge_struct a = get_edge(from_old, to_old, *G);

    if (a.found) {
        cout << "> Introduzca el arco nuevo: ";
        cout << "Vertice de origen: ";
        getline(cin, from_new, '\n');
        cout << "Vertice de destino: ";
        getline(cin, to_new, '\n');

        cout << "> Desea cambiar el peso[yes/no]?" << endl;
        getline(cin, temp_answ, '\n');

        if (temp_answ == "yes") {
            cout << "Ingrese el peso: " << endl;
            validateInput(weight);
        }

        Edge actual_edge = make_pair(vertex_i[get_vertex_by_name(from_old, *G).vertex],
                                     vertex_i[get_vertex_by_name(to_old, *G).vertex]);
        Edge new_edge = make_pair(vertex_i[get_vertex_by_name(from_new, *G).vertex],
                                  vertex_i[get_vertex_by_name(to_new, *G).vertex]);

        modify_weight(a.edge, weight);
        update_edge(actual_edge, new_edge, *G);
        update_edge_db(from_old, to_old, from_new, to_new, weight);
        cout << "** Arco actualizado **" << endl;
        pause_f();
    } else {
        cout << "XX - No existe el arco - XX" << endl;
        pause_f();
    }
}

void delete_vertex_m() {
    string name;
    cout << "> Ingrese el nombre del vertice: ";
    cin.ignore();
    getline(cin, name, '\n');

    vertex_struct a = get_vertex_by_name(name, *G);
    if (a.found) {
        clear_vertex(a.vertex, *G);
        remove_vertex(a.vertex, *G);
        delete_vertex_from_db(name);
        cout << "** Vertice eliminado **" << endl;
        pause_f();
    } else {
        cout << "XX - No existe el vertice - XX" << endl;
        pause_f();
    }
}

void delete_edge_m() {
    string from;
    string to;
    cout << "> Introduzca el vertice de origen: ";
    cin.ignore();
    getline(cin, from, '\n');
    cout << "> Introduzca el vertice de destino: ";
    getline(cin, to, '\n');

    edge_struct a = get_edge(from, to, *G);

    if (a.found) {
        remove_edge(a.edge, *G);
        delete_edge_from_db(from, to);
        cout << "** Arco borrado con exito **";
        pause_f();
    } else {
        cout << "XX - Arco no existe - XX" << endl;
        pause_f();
    }

}


void get_shortest_path() {
    string from, to;
    cout << "> Ingrese el nombre del vertice de origen: ";
    cin.ignore();
    getline(cin, from, '\n');
    cout << "> Ingrese el nombre del vertice de destino: ";
    getline(cin, to, '\n');
    vertex_struct a = get_vertex_by_name(from, *G);
    vertex_struct b = get_vertex_by_name(to, *G);
    if (a.found && b.found) {
        path_and_dist dist = shortest_path(a.vertex, b.vertex, *G);

        for (std::size_t i = 0; i < dist.path.size(); i++) {
            vertex_struct a = get_vertex_by_index(vertex_i(dist.path[i]), *G);
            cout << name_node(a.vertex) << " --> ";
        }
        cout << "end \n";
        pause_f();
    } else {
        cout << "XX - No existe uno de los vertices - XX" << endl;
        pause_f();
    }
}

void get_adjacent_vertices() {
    string name;
    cout << "> Ingrese el nombre del vertice: ";
    cin.ignore();
    getline(cin, name, '\n');
    vertex_struct a = get_vertex_by_name(name, *G);
    if (a.found) {
        cout << "Vertices adyacentes: " << endl;
        retrieve_adjacent_vertices(a.vertex, *G);
        cout << endl;
        pause_f();
    } else {
        cout << "XX - No existe el vertice - XX" << endl;
        pause_f();
    }
}

void print_vertices() {
    for (vp = vertices(*G); vp.first != vp.second; ++vp.first) {
        cout << "Vertice con posicion: " << vertex_i[*vp.first] << ", Nombre: " << name_node[*vp.first] << endl;
    }
    pause_f();
}

void print_edges() {
    int i = 0;
    for (tie(ei, ei_end) = edges(*G); ei != ei_end; ++ei) {
        cout << "Arco #" << i << " desde: " << vertex_i[source(*ei, *G)] << " hasta: " << vertex_i[target(*ei, *G)]
             << ", peso: " <<
             edge_weight_map[*ei] << endl;
        i++;
    }
    pause_f();
}








