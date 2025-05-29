#!/bin/bash

# TLB Benchmark Script
# Runs the tlb program with varying page counts and collects results

# Configuration
PROGRAM="./tlb"
TRIALS=30
OUTPUT_FILE="tlb_results.csv"
MIN_PAGES=1
MAX_PAGES=64

# Create CSV header
echo "pages,output" > "$OUTPUT_FILE"

echo "Running TLB benchmark..."
echo "Program: $PROGRAM"
echo "Trials per run: $TRIALS"
echo "Page range: $MIN_PAGES to $MAX_PAGES"
echo "Output file: $OUTPUT_FILE"
echo

# Run the program for each page count
for pages in $(seq $MIN_PAGES $MAX_PAGES); do
    echo -n "Testing $pages pages... "

    # Run the program and capture stdout
    output=$($PROGRAM $pages $TRIALS 2>/dev/null)
 
    # Check if the program ran successfully
    if [ $? -eq 0 ]; then
        # Add the result to CSV (escape any commas in output)
        echo "$pages,\"$output\"" >> "$OUTPUT_FILE"
        echo "done"
    else
        echo "failed (exit code $?)"
        echo "$pages,ERROR" >> "$OUTPUT_FILE"
    fi
    sleep 0.1
done

echo
echo "Benchmark complete! Results saved to $OUTPUT_FILE"
echo "Total runs: $((MAX_PAGES - MIN_PAGES + 1))"
