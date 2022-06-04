#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <vector>

using namespace boost;
using std::vector;
using std::cout;
using std::cin;
using std::string;

// Define a new vertex property
struct node_name_t {
    typedef vertex_property_tag kind;
};

typedef property<node_name_t, std::string> NodeNameProperty;
typedef property<edge_weight_t, int> EdgeProperty;
typedef adjacency_list<vecS, vecS, undirectedS, NodeNameProperty, EdgeProperty> Graph;
typedef vector<int> vector_int;
typedef vector<float> vector_float;
typedef std::pair<int, int> Edge;
typedef vector<Edge> vector_edges;
typedef vector<string> vector_string;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge_desc;

Graph *G = new Graph;

typename property_map<Graph, edge_weight_t>::type edge_weight_map = get(edge_weight, *G);
typename property_map<Graph, node_name_t>::type name_node = get(node_name_t(), *G);
typedef property_map<Graph, vertex_index_t>::type IndexMap;
IndexMap vertex_i = get(vertex_index, *G);

typedef graph_traits<Graph>::vertex_iterator vertex_iter;
graph_traits<Graph>::edge_iterator ei, ei_end;
std::pair<vertex_iter, vertex_iter> vp;

void add_edges(Edge edge, Graph &referenced_graph) {
    add_edge(edge.first, edge.second, referenced_graph);
}

void add_node(Graph &referenced_graph) {
    add_vertex(referenced_graph);
}

void modify_vertex_name(Vertex vertex, string name_vertex_p) {
    name_node[vertex] = name_vertex_p;
}

Vertex get_vertex_by_index( int index_vertex_p, Graph &referenced_graph) {
    for (vp = vertices(referenced_graph); vp.first != vp.second; ++vp.first) {
        if (vertex_i[*vp.first] == index_vertex_p) {
            return *vp.first;
        }
    }
}
Vertex get_vertex_by_name(string vertex_name,Graph &referenced_graph) {
    for (vp = vertices(referenced_graph); vp.first != vp.second; ++vp.first) {
        if(name_node[*vp.first]==vertex_name){
            return *vp.first;
        }
    }
}

Edge_desc get_edge(int from, int to, Graph &referenced_graph) {
    for (tie(ei, ei_end) = edges(referenced_graph); ei != ei_end; ++ei) {
        if ((vertex_i[source(*ei, referenced_graph)] == from && vertex_i[target(*ei, referenced_graph)] == to)||
        (vertex_i[target(*ei, referenced_graph)] == from && vertex_i[source(*ei, referenced_graph)] == to)) {
            return *ei;
        }
        }
    }

void remove_node(Vertex vertex,Graph &referenced_graph) {
    remove_vertex(vertex, referenced_graph);
}

void remove_Edge(Vertex v1, Vertex v2, Graph &referenced_graph) {
    remove_edge(v1, v2, referenced_graph);
}

void modify_weight(Edge_desc arco, int weight_value) {
    edge_weight_map[arco] = weight_value;
}

void clear_node(Vertex vertex, Graph &referenced_graph) {
    clear_vertex(vertex, referenced_graph);
}
