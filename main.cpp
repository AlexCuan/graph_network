#include<iostream>
#include "Graph.h"
 
using namespace boost;
using std::vector;
using std::cout;
using std::cin;
using std::string;


int main() {


  //vector_edges edges1;

  /*edges1 = {(0,1), (2,3),(4,5), (6,7), (8,9)};
  for(int i = 0; i <= 4; i++){
    add_edges(edges[i], *G);
  }*/
  Edge arco, arco1, arco2, arco3, arco4, arco5, arco6;

  cout << "helo \n";
  arco = std::make_pair(0,1);
  arco1 = std::make_pair(0,2);
  arco2 = std::make_pair(0,3);
  arco3 = std::make_pair(1,2);
  arco4 = std::make_pair(2,3);
  arco5 = std::make_pair(2,4);
  arco6 = std::make_pair(3,4);
  

  add_edges(arco, *G);
  add_edges(arco1, *G);
  add_edges(arco2, *G);
  add_edges(arco3, *G);
  add_edges(arco4, *G);
  add_edges(arco5, *G);
  add_edges(arco6, *G);

 modify_weight(get_edge(0, 1, *G), 2);
  modify_weight(get_edge(0, 2, *G), 3);
  modify_weight(get_edge(0, 3, *G), 2);
  modify_weight(get_edge(1, 2, *G), 2);
  modify_weight(get_edge(2, 3, *G), 1);
  modify_weight(get_edge(2, 4, *G), 2);
  modify_weight(get_edge(4, 3, *G), 2);

  path_and_dist dist;
  vector <Vertex> ruta;
  dist = shortest_path(get_vertex_by_index(0, *G), get_vertex_by_index(4, *G));
  ruta = dist.path;

  for(std::size_t i = 0; i < ruta.size(); i++){
     cout << vertex_i(ruta[i]) << " ";
  }
 /* cout << " aqui"<< vertex_i(ruta[0]);
  cout << " aqui"<< vertex_i(ruta[1]);
  cout << " aqui"<< vertex_i(ruta[2]) << ruta.size();*/

  cout <<" \n"<< dist.dist<< "\n";
 cout << num_vertices(*G);

    return EXIT_SUCCESS;
}
