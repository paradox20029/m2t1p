#include <iostream>
#include <pthread.h>
#include <chrono>
#include <fstream>

#define MAX_THREADS 8

using namespace std;
using namespace chrono;

const int N = 1000;

double A[N][N], B[N][N], C[N][N];
int num_threads;

void* matrixMultiplication(void* arg) {
    long thread_id = (long)arg;

    int rows_per_thread = N / num_threads;
    int start_row = thread_id * rows_per_thread;
    int end_row = (thread_id + 1) * rows_per_thread;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    // Initialize matrices with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (double)rand() / (RAND_MAX / 10);
            B[i][j] = (double)rand() / (RAND_MAX / 10);
            C[i][j] = 0.0;
        }
    }

    // Create threads and calculate execution time
    for (int t = 1; t <= MAX_THREADS; t++) {
        num_threads = t;

        pthread_t threads[num_threads];
        auto start_time = high_resolution_clock::now();

        for (long i = 0; i < num_threads; i++) {
            pthread_create(&threads[i], NULL, matrixMultiplication, (void*)i);
        }

        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }

        auto end_time = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end_time - start_time);

        cout << "Execution time for " << num_threads << " threads: " << duration.count() << " microseconds" << endl;

        // Write output to file
        ofstream outfile;
        outfile.open("output_" + to_string(num_threads) + ".txt");

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                outfile << C[i][j] << " ";
            }
            outfile << endl;
        }

        outfile.close();
    }

    return 0;
}
