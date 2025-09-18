#include <stdio.h>
#include <string.h>

#define MAX 1000  // dígitos máximos

// Imprime un arreglo de dígitos alineado a la derecha (sin ceros a la izquierda)
void print_digits_right(const int *a, int n) {
    int i = 0;
    while (i < n - 1 && a[i] == 0) i++;  // quitar ceros iniciales
    // espacios a la izquierda para alinear a n columnas
    for (int s = 0; s < i; s++) putchar(' ');
    for (; i < n; i++) printf("%d", a[i]);
    putchar('\n');
}

void print_line(int n) {
    for (int i = 0; i < n; i++) putchar('-');
    putchar('\n');//incluye una linea 
}

int main(void) {
    char num1[MAX], num2[MAX];
    printf("Ingrese el primer numero: ");
    scanf("%s", num1);
    printf("Ingrese el segundo numero: ");
    scanf("%s", num2);

    int len1 = (int)strlen(num1);
    int len2 = (int)strlen(num2);
    int width = len1 + len2;            // ancho máximo (dígitos del resultado)
    int resultado[MAX] = {0};           // acumulador final (right-aligned en width)

    // Encabezado (alineado a la derecha)
    printf("\n");
    printf("%*s\n", width, num1);
    printf("%*s%s\n", width - len2 - 2, "", "x ");
    printf("%*s\n", width, num2);
    print_line(width);

    // Para cada dígito del multiplicador (num2), de derecha a izquierda
    for (int j = len2 - 1; j >= 0; j--) {
        int d2 = num2[j] - '0';
        int parcial[MAX] = {0};

        // desplazamiento: cuántos ceros a la derecha (como en el cuaderno)
        int shift = (len2 - 1) - j;

        // índice de escritura empezando desde la derecha,
        // dejando 'shift' posiciones libres al final
        int k = width - 1 - shift;
        int carry = 0;

        // multiplicar num1 (de derecha a izquierda) por d2
        for (int i = len1 - 1; i >= 0; i--) {
            int d1 = num1[i] - '0';
            int prod = d1 * d2 + carry;
            parcial[k] = prod % 10;   // escribir dígito
            carry = prod / 10;
            k--;                      // moverse hacia la izquierda
        }
        if (carry > 0 && k >= 0) {
            parcial[k] = carry;
        }

        // Imprimir fila parcial (alineada, sin 0 extra a la derecha)
        print_digits_right(parcial, width);

        // Sumar el parcial al resultado
        int c = 0;
        for (int p = width - 1; p >= 0; p--) {
            int s = resultado[p] + parcial[p] + c;
            resultado[p] = s % 10;
            c = s / 10;
        }
    }

    print_line(width);
    printf("Resultado: ");
    // Imprimir resultado final sin ceros a la izquierda
    int start = 0;
    while (start < width - 1 && resultado[start] == 0) start++;
    for (int i = start; i < width; i++) printf("%d", resultado[i]);
    printf("\n");

    return 0;
}