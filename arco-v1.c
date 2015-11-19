// #include <windows.h>
#include <stdio.h>
#include <math.h>
#define FACTOR_RADIAN M_PI / 180

int main () {
    int i, k, centro, coincidencias[4];
    float x, y, ha, hb, ka, kb, x1, x2, x3, y1, y2, y3, r, q, alfa; 

    printf("Introduce las coordenadas del primer punto\n");
    scanf("%f%f", &x1, &y1);
    printf("Introduce las coordenadas del segundo punto\n");
    scanf("%f%f", &x2, &y2);
    printf("Introduce la magnitud del radio\n");
    scanf("%f", &r);

    q = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)); // Distancia entre los puntos
    x3 = (x1+x2)/2; y3 = (y1+y2)/2; // Punto Medio

    ha = x3 + sqrt(r*r-(q/2)*(q/2))*(y1-y2)/q; // Centro 1 (X)
    ka = y3 + sqrt(r*r-(q/2)*(q/2))*(x2-x1)/q; // Centro 1 (Y)

    hb = x3 - sqrt(r*r-(q/2)*(q/2))*(y1-y2)/q; // Centro 2 (X)
    kb = y3 - sqrt(r*r-(q/2)*(q/2))*(x2-x1)/q; // Centro 2 (Y)

    alfa = 2*asin((q/2)/r)*(180/M_PI); // Apertura del Arco
        
    printf("Elige el centro con el que deseas trabajar (1 o 2)\n");
    printf("Centro 1: (%f, %f)\nCentro 2: (%f, %f)\n", ha, ka, hb, kb);
    scanf("%i", &centro);

    // Determinación del Centro a usar
    if (centro == 1) {
        x = ha;
        y = ka;
        printf("El centro con el que vamos a trabajar es (%f, %f)\n", floor(x), floor(y));
        printf("El ángulo con el que vamos a trabajar es: %f\n", floor(alfa));
    } else if (centro == 2) {
        x = hb;
        y = kb;
        printf("El centro con el que vamos a trabajar es (%f, %f)\n", floor(x), floor(y));
        printf("El ángulo con el que vamos a trabajar es: %f\n", floor(alfa));
    } else {
        printf("%i no es un valor válido\n", centro);
        scanf("%i", &centro);
    }

    // Coincidencias de puntos dados con un punto en la circunferencia
    // Margen de error 0.0157 radianes o 0.9 grados
    k = 0;    
    for (i = 0; i < 360; i++) {
        float a = r * cos(i * FACTOR_RADIAN) + x;
        float b = r * sin(i * FACTOR_RADIAN) + y;
        if (((fabs(a - x1) < fabs(r*0.0157)) && (fabs(b - y1) < fabs(r*0.0157)))
        || ((fabs(a - x2) < fabs(r*0.0157)) && (fabs(b - y2) < fabs(r*0.0157)))) {
            coincidencias[k] = i;
            k++;
        }
    }

    // Imprime, adecuadamente, los puntos entre las coincidencias
    // En caso de que los círculos sean tangentes el arco predeterminado
    // abarca de 0 a PI radianes
    if (fabs(fabs(coincidencias[0] - coincidencias[k-1]) - alfa) < 5) {
        for (i = 0; i < 360; i++) {
            if ((i >= coincidencias[0]) && (i <= coincidencias[k-1]))
                printf("%i\t(%f, %f)\n", i, r * cos(i * FACTOR_RADIAN) + x, 
                    r * sin(i * FACTOR_RADIAN) + y);
        }
    } else {
        for (i = 0; i < 360; i++) {
            if ((i <= coincidencias[0]) || (360 - coincidencias[k-1] >= 360 - i))
                printf("%i\t(%f, %f)\n", i, r * cos(i * FACTOR_RADIAN) + x, 
                    r * sin(i * FACTOR_RADIAN) + y);
        }
    }

    // system("pause");
}