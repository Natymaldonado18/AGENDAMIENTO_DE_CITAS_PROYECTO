#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// Variable general donde se va a almacenar varias puntuaciones y comentarios de los pacientes
char valoracionPaciente[1000];

// Función para ingresar la valoración y el comentario
void valorarServicio() {
    system("cls");
    printf("Valoraci\242n y comentario del servicio:\n");

    // Valoracion
    int valoracion;
    do {
        printf("Ingresa la valoraci\242n del 1 al 5:\n");
        scanf("%d", &valoracion);
    } while (!(valoracion >= 1 && valoracion <= 5));

    // Comentario
    char comentario[100];
    fflush(stdin); // Limpiar el búfer de entrada antes de leer el comentario
    printf("Ingrese un comentario:\n");
    fgets(comentario, sizeof(comentario), stdin);

    // Eliminar el carácter de nueva línea del comentario
    comentario[strcspn(comentario, "\n")] = '\0';

    // Almacenar la valoración y el comentario en la variable global y cuando se ingrese una nueva
    // valoración y comentario, se va a concatenar con la anterior
    char valoracionComentario[1000];
    sprintf(valoracionComentario, "Valoraci\242n: %d\nComentario: %s\n", valoracion, comentario);
    strcat(valoracionPaciente, valoracionComentario);

}

void valoracionMenu() {
    system("cls");
    int opcion;
    do {
        printf("\n-- Men\243 Valoracion y Comentarios --\n");
        printf("1. Visualizar valoraci\242n y comentarios de los pacientes\n");
        printf("2. Regresar\n");
        printf("Seleccione una opci\242n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                system("cls");
                printf("Visualizar valoraci\242n y comentarios de los pacientes:\n");
                printf("%s\n", valoracionPaciente);
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                printf("Saliendo del men\243 valoracion y comentarios...\n");
                system("pause");
                system("cls");
                break;
            default:
                printf("Opci\242n inv\240lida. Intente nuevamente.\n");
                system("cls");
                break;
        }
    } while (opcion != 2);
}