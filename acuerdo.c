#include <stdio.h>
#include <stdlib.h>

int acuerdo() {
    int acuerdo_tratamiento_de_datos;

    do {
        system("cls");
        // Establecimiento de acuerdo de tratamiento de datos personales //
        printf("............................................................................................................\n");
        printf("ACUERDO DE TRATAMIENTO DE DATOS:\n");
        printf("La Fundaci\242n Salud Para Todos basa el tratamiento de datos de sus usuarios bajo la Ley de ");
        printf("Protecci\242n de Datos Personales instaurada en 2021 en Ecuador.\n");
        printf("\n");
        printf("Por ello, es fundamental conocer si se encuentra o no de acuerdo que la fundaci\242n maneje ");
        printf ("sus datos personales rigi\202ndose en la LOPDP\n");
        printf("............................................................................................................\n");
        printf("\n");
        printf("\nPor favor, digite la opci\242n que se aducue a su opini\242n:\n");
        printf("1.- S\241 estoy de acuerdo   --   2.- No estoy de acuerdo\n");
        printf("\nOpci\242n: ");
        scanf("%d", &acuerdo_tratamiento_de_datos);

        switch (acuerdo_tratamiento_de_datos) {
            case 1:
                return 1;
            case 2:
                printf("Programa finalizado.\n");
                exit(0);
            default:
                system("cls");
                printf("Opci\242n inv\240lida. Intente nuevamente.\n");
                system("pause");
        }
    } while (acuerdo_tratamiento_de_datos != 1 && acuerdo_tratamiento_de_datos != 2);

    return 0;
}