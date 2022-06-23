#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <vector>
#include "db_utils.h"

using namespace boost;
using std::vector;
using std::cout;
using std::cin;
using std::string;

// Define a new vertex property
struct node_name_t {
    typedef vertex_property_tag kind;
};

typedef property<node_name_t, string> NodeNameProperty;
typedef property<edge_weight_t, int> EdgeProperty;
typedef adjacency_list<vecS, vecS, undirectedS, NodeNameProperty, EdgeProperty> Graph;
typedef vector<int> vector_int;
typedef vector<float> vector_float;
typedef std::pair<int, int> Edge;
typedef vector<string> vector_string;
typedef graph_traits<Graph>::vertex_descriptor Vertex_desc;
typedef graph_traits<Graph>::edge_descriptor Edge_desc;

Graph *G = new Graph;

typename property_map<Graph, edge_weight_t>::type edge_weight_map = get(edge_weight, *G);
typename property_map<Graph, node_name_t>::type name_node = get(node_name_t(), *G);
typename property_map<Graph, vertex_index_t>::type vertex_i = get(vertex_index, *G);
//typedef property_map<Graph, vertex_index_t>::type vertex_i = get(vertex_index, *G);
//IndexMap vertex_i = get(vertex_index, *G);

typedef graph_traits<Graph>::vertex_iterator vertex_iter;
graph_traits<Graph>::edge_iterator ei, ei_end;
std::pair<vertex_iter, vertex_iter> vp;
boost::graph_traits<Graph>::adjacency_iterator ai, ai_end;
graph_traits<Graph>::vertex_iterator vi, vend;

typedef struct path_dist {
    int dist;
    vector<Vertex_desc> path;

} path_and_dist;

typedef struct edge_type {
    bool found = false;
    Edge_desc edge;

} edge_struct;

typedef struct vertex_type {
    bool found = false;
    Vertex_desc vertex;

} vertex_struct;


void modify_vertex_name(Vertex_desc vertex, string name_vertex_p) {
    name_node[vertex] = name_vertex_p;
}

vertex_struct get_vertex_by_index(int index_vertex_p, Graph &referenced_graph) {
    vertex_struct vertex_found;
    for (vp = vertices(referenced_graph); vp.first != vp.second; ++vp.first) {
        if (vertex_i[*vp.first] == index_vertex_p) {
            //return *vp.first;
            vertex_found.found = true;
            vertex_found.vertex = *vp.first;

        }
    }
    return vertex_found;
}

vertex_struct get_vertex_by_name(string vertex_name, Graph &referenced_graph) {
    vertex_struct vertex;
    for (vp = vertices(referenced_graph); vp.first != vp.second; ++vp.first) {
        if (name_node[*vp.first] == vertex_name) {
            //return *vp.first;
            vertex.found = true;
            vertex.vertex = *vp.first;
            return vertex;
        }
    }
    return vertex;
}

edge_struct get_edge(string from, string to, Graph &referenced_graph) {
    edge_struct edge;
    Edge temp = make_pair(vertex_i[get_vertex_by_name(from, *G).vertex],
                          vertex_i[get_vertex_by_name(to, *G).vertex]);


    for (tie(ei, ei_end) = edges(referenced_graph); ei != ei_end; ++ei) {
        if ((vertex_i[source(*ei, referenced_graph)] == temp.first && vertex_i[target(*ei, referenced_graph)] == temp.second) ||
            (vertex_i[target(*ei, referenced_graph)] == temp.first && vertex_i[source(*ei, referenced_graph)] == temp.second)) {

            edge.found = true;
            edge.edge = *ei;
            return edge;
        }
    }
    return edge;
}

void add_node(string name, Graph &referenced_graph) {
    Vertex_desc temp = add_vertex(referenced_graph);
    modify_vertex_name(temp, name);
}

//void remove_node(Vertex_desc vertex, Graph &referenced_graph) {
//    remove_vertex(vertex, referenced_graph);
//}

void remove_Edge(Vertex_desc v1, Vertex_desc v2, Graph &referenced_graph) {
    remove_edge(v1, v2, referenced_graph);
}

void update_edge(Edge actual_edge, Edge new_edge) {
    remove_edge(vertex_i[actual_edge.first], vertex_i[actual_edge.second], *G);
    add_edge(new_edge.first, new_edge.second, *G);
}

void modify_weight(Edge_desc arco, int weight_value) {
    edge_weight_map[arco] = weight_value;
}

void clear_node(Vertex_desc vertex, Graph &referenced_graph) {
    clear_vertex(vertex, referenced_graph);
}

void retrieve_adjacent_vertices(Vertex_desc v, Graph &referenced_graph) {
    cout << name_node[v];
    //TO-DO: Fix at the end of the function retrieves a % when the vertex is not found
    for (tie(ai, ai_end) = adjacent_vertices(v, referenced_graph); ai != ai_end; ++ai) {
        cout << "->" << vertex_i[*ai];
    }
}

vector<Vertex_desc> get_Path(
        const Graph &graph,
        const vector<Vertex_desc> &pMap,
        const Vertex_desc &source,
        const Vertex_desc &destination
) {
    vector<Vertex_desc> path;
    Vertex_desc current = destination;
    while (current != source) {
        path.push_back(current);
        current = pMap[current];
    }
    path.push_back(source);
    return path;
}


path_and_dist shortest_path(Vertex_desc src,
                            Vertex_desc dest) { //determina el camino mas corto desde un vertice hacia todos los demas del grafo
    vector<Vertex_desc> p(num_vertices(*G));
    vector<int> d(num_vertices(*G));
    Vertex_desc s = vertex(src, *G);
    dijkstra_shortest_paths(*G, src,
                            predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index,
                                                                                             *G))).distance_map(
                                    boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, *G))));

    path_and_dist path_distance = {.dist = d[dest],
            .path = get_Path(*G, p, src, dest)};

    return path_distance;
}

void graph_builder(){
    vector_vertices v = retrieve_vertex_from_db();
    for(int i = 0; i < v.size(); i++){
        add_node(v[i].name, *G);
    }
    vector_edges e = retrieve_edge_from_db();
    for(int i = 0; i < e.size(); i++){
        Edge temp = make_pair(vertex_i[get_vertex_by_name(e[i].origin, *G).vertex], vertex_i[get_vertex_by_name(e[i].destination, *G).vertex]);
        pair<Edge_desc, bool>a = add_edge(temp.first, temp.second, *G);
        modify_weight(a.first,e[i].weight);
    }
}

