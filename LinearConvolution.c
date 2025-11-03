#include <stdio.h>
#include <stdlib.h> // Needed for malloc and free

void linear_convolution(float *x, int x_len, float *h, int h_len, float *y) {
    int y_len = x_len + h_len - 1;
    
    for (int n = 0; n < y_len; n++) {
        y[n] = 0.0;
        for (int k = 0; k < h_len; k++) {
            // Check if the index (n - k) is within the bounds of the x signal
            if (n - k >= 0 && n - k < x_len) {
                y[n] += x[n - k] * h[k];
            }
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
    // Define input signals
    float x[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    float h[] = {2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0};
    
    
    int x_len = sizeof(x) / sizeof(x[0]);
    int h_len = sizeof(h) / sizeof(h[0]);
    
    
    int y_linear_len = x_len + h_len - 1;
    
    
    float *y_linear = (float *)malloc(sizeof(float) * y_linear_len);
    if (y_linear == NULL) {
        printf("Error: Could not allocate memory.\n");
        return -1;
    }

    
    linear_convolution(x, x_len, h, h_len, y_linear);

    
    print_array(x, x_len, "Input x[n]");
    print_array(h, h_len, "Impulse Response h[n]");
    print_array(y_linear, y_linear_len, "Linear Convolution Output");

    
    free(y_linear);
    
    return 0;
}
