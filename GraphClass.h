#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
//#include < boost/graph/properties.hpp>

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
  typedef adjacency_list<listS, vecS, undirectedS, NodeNameProperty, property<edge_weight_t, int> > Graph;
  typedef vector< int > vector_int;
  typedef vector< float > vector_float;
  typedef std::pair<int, int> Edge;
  typedef vector< Edge > vector_edges;
  typedef vector< string > vector_string;

class Grafo{
public:

// atributos
    Graph g;
    int num_edges;
    vector_edges vector_edge;
    vector_float weigths;
    vector_string name_vertex;
    vector_int index_vertex;
    property_map<Graph, node_name_t>::type name = get(node_name_t(), g);
    // METODOS
    Grafo(){}
    Grafo(vector_edges edges_input, vector_float weigths_input,
            vector_int index_vertex_input, vector_string name_node_input){

        add_edges(edges_input, weigths_input);
        add_name_vertex(index_vertex_input, name_node_input);

        name_vertex.insert(name_vertex.end(), name_node_input.begin(), name_node_input.end() ); // poner condicional para si esta vacio
        weigths.insert(weigths.end(), weigths_input.begin(), weigths_input.end());
        index_vertex.insert(index_vertex.end(), index_vertex_input.begin(), index_vertex_input.end());
        vector_edge.insert(vector_edge.end() , edges_input.begin(), edges_input.end());

    }

    void add_edges(vector_edges vector_edge_p, vector_float weigths_p){
        for(int i = 0; i < num_edges; i++){
            add_edge(vector_edge_p[i].first, vector_edge_p[i].second, weigths_p[i], g); // agrega un arco con su respectivo peso
     }

}// end of add_edges function

    void add_name_vertex(vector_int index_vertex_p, vector_string name_vertex_p){
       // property_map<Graph, node_name_t>::type name = get(node_name_t(), g);

        for(auto i: index_vertex_p){ // hay q ver eso
           name[i] = name_vertex_p[i]; // establece un nombre para cada vertice
           // si no funciona asi poner  boost::put(name, i, name_vertex[i])
        }

    }
};
