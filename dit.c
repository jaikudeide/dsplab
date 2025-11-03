#include <stdio.h>
#include <math.h> 

double x[8] = {1, 1, 2, 0, 1, 2, 0, 1}; 
double XR[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double XI[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double WR[4] = {1.0, 0.707, 0.0, -0.707}; 
double WI[4] = {0.0, -0.707, -1.0, -0.707}; 
double amplitude[8], phase[8];

int main(void) {
    int i, j;

    XR[0] = x[0];
    XR[1] = x[4];
    XR[2] = x[2];
    XR[3] = x[6];
    XR[4] = x[1];
    XR[5] = x[5];
    XR[6] = x[3];
    XR[7] = x[7];

    i = 0;
    for (j = 0; j <= 3; j++) {
        double sum1r = XR[i] + XR[i + 1];
        double sum1i = XI[i] + XI[i + 1];
        double temp_r = (WR[0] * XR[i + 1]) - (WI[0] * XI[i + 1]);
        double temp_i = (WR[0] * XI[i + 1]) + (WI[0] * XR[i + 1]);
        
        XR[i] = XR[i] + temp_r;
        XI[i] = XI[i] + temp_i;

        XR[i + 1] = (sum1r - XR[i+1]) - temp_r;
        XI[i + 1] = (sum1i - XI[i+1]) - temp_i;
        
        i = i + 2;
    }

    i = 0;
    int x_loop; 
    for (x_loop = 0; x_loop < 2; x_loop++) {
        for (j = 0; j < 2; j++) {
            int w = j * 2; 

            double temp_r = (WR[w] * XR[i + 2]) - (WI[w] * XI[i + 2]);
            double temp_i = (WR[w] * XI[i + 2]) + (WI[w] * XR[i + 2]);

            double sum1r = XR[i] + temp_r;
            double sum1i = XI[i] + temp_i;

            double sum2r = XR[i] - temp_r;
            double sum2i = XI[i] - temp_i;

            XR[i] = sum1r;
            XI[i] = sum1i;
            XR[i + 2] = sum2r;
            XI[i + 2] = sum2i;
            i = i + 1;
        }
        i = i + 2;
    }

    i = 0;
    int w = 0;
    for (j = 0; j < 4; j++) {
        double temp_r = (WR[w] * XR[i + 4]) - (WI[w] * XI[i + 4]);
        double temp_i = (WR[w] * XI[i + 4]) + (WI[w] * XR[i + 4]);

        double sum1r = XR[i] + temp_r;
        double sum1i = XI[i] + temp_i;

        double sum2r = XR[i] - temp_r;
        double sum2i = XI[i] - temp_i;
        
        XR[i] = sum1r;
        XI[i] = sum1i;
        XR[i + 4] = sum2r;
        XI[i + 4] = sum2i;
        i = i + 1;
        w = w + 1;
    }

    printf("--- 8-Point FFT (Real + i * Imaginary) ---\n");
    for (i = 0; i < 8; i++) {
        printf("X[%d]: %f +i %f \n", i, XR[i], XI[i]);
    }

    printf("\n--- Amplitude Spectrum ---\n");
    for (i = 0; i < 8; i++) {
        amplitude[i] = sqrt((XR[i] * XR[i]) + (XI[i] * XI[i]));
        printf("Amp[%d]: %f \n", i, amplitude[i]);
    }

    printf("\n--- Phase Spectrum (in Radians) ---\n");
    for (i = 0; i < 8; i++) {
        phase[i] = atan2(XI[i], XR[i]);
        printf("Phase[%d]: %f \n", i, phase[i]);
    }
    
    return 0;
}
