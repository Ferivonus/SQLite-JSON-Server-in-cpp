#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <httplib.h>
#include "Database.h"

class Server {
public:
    explicit Server(int port);
    void start();

private:
    int port;
    Database db;

    // Setup API routes for handling requests
    void setupRoutes(httplib::Server& svr);

    // Helper functions for specific routes
    void handleQuery(const httplib::Request& req, httplib::Response& res);
    void handleGetTables(const httplib::Request& req, httplib::Response& res);
};

#endif
