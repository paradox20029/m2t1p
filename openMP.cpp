#include <iostream>
#include <fstream>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Function to initialize a matrix with random values
void initialize_matrix(double* matrix, int n) {
    for (int i = 0; i < n*n; i++) {
        matrix[i] = static_cast<double>(rand()) / RAND_MAX * 10.0;
    }
}

// Function to multiply two matrices using OpenMP
void multiply_matrices_omp(double* a, double* b, double* c, int n, int num_threads) {
    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += a[i*n + k] * b[k*n + j];
            }
            c[i*n + j] = sum;
        }
    }
}

int main() {
    // Initialize variables
    int n = 1000; // matrix size
    int num_threads = 8; // number of threads to use in OpenMP
    double* a = new double[n*n];
    double* b = new double[n*n];
    double* c = new double[n*n];

    // Initialize matrices
    initialize_matrix(a, n);
    initialize_matrix(b, n);

    // Multiply matrices using OpenMP
    auto start_time = high_resolution_clock::now();
    multiply_matrices_omp(a, b, c, n, num_threads);
    auto end_time = high_resolution_clock::now();

    // Calculate execution time
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    // Write output to file
    ofstream outfile("output_omp.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outfile << c[i*n + j] << " ";
        }
        outfile << endl;
    }
    outfile.close();

    // Print execution time
    cout << "Execution time (OpenMP): " << duration.count() << " milliseconds" << endl;

    // Free memory
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}