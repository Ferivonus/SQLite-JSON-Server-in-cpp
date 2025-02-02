# SQLite JSON Server

This program is a simple SQLite-based server that allows users to send JSON requests to execute SQL queries. It also provides an API to list available tables in the database.

## Features

- Automatically creates a `database.db` file when the server starts.
- Accepts JSON-based HTTP requests to run SQL queries.
- Provides an API to list all tables in the database.
- Uses `argv` and `argc` to allow users to specify a port when starting the server.
- If the specified port is unavailable, the program searches for an open port automatically.

## Usage

### Running the Server

By default, the server runs on port `8080`. However, you can specify a different port when starting it:

```bash
./server 9090
```

If the specified port is unavailable, the server will find the next available port.

### API Endpoints

#### 1. Execute SQL Query

- **Endpoint:** `POST /query`
- **Request Format:** JSON
- **Example Request (using cURL):**

```bash
curl -X POST http://localhost:8080/query \
     -H "Content-Type: application/json" \
     -d '{"query": "SELECT * FROM users;"}'
```

- **Response Example:**

```json
{
    "status": "success",
    "data": [
        {"id": 1, "name": "Orkun"},
        {"id": 2, "name": "Bey"}
    ]
}
```

#### 2. List All Tables

- **Endpoint:** `GET /tables`
- **Example Request (using cURL):**

```bash
curl -X GET http://localhost:8080/tables
```

- **Response Example:**

```json
{
    "tables": ["users", "orders", "products"]
}
```

#### 3. List All Tables (Query Version)

- **Endpoint:** `POST /query`
- **Request Format:** JSON
- **Example Request (using cURL):**

```bash
curl -X POST http://localhost:8080/query \
     -H "Content-Type: application/json" \
     -d '{"query": "SELECT name FROM sqlite_master WHERE type='table';"}'
```

- **Response Example:**

```json
{
    "status": "success",
    "data": [
        {"name": "users"},
        {"name": "orders"},
        {"name": "products"}
    ]
}
```

## Notes

- This server simplifies SQLite usage by allowing users to send queries over HTTP.
- It automatically creates `database.db` if it does not exist.
- If the specified port is taken, it finds an open port to use instead.

If you have any questions or need further modifications, feel free to ask! 🚀
