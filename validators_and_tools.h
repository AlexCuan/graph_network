#include <iostream>
#include <ncurses.h>
#include <string>

using namespace std;

void pause_f() {
    cout << "Presione enter para continuar ...";
    cin.clear();
    getchar();
}
void clean_console() {
    system("clear");
}
template<typename T>
T &validateInput(T &val) {
    while (true) {

        if (cin >> val && val > 0) {
            break;
        } else {
            cout << "Enter a valid integer value!: ";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return val;
}