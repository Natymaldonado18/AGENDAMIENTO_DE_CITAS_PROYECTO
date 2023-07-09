#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "doctor.h"
#include "valoracion.h"

// Variables globales
// 3 doctores, 5 turnos por doctor, 7 dias de la semana
bool horariosOcupados[NUM_DOCTORES][5][7] = {false};

// Datos del paciente
char nombre[50];
char apellido[50];
char genero[10];
int edad;


void datosPaciente() {
    printf("\n-- Reg\241strese --\n");

    printf("Ingrese el nombre del paciente: ");
    scanf("%s", nombre);

    printf("Ingrese el apellido del paciente: ");
    scanf("%s", apellido);

    printf("Ingrese el g\202nero del paciente: ");
    scanf("%s", genero);

    printf("Ingrese la edad del paciente: ");
    scanf("%d", &edad);
}

void mostrarDatosPaciente() {
    printf("\nDatos del paciente:\n");
    printf("\tNombre: %s\n", nombre);
    printf("\tApellido: %s\n", apellido);
    printf("\tG\202nero: %s\n", genero);
    printf("\tEdad: %d\n", edad);
}

int seleccionarDoctor() {
    printf("Seleccione un doctor:\n");
    visualizarDoctores();

    int seleccionDoctor;
    do {
        printf("Ingrese el n\243mero del doctor seleccionado: ");
        scanf("%d", &seleccionDoctor);
    } while (!(seleccionDoctor >= 1 && seleccionDoctor <= NUM_DOCTORES));

    return seleccionDoctor;
}

int seleccionarDia() {
    printf("Seleccione un d\241a de la semana:\n");
    printf("1. Lunes\n2. Martes\n3. Mi\202rcoles\n4. Jueves\n5. Viernes\n");

    int seleccionDia;
    do {
        printf("Ingrese el n\243mero del d\241a seleccionado: ");
        scanf("%d", &seleccionDia);
    } while (!(seleccionDia >= 1 && seleccionDia <= 5));

    return seleccionDia;
}

int seleccionarHorario() {
    printf("Seleccione un horario de atenci\242n (desde las 09:00 hasta las 16:00):\n");
    printf("1. 09:00 - 10:00\n2. 10:00 - 11:00\n3. 11:00 - 12:00\n4. 12:00 - 13:00\n5. 13:00 - 14:00\n");
    printf("6. 14:00 - 15:00\n7. 15:00 - 16:00\n");

    int seleccionHorario;
    do {
        printf("Ingrese el n\243mero del horario seleccionado: ");
        scanf("%d", &seleccionHorario);
    } while (!(seleccionHorario >= 1 && seleccionHorario <= 7));

    return seleccionHorario;
}

bool verificarHorarioOcupado(int doctor, int dia, int horario) {
    return horariosOcupados[doctor - 1][dia - 1][horario - 1];
}

void marcarHorarioOcupado(int doctor, int dia, int horario) {
    horariosOcupados[doctor - 1][dia - 1][horario - 1] = true;
}

char *obtenerTurno(int doctor, int dia, int horario) {
    char **doctores = arregloDoctores();
    char *turno = (char *) malloc(1000 * sizeof(char)); // Reservar memoria para el turno

    sprintf(turno, "\nVisualizaci\242n final:\nNombre del Doctor:\n%s\nD\241a: ", doctores[doctor - 1]);

    switch (dia) {
        case 1:
            strcat(turno, "Lunes");
            break;
        case 2:
            strcat(turno, "Martes");
            break;
        case 3:
            strcat(turno, "Mi\202rcoles");
            break;
        case 4:
            strcat(turno, "Jueves");
            break;
        case 5:
            strcat(turno, "Viernes");
            break;
    }

    strcat(turno, "\nHorario: ");
    switch (horario) {
        case 1:
            strcat(turno, "09:00 - 10:00");
            break;
        case 2:
            strcat(turno, "10:00 - 11:00");
            break;
        case 3:
            strcat(turno, "11:00 - 12:00");
            break;
        case 4:
            strcat(turno, "12:00 - 13:00");
            break;
        case 5:
            strcat(turno, "13:00 - 14:00");
            break;
        case 6:
            strcat(turno, "14:00 - 15:00");
            break;
        case 7:
            strcat(turno, "15:00 - 16:00");
            break;
    }

    strcat(turno, "\n");

    // Agregar información del paciente
    strcat(turno, "Informaci\242n del paciente:");
    strcat(turno, "\nNombre: ");
    strcat(turno, nombre);
    strcat(turno, "\nApellido: ");
    strcat(turno, apellido);
    strcat(turno, "\nG\202nero: ");
    strcat(turno, genero);
    strcat(turno, "\nEdad: ");
    char edadStr[10];
    sprintf(edadStr, "%d", edad);
    strcat(turno, edadStr);
    strcat(turno, "\n");

    return turno;
}

void guardarTurnoEnArchivo(char *turno, int numeroTurno, char *nombreDoctor) {
    char nombreArchivo[50];
    sprintf(nombreArchivo, "turno%02d_%s.txt", numeroTurno, nombreDoctor); // Generar el nombre del archivo

    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar el turno.\n");
        return;
    }

    fprintf(archivo, "%s", turno); // Escribir el turno en el archivo

    fclose(archivo);
}

void visualizarTurno(int doctor, int dia, int horario) {
    char **doctores = arregloDoctores();
    char *turno = obtenerTurno(doctor, dia, horario);
    static int numeroTurno = 1; // Contador de turno
    guardarTurnoEnArchivo(turno, numeroTurno, doctores[doctor - 1]);
    printf("%s", turno); // Mostrar el turno en la consola
    system("pause");
    system("cls");
    printf("\nEl turno ha sido guardado en el archivo turno%02d_%s.txt\n", numeroTurno, doctores[doctor - 1]);
    numeroTurno++;
    free(turno); // Liberar memoria del turno
}

void tomarTurno() {
    system("cls");
    int seleccionDoctor = seleccionarDoctor();
    system("cls");
    int seleccionDia = seleccionarDia();
    system("cls");
    int seleccionHorario = seleccionarHorario();

    system("cls");
    if (verificarHorarioOcupado(seleccionDoctor, seleccionDia, seleccionHorario)) {
        printf("El horario seleccionado ya est\240 ocupado. Por favor, seleccione otro horario.\n");
        return;
    }

    marcarHorarioOcupado(seleccionDoctor, seleccionDia, seleccionHorario);

    system("cls");
    visualizarTurno(seleccionDoctor, seleccionDia, seleccionHorario);
}

void pacienteMenu() {
    system("cls");
    datosPaciente();
    system("pause");
    system("cls");
    mostrarDatosPaciente();
    system("pause");
    system("cls");
    int opcion;
    do {
        printf("\n-- Men\243 Paciente --\n");
        printf("1. Visualizar informaci\242n de los doctores\n");
        printf("2. Tomar turno\n");
        printf("3. Valorar el servicio\n");
        printf("4. Regresar\n");
        printf("Seleccione una opci\242n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                system("cls");
                visualizarDoctores();
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                tomarTurno();
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                valorarServicio();
                system("pause");
                system("cls");
                break;
            case 4:
                system("cls");
                printf("Saliendo del menu paciente...\n");
                system("pause");
                system("cls");
                break;
            default:
                printf("Opci\242n inv\240lida. Intente nuevamente.\n");
                system("cls");
                break;
        }
    } while (opcion != 4);
}