#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h> // Include AVX2 Intrinsics header

#define MATRIX_SIZE 1000
#define VECTOR_SIZE 4 // AVX2 can process 4 double values (256 bits)

double matrix[MATRIX_SIZE][MATRIX_SIZE];
double vector[MATRIX_SIZE];
double result[MATRIX_SIZE];

void initialize() {
    // Initialize matrix and vector with random values
    srand(time(NULL));
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX;
        }
        vector[i] = (double)rand() / RAND_MAX;
    }
}

void matrix_vector_multiply_avx2() {
    // Perform matrix-vector multiplication with AVX2 intrinsics
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0.0;
        __m256d sum = _mm256_setzero_pd(); // Initialize sum vector with zeros

        for (int j = 0; j < MATRIX_SIZE; j += VECTOR_SIZE) {
            __m256d mat_row = _mm256_loadu_pd(&matrix[i][j]); // Load 4 elements from matrix row
            __m256d vec_elements = _mm256_loadu_pd(&vector[j]); // Load 4 elements from vector

            sum = _mm256_fmadd_pd(mat_row, vec_elements, sum); // Fused multiply-add operation
        }

        // Horizontal sum of elements in the sum vector
        sum = _mm256_hadd_pd(sum, sum);
        sum = _mm256_hadd_pd(sum, sum);

        // Store the result in the result array
        result[i] = ((double*)&sum)[0] + ((double*)&sum)[2];
    }
}

int main() {
    initialize();

    clock_t start_time = clock();
    matrix_vector_multiply_avx2();
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print time taken
    printf("Time taken: %f seconds\n", elapsed_time);

    // Calculate total floating point operations
    long long flops = 2 * MATRIX_SIZE * MATRIX_SIZE;

    // Calculate GFLOPS
    double gflops = flops / (elapsed_time * 1e9);
    printf("GFLOPS: %f\n", gflops);

    return 0;
}
