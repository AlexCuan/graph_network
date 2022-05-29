#include "iostream"
#include "SQL/sqlite3.h"
#include <string>

using namespace std;

void create_tables(){
    sqlite3* db;

    string sql = "CREATE TABLE IF NOT EXISTS VERTEX("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "NAME CHAR[4] UNIQUE NOT NULL);"
                 "CREATE TABLE IF NOT EXISTS EDGE("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "ORIGIN INTEGER FOREIGNKEY REFERENCES VERTEX(ID),"
                 "DESTINATION INTEGER FOREIGNKEY REFERENCES VERTEX(ID),"
                 "WEIGHT INTEGER);";
    int exit;
    exit = sqlite3_open("test.db", &db);
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if(exit != SQLITE_OK){
        cout << "Error: " << messageError << endl;
    }
    else{
        cout << "Table created successfully" << endl;
    }
    sqlite3_close(db);
}

void save_vertex_to_db(string vertex_name){
    sqlite3* db;
    string sql ="INSERT INTO VERTEX(NAME) VALUES('"+vertex_name+"');";
    int exit = sqlite3_open("test.db", &db);
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if(exit != SQLITE_OK){
        cerr << "Error" << messageError <<endl;
        sqlite3_free(messageError);
    }
    else{
        cout << "Vertex added successfully" << endl;
    }
    sqlite3_close(db);
}

void save_edge_to_db(int origin, int destination, int weight){
    sqlite3* db;
    string sql ="INSERT INTO EDGE(ORIGIN, DESTINATION, WEIGHT) VALUES("+to_string(origin)+","+to_string(destination)+","+to_string(weight)+");";
    int exit = sqlite3_open("test.db", &db);
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if(exit != SQLITE_OK){
        cerr << "Error" << messageError <<endl;
        sqlite3_free(messageError);
    }
    else{
        cout << "Edge added successfully" << endl;
    }
    sqlite3_close(db);
}


// Actually unused function

//void create_db() {
//    sqlite3 *db;
//    int exit = 0;
//    exit = sqlite3_open("test.db", &db);
//    if (exit == SQLITE_OK) {
//        cout << "Created db successfully\n";
//    } else {
//        cout << "Failed to create db\n";
//    }
//    sqlite3_close(db);
//    cout <<"Connection closed\n";
//}

