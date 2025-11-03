#include <stdio.h>
#include <stdlib.h> // Needed for calloc, malloc, and free

void circular_convolution(float *x, float *h, float *y, int N) {
    for (int n = 0; n < N; n++) {
        y[n] = 0.0;
        for (int k = 0; k < N; k++) {
            // Calculate the circular index for h
            // (n - k + N) % N ensures the index is always positive
            int index = (n - k + N) % N;
            y[n] += x[k] * h[index];
        }
    }
}

void print_array(float *arr, int len, const char *label) {
    printf("%s:\n", label);
    for (int i = 0; i < len; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n\n");
}

int main() {
    
    float x[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    float h[] = {2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0};
    
    
    int x_len = sizeof(x) / sizeof(x[0]);
    int h_len = sizeof(h) / sizeof(h[0]);

    
    int N = (x_len > h_len) ? x_len : h_len;


    float *x_pad = (float *)calloc(N, sizeof(float));
    float *h_pad = (float *)calloc(N, sizeof(float));
    float *y_circular = (float *)malloc(sizeof(float) * N);

    if (x_pad == NULL || h_pad == NULL || y_circular == NULL) {
        printf("Error: Could not allocate memory.\n");
        return -1;
    }

       for (int i = 0; i < N; i++) {
        x_pad[i] = (i < x_len) ? x[i] : 0.0;
        h_pad[i] = (i < h_len) ? h[i] : 0.0;
    }

    
    circular_convolution(x_pad, h_pad, y_circular, N);

   
    print_array(x, x_len, "Original Input x[n]");
    print_array(h, h_len, "Original Impulse Response h[n]");
    print_array(x_pad, N, "Padded Input x_pad[n]");
    print_array(h_pad, N, "Padded Impulse Response h_pad[n]");
    print_array(y_circular, N, "Circular Convolution Output");

    
    free(x_pad);
    free(h_pad);
    free(y_circular);
    
    return 0;
}
