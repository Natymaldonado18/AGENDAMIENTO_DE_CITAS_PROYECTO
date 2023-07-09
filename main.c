#include <stdio.h>
#include <stdlib.h>

#include "doctor.h"
#include "paciente.h"
#include "valoracion.h"
#include "acuerdo.h"

int main() {
    if (acuerdo() == 1) {
        system("cls");
        int opcion;
        do {
            printf("-- Men\243 Principal --\n");
            printf("1. Paciente\n");
            printf("2. Doctor\n");
            printf("3. Valoraci\242n y Comentarios\n");
            printf("4. Salir\n");
            printf("Seleccione una opci\242n: ");
            scanf("%i", &opcion);

            switch (opcion) {
                case 1:
                    pacienteMenu();
                    break;
                case 2:
                    doctorMenu();
                    break;
                case 3:
                    valoracionMenu();
                    break;
                case 4:
                    printf("Saliendo del programa...\n");
                    break;
                default:
                    printf("Opci\242n inv\240lida. Intente nuevamente.\n");
                    break;
            }
        } while (opcion != 4);
    }
    return 0;
}