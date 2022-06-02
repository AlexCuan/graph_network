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
typedef adjacency_list<vecS, vecS, undirectedS, NodeNameProperty , EdgeProperty > Graph;
typedef vector<int> vector_int;
typedef vector<float> vector_float;
typedef std::pair<int, int> Edge;
typedef vector<Edge> vector_edges;
typedef vector<string> vector_string;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor edge;
Graph* G = new Graph;

property_map<Graph, edge_weight_t>::type edge_weight_map = get(edge_weight, *G);


//  property_map<Graph, node_name_t>::type name_node = get(node_name_t(), G);
//Edge a = std::make_pair(2,3);
//Edge b = std::make_pair(3,4);


void add_edges(Edge edge, Graph &referenced_graph) {
    add_edge(edge.first, edge.second, referenced_graph);
}


//  void add_edges(Edge arco, float& weigth){
//       add_edge(arco.first, arco.second, weigth, &G); // agrega un arco con su respectivo peso
//     }


<<<<<<< HEAD
 /* void add_weight(Edge Ed, float weight_value){
    boost :: put(boost::edge_weight_t(), G, Ed, weight_value); //agreg un peso dd
  }*/
=======
//
//    void add_name_vertex(int index_vertex_p, string name_vertex_p){
//        boost::put(name_node, index_vertex_p, name_vertex_p);
//        }

void add_node(Graph &referenced_graph) {
    add_vertex(referenced_graph);
}

//void remove_node(Graph &G) {
//    clear_vertex(v1, G);
//    remove_vertex(v1, G);
//}
//
//void remove_Edge(Vertex v1, Vertex v2) {
//    remove_edge(v1, v2, G);
//}
//
//void add_weight(Edge edge, int weight_value) {
//    boost::put(boost::edge_weight_t(), G, edge, weight_value); //agreg un peso dd
//}
>>>>>>> 2de2af69fece162d5bbf533c43a57b849b7a71b5
