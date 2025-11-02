#!/bin/bash
URL=${1:-http://localhost:8080/}
OUTPUT="benchmarks/results.txt"

echo "Running Apache Bench on $URL..."
ab -n 500 -c 20 $URL >> $OUTPUT
echo "----" >> $OUTPUT
ab -n 500 -c 20 "${URL}index.html" >> $OUTPUT
echo "Results saved to $OUTPUT"
