/*
 * Problem: Build a String from Two Matrices on GPU with Prefix Array
 *
 * In this problem, you will generate an output string by processing two matrices,
 * one containing integer counts and the other containing characters, using GPU
 * parallelism. The matrices share the same dimensions (m × n) and are flattened
 * into 1D arrays of length N = m * n. On the host, you compute for each element
 * how many times its corresponding character should appear—doubling the count
 * if the integer is prime or using it directly otherwise—and then build a prefix‐sum
 * array that records the starting index for each character’s block in the final string.
 * This prefix array and the character array are transferred to the device, where a
 * scatter kernel uses each thread to write its character into the correct segment
 * of a pre‐allocated output buffer. Once the GPU completes this parallel scatter,
 * the assembled buffer is copied back to the host, null‑terminated, and printed.
 * This design avoids write conflicts, balances work across threads, and scales
 * efficiently for large matrices (up to 1000×1000).
 *
 * Host‐Device Workflow:
 *   1. Flatten A[m][n] → A_flat[N], C[m][n] → C_flat[N].
 *   2. On host, compute lengths[k] = isPrime(A_flat[k]) ? 2*A_flat[k] : A_flat[k].
 *   3. Build prefix‑sum P of size N+1: P[0]=0; for k in [0..N-1], P[k+1]=P[k]+lengths[k].
 *   4. Copy C_flat and P to device memory.
 *   5. Launch scatterChars kernel to fill device output buffer.
 *   6. Copy result back to host, append '\0', and print the string.
 *
 * Function Signature:
 *   // Builds the string on the GPU and prints it on the host.
 *   void buildStringGPU(int m, int n, int A[m][n], char C[m][n]);
 *
 */


#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__device__ __host__ int isprime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}

__global__ void kernel(int *array, char *chararray, int *prefix, char *string, int m, int n) {
    int tid = threadIdx.x;
    if (tid >= m * n) return;

    int sid  = prefix[tid];             
    int temp = array[tid];              
    int nott = isprime(temp) ? 2*temp : temp; 

    for (int k = 0; k < nott; ++k) {
        string[sid + k] = chararray[tid];
    }
}

int main() {
    int m, n;
    printf("Enter m and n: ");
    scanf("%d %d", &m, &n);
    int size = m * n;

    printf("Enter int array: ");
    int array[size];
    for (int i = 0; i < size; ++i) {
        scanf("%d", &array[i]);
    }

    printf("Enter char array: ");
    char chararray[size];
    for (int i = 0; i < size; ++i) {
        scanf(" %c", &chararray[i]);
    }

    int prefix[size];
    int oldval = 0;
    for (int i = 0; i < size; ++i) {
        prefix[i] = oldval;
        int temp = array[i];
        oldval += isprime(temp) ? temp * 2 : temp;
    }

    int  *d_array, *d_prefix;
    char *d_chararray, *d_str;
    cudaMalloc(&d_array,     sizeof(int)  * size);
    cudaMalloc(&d_prefix,    sizeof(int)  * size);
    cudaMalloc(&d_chararray, sizeof(char) * size);
    cudaMalloc(&d_str,       sizeof(char) * oldval);

    cudaMemcpy(d_array,     array,      sizeof(int)  * size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_prefix,    prefix,     sizeof(int)  * size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_chararray, chararray,  sizeof(char) * size, cudaMemcpyHostToDevice);

    kernel<<<1, size>>>(d_array, d_chararray, d_prefix, d_str, m, n);
    cudaDeviceSynchronize();

    char string[size * size];  
    cudaMemcpy(string, d_str, sizeof(char) * oldval, cudaMemcpyDeviceToHost);
    string[oldval] = '\0';

    printf("%s\n", string);

    cudaFree(d_array);
    cudaFree(d_prefix);
    cudaFree(d_chararray);
    cudaFree(d_str);

    return 0;
}
