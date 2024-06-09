
# Performance Optimization Analysis
This Repo provides an analysis of the performance results obtained from different scenarios of code optimization and parallelization techniques.

## Performance without compiler optimization (-O0)
Average Time taken over 10 runs: 0.002858 seconds
Average GFLOPS over 10 runs: 0.6998
## Reasoning:
Without compiler optimization, the code is compiled with minimal optimizations. This leads to slower execution times and lower GFLOPS due to inefficient code generation.

## Performance with compiler optimization -O1
Average Time taken over 10 runs: 0.000958 seconds
Average GFLOPS over 10 runs: 2.0887
## Performance with compiler optimization -O2
Average Time taken over 10 runs: 0.00095 seconds
Average GFLOPS over 10 runs: 2.1079
## Performance with compiler optimization -O3
Average Time taken over 10 runs: 0.0008936 seconds
Average GFLOPS over 10 runs: 2.2396
## Reasoning:
Compiler optimizations at different levels (-O1, -O2, -O3) progressively improve code performance by enabling various optimization techniques such as loop optimizations, inline functions, and instruction scheduling. As optimization level increases, the compiler applies more aggressive optimizations resulting in faster execution and higher GFLOPS.

## Performance with compiler flags optimization
Average Time taken over 10 runs: 0.0008989 seconds
Average GFLOPS over 10 runs: 2.2328
Flags Used: gcc -O3 -funroll-loops -ftree-vectorize -march=native -fno-strict-aliasing

## Reasoning:
Additional compiler flags such as loop unrolling (-funroll-loops), vectorization (-ftree-vectorize), and architecture-specific optimizations (-march=native) further enhance code performance. These optimizations exploit parallelism and reduce loop overhead, leading to improved GFLOPS.

## Performance with manual code vectorization using intrinsics
Average Time taken over 10 runs: 0.0006055 seconds
Average GFLOPS over 10 runs: 3.3077
## Reasoning:
Manual code vectorization using SIMD intrinsics allows direct access to CPU-specific instructions (e.g., AVX, SSE) for parallel processing. This optimization technique significantly improves performance by leveraging SIMD capabilities, resulting in higher GFLOPS.

## Performance with only parallelization using OpenMP
Average Time taken over 10 runs: 0.0008265 seconds
Average GFLOPS over 10 runs: 2.4361
## Reasoning:
OpenMP parallelization distributes workload across multiple threads, utilizing multicore processors for concurrent execution. While it improves performance compared to non-parallelized code, it may not fully exploit SIMD capabilities for optimal performance.

## Performance with vectorization and OpenMP
Average Time taken over 10 runs: 0.0013383 seconds
Average GFLOPS over 10 runs: 2.2512
## Reasoning:
Combining manual code vectorization using intrinsics with OpenMP parallelization aims to leverage both SIMD optimizations and multicore parallelism. However, improper synchronization or overhead from parallelization can sometimes offset the gains from vectorization, resulting in slightly reduced GFLOPS compared to manual vectorization alone.

## Summary

| Scenario                                 | Average Time (seconds) | Average GFLOPS |
|------------------------------------------|------------------------|----------------|
| Without compiler optimization (-O0)       | 0.002858               | 0.6998         |
| Compiler optimization -O1                 | 0.000958               | 2.0887         |
| Compiler optimization -O2                 | 0.00095                | 2.1079         |
| Compiler optimization -O3                 | 0.0008936              | 2.2396         |
| Compiler flags optimization               | 0.0008989              | 2.2328         |
| Manual code vectorization using intrinsics| 0.0006055              | 3.3077         |
| Only parallelization using OpenMP         | 0.0008265              | 2.4361         |
| Vectorization and OpenMP                  | 0.0013383              | 2.2512         |


##  Contents

It contains the following files:

- **avg.py**: Python script to calculate the average score of runs.
- **lscpu.md**: File containing CPU information.
- **Makefile**: Makefile for building C programs.
- **mat-vec.c**: C file implementing matrix-vector multiplication.
- **mat-vec-omp.c**: C file implementing matrix-vector multiplication with OpenMP parallelization.
- **mat-vec-omp-vect.c**: C file implementing matrix-vector multiplication with OpenMP parallelization and manual vectorization using intrinsics.
- **mat-vec.py**: Python file for matrix-vector multiplication.
- **mat-vec-vect.c**: C file implementing matrix-vector multiplication with manual vectorization using SIMD intrinsics.
- **out4.out**: Output file.

## Makefile Targets

The Makefile includes the following targets for compiling different versions of the `mat-vec` program:

```makefile
mat-vec-vanilla: mat-vec.c
	gcc -O0 mat-vec.c -o mat-vec-vanilla

mat-vec-opt1: mat-vec.c
	gcc -O1 mat-vec.c -o mat-vec-opt1 

mat-vec-opt2: mat-vec.c
	gcc -O2 mat-vec.c -o mat-vec-opt2 

mat-vec-opt3: mat-vec.c
	gcc -O3 mat-vec.c -o mat-vec-opt3 

mat-vec-flg: mat-vec.c
	gcc -O3 -funroll-loops -ftree-vectorize -march=native -mavx2 -fno-strict-aliasing mat-vec.c -o mat-vec-flg

mat-vec-vect: mat-vec-vect.c
	gcc -O3 -march=native -ftree-vectorize -funroll-loops -ffast-math -mavx2 -mfma mat-vec-vect.c -o out4.out

mat-vec-omp: mat-vec-omp.c
	gcc -O3 -fopenmp  mat-vec-omp.c -o mat-vec-omp	

mat-vec-omp-vect: mat-vec-omp-vect.c
	gcc -O3 -march=native -ftree-vectorize -funroll-loops -fopenmp -ffast-math -mavx2 -mfma mat-vec-omp-vect.c -o mat-vec-omp-vect
```
