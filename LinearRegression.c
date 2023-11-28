
#include <stdio.h>

int main() {
    int n, i;

    printf("Enter the number of elements to be input: ");
    scanf("%d", &n);
    
    float X[100] = {}, Y[100] = {}, m = 0, b = 0, sigmaX = 0, sigmaY = 0, sigmaXsq = 0, sigmaXY = 0;
    

    for (i = 0; i < n; i++) {
        scanf("%f", &X[i]);
        scanf("%f", &Y[i]);
    }
    

    for (i = 0; i < n; i++) {
        sigmaX += X[i];
        sigmaY += Y[i];
        sigmaXsq += X[i] * X[i];
        sigmaXY += X[i] * Y[i];
    }
    
    m = (n * sigmaXY - sigmaX * sigmaY) / (n * sigmaXsq - sigmaX * sigmaX);
    b = (sigmaY - m * sigmaX) / n;
    

    printf("\nY = %.2f X + (%.2f)\n", m, b);
    
    float x, y;

    printf("Enter value of X to predict value of Y: ");
    scanf("%f", &x);

    y = m * x + b;

    printf("Y = %.2f (Predicted for X = %.2f)\n\n", y, x);
    
    return 0;
}

