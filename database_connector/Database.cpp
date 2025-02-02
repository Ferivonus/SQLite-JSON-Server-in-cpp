#include "Database.h"

Database::Database() {

    if (sqlite3_open(dbFile.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Opened database successfully\n";
    }
}

Database::~Database() {

    if (db) {
        sqlite3_close(db);
    }
}

void Database::executeSQL(const std::string& query) {
    std::cout << "Executing SQL: " << query << std::endl;

    char* errMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMessage);

    if (result != SQLITE_OK) {
        std::cerr << "SQL Error: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
    else {
        std::cout << "Query executed successfully" << std::endl;
    }
}

std::string Database::getTablesAsJson() {
    nlohmann::json j;
    const char* query = "SELECT name FROM sqlite_master WHERE type='table';";
    sqlite3_stmt* stmt;

    int result = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Failed to fetch table names: " << sqlite3_errmsg(db) << std::endl;
        return "{}";
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* tableName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        j["tables"].push_back(tableName);
    }

    sqlite3_finalize(stmt);
    return j.dump(4);
}

std::string Database::executeQuery(const std::string& query) {
    sqlite3_stmt* stmt;
    std::string result;

    int res = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (res != SQLITE_OK) {
        result = "Error: " + std::string(sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return result;
    }

    if (sqlite3_column_count(stmt) > 0) {
        nlohmann::json jsonResult;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            nlohmann::json row;
            for (int col = 0; col < sqlite3_column_count(stmt); ++col) {
                row[sqlite3_column_name(stmt, col)] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, col));
            }
            jsonResult.push_back(row);
        }
        result = jsonResult.dump(4);
    }
    else {
        result = "Query executed successfully.";
    }

    sqlite3_finalize(stmt);
    return result;
}
