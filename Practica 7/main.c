/*
 *El Hospital veterinario para pequeñas especies es un centro comunitario de la
 *UABC, que brinda servicios médicos veterinarios de calidad a la sociedad en
 *general. Para realizar estos servicios se cuenta con un sistema que registra la
 *información y costo de los servicios disponibles así como el historial de citas
 *programadas.
 */

/* 
 * File:   main.c
 * Author: kevin
 *
 * Created on 21 de mayo de 2020, 10:54 AM
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <string.h>
#include <ctype.h>

struct servicio {
    int clv;
    char nombre[30];
    float costo;
    char descrip[60];
};

struct fechaHora {
    int dia, mes, anio, hr, min;
};

struct cita {
    struct fechaHora fH;
    int clv,clvServicio;
    char nombreSolicitante[40], nombrePaciente[40], conclusion[30];
    int status;
};

typedef struct servicio SERVICIO;
typedef struct cita CITA;

enum modo {
    inactivo, activo
};

int menu();
int abrirArchivo(char nombreArchivo[]);
void registrarServicio(int fdS);
void registrarCita(int fdS, int fdC);
void menuConsultar(int fdS, int fdC);
void consultaGeneralS(int fdS);
void consultaEspecificaC(int fdC);
void consultaEspecificaS(int fdS);
void consultaGeneralC(int fdC);
void citasPorRealizar(int fdC);
void mostrarCita(CITA c);
void bajaFisicaServicio(int fdS, int fdC);
void menuModificarCita(int fdC);
void bajaLogicaCita(int fdC);
int disponibilidadCita(char clave[], int fdC);
void concluirCita(int fdC);
int ingresarClave(char clave[]);
void reprogramarCita(int fdC);
int validacionIngreso(char cadena[], int op);
int validarFormatoFecha(char cadena[]);
int validarFormatoHora(char cadena[]);
int validarIngresoFecha(char cadena[], int op);
int validarIngresoHora(char cadena[], int op, int hora);
void programarCita(CITA *c, int fd, int op);
int verficarCita(CITA c, int fd);
int verificarContenidoCitas(int fdC);
int continuar();

/*
 * 
 */
int main(int argc, char** argv) {
    int op, fdS, fdC;
    fdS = abrirArchivo("servicio.txt");
    fdC = abrirArchivo("citas.txt");
    if (fdS == -1) {
        printf("\nNo se pudo abrir el archivo de servicio");
        exit(1);
    } else if (fdC == -1) {
        printf("\nNo se pudo abrir el archivo de citas");
        exit(1);
    } else {
        do {
            op = 0;
            op = menu();
            switch (op) {
                case 1:
                    registrarServicio(fdS);
                    break;
                case 2:
                    registrarCita(fdS, fdC);
                    break;
                case 3:
                    menuConsultar(fdS, fdC);
                    break;
                case 4:
                    bajaFisicaServicio(fdS, fdC);
                    break;
                case 5:
                    menuModificarCita(fdC);
                    break;
                case 6:
                    printf("\nSaliendo...\n");
                    close(fdS);
                    close(fdC);
                    break;
                default:
                    printf("\nOpcion invalida\n\n");
            }
        } while (op != 6);
    }
    return (EXIT_SUCCESS);
}

/**
 * Menu principal para realizar diferentes opciones en la simulacion de la vida real
 * @param op
 * @return 
 */
int menu() {
    char opA[10];
    int b;
    do {
        b = 0, opA[0] = '\0';
        printf("\nHospital veterinario para pequeñas especies\n1.-Registrar servicio\n2.-Registrar cita\n3.-Consultas\n4.-Eliminar servicio\n5.-Modificar cita\n6.-Salir\nOPCION: ");
        scanf("%[^\n]", opA);
        while (getchar() != '\n');
        if (strlen(opA) > 1) {
            printf("\nOpcion invalida\n\n");
            b = -1;
        }
    } while (b == -1);
    return atoi(opA);
}

/**
 * En esta opción se piden los datos de un nuevo servicio que ofrecerá la veterinaria.
 *Cada registro deberá ser anexado a un archivo de acceso directo llamado "servicios.txt".
 * @param fd
 */
void registrarServicio(int fd) {
    SERVICIO svc;
    char clave[35], costo[20];
    int b;
    svc.clv = 0;
    do {
        b = 0;
        printf("\nRegistro de servicio\n");
        b = ingresarClave(clave);
        if (b == 0) {
            lseek(fd, (atoi(clave) - 1) * sizeof (SERVICIO), SEEK_SET);
            read(fd, &svc, sizeof (SERVICIO));
            if (svc.clv == atoi(clave)) {
                printf("\nLa clave ingresada ya pertenece a otro servicio,ingrese otra clave");
                b = -1;
            }
        }
    } while (b == -1);
    do {
        svc.nombre[0] = '\0', b = 0;
        printf("\nIngrese el nombre del servicio: ");
        scanf("%[^\n]", svc.nombre);
        while (getchar() != '\n');
        if (validacionIngreso(svc.nombre, 2) == -1 || strlen(svc.nombre) == 0) {
            printf("\nIngrese una opcion valida de nombre\n");
            b = -1;
        }
    } while (b == -1);
    do {
        costo[0] = '\0', b = 0;
        printf("\nIngrese el costo del servicio: ");
        scanf("%[^\n]", costo);
        while (getchar() != '\n');
        if (validacionIngreso(costo, 3) == -1 || atof(costo) < 1) {
            printf("\nIngrese una opcion valida de costo\n");
            b = -1;
        }
    } while (b == -1);
    do {
        svc.descrip[0] = '\0', b = 0;
        printf("\nIngrese la descripcion del servicio: ");
        scanf("%[^\n]", svc.descrip);
        while (getchar() != '\n');
        if (validacionIngreso(svc.descrip, 2) == -1 || strlen(svc.descrip) == 0) {
            printf("\nIngrese una opcion valida de descripcion\n");
            b = -1;
        }
    } while (b == -1);
    svc.clv = atoi(clave);
    svc.costo = atof(costo);
    lseek(fd, (atoi(clave) - 1) * sizeof (SERVICIO), SEEK_SET);
    write(fd, &svc, sizeof (SERVICIO));
}

/**
 * Realiza el ingreso al archivo de un registro de una cita.Cada registro deberá ser anexado a un archivo de acceso directo llamado "citas.txt".
 * @param fdS
 * @param fdC
 */
void registrarCita(int fdS, int fdC) {
    CITA c;
    SERVICIO svc;
    char clave[35], claveS[35];
    int b;
    if (lseek(fdS, 0, SEEK_END) != 0) {
        do {
            b = 0;
            b = ingresarClave(clave);
            if (b == 0) {
                lseek(fdC, (atoi(clave) - 1) * sizeof (CITA), SEEK_SET);
                read(fdC, &c, sizeof (CITA));
                if (c.clv == atoi(clave) && c.status == activo) {
                    printf("\nLa clave ingresada ya pertenece a otra cita,ingrese otra clave\n");
                    b = -1;
                }
            }
        } while (b == -1);
        do {
            b = 0;
            printf("Clave de servicio\n");
            b = ingresarClave(claveS);
            if (b == 0) {
                lseek(fdS, (atoi(claveS) - 1) * sizeof (SERVICIO), SEEK_SET);
                read(fdS, &svc, sizeof (SERVICIO));
                if (svc.clv != atoi(claveS)) {
                    printf("\nLa clave de servicio no ha sido registrada\n");
                    b = -1;
                }
            }
        } while (b == -1);
        do {
            b = 0, c.nombreSolicitante[0] = '\0';
            printf("\nIngrese el nombre del solicitante: ");
            scanf("%[^\n]", c.nombreSolicitante);
            while (getchar() != '\n');
            if (validacionIngreso(c.nombreSolicitante, 2) == -1 || strlen(c.nombreSolicitante) == 0) {
                printf("\nIngrese una opcion valida de nombre de solicitante\n");
                b = -1;
            }
        } while (b == -1);
        do {
            b = 0;
            c.nombrePaciente[0] = '\0';
            printf("\nIngrese el nombre del paciente: ");
            scanf("%[^\n]", c.nombrePaciente);
            while (getchar() != '\n');
            if (validacionIngreso(c.nombrePaciente, 2) == -1 || strlen(c.nombrePaciente) == 0) {
                printf("\nIngrese una opcion valida de nombre de paciente\n");
                b = -1;
            }
        } while (b == -1);
        programarCita(&c, fdC, 1);
        c.clv = atoi(clave);
        c.clvServicio = atoi(claveS);
        strcpy(c.conclusion, "Por realizarse");
        c.status = activo;
        lseek(fdC, (atoi(clave) - 1) * sizeof (CITA), SEEK_SET);
        write(fdC, &c, sizeof (CITA));
    } else {
        printf("\nLa veterinaria no ofrece servicios por el momento\n");
    }
}

/**
 * Realiza el ingreso de la fecha y hora en la cual se puede realizar alguna cita segun la informacion que el usuario ingrese
 * @param c
 * @param fd
 * @param op
 */
void programarCita(CITA *c, int fd, int op) {
    char fecha[35], hora[20];
    int b;
    do {
        do {
            b = 0, fecha[0] = '\0', hora[0] = '\0';
            printf("\nFecha de cita con formato dd-mm-aaaa(Ejemplo:01-01-2005): ");
            scanf("%[^\n]", fecha);
            while (getchar() != '\n');
            if (op == 1 || (op == 2 && strlen(fecha) != 0)) {
                b = validarFormatoFecha(fecha);
                if (b == 0) {
                    b = validarIngresoFecha(fecha, 1);
                    c->fH.dia = b;
                    if (b != -1) {
                        b = validarIngresoFecha(fecha, 2);
                        c->fH.mes = b;
                        if (b != -1) {
                            b = validarIngresoFecha(fecha, 3);
                            c->fH.anio = b;
                        }
                    }
                }
            }
        } while (b == -1);
        do {
            b = 0, hora[0] = '\0';
            printf("\nHora de cita con formato de 24 horas(hh:mm): ");
            scanf("%[^\n]", hora);
            while (getchar() != '\n');
            if (op == 1 || (op == 2 && strlen(hora) != 0)) {
                b = validarFormatoHora(hora);
                if (b == -0) {
                    b = validarIngresoHora(hora, 1, 0);
                    c->fH.hr = b;
                    if (b != -1) {
                        b = validarIngresoHora(hora, 2, c->fH.hr);
                        c->fH.min = b;
                    }
                    if (b != -1) {
                        b = verficarCita(*c, fd);
                    }
                }
                if (b == -1) {
                    printf("¿Desea volver a ingresar la fecha por posibles cambios?\n");
                    b = continuar();
                }
            } else if (strlen(fecha) > 0 && strlen(hora) == 0 && op == 2) {
                b = verficarCita(*c, fd);
                if (b == -1) {
                    printf("¿Desea volver a ingresar la fecha por posibles cambios?\n");
                    b = continuar();
                }
            }
        } while (b == 2);
    } while (b == 1);
}

/**
 * Menu en el cual muestra las opciones con las cuales el usuario puede consultar de los archivos "citas.txt" y "servicios.txt"
 * @param fdS
 * @param fdC
 */
void menuConsultar(int fdS, int fdC) {
    char opA[10], opB[10];
    int b;
    do {
        b = 0, opA[0] = '\0';
        printf("\nConsultas");
        printf("\n1.-Servicios\n2.-Citas\n3.-Regresar\nOPCION: ");
        scanf("%[^\n]", opA);
        while (getchar() != '\n');
        if (strlen(opA) > 1) {
            printf("\nOpcion invalida\n\n");
            b = -1;
        }
        if (b != -1) {
            switch (atoi(opA)) {
                case 1:
                    if (lseek(fdS, 0, SEEK_END) != 0) {
                        do {
                            b = 0, opB[0] = '\0';
                            printf("\nConsultas de servicios");
                            printf("\n1.-Especifica\n2.-General\n3.-Regresar\nOPCION: ");
                            scanf("%[^\n]", opB);
                            while (getchar() != '\n');
                            if (strlen(opB) > 1) {
                                printf("\nOpcion invalida\n\n");
                                b = -1;
                            }
                            if (b != -1) {
                                if (atoi(opB) == 1) {
                                    consultaEspecificaS(fdS);
                                } else if (atoi(opB) == 2) {
                                    consultaGeneralS(fdS);
                                } else if (atoi(opB) == 3) {
                                    printf("\nRegresando...\n");
                                } else {
                                    printf("\nOpcion invalida\n\n");
                                }
                            }
                        } while (atoi(opB) != 3);
                    } else {
                        printf("\nDebe existir por lo menos un servicio para escoger esta opcion\n");
                    }
                    break;
                case 2:
                    if (verificarContenidoCitas(fdC) == 1) {
                        do {
                            b = 0, opB[0] = '\0';
                            printf("\nConsultas de citas");
                            printf("\n1.-Especifica\n2.-General\n3.-Por realizar\n4.-Regresar\nOPCION: ");
                            scanf("%[^\n]", opB);
                            while (getchar() != '\n');
                            if (strlen(opB) > 1) {
                                printf("\nOpcion invalida\n\n");
                                b = -1;
                            }
                            if (b != -1) {
                                if (atoi(opB) == 1) {
                                    consultaEspecificaC(fdC);
                                } else if (atoi(opB) == 2) {
                                    consultaGeneralC(fdC);
                                } else if (atoi(opB) == 3) {
                                    citasPorRealizar(fdC);
                                } else if (atoi(opB) == 4) {
                                    printf("\nRegresando...\n");
                                } else {
                                    printf("\nOpcion invalida\n\n");
                                }
                            }
                        } while (atoi(opB) != 4);
                    } else {
                        printf("\nDebe existir por lo menos una cita para escoger esta opcion\n");
                    }
                    break;
                case 3:
                    printf("\nRegresando...\n");
                    break;
                default:
                    printf("\nOpcion invalida\n\n");
            }
        }
    } while (atoi(opA) != 3);
}

/**
 * Realiza la busqueda de un registro en el archivo "servicios.txt" apartir de su clave ingresada para mostrar toda su informacion
 * @param fdS
 */
void consultaEspecificaS(int fdS) {
    SERVICIO svc;
    char clave[35];
    int x = 1, b = 0;
    do {
        printf("\nConsulta especifica\n");
        b = ingresarClave(clave);
        if (b == 0) {
            lseek(fdS, (atoi(clave) - 1) * sizeof (SERVICIO), SEEK_SET);
            read(fdS, &svc, sizeof (SERVICIO));
            if (svc.clv == atoi(clave)) {
                printf("\nServicio:\nClave:\t\tNombre:\t\tCosto:\t\tDescripcion:\n%-16d%-16s%-16.2f%-20s\n", svc.clv, svc.nombre, svc.costo, svc.descrip);
            } else {
                printf("\nNo se encontro el servicio especificado\n");
            }
        }
    } while (b == -1);
}

/**
 * Muestra todos los registros e informacion del archivo "servicios.txt"
 * @param fdS
 */
void consultaGeneralS(int fdS) {
    SERVICIO svc;
    int x = 1;
    lseek(fdS, 0, SEEK_SET);
    printf("\nLista de Servicios\nClave:\t\tNombre:\t\tCosto:\t\tDescripcion:\n");
    while (read(fdS, &svc, sizeof (SERVICIO)) != 0) {
        if (svc.clv == x) {
            printf("%-16d%-16s%-16.2f%-20s\n", svc.clv, svc.nombre, svc.costo, svc.descrip);
        }
        x++;
    }
}

/**
 * Realiza la busqueda de un registro en el archivo "citas.txt" apartir de su clave ingresada para mostrar toda su informacion
 * @param fdC
 */
void consultaEspecificaC(int fdC) {
    CITA c;
    char clave[35];
    int x = 1, b = 0;
    do {
        printf("\nConsulta especifica\n");
        b = ingresarClave(clave);
        if (b == 0) {
            lseek(fdC, (atoi(clave) - 1) * sizeof (CITA), SEEK_SET);
            read(fdC, &c, sizeof (CITA));
            if (c.clv == atoi(clave) && c.status == activo){
                printf("\nCita:\nClave cita:\tClave de servicio:\tSolicitante:\t\tPaciente:\tConclusion:\t\tFecha:\t\tHora:\n");
                mostrarCita(c);
            } else {
                printf("\nNo se encontro la cita especificada\n");
            }
        }
    } while (b == -1);
}

/**
 * Muestra todos los registros e informacion del archivo "citas.txt" siempre y cuando su status sea activo
 * @param fdC
 */
void consultaGeneralC(int fdC) {
    CITA c;
    int x = 1, i = 0;
    lseek(fdC, 0, SEEK_SET);
    printf("\nLista de Citas\nClave cita:\tClave de servicio:\tSolicitante:\t\tPaciente:\tConclusion:\t\tFecha:\t\tHora:\n");
    while (read(fdC, &c, sizeof (CITA)) != 0) {
        if (c.clv == x && c.status == activo) {
            mostrarCita(c);
            i++;
        }
        x++;
    }
}

/**
 * Muestra los registros e informacion del archivo "citas.txt" siempre y cuando su status sea activo y su conclusion este definida como "por realizarse"
 * @param fdC
 */
void citasPorRealizar(int fdC) {
    CITA c;
    int x = 1,i=0;
    lseek(fdC, 0, SEEK_SET);
    while (read(fdC, &c, sizeof (CITA)) != 0) {
        if (c.clv == x && c.status == activo && strcmp(c.conclusion, "Por realizarse") == 0) {
            if(i==0){
          printf("\nLista de Citas por realizar\nClave cita:\tClave de servicio:\tSolicitante:\t\tPaciente:\tConclusion:\t\tFecha:\t\tHora:\n");
            }
            mostrarCita(c);
            i++;
        }
        x++;
    }
    if(i==0){
        printf("\nNo existen citas por realizarse\n");
    }
}

/**
 * Realiza una baja fisica del archivo "servicios.txt" por medio de la clave ingresada por el usuario 
 * @param fdS
 * @param fdC
 */
void bajaFisicaServicio(int fdS, int fdC) {
    SERVICIO svc;
    char clave[35], op[15];
    int x = 1, b = 0, fdAux;
    if (lseek(fdS, 0, SEEK_END) != 0) {
        printf("\nEliminar servicio\n ");
        b = ingresarClave(clave);
        if (b == 0) {
            lseek(fdS, (atoi(clave) - 1) * sizeof (SERVICIO), SEEK_SET);
            read(fdS, &svc, sizeof (SERVICIO));
            if (svc.clv == atoi(clave)) {
                b = disponibilidadCita(clave, fdC);
                if (b == 0) {
                    printf("\nServicio\nClave\t\tNombre:\t\tCosto:\t\tDescripcion:\n%-16d%-16s%-16.2f%-20s\n", svc.clv, svc.nombre, svc.costo, svc.descrip);
                    printf("Dar de baja:");
                    b = continuar();
                    if (b == 1) {
                        fdAux = abrirArchivo("servicioCopia.txt");
                        lseek(fdS, 0, SEEK_SET);
                        while (read(fdS, &svc, sizeof (SERVICIO)) != 0) {
                            if (svc.clv != atoi(clave) && x == svc.clv) {
                                lseek(fdAux, (svc.clv - 1) * sizeof (SERVICIO), SEEK_SET);
                                write(fdAux, &svc, sizeof (SERVICIO));
                            }
                            x++;
                        }
                        close(fdS);
                        if (unlink("servicio.txt") == -1) {
                            printf("Error al abrir archivo de servicio");
                            exit(1);
                        }
                        close(fdAux);
                        rename("servicioCopia.txt", "servicio.txt");
                        fdS = abrirArchivo("servicio.txt");
                        printf("\nEliminacion exitosa\n\n");
                    } else {
                        printf("\nEl producto no se eliminara\n\n");
                    }
                } else {
                    printf("No se puede eliminar puesto que por lo menos hay una cita con este servicio por realizarse\n");
                }
            } else {
                printf("\nNo se encontro el servicio ingresado\n");
            }
        }
    } else {
        printf("\nLa veterinaria no ofrece servicios por el momento para entrar a esta opcion\n");
    }
}

/**
 * Menu en el cual muestra las opciones con las cuales el usuario puede realizar modificaciones a los registros de el archivo "citas.txt" 
 * @param fdC
 */
void menuModificarCita(int fdC) {
    char opA[10];
    int b;
     if (verificarContenidoCitas(fdC) == 1) {
        do {
            b = 0, opA[0] = '\0';
            printf("\nModificacion de citas\n1.-Eliminar cita\n2.-Concluir cita\n3.-Reprogramar cita\n4.-Regresar\nOPCION: ");
            scanf("%[^\n]", opA);
            while (getchar() != '\n');
            if (strlen(opA) > 1) {
                printf("\nOpcion invalida\n\n");
                b = -1;
            }
            if (b == 0) {
                switch (atoi(opA)) {
                    case 1:
                        bajaLogicaCita(fdC);
                        break;
                    case 2:
                        concluirCita(fdC);
                        break;
                    case 3:
                        reprogramarCita(fdC);
                        break;
                    case 4:
                        printf("\nRegresando...\n");
                        break;
                    default:
                        printf("\nOpcion invalida\n\n");
                }
            }

        } while (atoi(opA) != 4);
    } else {
        printf("\nLa veterinaria no cuenta con citas por el momento para entrar a esta opcion\n");
    }
}

/**
 * Realiza una baja logica del archivo "citas.txt" por medio de la clave ingresada por el usuario.
 * Se modificara el status a 0 si se decio eliminarlo.
 * @param fdC
 */
void bajaLogicaCita(int fdC) {
    CITA c;
    char clave[35];
    int b = 0;
    printf("\nRealizar baja\n");
    b = ingresarClave(clave);
    if (b == 0) {
        lseek(fdC, (atoi(clave) - 1) * sizeof (CITA), SEEK_SET);
        read(fdC, &c, sizeof (CITA));
        if (c.clv == atoi(clave) && c.status == activo) {
            if (strcmp(c.conclusion, "Concluida") == 0) {
                printf("\nCita:\nClave cita:\tClave de servicio:\tSolicitante:\t\tPaciente:\tConclusion:\t\tFecha:\t\tHora:\n");
                mostrarCita(c);
                b = continuar();
                if (b == 1) {
                    c.status = inactivo;
                    lseek(fdC, (atoi(clave) - 1) * sizeof (CITA), SEEK_SET);
                    write(fdC, &c, sizeof (CITA));
                    printf("\nEliminacion exitosa\n");
                } else if (b == 2) {
                    printf("\nSe ha cancelado la eliminacion...\n");
                }
            } else {
                printf("\nLa cita ingresada aun no sea concluido\n");
            }
        } else {
            printf("\nNo se encontro la cita ingresada\n");
        }
    }
}

/**
 * Concluye la cita programa en el archivo "citas.txt" segun la clave ingresada por el usuario y siempre y cuando en su conclusion este defindo con: "por realizarse"
 * @param fdC
 */
void concluirCita(int fdC) {
    CITA c;
    char clave[35];
    int b = 0;
    printf("\nConcluir cita\n");
    b = ingresarClave(clave);
    if (b == 0) {
        lseek(fdC, (atoi(clave) - 1) * sizeof (CITA), SEEK_SET);
        read(fdC, &c, sizeof (CITA));
        if (c.clv == atoi(clave) && c.status == activo) {
            if (strcmp(c.conclusion, "Por realizarse") == 0) {
                printf("\nCita:\nClave cita:\tClave de servicio:\tSolicitante:\t\tPaciente:\tConclusion:\t\tFecha:\t\tHora:\n");
                mostrarCita(c); //Valida que si cambia la fecha la hora anterior al no ser modificado no se traslape con otra
                b = continuar();
                if (b == 1) {
                    strcpy(c.conclusion, "Concluida");
                    lseek(fdC, (atoi(clave) - 1) * sizeof (CITA), SEEK_SET);
                    write(fdC, &c, sizeof (CITA));
                    printf("\nProceso exitoso\n");
                } else if (b == 2) {
                    printf("\nSe ha cancelado el concluir la cita...\n");
                }
            } else {
                printf("\nLa cita ingresada ya antes ha sido concluida\n");
            }
        } else {
            printf("\nNo se encontro la cita ingresada\n");
        }
    }
}

/**
 * Permite cambiar la hora y fecha definida en un registro del archivo "citas.txt" 
 * @param fdC
 */
void reprogramarCita(int fdC) {
    CITA c;
    char clave[35];
    int b = 0;
    printf("\nReprogramar cita\n");
    b = ingresarClave(clave);
    if (b == 0) {
        lseek(fdC, (atoi(clave) - 1) * sizeof (CITA), SEEK_SET);
        read(fdC, &c, sizeof (CITA));
        if (c.clv == atoi(clave) && c.status == activo) {
            if (strcmp(c.conclusion, "Por realizarse") == 0) {
                printf("\nCita:\nClave cita:\tClave de servicio:\tSolicitante:\t\tPaciente:\tConclusion:\t\tFecha:\t\tHora:\n");
                mostrarCita(c);
                printf("\nSi desea no realizar alguna modificacion ya sea hora o fecha ingrese ENTER\n");
                programarCita(&c, fdC, 2);
                lseek(fdC, (atoi(clave) - 1) * sizeof (CITA), SEEK_SET);
                write(fdC, &c, sizeof (CITA));
                printf("\nModificacion exitosa\n");
            } else {
                printf("\nLa cita ingresada ya antes ha sido concluida\n");
            }
        } else {
            printf("\nNo se encontro la cita ingresada\n");
        }
    }
}

/**
 * Abre por el nombre del archivo, de caso contrario al impedirlo retornara un -1
 * @param nombreArchivo
 * @return 
 */
int abrirArchivo(char nombreArchivo[]) {
    int fd;
    fd = open(nombreArchivo, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    return fd;
}

/**
 *Realiza la confirmacion de alguna accion que se procedera a realizar en la cual el usuario decidira
 * @return 
 */
int continuar() {
    char op[15];
    int b;
    do {
        b = 0, op[0] = '\0';
        printf("\nIngrese la confirmacion[SI/NO]: ");
        scanf("%[^\n]", op);
        while (getchar() != '\n');
        if (strcasecmp(op, "SI") == 0) {
            b = 1;
        } else if (strcasecmp(op, "NO") == 0) {
            b = 2;
        } else {
            printf("\nIngrese una opcion valida [SI/NO]\n\n");
            b = -1;
        }
    } while (b == -1);
    return b;
}

/**
 * Muestra la informacion de el registro que se consulta en el archivo "citas.txt"
 * @param c
 */
void mostrarCita(CITA c) {
    printf("%-16d%-24d%-24s%-15s%-25s", c.clv, c.clvServicio, c.nombreSolicitante, c.nombrePaciente, c.conclusion);
    if (c.fH.dia <= 9) {
        printf("0%d-", c.fH.dia);
    } else {
        printf("%d-", c.fH.dia);
    }
    if (c.fH.mes <= 9) {
        printf("0%d-", c.fH.mes);
    } else {
        printf("%d-", c.fH.mes);
    }
    printf("%-10d", c.fH.anio);
    if (c.fH.hr <= 9) {
        printf("0%d:", c.fH.hr);
    } else {
        printf("%d:", c.fH.hr);
    }
    if (c.fH.min <= 9) {
        printf("0%d\n", c.fH.min);
    } else {
        printf("%d\n", c.fH.min);
    }
}

/**
 * Verifica que la hora ingresado no se traslape con otro registrado en el mismo dia en el archivo "citas.txt"
 * @param c
 * @param fd
 * @return 
 */
int verficarCita(CITA c, int fd) {
    CITA aux;
    int b = 0;
    lseek(fd, 0, SEEK_SET);
    while (read(fd, &aux, sizeof (CITA)) != 0 && b == 0) {
        if (aux.clv != c.clv) {
            if (aux.status == activo) { //Verifica primero que la cita en analisis este activa para verificar su hora de cita
                if (aux.fH.dia == c.fH.dia && aux.fH.mes == c.fH.mes && aux.fH.anio == c.fH.anio) { //Verifica si las dos fechas coinciden para verificar su horario de cita
                    if (aux.fH.hr == c.fH.hr + 1) {//Verifica si la hora analizada es igual a la nueva hora si le suma 1 por lo cual se puede traslapar 
                        if ((aux.fH.min - c.fH.min) < 0) { //Si el resultado es negativo la hora de la cita se traslapa con otra
                            b = -1;
                        }
                    } else if (aux.fH.hr + 1 == c.fH.hr) { //Verifica si la hora analizada se le suma 1 y es igual a la nueva hora la cual se puede traslapar 
                        if ((aux.fH.min - c.fH.min) > 0) { //Si el resultado es positivo la hora de la cita se traslapa con otra
                            b = -1;
                        }
                    } else if (aux.fH.hr == c.fH.hr) { //Al ser la misma hora y descartarse las otras condiciones significara que se traslapan las horas
                        b = -1;
                    }
                }
            }
        }
    }
    if (b == -1) {
        printf("\nLa hora ingresada se traslapa con la realizacion de otra cita ya programada\n");
    }
    return b;
}

/**
 * Verifica si la conclusion del registrado analizado del archivo "citas.txt" aun se encuentra en: "por realizarse"
 * @param clave
 * @param fdC
 * @return 
 */
int disponibilidadCita(char clave[], int fdC) {
    CITA c;
    int b = 0;
    lseek(fdC, 0, SEEK_SET);
    while (read(fdC, &c, sizeof (CITA)) != 0 && b == 0) {
        if (atoi(clave) == c.clvServicio) {
            if (c.status == activo) {
                if (strcmp(c.conclusion, "Por realizarse") == 0) {
                    b = 1;
                }
            }
        }
    }
    return b;
}

/**
 * Verifica que el formato ingresado de la fecha sea correcto
 * @param cadena
 * @return 
 */
int validarFormatoFecha(char cadena[]) {
    int i = 0, b = 0;
    while (cadena[i] != '\0' && b == 0) {
        if (isdigit(cadena[i]) == 0) {
            if (i == 2 || i == 5) {
                if (cadena[i] != '-') {
                    b = -1;
                }
            } else {
                b = -1;
            }
        }
        i++;
    }
    if (strlen(cadena) != 10 || b == -1) {
        printf("\nIngrese la fecha de la cita correctamente con el formato dd-mm-aaaa\n");
        b = -1;
    }
    return b;
}

/**
 * Permite el ingreso de la clave y realiza su validacion.Se utiliza en los dos archivos "citas.txt" y "servicios.txt"
 * @param clave
 * @return 
 */
int ingresarClave(char clave[]) {
    int b = 0;
    clave[0] = '\0';
    printf("Ingrese la clave: ");
    scanf("%[^\n]", clave);
    while (getchar() != '\n');
    if (validacionIngreso(clave, 1) == -1 || atoi(clave) < 1 || strlen(clave) == 0) {
        printf("\nIngrese una opcion valida y que sea solo numerica con decimales enteros\n");
        b = -1;
    }
    return b;
}

/**
 * Valida el formato ingresado de la hora sea correcto
 * @param cadena
 * @return 
 */
int validarFormatoHora(char cadena[]) {
    int i = 0, b = 0;
    while (cadena[i] != '\0' && b == 0) {
        if (strlen(cadena) == 5) {
            if (isdigit(cadena[i]) == 0) {
                if (i == 2) {
                    if (cadena[i] != ':') {
                        b = -1;
                    }
                } else {
                    b = -1;
                }
            }
        } else if (strlen(cadena) == 4) {
            if (isdigit(cadena[i]) == 0) {
                if (i == 1) {
                    if (cadena[i] != ':') {
                        b = -1;
                    }
                } else {
                    b = -1;
                }
            }
        }
        i++;
    }
    if (strlen(cadena) != 5 && strlen(cadena) != 4 || b == -1) {
        printf("\nIngrese la hora de la cita correctamente con el formato hh:mm \n");
        b = -1;
    }
    return b;
}

/**
 * Valida los valores ingresados de la fecha en las secciones de dia-mes-año
 * @param cadena
 * @param op
 * @return 
 */
int validarIngresoFecha(char cadena[], int op) {
    char dato[10];
    if (op == 1) { //Opcion de dia
        dato[0] = cadena[0], dato[1] = cadena[1], dato[2] = '\0';
        if (atoi(dato) > 31 || atoi(dato) == 0) {
            strcpy(dato, "-1");
            printf("\nIngrese el dia correctamente\n");
        }
    } else if (op == 2) { //Opcion de mes
        dato[0] = cadena[3], dato[1] = cadena[4], dato[2] = '\0';
        if (atoi(dato) > 12 || atoi(dato) == 0) {
            strcpy(dato, "-1");
            printf("\nIngrese el mes correctamente\n");
        }
    } else if (op == 3) { //Opcion de año
        dato[0] = cadena[6], dato[1] = cadena[7], dato[2] = cadena[8], dato[3] = cadena[9], dato[4] = '\0';
        if (atoi(dato) == 0 || atoi(dato) <= 2000) {
            strcpy(dato, "-1");
            printf("\nIngrese el año correctamente y que sea un año mayor al año 2000\n");
        }
    }
    return atoi(dato);
}

/**
 * Valida las secciones de la hora en las secciones hora:minuto
 * @param cadena
 * @param op
 * @param hora
 * @return 
 */
int validarIngresoHora(char cadena[], int op, int hora) {
    char dato[10];
    if (op == 1) { //Opcion de hora
        if (strlen(cadena) == 5) {
            dato[0] = cadena[0];
            dato[1] = cadena[1];
            dato[2] = '\0';
        } else if (strlen(cadena) == 4) {
            dato[0] = cadena[0];
            dato[1] = '\0';
        }
        if (atoi(dato) > 20 || atoi(dato) < 8) {
            strcpy(dato, "-1");
            printf("\nIngrese la hora correctamente\nCompruebe que la hora solicitada corresponda entre el horario de atencion de 8:00 a 21:00hrs(duracion de cita 1 hr)\n");
        }
    } else if (op == 2) { //Opcion de minuto
        if (strlen(cadena) == 5) {
            dato[0] = cadena[3];
            dato[1] = cadena[4];
            dato[2] = '\0';
        } else if (strlen(cadena) == 4) {
            dato[0] = cadena[2];
            dato[1] = cadena[3];
            dato[2] = '\0';
        }
        if (hora == 20) {
            if (atoi(dato) != 0) {
                strcpy(dato, "-1");
                printf("\nVerifique que haya por lo menos 1 hora de diferencia antes de acabar la hora de atencion la cual es hasta las 21:00 hrs\n");
            }
        } else if (atoi(dato) > 59) {
            strcpy(dato, "-1");
            printf("\nIngrese el minuto correctamente\n");
        }
    }
    return atoi(dato);
}

/**
 * Comprueba que si en el archivo de "citas.txt" se encuentra por lo menos una cita con status de activo
 * @param fdC
 * @return 
 */
int verificarContenidoCitas(int fdC) {
    CITA c;
    int x = 1,b=0;
    lseek(fdC, 0, SEEK_SET);
    while (read(fdC, &c, sizeof (CITA)) != 0 && b==0) {
        if (c.clv == x && c.status==activo) {
            b=1;
        }
        x++;
    }
    return b;
}

/**
 * Valida los valores ingresados por el usuario cuando ingresa en el archivo 
 * @param cadena
 * @param op
 * @return 
 */
int validacionIngreso(char cadena[], int op) {
    int i = 0, b = 0, k = 0;
    if (op == 1) { //Permitir solo el ingreso de numeros sin decimales
        while (cadena[i] != '\0' && b == 0) {
            if (isdigit(cadena[i]) == 0) {
                b = -1;
            }
            i++;
        }
    } else if (op == 2) { //Valida el ingreso de letras con espacios
        while (cadena[i] != '\0' && b == 0) {
            if (isalpha(cadena[i]) == 0) {
                if (isspace(cadena[i]) == 0) {
                    b = -1;
                }
            }
            i++;
        }
        if (isspace(cadena[i - 1]) != 0 && b == 0) {//Valida que el ultimo no sea un espacio
            b = -1;
        }
    } else if (op == 3) { //Permitir solo el ingreso de numeros con decimales
        while (cadena[i] != '\0' && b == 0) {
            if (isdigit(cadena[i]) == 0) {
                if (cadena[i] != '.') {
                    b = -1;
                } else {
                    k++;
                }
                if (k > 1) //Se ingreso mas de 2 puntos decimales
                {
                    b = -1;
                }
            }
            i++;
        }
    }
    return b;
}