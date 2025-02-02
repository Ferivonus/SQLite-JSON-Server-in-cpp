#include "Server.h"

Server::Server(int port) : port(port) {}

void Server::setupRoutes(httplib::Server& svr) {
    svr.Post("/query", [this](const httplib::Request& req, httplib::Response& res) {
        handleQuery(req, res);
        });

    svr.Get("/tables", [this](const httplib::Request& req, httplib::Response& res) {
        handleGetTables(req, res);
        });
}

void Server::handleQuery(const httplib::Request& req, httplib::Response& res) {

    std::cout << "Received query request: " << req.body << std::endl;

    try {
        std::string queryResult = db.executeQuery(req.body);
        res.set_content(queryResult, "application/json");
    }
    catch (const std::exception& e) {
        std::cerr << "Error executing query: " << e.what() << std::endl;
        res.status = 400;
        res.set_content("{\"error\": \"Failed to execute query\"}", "application/json");
    }
}

void Server::handleGetTables(const httplib::Request& req, httplib::Response& res) {
    try {
        std::string tablesJson = db.getTablesAsJson();
        res.set_content(tablesJson, "application/json");
    }
    catch (const std::exception& e) {
        std::cerr << "Error fetching tables: " << e.what() << std::endl;
        res.status = 500;
        res.set_content("{\"error\": \"Failed to fetch tables\"}", "application/json");
    }
}

void Server::start() {
    httplib::Server svr;
    setupRoutes(svr);

    if (!svr.listen("0.0.0.0", port)) {
        std::cerr << "Error starting server on port " << port << std::endl;
    }
}
