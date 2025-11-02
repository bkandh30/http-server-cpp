# C++ HTTP Server

A lightweight **HTTP/1.1 web server** built from scratch in **modern C++17**, without relying on external web frameworks.

---

## Overview

This project implements a minimal yet performant HTTP server that can:

- Accept TCP connections and handle multiple clients concurrently.
- Parse raw HTTP requests and generate valid HTTP/1.1 responses.
- Serve static files (HTML, CSS, JSON, etc.) from disk.
- Support custom routing for API endpoints.
- Implement in-memory caching for faster file delivery.
- Collect and expose runtime metrics (`/metrics` endpoint).
- Gracefully shut down and handle concurrent requests safely.
- Benchmark throughput and latency using tools like ApacheBench (`ab`) and `wrk`.

---

## Tech Stack

| Component              | Technology                        |
| ---------------------- | --------------------------------- |
| Language               | C++17                             |
| Build System           | CMake                             |
| Networking             | POSIX Sockets (`sys/socket.h`)    |
| Concurrency            | `std::thread`, Thread Pool        |
| Caching                | In-memory LRU Cache               |
| Metrics                | Custom JSON endpoint (`/metrics`) |
| Logging                | Custom log levels with timestamps |
| Testing & Benchmarking | ApacheBench (`ab`), `wrk`         |
| Packaging              | Docker (for deployment)           |

---

## Build & Run

### Build

```bash
mkdir build && cd build
cmake ..
make
```

### Run

```bash
./server
```

Default: `http://localhost:8080`  
Custom port:

```bash
PORT=9090 ./server
```

---

## Testing Reference

For detailed testing guide, see [TESTING.md](./TESTING.md).  
It includes verification steps for request handling, routing, caching, metrics, concurrency, and graceful shutdown.

---

## Roadmap

| Phase | Description                       | Progress |
| ----- | --------------------------------- | -------- |
| 0     | Setup and documentation           | [ X ]    |
| 1     | Basic TCP socket server           | [ X ]    |
| 2     | HTTP request parsing and response | [ X ]    |
| 3     | Static file serving               | [ X ]    |
| 4     | Multithreaded connection handling | [ X ]    |
| 5     | Routing system                    | [ X ]    |
| 6     | Configuration and logging         | [ X ]    |
| 7     | Thread pool and graceful shutdown | [ X ]    |
| 8     | Caching system                    | [ X ]    |
| 8     | Metrics and benchmarking          | [ X ]    |
| 9     | Final polish                      | [ X ]    |

---
