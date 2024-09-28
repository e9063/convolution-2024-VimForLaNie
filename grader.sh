#!/bin/bash

# Array of input and output file names
input_files=("input_demo.txt" "input_easy1.txt" "input_easy2.txt" "input_medium1.txt" "input_medium2.txt")
output_files=("output_demo.txt" "output_easy1.txt" "output_easy2.txt" "output_medium1.txt" "output_medium2.txt")

# Compile the sequential and parallel programs
gcc -o conv_sequential conv_sequential.c
gcc -fopenmp -o conv_parallel conv_parallel.c

# Iterate over each input file
for i in "${!input_files[@]}"; do
    echo "Running tests for input: ${input_files[i]}"

    # Run the sequential program and measure its time
    echo "Running conv_sequential..."
    { time ./conv_sequential < "${input_files[i]}" > seq_output.txt; } 2> seq_time.txt
    seq_time=$(cat seq_time.txt | grep real)

    # Run the parallel program and measure its time
    echo "Running conv_parallel..."
    { time ./conv_parallel < "${input_files[i]}" > par_output.txt; } 2> par_time.txt
    par_time=$(cat par_time.txt | grep real)

    # Compare the outputs
    echo "Comparing outputs..."
    if diff seq_output.txt "${output_files[i]}" > /dev/null && diff par_output.txt "${output_files[i]}" > /dev/null; then
        echo "Test ${input_files[i]} passed for both programs!"
    else
        echo "Test ${input_files[i]} failed!"
    fi

    # Show the time comparison
    echo "Time taken by conv_sequential: $seq_time"
    echo "Time taken by conv_parallel: $par_time"
    echo "-----------------------------------"
done
