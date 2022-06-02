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


struct node_name_t { // crea una nueva propiedad para el vertice
    typedef vertex_property_tag kind;
  };

  typedef property<node_name_t, std::string> NodeNameProperty;
  typedef adjacency_list<listS, vecS, undirectedS, NodeNameProperty, property<edge_weight_t, float> > Graph;
  typedef vector< int > vector_int;
  typedef vector< float > vector_float;
  typedef std::pair<int, int> Edge;
  typedef vector< Edge > vector_edges;
  typedef vector< string > vector_string;
  typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
  typedef boost::graph_traits<Graph>::edge_descriptor edge;

  Graph G;
  property_map<Graph, node_name_t>::type name_node = get(node_name_t(), G);
 // property_map<Graph, edge_weight_t>::type weight_of_edge = get(edge_weigth_t(), G);

  void add_edges(Edge arco, float weigth = 0){
       add_edge(arco.first, arco.second, weigth, G); // agrega un arco con su respectivo peso
     }



    void add_name_vertex(int index_vertex_p, string name_vertex_p){
        boost::put(name_node, index_vertex_p, name_vertex_p);
        }

    Vertex add_node(){
       Vertex v1 = boost::add_vertex(G);
       return v1;

       
    }

   void remove_node(Vertex v1){
      clear_vertex(v1, G);
      remove_vertex(v1, G);
    }

  void remove_Edge(Vertex v1, Vertex v2){
    remove_edge(v1, v2, G);
  }

 /* void add_weight(Edge Ed, float weight_value){
    boost :: put(boost::edge_weight_t(), G, Ed, weight_value); //agreg un peso dd
  }*/
