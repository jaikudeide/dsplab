#include <stdio.h>
#include <math.h>

double XR[8] = {1, 1, 2, 0, 1, 2, 0, 1};
double XI[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double Xr[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double Xi[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double WR[4] = {1.0, 0.707, 0.0, -0.707};
double WI[4] = {0.0, -0.707, -1.0, -0.707};
double amplitude[8], phase[8];

int main(void) {
    int i, j;

    i = 0;
    int w = 0;
    for (j = 0; j < 4; j++) {
        double sum1r = XR[i] + XR[i + 4];
        double sum1i = XI[i] + XI[i + 4];
        double sum2r = ((XR[i] - XR[i + 4]) * WR[w]) - ((XI[i] - XI[i + 4]) * WI[w]);
        double sum2i = ((XI[i] - XI[i + 4]) * WR[w]) + ((XR[i] - XR[i + 4]) * WI[w]);
        XR[i] = sum1r;
        XI[i] = sum1i;
        XR[i + 4] = sum2r;
        XI[i + 4] = sum2i;
        i = i + 1;
        w = w + 1;
    }

    i = 0;
    int x;
    for (x = 0; x < 2; x++) {
        int w = 0;
        for (j = 0; j < 2; j++) {
            double sum1r = XR[i] + XR[i + 2];
            double sum1i = XI[i] + XI[i + 2];
            double sum2r = ((XR[i] - XR[i + 2]) * WR[w]) - ((XI[i] - XI[i + 2]) * WI[w]);
            double sum2i = ((XI[i] - XI[i + 2]) * WR[w]) + ((XR[i] - XR[i + 2]) * WI[w]);
            XR[i] = sum1r;
            XI[i] = sum1i;
            XR[i + 2] = sum2r;
            XI[i + 2] = sum2i;
            i = i + 1;
            w = w + 2;
        }
        i = i + 2;
    }

    i = 0;
    w = 0;
    for (j = 0; j <= 3; j++) {
        double sum1r = XR[i] + XR[i + 1];
        double sum1i = XI[i] + XI[i + 1];
        double sum2r = ((XR[i] - XR[i + 1]) * WR[w]) - ((XI[i] - XI[i + 1]) * WI[w]);
        double sum2i = ((XI[i] - XI[i + 1]) * WR[w]) + ((XR[i] - XR[i + 1]) * WI[w]);
        XR[i] = sum1r;
        XI[i] = sum1i;
        XR[i + 1] = sum2r;
        XI[i + 1] = sum2i;
        i = i + 2;
    }

    Xr[0] = XR[0];
    Xr[1] = XR[4];
    Xr[2] = XR[2];
    Xr[3] = XR[6];
    Xr[4] = XR[1];
    Xr[5] = XR[5];
    Xr[6] = XR[3];
    Xr[7] = XR[7];

    Xi[0] = XI[0];
    Xi[1] = XI[4];
    Xi[2] = XI[2];
    Xi[3] = XI[6];
    Xi[4] = XI[1];
    Xi[5] = XI[5];
    Xi[6] = XI[3];
    Xi[7] = XI[7];

    printf("--- 8-Point FFT (Real + i * Imaginary) ---\n");
    for (i = 0; i < 8; i++) {
        printf("X[%d]: %f +i %f \n", i, Xr[i], Xi[i]);
    }

    printf("\n--- Amplitude Spectrum ---\n");
    for (i = 0; i < 8; i++) {
        amplitude[i] = sqrt((Xr[i] * Xr[i]) + (Xi[i] * Xi[i]));
        printf("Amp[%d]: %f \n", i, amplitude[i]);
    }

    printf("\n--- Phase Spectrum (in Radians) ---\n");
    for (i = 0; i < 8; i++) {
        phase[i] = atan2(Xi[i], Xr[i]);
        printf("Phase[%d]: %f \n", i, phase[i]);
    }
    
    return 0;
}
