  /*
 * Una empresa de renta de automóviles en Mexicali necesita un sistema para mejorar el control y
 * organización en la renta de sus automóviles.
 */

/* 
 * Author: Inzunza Rodriguez Kevin Giovani
 * Created on 27 de marzo de 2020, 01:34 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct fechaDevolucion {
    int anio;
    int mes;
    int dia;
};
struct historialRenta {
    struct fechaDevolucion fecha;
    char nombre[30];
   long int numTelefono;
    int kilomEntregado;
};
struct automovil {
    struct historialRenta historial[35];
    char numPlacas[25];
    char color[25];
    char modelo[25];
    char marca[25];
    int anioAuto;
    int kilometraje;
    char estado[25];
    int contFecha;
};
char menu();
void altas(struct automovil carro[], int *cont);
void baja(struct automovil carro[], int *cont);
void menuConsultas(struct automovil carro[], int cont);
void consultaGeneral(struct automovil carro[], int cont);
void consultaEspecifica(struct automovil carro[], int cont);
void consultaRenta(struct automovil carro[], int cont);
void consultaPorKm(struct automovil carro[], int cont);
void consultaHistorialEspecifico(struct automovil carro[], int cont);
void menuModificacion(struct automovil carro[], int cont);
void modificar(struct automovil *carro, int tipo, char mod[]);
void menuRentaYDevolucion(struct automovil carro[], int cont);
void renta(struct automovil carro[], int cont);
void devolucion(struct automovil carro[], int cont);
void ordenarKm(struct automovil carro[], int cont);
/*
 * 
 */
int main(int argc, char** argv) {
    struct automovil carro[30];
    char op;
    int cont;
    do {
        op = '\0';
        op = menu();
        switch (op) {
            case 'A':
                altas(carro, &cont);
                break;
            case 'B':
                baja(carro, &cont);
                break;
            case 'C':
                menuConsultas(carro, cont);
                break;
            case 'D':
                menuModificacion(carro, cont);
                break;
            case 'E':
                menuRentaYDevolucion(carro, cont);
                break;
            case 'F':
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nOpcion invalida\n");
        }
    } while ((op) != 'F');
    return (EXIT_SUCCESS);
}
/**
 * Muestra el menu principal de las renta de autos
 * @return 
 */
char menu() {
    char op1[15];
    int b, i;
    do {
        op1[0] = '\0',b = 0;
        printf("\n\nEmpresa de automoviles Mexicali\nA.-Altas\nB.-Bajas\nC.-Consultas\nD.-Modificaciones\nE.-Renta y devolucion de automoviles\nF.-Salir\nOpcion: ");
        scanf("%[^\n]", op1);
        while (getchar() != '\n');
        if (strlen(op1) > 1) {
            b = 1;
        } else {
            i = 0;
            while (op1[i] != '\0') {
                if (isalpha(op1[i]) == 0) {
                    b = 1;
                }
                i++;
            }
        }
        if (b == 1 ) {
            printf("\nSolo ingrese alguna de las opciones disponibles\n");
            b = 1;
        }
    } while (b == 1);
    return toupper(op1[0]);
}
/**
 * Hace que el usuario pueda dar de alta algun auto que tenga disponible
 * @param carro
 * @param cont
 */
void altas(struct automovil carro[], int *cont) {
    char numPlacas[25], color[25], modelo[25], marca[25], aux[25];
    int anioAuto, b, i, kilometraje;
    do {
        numPlacas[0] = '\0',i = 0, b = 0;
        printf("\nIngrese el numero de placa del auto: ");
        scanf("%[^\n]", numPlacas);
        while (getchar() != '\n');
        while (numPlacas[i] != '\0' && b == 0) {
            if (isalnum(numPlacas[i]) == 0) {
                b = 2;
            }
            i++;
        }
        i = 0;
        if (b == 0) {
            while (i<*cont && b == 0) {
                if (strcasecmp(carro[i].numPlacas, numPlacas) == 0) {
                    b = 1;
                }
                i++;
            }
        }
        if (b == 1) {
            printf("\nEl numero de placas ingresado se repite con otra placa ingresada anteriormente\n");
        } else if (b == 2) {
            printf("\nNOTA:Solo se permiten numeros o letras como placa de automovil\n");
        } else if (strlen(numPlacas) < 1 || isspace(numPlacas[0]) != 0) {
            printf("\nIngrese un numero de placas de automovil valido\n");
            b = 1;
        }
    } while (b == 1 || b == 2);
    do {
        color[0] = '\0',i = 0, b = 0;
        printf("\nIngrese el color del auto: ");
        scanf("%[^\n]", color);
        while (getchar() != '\n');
        while (color[i] != '\0' && b == 0) {
            if (isalpha(color[i]) == 0) {
                if (isspace(color[i]) == 0) {
                    b = 1;
                }
            }
            i++;
        }
        if (strlen(color) < 1 || isspace(color[0]) != 0 || b == 1) {
            printf("\nIngrese un color de automovil valido\n");
            b = 1;
        }
    } while (b == 1);
    do {
        modelo[0] = '\0',i = 0, b = 0;
        printf("\nIngrese el modelo del auto: ");
        scanf("%[^\n]", modelo);
        while (getchar() != '\n');
        while (modelo[i] != '\0' && b == 0) {
            if (isalnum(modelo[i]) == 0) {
                if (isspace(modelo[i]) == 0) {
                    b = 1;
                }
            }
            i++;
        }
        if (strlen(modelo) < 1 || isspace(modelo[0]) != 0 || b == 1) {
            printf("\nIngrese un modelo de automovil valido\n");
            b = 1;
        }
    } while (b == 1);
    do {
        marca[0] = '\0',i = 0, b = 0;
        printf("\nIngrese la marca del auto: ");
        scanf("%[^\n]", marca);
        while (getchar() != '\n');
        while (marca[i] != '\0' && b == 0) {
            if (isalpha(marca[i]) == 0) {
                if (isspace(marca[i]) == 0) {
                    b = 1;
                }
            }
            i++;
        }
        if (b == 1) {
            printf("\nIngrese una marca valida\n");
        } else if (strlen(marca) < 1 || isspace(marca[0]) != 0) {
            printf("\nIngrese una marca de automovil valido\n");
            b = 1;
        }
    } while (b == 1);
    do {
        aux[0] = '\0',i = 0, b = 0;
        printf("\nIngrese el año del auto: ");
        scanf("%[^\n]", aux);
        while (getchar() != '\n');
        while (aux[i] != '\0' && b == 0) {
            if (isdigit(aux[i]) == 0) {
                b = 1;
            }
            i++;
        }
        if (strlen(aux) < 1 || atoi(aux) == 0 || b == 1 || atoi(aux) > 9999 || atoi(aux) < 1886) {
            printf("\nIngrese un año valido y que sea apartir del año 1886 en adelante en formato aaaa(4 digitos)\n");
            b = 1;
        }
    } while (b == 1);
    anioAuto = atoi(aux);
    do {
        aux[0] = '\0',b = 0, i = 0;
        printf("\nIngrese el kilometraje del auto: ");
        scanf("%[^\n]", aux);
        while (getchar() != '\n');
        while (aux[i] != '\0' && b == 0) {
            if (isdigit(aux[i]) == 0) {
                b = 1;
            }
            i++;
        }
        if (strlen(aux) < 1 || atoi(aux) == 0 || b == 1) {
            printf("\nIngrese un kilometraje valido\n");
            b = 1;
        }
    } while (b == 1);
    kilometraje = atoi(aux);
    strcpy(carro[*cont].numPlacas, numPlacas);
    strcpy(carro[*cont].color, color);
    strcpy(carro[*cont].modelo, modelo);
    strcpy(carro[*cont].marca, marca);
    carro[*cont].anioAuto = anioAuto;
    carro[*cont].kilometraje = kilometraje;
    strcpy(carro[*cont].estado, "Disponible");
    carro[*cont].contFecha = 0;
    (*cont)++;
    printf("\n-Registro de automovil completado\n");
}
/**
 * Da de baja el auto para que ya no aparezca disponible para su uso
 * @param carro
 * @param cont
 */
void baja(struct automovil carro[], int *cont) {
    char numPlacas[35], conf[10];
    int b, i, j;
    if (*cont > 0) {
        numPlacas[0] = '\0',i = 0, b = 0;
        printf("\nIngrese el numero de placa del auto a dar de baja: ");
        scanf("%[^\n]", numPlacas);
        while (getchar() != '\n');
        while (i < *cont && b == 0) {
            if (strcasecmp(carro[i].numPlacas, numPlacas) == 0) {
                b = 1;
            }
            i++;
        }
        if (strlen(numPlacas) < 1) {
            printf("\nIngrese un numero de placas de automovil valido\n");
        } else if (b == 0) {
            printf("\nEl numero de placas ingresado no ha sido registrado\n");
            b = 2;
        } else if (b == 1) //Si existe, ahora hay que revisar que se desea eliminar
        {
            j = i - 1;
            if (strcasecmp(carro[j].estado, "Disponible") == 0) {
                do {
                    b = 0;
                    printf("\nConfirmacion de eliminacion de automovil\n¿Desea eliminarlo?[SI/NO]: ");
                    scanf("%[^\n]", conf);
                    while (getchar() != '\n');
                    if (strcasecmp(conf, "si") == 0) {
                        b = 2;
                    } else if (strcasecmp(conf, "no") == 0) {
                        printf("\nUsted ha decidido no eliminar el automovil\n");
                    } else {
                        printf("\nIngrese una opcion valida,para confirmar ingrese SI, para no eliminar ingrese NO\n");
                        b = 1;
                    }
                } while (b == 1);
                if (b == 2) {
                    (*cont)--;
                    while (j<*cont) {
                        carro[j] = carro[j + 1];
                        j++;
                    }
                    printf("\nUsted ha decidido eliminar el automovil.ELIMINACION EXITOSA!\n");
                }
            } else {
                printf("\nEl automovil elegido no esta disponible para darse de baja porque esta rentado\n");
            }
        }
    } else {
        printf("\nNo existen automoviles dados de alta\n");
    }
}
/**
 * Submenu para visualizar las tipos de consultas disponibles
 * @param carro
 * @param cont
 */
void menuConsultas(struct automovil carro[], int cont) {
    char aux[15];
    int op, b, i;
    if (cont > 0) {
        do {
            op = 0, b = 0, i = 0,aux[0] = '\0';
            printf("\n\nRealizar consulta por:\n1.-Consulta general\n2.-Consulta especifica\n3.-Consulta de autos en renta\n4.-Consulta general ordenada por kilometraje\n5.-Consulta de historial de renta de algun auto especifico\n6.-Regresar al menu principal\nOPCION: ");
            scanf("%[^\n]", aux);
            while (getchar() != '\n');
            while (aux[i] != '\0' && b == 0) {
                if (aux[i] == '.') {
                    b = 1;
                }
                i++;
            }
            if (strlen(aux) > 1 || atoi(aux) == 0 || b == 1) {
                printf("\nIngrese una opcion valida\n");
                b = 1;
            }
            if (b == 0) {
                op = atoi(aux);
                switch (op) {
                    case 1:
                        consultaGeneral(carro, cont);
                        break;
                    case 2:
                        consultaEspecifica(carro, cont);
                        break;
                    case 3:
                        consultaRenta(carro, cont);
                        break;
                    case 4:
                        consultaPorKm(carro, cont);
                        break;
                    case 5:
                        consultaHistorialEspecifico(carro, cont);
                        break;
                    case 6:
                        printf("\nRegresando al menu principal...\n");
                        break;
                    default:
                        printf("\nIngrese una opcion valida\n");
                        b = 1;
                }
            }
        } while (b == 1 || atoi(aux) != 6);
    } else {
        printf("\nNo existen automoviles dados de alta para consultar\n");
    }
}
/**
 * Muestra todos los autos con sus datos y detalles del historial de cada uno si esta disponible
 * @param carro
 * @param cont
 */
void consultaGeneral(struct automovil carro[], int cont) {
    int i, j, k;
    printf("\nConsulta general:");
    for (i = 0; i < cont; i++) {
        printf("\nNUMERO DE PLACA:%s  COLOR:%s  MODELO:%s  MARCA:%s  AÑO:%d  KILOMETRAJE:%d km  ESTADO:%s", carro[i].numPlacas, carro[i].color, carro[i].modelo, carro[i].marca, carro[i].anioAuto, carro[i].kilometraje, carro[i].estado);
        if (carro[i].contFecha > 0) {
            j = carro[i].contFecha;
            printf("\nHISTORIAL DE RENTA DEL AUTO CON NUMERO DE PLACA %s:\n", carro[i].numPlacas);
            printf("Rentado por:\t\tNum.telefono:\tKilometraje al ser entregado:\tFechaDevolucion\n");
            for (k = 0; k < j; k++) {
                printf("%-24s%-28ld%-23d", carro[i].historial[k].nombre, carro[i].historial[k].numTelefono, carro[i].historial[k].kilomEntregado);
                if (carro[i].historial[k].fecha.dia <= 9) {
                    printf("0%d-", carro[i].historial[k].fecha.dia);
                }else {
                    printf("%d-", carro[i].historial[k].fecha.dia);
                }
                if (carro[i].historial[k].fecha.mes <= 9) {
                    printf("0%d-", carro[i].historial[k].fecha.mes);
                } else {
                    printf("%d-", carro[i].historial[k].fecha.mes);
                }
                printf("%d\n", carro[i].historial[k].fecha.anio);
            }
        } else {
            printf("\nEL AUTOMOVIL CON NUMERO DE PLACA %s NO CUENTA CON HISTORIAL DE RENTA POR EL MOMENTO\n", carro[i].numPlacas);
        }
    }
}
/**
 * Muestra los datos de un auto en especifico con su historial si esta disponible
 * @param carro
 * @param cont
 */
void consultaEspecifica(struct automovil carro[], int cont) {
    char numPlacas[35];
    int b = 0, i = 0, j, k;
    printf("\nIngrese el numero de placa del auto a consultar: ");
    scanf("%[^\n]", numPlacas);
    while (getchar() != '\n');
    while (i < cont && b == 0) {
        if (strcasecmp(carro[i].numPlacas, numPlacas) == 0) {
            b = 1;
        }
        i++;
    }
    if (strlen(numPlacas) < 1) {
        printf("\nIngrese un numero de placas de automovil valido\n");
    } else if (b == 0) {
        printf("\nEl numero de placas ingresado no ha sido registrado\n");
        b = 2;
    } else if (b == 1) {
        i--;
        printf("\nNUMERO DE PLACA:%s  COLOR:%s  MODELO:%s  MARCA:%s  AÑO:%d  KILOMETRAJE:%d km  ESTADO:%s", carro[i].numPlacas, carro[i].color, carro[i].modelo, carro[i].marca, carro[i].anioAuto, carro[i].kilometraje, carro[i].estado);
        if (carro[i].contFecha > 0) {
            j = carro[i].contFecha;
            printf("\nHISTORIAL DE RENTA DEL AUTO CON NUMERO DE PLACA %s:\n", carro[i].numPlacas);
            printf("Rentado por:\t\tNum.telefono:\tKilometraje al ser entregado:\tFechaDevolucion\n");
            for (k = 0; k < j; k++) {
                printf("%-24s%-28ld%-23d", carro[i].historial[k].nombre, carro[i].historial[k].numTelefono, carro[i].historial[k].kilomEntregado);
                if (carro[i].historial[k].fecha.dia <= 9) {
                    printf("0%d-", carro[i].historial[k].fecha.dia);
                } else {
                    printf("%d-", carro[i].historial[k].fecha.dia);
                }
                if (carro[i].historial[k].fecha.mes <= 9) {
                    printf("0%d-", carro[i].historial[k].fecha.mes);
                } else {
                    printf("%d-", carro[i].historial[k].fecha.mes);
                }
                printf("%d\n", carro[i].historial[k].fecha.anio);
            }
        } else {
            printf("\nEL AUTOMOVIL CON NUMERO DE PLACA %s NO CUENTA CON HISTORIAL DE RENTA POR EL MOMENTO\n", carro[i].numPlacas);
        }
    }
}
/**
 * Muestra los datos de renta de aquellos autos los cuales su estado es "en renta"
 * @param carro
 * @param cont
 */
void consultaRenta(struct automovil carro[], int cont) {
    int i, j, k = 0;
    printf("\nConsulta de autos en renta:");
    for (i = 0; i < cont; i++) {
        if (strcasecmp(carro[i].estado, "En renta") == 0) {
            j = carro[i].contFecha - 1;
            printf("\nAUTO EN RENTA CON NUMERO DE PLACA %s:\n", carro[i].numPlacas);
            printf("Rentado por:\t\tNum.telefono:\tFechaDevolucion\n");
            printf("%-24s%-18ld", carro[i].historial[j].nombre, carro[i].historial[j].numTelefono);
            if (carro[i].historial[j].fecha.dia <= 9) {
                printf("0%d-", carro[i].historial[j].fecha.dia);
            } else {
                printf("%d-", carro[i].historial[j].fecha.dia);
            }
            if (carro[i].historial[j].fecha.mes <= 9) {
                printf("0%d-", carro[i].historial[j].fecha.mes);
            } else {
                printf("%d-", carro[i].historial[j].fecha.mes);
            }
            printf("%d\n", carro[i].historial[j].fecha.anio);
            k++;
        }
    }
    if (k == 0) {
        printf("\nPor el momento no existen autos en renta\n");
    }
}
/**
 * Muestra los datos de los autos ordenados por su kilometraje de menor a mayor
 * @param carro
 * @param cont
 */
void consultaPorKm(struct automovil carro[], int cont) {
    int i, j;
    struct automovil carroA[cont];
    for (j = 0; j < cont; j++) {
        carroA[j] = carro[j];
    }
    ordenarKm(carroA, cont);
    printf("\nConsulta general ordenada por kilometraje:");
    for (i = 0; i < cont; i++) {
        printf("\nNUMERO DE PLACA:%s  COLOR:%s  MODELO:%s  MARCA:%s  AÑO:%d  KILOMETRAJE:%d km  ESTADO:%s", carroA[i].numPlacas, carroA[i].color, carroA[i].modelo, carroA[i].marca, carroA[i].anioAuto, carroA[i].kilometraje, carroA[i].estado);
    }
}
/**
 * Muestra los datos de renta del auto buscado por el usuario y que al menos fuera rentado 1 vez
 * @param carro
 * @param cont
 */
void consultaHistorialEspecifico(struct automovil carro[], int cont) {
    char numPlacas[35];
    int b = 0, i = 0, j, k;
    printf("\nIngrese el numero de placa del auto a consultar: ");
    scanf("%[^\n]", numPlacas);
    while (getchar() != '\n');
    while (i < cont && b == 0) {
        if (strcasecmp(carro[i].numPlacas, numPlacas) == 0) {
            b = 1;
        }
        i++;
    }
    if (strlen(numPlacas) < 1) {
        printf("\nIngrese un numero de placas de automovil valido\n");
    } else if (b == 0) {
        printf("\nEl numero de placas ingresado no ha sido registrado\n");
        b = 2;
    } else if (b == 1) {
        i--;
        if (carro[i].contFecha > 0) {
            j = carro[i].contFecha;
            printf("\nHISTORIAL DE RENTA DEL AUTO CON NUMERO DE PLACA %s:\n", carro[i].numPlacas);
            printf("Rentado por:\t\tNum.telefono:\tKilometraje al ser entregado:\tFechaDevolucion\n");
            for (k = 0; k < j; k++) {
                printf("%-24s%-28ld%-23d", carro[i].historial[k].nombre, carro[i].historial[k].numTelefono, carro[i].historial[k].kilomEntregado);
                if (carro[i].historial[k].fecha.dia <= 9) {
                    printf("0%d-", carro[i].historial[k].fecha.dia);
                } else {
                    printf("%d-", carro[i].historial[k].fecha.dia);
                }
                if (carro[i].historial[k].fecha.mes <= 9) {
                    printf("0%d-", carro[i].historial[k].fecha.mes);
                } else {
                    printf("%d-", carro[i].historial[k].fecha.mes);
                }
                printf("%d\n", carro[i].historial[k].fecha.anio);
            }
        } else {
            printf("\nEL AUTOMOVIL CON NUMERO DE PLACA %s NO CUENTA CON HISTORIAL DE RENTA POR EL MOMENTO\n", carro[i].numPlacas);
        }
    }
}
/**
 * Muestre un submenu con los tipos de modificaciones disponibles
 * @param carro
 * @param cont
 */
void menuModificacion(struct automovil carro[], int cont) {
    char numPlacas[35], aux[15];
    int b = 0, i = 0, k, op;
    if (cont > 0) {
        printf("\nIngrese el numero de placa del auto a modificar: ");
        scanf("%[^\n]", numPlacas);
        while (getchar() != '\n');
        while (i < cont && b == 0) {
            if (strcasecmp(carro[i].numPlacas, numPlacas) == 0) {
                b = 1;
            }
            i++;
        }
        if (strlen(numPlacas) < 1) {
            printf("\nIngrese un numero de placas de automovil valido\n");
        } else if (b == 0) {
            printf("\nEl numero de placas ingresado no ha sido registrado\n");
            b = 2;
        } else if (b == 1) {
            i--;
            if (strcasecmp(carro[i].estado, "Disponible") == 0) {
                do {
                    op = 0, b = 0, k = 0,aux[0] = '\0';
                    printf("\nModificacion de automovil:\nNUMERO DE PLACA:%s  COLOR:%s  MODELO:%s  MARCA:%s  AÑO:%d  KILOMETRAJE:%d km\n", carro[i].numPlacas, carro[i].color, carro[i].modelo, carro[i].marca, carro[i].anioAuto, carro[i].kilometraje);
                    printf("1.-Marca\n2.-Modelo\n3.-Color\n4.-Año\n5.-Regresar al menu principal\nOPCION: ");
                    scanf("%[^\n]", aux);
                    while (getchar() != '\n');
                    while (aux[k] != '\0' && b == 0) {
                        if (aux[k] == '.') {
                            b = 1;
                        }
                        k++;
                    }
                    if (strlen(aux) > 1 || atoi(aux) == 0 || b == 1) {
                        printf("\nIngrese una opcion valida\n");
                        b = 1;
                    }
                    if (b == 0) {
                        op = atoi(aux);
                        switch (op) {
                            case 1:
                                modificar(&carro[i], 1, "marca");
                                break;
                            case 2:
                                modificar(&carro[i], 2, "modelo");
                                break;
                            case 3:
                                modificar(&carro[i], 3, "color");
                                break;
                            case 4:
                                modificar(&carro[i], 4, "año");
                                break;
                            case 5:
                                printf("\nRegresando al menu principal...\n");
                                break;
                            default:
                                printf("\nIngrese una opcion valida\n");
                                b = 1;
                        }
                    }
                } while (b == 1 || atoi(aux) != 5);
            } else {
                printf("\nEl auto no es candidato a ser modificado porque se encuentra en renta\n");
            }
        }
    } else {
        printf("\nNo existen automoviles dados de alta para realizar alguna modificacion\n");
    }
}
/**
 * Se encarga de realizar todas las modificaciones que el usuario realice
 * @param carro
 * @param tipo
 * @param mod
 */
void modificar(struct automovil *carro, int tipo, char mod[]) {
    char aux[35];
    int i, b;
    do {
        aux[0] = '\0',i = 0, b = 0;
        printf("\nIngrese la modificacion de %s del auto: ", mod);
        scanf("%[^\n]", aux);
        while (getchar() != '\n');
        if (tipo == 1 || tipo == 3) {
            while (aux[i] != '\0' && b == 0) {
                if (isalpha(aux[i]) == 0) {
                    if (isspace(aux[i]) == 0) {
                        b = 1;
                    }
                }
                i++;
            }
            if (b == 1) {
                printf("\nIngrese correctamente en el apartado de %s como corresponde\n", mod);
            }
        } else if (tipo == 4) {
            while (aux[i] != '\0' && b == 0) {
                if (isdigit(aux[i]) == 0) {
                    b = 1;
                }
                i++;
            }
            if (b == 1 || atoi(aux) > 9999 || atoi(aux) < 1886) {
                printf("\nIngrese un año valido y que sea apartir del año 1886 en adelante en formato aaaa(4 digitos)\n");
                b = 1;
            } else if (carro->contFecha > 0) {
                if (carro->historial[0].fecha.anio > atoi(aux)) {
                    printf("\nEl año del automovil no puede ser menor a la primera renta de el mismo\n");
                    b = 1;
                }
            }
        } else {
            while (aux[i] != '\0' && b == 0) {
                if (isalnum(aux[i]) == 0) {
                    if (isspace(aux[i]) == 0) {
                        b = 1;
                    }
                }
                i++;
            }
            if (b == 1) {
                printf("\nIngrese un modelo de auto valido\n");
            }
        }
        if (strlen(aux) < 1 || isspace(aux[0]) != 0) {
            b = 2;
        }
    } while (b == 1);
    if (b == 2) {
        printf("\nNo sea realizado ninguna modificacion\n");
    } else {
        if (tipo == 1) {
            strcpy(carro->marca, aux);
        } else if (tipo == 2) {
            strcpy(carro->modelo, aux);
        } else if (tipo == 3) {
            strcpy(carro->color, aux);
        } else {
            carro->anioAuto = atoi(aux);
        }
        printf("\nModificacion exitosa\n");
    }
}
/**
 * Submenu con las opciones para que el usuario pueda escoger entre renta y devolver algun auto
 * @param carro
 * @param cont
 */
void menuRentaYDevolucion(struct automovil carro[], int cont) {
    char aux[15];
    int op, b, i;
    if (cont > 0) {
        do {
            aux[0] = '\0',op = 0, b = 0, i = 0;
            printf("\nRenta y Devoluciones:\n1.-Renta\n2.-Devolucion\n3.-Regresar al menu principal\nOPCION: ");
            scanf("%[^\n]", aux);
            while (getchar() != '\n');
            while (aux[i] != '\0' && b == 0) {
                if (aux[i] == '.') {
                    b = 1;
                }
                i++;
            }
            if (strlen(aux) > 1 || atoi(aux) == 0 || b == 1) {
                printf("\nIngrese una opcion valida\n");
                b = 1;
            }
            if (b == 0) {
                op = atoi(aux);
                switch (op) {
                    case 1:
                        renta(carro, cont);
                        break;
                    case 2:
                        devolucion(carro, cont);
                        break;
                    case 3:
                        printf("\nRegresando al menu principal...\n");
                        break;
                    default:
                        printf("\nIngrese una opcion valida\n");
                        b = 1;
                }
            }
        } while (b == 1 || atoi(aux) != 3);
    } else {
        printf("\nNo existen automoviles dados de alta para realizar alguna renta o devolucion\n");
    }
}
/**
 * El usuario puede ingresar los datos para poder rentar el auto
 * @param carro
 * @param cont
 */
void renta(struct automovil carro[], int cont) {
    char numPlacas[15], nombreAux[30], numTelefonoAux[35], fechaDevolucion[35], anioAux[5], mesAux[3], diaAux[3];
    int b, i, j, contH;
    do {
        numPlacas[0] = '\0',i = 0, b = 0;
        printf("\nIngrese el numero de placa del auto a rentar: ");
        scanf("%[^\n]", numPlacas);
        while (getchar() != '\n');
        while (i < cont && b == 0) {
            if (strcasecmp(carro[i].numPlacas, numPlacas) == 0) {
                b = 1;
            }
            i++;
        }
        if (strlen(numPlacas) < 1) {
            printf("\nIngrese un numero de placas de automovil valido\n");
        } else if (b == 0) {
            printf("\nEl numero de placas ingresado no ha sido registrado\n");
            b = 2;
        }
    } while (b == 0);
    if (b == 1) //Si existe, ahora hay que revisar que tiene disponibilidad
    {
        j = i - 1;
        if (strcasecmp(carro[j].estado, "En renta") == 0) {
            printf("\nEl automovil elegido no esta disponible porque esta rentado\n");
        } else {
            contH = carro[j].contFecha;
            printf("\nAutomovil disponible\n");
            do {
                b = 0, i = 0,nombreAux[0] = '\0';
                printf("\nIngrese su nombre: ");
                scanf("%[^\n]", nombreAux);
                while (getchar() != '\n');
                while (nombreAux[i] != '\0' && b == 0) {
                    if (isalpha(nombreAux[i]) == 0) {
                        if (isspace(nombreAux[i]) == 0) {
                            printf("\nIngrese su nombre correctamente\n");
                            b = 1;
                        }
                    }
                    i++;
                }
                if (strlen(nombreAux) < 1 || isspace(nombreAux[0]) != 0) {
                    printf("\nIngrese su nombre correctamente\n");
                    b = 1;
                }
            } while (b == 1);
            do {
                b = 0, i = 0, numTelefonoAux[0] = '\0';
                printf("\nIngrese su numero de telefono: ");
                scanf("%[^\n]", numTelefonoAux);
                while (getchar() != '\n');
                while (numTelefonoAux[i] != '\0' && b == 0) {
                    if (isdigit(numTelefonoAux[i]) == 0) {
                        printf("\nIngrese su numero de telefono correctamente\n");
                        b = 1;
                    }
                    i++;
                }
                if (strlen(numTelefonoAux) < 1 || strlen(numTelefonoAux)>10) {
                    printf("\nIngrese su numero de telefono correctamente\n");
                    b = 1;
                }
            } while (b == 1);
            do {
                fechaDevolucion[0] = '\0', anioAux[0] = '\0', mesAux[0] = '\0', diaAux[0] = '\0',b = 0, i = 0;
                printf("\nIngrese la fecha de devolucion del auto en formato dd-mm-aaaa: ");
                scanf("%[^\n]", fechaDevolucion);
                while (getchar() != '\n');
                while (fechaDevolucion[i] != '\0' && b == 0) {
                    if (isdigit(fechaDevolucion[i]) == 0) {

                        if (i == 2 || i == 5) {
                            if (fechaDevolucion[i] != '-') {
                                b = 1;
                            }
                        } else {
                            b = 1;
                        }
                    }
                    i++;
                }
                if (strlen(fechaDevolucion) < 1 || strlen(fechaDevolucion) > 10 || b == 1) {
                    printf("\nIngrese la fecha de devolucion correctamente con el formato dd-mm-aaaa\n");
                    b = 1;
                }
                if (b == 0) {
                    diaAux[0] = fechaDevolucion[0];
                    diaAux[1] = fechaDevolucion[1];
                    diaAux[2] = '\0';
                    if (atoi(diaAux) > 0 && atoi(diaAux) <= 31) {
                        mesAux[0] = fechaDevolucion[3];
                        mesAux[1] = fechaDevolucion[4];
                        mesAux[2] = '\0';
                    } else {
                        b = 1;
                    }
                    if (atoi(mesAux) > 0 && atoi(mesAux) <= 12 & b == 0) {
                        anioAux[0] = fechaDevolucion[6];
                        anioAux[1] = fechaDevolucion[7];
                        anioAux[2] = fechaDevolucion[8];
                        anioAux[3] = fechaDevolucion[9];
                        anioAux[4] = '\0';
                    } else {
                        b = 1;
                    }
                    if (atoi(anioAux) < 1886 && b == 0) {
                        b = 1;
                        printf("\nNo se permiten años menores a 1886");
                    }
                    if (b == 1) {
                        printf("\nIngrese la fecha correctamente segun como corresponda\n");
                    } else {
                        if (contH != 0) { //Comprobar que la fecha actual ingresada no sea menor a la fecha de la anterior renta
                            if (carro[j].historial[contH - 1].fecha.anio > atoi(anioAux)) {
                                b = 1;
                            } else if (carro[j].historial[contH - 1].fecha.anio < atoi(anioAux)) {
                                b = 2;
                            }
                            if (carro[j].historial[contH - 1].fecha.mes > atoi(mesAux) && b == 0) {
                                b = 1;
                            } else if (carro[j].historial[contH - 1].fecha.mes < atoi(mesAux) && b == 0) {
                                b = 2;
                            }
                            if (carro[j].historial[contH - 1].fecha.dia > atoi(diaAux) && b == 0) {
                                b = 1;
                            }
                            if (b == 1) {
                                printf("\nLa fecha ingresada no puede ser menor a la fecha ingresada en la renta anterior perteneciente a este automovil\n");
                            } else {
                            }
                        }
                        if (carro[j].anioAuto > atoi(anioAux)) {
                            printf("\nEl año ingresado de devolucion no puede ser menor al año del modelo del automovil\n");
                            b = 1;
                        }
                    }
                }
            } while (b == 1);
            strcpy(carro[j].historial[contH].nombre, nombreAux);
            carro[j].historial[contH].numTelefono = atol(numTelefonoAux);
            carro[j].historial[contH].fecha.dia = atoi(diaAux);
            carro[j].historial[contH].fecha.mes = atoi(mesAux);
            carro[j].historial[contH].fecha.anio = atoi(anioAux);
            carro[j].historial[contH].kilomEntregado = carro[j].kilometraje;
            strcpy(carro[j].estado, "En renta");
            carro[j].contFecha++;
        }
    }
}
/**
 * El usuario puede ingresar sus datos para regresar el auto que rento anteriormente
 * @param carro
 * @param cont
 */
void devolucion(struct automovil carro[], int cont) {
    char numPlacas[35], numTelefonoAux[30], kmAux[30];
    int b, i, j;
    long int tel;
    do {
        numPlacas[0] = '\0',i = 0, b = 0;
        printf("\nIngrese el numero de placa del auto a devolver: ");
        scanf("%[^\n]", numPlacas);
        while (getchar() != '\n');
        while (i < cont && b == 0) {
            if (strcasecmp(carro[i].numPlacas, numPlacas) == 0) {
                if (carro[i].contFecha > 0) //Verifica que almenos una vez este auto a sido rentado
                {
                    b = 1;
                } else {
                    printf("\nEste auto no ha sido rentado aun\n");
                    b = 2;
                }
            }
            i++;
        }
        if (strlen(numPlacas) < 1) {
            printf("\nIngrese un numero de placas de automovil valido\n");
        } else if (b == 0) {
            printf("\nEl numero de placas ingresado no ha sido registrado\n");
            b = 2;
        }
    } while (b == 0);
    if (b == 1) //Si existe, ahora hay que revisar que el numero de telefono coincida con el ultimo registrado en renta y su estado este en renta
    {
        j = i - 1;
        if (strcasecmp(carro[j].estado, "Disponible") == 0) {
            printf("\nERROR:El estado del auto se encuentra en disponible y no en renta\n");
        } else {
            do {
                b = 0, i = 0,numTelefonoAux[0] = '\0';
                printf("\nIngrese su numero de telefono: ");
                scanf("%[^\n]", numTelefonoAux);
                while (getchar() != '\n');
                while (numTelefonoAux[i] != '\0' && b == 0) {
                    if (isdigit(numTelefonoAux[i]) == 0) {
                        printf("\nIngrese su numero de telefono correctamente\n");
                        b = 1;
                    }
                    i++;
                }
                if (strlen(numTelefonoAux) < 1) {
                    printf("\nIngrese su numero de telefono correctamente\n");
                    b = 1;
                }
            } while (b == 1);
            i = carro[j].contFecha - 1;
            tel = atol(numTelefonoAux);
            if (tel == carro[j].historial[i].numTelefono) { //El numero de telefono si corresponde a la ultima renta de este auto
                do {
                    kmAux[0] = '\0';
                    b = 0, i = 0;
                    printf("\nIngrese el kilometraje del auto con el que es regresado: ");
                    scanf("%[^\n]", kmAux);
                    while (getchar() != '\n');
                    while (kmAux[i] != '\0' && b == 0) {
                        if (isdigit(kmAux[i]) == 0) {
                            b = 1;
                        }
                        i++;
                    }
                    if (strlen(kmAux) < 1 || b == 1) {
                        printf("\nIngrese un kilometraje valido\n");
                        b = 1;
                    } else if (atoi(kmAux) < carro[j].kilometraje) {
                        printf("\nEl kilometraje con el que fue regresado el auto no puede ser menor al que fue entregado al usuario que era %d km\n", carro[j].kilometraje);
                        b = 1;
                    }
                } while (b == 1);
                carro[j].kilometraje = atoi(kmAux);
                strcpy(carro[j].estado, "Disponible");
            } else {
                printf("\nEl numero de telefono ingresado no corresponde al registrado en la ultima renta de este auto\n");
            }
        }
    }
}
/**
 * Realiza el ordenamiento en un auxiliar para que el usuario pueda verlo ordenado de menor a mayor el kilometraje en el submenu de consulta->Consulta general ordenada por kilometraje-4
 * @param carro
 * @param cont
 */
void ordenarKm(struct automovil carro[], int cont) {
    int x, y, min;
    struct automovil aux;
    for (x = 0; x < cont; x++) {
        min = x;
        for (y = x + 1; y < cont; y++) {
            if (carro[min].kilometraje > carro[y].kilometraje) {
                min = y;
            }
        }
        aux = carro[min];
        carro[min] = carro[x];
        carro[x] = aux;
    }
}