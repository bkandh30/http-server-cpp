# C++ HTTP Server

A lightweight **HTTP/1.1 web server** built from scratch in **modern C++17**, without relying on external web frameworks.

---

## Overview

This project implements a minimal yet performant HTTP server that can:

- Accept TCP connections and handle multiple clients concurrently.
- Parse raw HTTP requests and generate valid HTTP/1.1 responses.
- Serve static files (HTML, CSS, JSON, etc.) from disk.
- Support custom routing for API endpoints.
- Benchmark throughput and latency using tools like ApacheBench (`ab`).

---

## Tech Stack

| Component              | Technology                     |
| ---------------------- | ------------------------------ |
| Language               | C++17                          |
| Build System           | CMake                          |
| Networking             | POSIX Sockets (`sys/socket.h`) |
| Concurrency            | `std::thread`, thread pool     |
| Testing & Benchmarking | ApacheBench (`ab`), `wrk`      |
| Packaging              | Docker (for deployment)        |

---

## Build & Run (to be implemented)

Once implemented:

```bash
mkdir build && cd build
cmake ..
make
./server
```

The server will start listening on `http://localhost:8080`.

---

## Roadmap

| Phase | Description                           | Progress |
| ----- | ------------------------------------- | -------- |
| 0     | Setup and documentation               | [ X ]    |
| 1     | Basic TCP socket server               | [ ]      |
| 2     | HTTP request parsing and response     | [ ]      |
| 3     | Static file serving                   | [ ]      |
| 4     | Multithreaded connection handling     | [ ]      |
| 5     | Routing system                        | [ ]      |
| 6     | Configuration and logging             | [ ]      |
| 7     | Benchmarking and optimization         | [ ]      |
| 8     | Final polish (Docker, README visuals) | [ ]      |

---
