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
                 "ORIGIN INTEGER FOREIGNKEY REFERENCES VERTEX(ID) DEFAULT NULL,"
                 "DESTINATION INTEGER FOREIGNKEY REFERENCES VERTEX(ID) DEFAULT NULL,"
                 "WEIGHT INTEGER DEFAULT NULL);";
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
    string sql ="PRAGMA foreign_keys = ON;"
                "INSERT INTO EDGE(ORIGIN, DESTINATION, WEIGHT) VALUES("+to_string(origin)+","+to_string(destination)+","+to_string(weight)+");";
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

void delete_vertex_from_db(string vertex_name){
    sqlite3* db;
    string sql ="DELETE FROM VERTEX WHERE NAME='"+vertex_name+"';";
    int exit = sqlite3_open("test.db", &db);
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if(exit != SQLITE_OK){
        cerr << "Error" << messageError <<endl;
        sqlite3_free(messageError);
    }
    else{
        cout << "Vertex deleted successfully" << endl;
    }
    sqlite3_close(db);
}

void delete_edge_from_db(int origin, int destination){
    sqlite3* db;
    string sql ="DELETE FROM EDGE WHERE ORIGIN="+to_string(origin)+" AND DESTINATION="+to_string(destination)+";";
    int exit = sqlite3_open("test.db", &db);
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if(exit != SQLITE_OK){
        cerr << "Error" << messageError <<endl;
        sqlite3_free(messageError);
    }
    else{
        cout << "Edge deleted successfully" << endl;
    }
    sqlite3_close(db);
}

//argc: holds the number of results
//azColName: holds each column returned in array
//argv holds each value in array
//TO-DO Pass "&" values for arrays containing column and value
static int callback (void* NotUsed, int argc, char** argv, char** azColName){
    int i;
    for(i=0; i<argc; i++){
        cout << azColName[i] << " = " << argv[i] << endl;
    }
    cout << endl;
    return 0;
}

void retrieve_vertex_from_db(){
    sqlite3* db;
    string sql = "SELECT * FROM VERTEX;";
    int exit = sqlite3_open("test.db", &db);
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), callback, 0, &messageError);
    if(exit != SQLITE_OK){
        cerr << "Error" << messageError <<endl;
        sqlite3_free(messageError);
    }
    else{
        cout << "Data selected successfully" << endl;
    }
}

void retrieve_edge_from_db(){
    sqlite3* db;
    string sql = "SELECT * FROM EDGE;";
    int exit = sqlite3_open("test.db", &db);
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), callback, 0, &messageError);
    if(exit != SQLITE_OK){
        cerr << "Error" << messageError <<endl;
        sqlite3_free(messageError);
    }
    else{
        cout << "Data selected successfully" << endl;
    }
}

void update_vertex(string vertex_name, string new_name){
    sqlite3* db;
    string sql = "UPDATE VERTEX SET NAME='"+new_name+"' WHERE NAME='"+vertex_name+"';";
    int exit = sqlite3_open("test.db", &db);
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if(exit != SQLITE_OK){
        cerr << "Error" << messageError <<endl;
        sqlite3_free(messageError);
    }
    else{
        cout << "Vertex updated successfully" << endl;
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

