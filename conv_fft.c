#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

typedef struct {
    double re; // Real part
    double im; // Imaginary part
} complex;

// Function to perform the FFT
void fft(complex *x, int N, int invert) {
    // Bit-reversal permutation
    int j = 0;
    for (int i = 0; i < N; i++) {
        if (i < j) {
            complex temp = x[i];
            x[i] = x[j];
            x[j] = temp;
        }
        int m = N / 2;
        while (m >= 1 && j >= m) {
            j -= m;
            m /= 2;
        }
        j += m;
    }

    // FFT computation
    for (int len = 2; len <= N; len *= 2) {
        double angle = 2 * M_PI / len * (invert ? -1 : 1);
        complex wlen = {cos(angle), sin(angle)};
        for (int i = 0; i < N; i += len) {
            complex w = {1.0, 0.0};
            for (int j = 0; j < len / 2; j++) {
                complex u = x[i + j];
                complex v = {w.re * x[i + j + len / 2].re - w.im * x[i + j + len / 2].im,
                              w.re * x[i + j + len / 2].im + w.im * x[i + j + len / 2].re};
                x[i + j] = (complex){u.re + v.re, u.im + v.im};
                x[i + j + len / 2] = (complex){u.re - v.re, u.im - v.im};
                // Update w
                complex temp = {w.re * wlen.re - w.im * wlen.im,
                                w.re * wlen.im + w.im * wlen.re};
                w = temp;
            }
        }
    }

    if (invert) {
        for (int i = 0; i < N; i++) {
            x[i].re /= N;
            x[i].im /= N;
        }
    }
}

// Function to perform convolution using FFT
void convolve(int *A, int NA, int *F, int NF) {
    int N = NA + NF - 1;
    int N_fft = 1;
    while (N_fft < N) N_fft *= 2; // Next power of 2

    // Allocate memory for complex arrays
    complex *A_fft = (complex *)malloc(sizeof(complex) * N_fft);
    complex *F_fft = (complex *)malloc(sizeof(complex) * N_fft);
    complex *C_fft = (complex *)malloc(sizeof(complex) * N_fft);

    // Initialize input arrays for FFT
    for (int i = 0; i < N_fft; i++) {
        A_fft[i].re = (i < NA) ? A[i] : 0.0; // Zero-padding
        A_fft[i].im = 0.0; // Imaginary part
        F_fft[i].re = (i < NF) ? F[i] : 0.0; // Zero-padding
        F_fft[i].im = 0.0; // Imaginary part
    }

    fft(A_fft, N_fft, 0); // Forward FFT for A
    fft(F_fft, N_fft, 0); // Forward FFT for F

    // Multiply FFT results
    #pragma omp parallel for
    for (int i = 0; i < N_fft; i++) {
        C_fft[i].re = A_fft[i].re * F_fft[i].re - A_fft[i].im * F_fft[i].im;
        C_fft[i].im = A_fft[i].re * F_fft[i].im + A_fft[i].im * F_fft[i].re;
    }

    fft(C_fft, N_fft, 1); // Inverse FFT

    for (int i = NF - 1; i < NA; i++) {
        printf("%.0f\n", C_fft[i].re); // Output the real part
    }

    // Free allocated memory
    free(A_fft);
    free(F_fft);
    free(C_fft);
}

int main() {
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for (int i = 0; i < NA; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < NF; i++) {
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    // Perform convolution
    convolve(A, NA, F, NF);

    // ---- free memory ----
    free(F);
    free(A);
    // ---- end free ----
    return 0;
}
