#include "iostream"
#include "SQL/sqlite3.h"
#include <string>
#include <vector>
#include "validators_and_tools.h"
using namespace std;

typedef struct edge_data {
    string origin;
    string destination;
    int weight;
} edge_data;

typedef struct vertex_data {
    string name;
} vertex_data;

typedef vector<edge_data> vector_edges;
typedef vector<vertex_data> vector_vertices;


void create_tables() {
    sqlite3 *db;

    string sql = "CREATE TABLE IF NOT EXISTS VERTEX("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "NAME CHAR[4] UNIQUE NOT NULL);"
                 "CREATE TABLE IF NOT EXISTS EDGE("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "ORIGIN STRING FOREIGNKEY REFERENCES VERTEX(NAME) ON DELETE CASCADE DEFAULT NULL,"
                 "DESTINATION STRING FOREIGNKEY REFERENCES VERTEX(NAME) ON DELETE CASCADE DEFAULT NULL,"
                 "WEIGHT INTEGER DEFAULT NULL);";
    int exit;
    exit = sqlite3_open("data.db", &db);
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cout << "Error: " << messageError << endl;
        sqlite3_free(messageError);
    }
    sqlite3_close(db);
}

void save_vertex_to_db(string vertex_name) {
    sqlite3 *db;
    string sql = "INSERT INTO VERTEX(NAME) VALUES('" + vertex_name + "');";
    int exit = sqlite3_open("data.db", &db);
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error" << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Vertex added successfully to db" << endl;
    }
    sqlite3_close(db);
}

void save_edge_to_db(string origin, string destination, int weight = 0) {
    sqlite3 *db;
    string sql = "PRAGMA foreign_keys = ON;"
                 "INSERT INTO EDGE(ORIGIN, DESTINATION, WEIGHT) VALUES('" + origin + "','" + destination + "','" +
                 to_string(weight) + "');";
    int exit = sqlite3_open("data.db", &db);
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error" << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Edge added successfully to db" << endl;
    }
    sqlite3_close(db);
}


vector_vertices retrieve_vertex_from_db() {
    sqlite3 *db;
    int exit = sqlite3_open("data.db", &db);
    sqlite3_stmt *stmt;;

    sqlite3_prepare_v2(db, "SELECT * FROM VERTEX;", -1, &stmt, 0);
    vertex_data e;
    vector_vertices vector_vertices;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        e.name = (char *) sqlite3_column_text(stmt, 1);
        vector_vertices.push_back(e);
    }
    sqlite3_finalize(stmt);
    return vector_vertices;
}

vector_edges retrieve_edge_from_db() {
    sqlite3 *db;
    int exit = sqlite3_open("data.db", &db);
    sqlite3_stmt *stmt;;

    sqlite3_prepare_v2(db, "SELECT * FROM EDGE;", -1, &stmt, 0);
    edge_data e;
    vector_edges edges_vector;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        e.origin = (char *) sqlite3_column_text(stmt, 1);
        e.destination = (char *) sqlite3_column_text(stmt, 2);
        e.weight = sqlite3_column_int(stmt, 3);
        edges_vector.push_back(e);
    }
    sqlite3_finalize(stmt);
    return edges_vector;
}

void update_vertex_db(string vertex_name, string new_name) {
    sqlite3 *db;
    string sql = "UPDATE VERTEX SET NAME='" + new_name + "' WHERE NAME='" + vertex_name + "';";
    int exit = sqlite3_open("data.db", &db);
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error" << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Vertex updated successfully in db" << endl;
    }
    sqlite3_close(db);
}

void update_edge_db(string origin, string destination, string new_origin, string new_destination, int new_weight) {
    sqlite3 *db;
    string sql = "PRAGMA foreign_keys = ON;"
                 "UPDATE EDGE SET ORIGIN='" + new_origin + "', DESTINATION='" + new_destination +
                 "', WEIGHT='" + to_string(new_weight) + "' WHERE ORIGIN='" + origin + "' AND DESTINATION='" +
                 destination + "';";
    int exit = sqlite3_open("data.db", &db);
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error" << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Edge updated in db successfully" << endl;
    }
    sqlite3_close(db);
}

void delete_vertex_from_db(string vertex_name) {
    sqlite3 *db;
    string sql = "PRAGMA foreign_keys = ON;"
            "DELETE FROM VERTEX WHERE NAME='" + vertex_name + "';";
    int exit = sqlite3_open("data.db", &db);
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error" << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Vertex deleted successfully from db" << endl;
    }
    sqlite3_close(db);
}

void delete_edge_from_db(string origin, string destination) {
    sqlite3 *db;
    string sql = "PRAGMA foreign_keys = ON;"
            "DELETE FROM EDGE WHERE ORIGIN='" + origin + "' AND DESTINATION='" + destination + "';";
    int exit = sqlite3_open("data.db", &db);
    char *messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error" << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Edge deleted successfully from db" << endl;
    }
    sqlite3_close(db);
}


