#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIO 20
#define MAX_CONTRASENA 20

int doctorLogeado;

char **arregloDoctores() {
    FILE *archivo = fopen("doctores.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo doctores.txt\n");
        return NULL;
    }

    // Contar la cantidad de doctores en el archivo
    int numDoctores = 0;
    char linea[500];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (strstr(linea, "Nombre y Apellidos: ") != NULL) {
            numDoctores++;
        }
    }
    rewind(archivo);

    // Crear el arreglo dinámico para almacenar los nombres y apellidos
    char **doctores = (char **) malloc(numDoctores * sizeof(char *));
    if (doctores == NULL) {
        printf("Error al asignar memoria para el arreglo de doctores.\n");
        fclose(archivo);
        return NULL;
    }

    // Leer el archivo y guardar los nombres y apellidos en el arreglo
    int i = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (strstr(linea, "Nombre y Apellidos: ") != NULL) {
            char *nombreApellido = strchr(linea, ':') + 2;
            nombreApellido[strcspn(nombreApellido, "\n")] = '\0'; // Eliminar el salto de línea
            doctores[i] = strdup(nombreApellido);
            i++;
        }
    }

    fclose(archivo);
    return doctores;
}


void visualizarDoctores() {
    FILE *archivo = fopen("doctores.txt","r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo doctores.txt\n");
        return;
    }

    printf("Lista de doctores:\n");

    char linea[500];
    int numDoctor = 1;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (strcmp(linea, "\n") == 0) {
            continue;
        } else if (strstr(linea, "Nombre y Apellidos: ") != NULL) {
            printf("%d. Doctor/a:\n", numDoctor);
            printf("%s", linea);
        } else {
            printf("%s", linea);
        }

        if (strstr(linea, "Especialidad: ") != NULL) {
            numDoctor++;
        }
    }

    printf("\nNo se encontraron mas l\241neas en el archivo.\n");

    fclose(archivo);
}

// Función para realizar el login del doctor
int login() {
    char usuario[MAX_USUARIO];
    char contrasena[MAX_CONTRASENA];

    printf("Usuario: ");
    scanf("%s", usuario);
    printf("Contrasena: ");
    scanf("%s", contrasena);

    // Abrir el archivo de credenciales
    FILE *archivo = fopen("credenciales.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de credenciales.\n");
        return 0;  // Indicar error de login
    }

    char usuarioArchivo[MAX_USUARIO];
    char contrasenaArchivo[MAX_CONTRASENA];
    int encontrado = 0;  // Indicador de si se encontró la credencial del doctor

    // Buscar las credenciales en el archivo
    while (fscanf(archivo, "%s %s", usuarioArchivo, contrasenaArchivo) == 2) {
        if (strcmp(usuario, usuarioArchivo) == 0 && strcmp(contrasena, contrasenaArchivo) == 0) {
            encontrado = 1;
            break;
        }
    }

    fclose(archivo);

    if (encontrado) {
        printf("Login exitoso\n");
        char ultimoCaracter = usuario[strlen(usuario) - 1];

        char **doctores = arregloDoctores();
        if (doctores == NULL) {
            printf("Error al obtener la lista de doctores.\n");
            return 0;  // Indicar error de login
        }

        printf("Bienvenido, %s.\n", doctores[ultimoCaracter - '1']);
        doctorLogeado = (int) ultimoCaracter - 48;
        return 1;  // Indicar login exitoso y devolver el número de doctor
    } else {
        printf("Usuario o contrasena incorrectos.\n");
        return 0;  // Indicar error de login
    }
}

// Función para mostrar los turnos asociados al doctor
void mostrarTurnosDoctor() {
    char nombreArchivo[50];
    char **doctores = arregloDoctores();


    for (int numeroArchivo = 1; numeroArchivo < 10; numeroArchivo++) {
        sprintf(nombreArchivo, "turno%02d_%s.txt", numeroArchivo, doctores[doctorLogeado - 1]);

        FILE *archivo = fopen(nombreArchivo, "r");
        if (archivo == NULL) {
            printf("No se encuentran mas turno o se presento un error al abrir el archivo de turno.\n");
            break;
        }

        printf("Turnos del doctor: %s:\n", doctores[doctorLogeado - 1]);

        char turno[1000];
        while (fgets(turno, sizeof(turno), archivo) != NULL) {
            printf("%s", turno);
        }

        fclose(archivo);

        numeroArchivo++;
    }
}


void doctorMenu() {
    system("cls");
    int opcion;
    int doctorLogueado = 0;  // Indicador de si el doctor ha iniciado sesión

    do {
        printf("----- Men\243 -----\n");
        printf("1. Login\n");
        printf("2. Mostrar turnos\n");
        printf("3. Salir\n");
        printf("Selecciona una opci\242n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                system("cls");
                if (doctorLogueado) {
                    printf("Ya has iniciado sesi\242n.\n");
                } else {
                    doctorLogueado = login();
                }
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                if (doctorLogueado) {
                    mostrarTurnosDoctor();
                } else {
                    printf("Debes iniciar sesi\242n primero.\n");
                }
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                printf("Saliendo del men\243 Doctor...\n");
                system("pause");
                system("cls");
                break;
            default:
                system("cls");
                printf("Opci\242n inv\240lida. Por favor, seleccione una opci\242n v\240lida.\n");
                system("pause");
                system("cls");
                break;
        }
    } while (opcion != 3);
}