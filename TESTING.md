# HTTP Server Testing Guide

This guide tests all the features of HTTP server on the `main` branch.  
It tests correctness, performance, concurrency, caching, and metrics.

---

## Setup

### Build

```bash
rm -rf build && mkdir build && cd build
cmake ..
make
./server
```

### Run Server

```bash
./server
```

Default port: `8080`  
Optional: `PORT=9090 ./server`

---

## Functional Testing

### **1. Basic Request Handling**

Confirm that the server starts, accepts requests, and responds to valid HTTP requests.

```bash
curl http://localhost:8080/
curl http://localhost:8080/index.html
curl http://localhost:8080/missing.html
```

**Expected:**

- `/` or `/index.html` → serves your HTML file.
- Missing file → `404 Not Found`.
- Logs show connection acceptances and request details.

---

### **2. HTTP Method Validation**

Verify that unsupported methods are rejected.

```bash
curl -v -X POST http://localhost:8080/
```

**Expected:**

- HTTP status: `405 Method Not Allowed`
- Logs contain: `[WARN] Method Not Allowed`

---

### **3. Routing and API Endpoints**

Check all dynamic routes work correctly.

```bash
curl http://localhost:8080/health
curl http://localhost:8080/api/hello
curl http://localhost:8080/unknown
```

**Expected:**

- `/health` → `"OK"`
- `/api/hello` → `{"message":"Hello from API!"}`
- `/unknown` → `404 Not Found`

---

### **4. Logging and Configuration**

Confirm structured logging and environment variable support.

```bash
PORT=9090 ./server
curl http://localhost:9090/
```

**Expected:**

- Logs display color-coded levels (`[INFO]`, `[WARN]`, `[ERROR]`).
- Logs show timestamps and latency per request.

---

### **5. Static File Caching**

Ensure repeated file requests are served from cache.

```bash
curl http://localhost:8080/index.html
curl http://localhost:8080/index.html
```

**Expected:**

- First request → `[Cache miss]` in logs
- Second request → `[Cache hit]` in logs
- Significantly reduced response time on repeat

---

### **6. Concurrency and Stability**

Validate that multiple clients can connect concurrently.

```bash
ab -n 100 -c 10 http://127.0.0.1:8080/
```

or

```bash
wrk -t2 -c50 -d10s http://127.0.0.1:8080/
```

**Expected:**

- High request throughput (hundreds or thousands per second)
- No crashes, segmentation faults, or connection resets
- Logs interleave without corruption

---

### **7. Metrics Endpoint**

Confirm real-time statistics are available.

```bash
curl http://localhost:8080/metrics
```

**Expected:**

```json
{ "total_requests": 100, "cache_hits": 60, "avg_latency_ms": 2.3 }
```

- Values increase as more requests are sent.
- `cache_hits` count should match observed `[Cache hit]` logs.

---

### **8. Graceful Shutdown**

Ensure the server exits cleanly when interrupted.

While server is running:

- Press **Ctrl +C**

**Expected:**

- Logs: `[INFO] Shutting down server gracefully...`
- No socket errors on restart (`Address already in use` should not appear).

---

## Performance and Reliability Checks

| Test                 | Command                                      | Expected Result       |
| -------------------- | -------------------------------------------- | --------------------- |
| **Throughput test**  | `ab -n 500 -c 20 http://127.0.0.1:8080/`     | >1000 req/s           |
| **Cache validation** | Request same file twice                      | Second request faster |
| **Memory safety**    | `valgrind ./server`                          | 0 leaks               |
| **Stress**           | `wrk -t4 -c100 -d15s http://127.0.0.1:8080/` | Stable under load     |
| **Port cleanup**     | `lsof -i :8080` after exit                   | Port free             |

---

## Example Log Output

```
[INFO] Server listening on port 8080
[INFO] GET /index.html | 2050 bytes | 1.2 ms
[INFO] [Cache hit] public/index.html
[INFO] GET /metrics | 120 bytes | 0.5 ms
[INFO] Shutting down server gracefully...
```

---

## Complete Testing Criteria

- All routes return correct responses.
- Caching and metrics verified.
- Server handles concurrent requests safely.
- Graceful shutdown works without errors.
- No memory leaks or socket issues.
