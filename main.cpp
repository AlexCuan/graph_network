#include<iostream>
#include "menu.h"
using namespace boost;
using std::vector;
using std::cout;
using std::cin;
using std::string;


int main() {
    create_tables();
    graph_builder();
    introduction();
    main_menu();
    return 0;
}