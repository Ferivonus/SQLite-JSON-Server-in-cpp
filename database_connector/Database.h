#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <nlohmann/json.hpp>

class Database {
private:
    sqlite3* db;
    std::string dbFile = "database.db";

public:
    Database();
    ~Database();
    void executeSQL(const std::string& query);
    std::string getTablesAsJson();
    std::string executeQuery(const std::string& query);
};

#endif
