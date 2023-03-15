//implementation of a simple matrix multiplication program in C++ using nested loops:
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

int main() {
    int n = 1000;
    double **A = new double*[n];
    double **B = new double*[n];
    double **C = new double*[n];

    // Initialize matrices A and B with random values
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    for(int i = 0; i < n; ++i) {
        A[i] = new double[n];
        B[i] = new double[n];
        C[i] = new double[n];

        for(int j = 0; j < n; ++j) {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
            C[i][j] = 0.0;
        }
    }

    // Matrix multiplication
    auto start_time = chrono::high_resolution_clock::now();

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout << "Time taken: " << duration << " microseconds." << endl;

    // Write output to file
    ofstream outfile("output.txt");

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            outfile << C[i][j] << " ";
        }
        outfile << endl;
    }

    outfile.close();

    // Free memory
    for(int i = 0; i < n; ++i) {
        delete [] A[i];
        delete [] B[i];
        delete [] C[i];
    }

    delete [] A;
    delete [] B;
    delete [] C;

    return 0;
}