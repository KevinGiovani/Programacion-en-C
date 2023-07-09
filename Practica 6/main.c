/**
 * En esta práctica se hará una “simulación de la vida real”, utilizando una lista de personas.
 *Cada persona de la lista tendrá un Nombre, Número de identificación único, Edad, Año de
 *nacimiento, Estatura en centímetros y Peso en kilos. La lista no tiene un límite, por lo cual se deberá
 *utilizar para el almacenamiento de las personas memoria dinámica.
 */

/* 
 * File:   main.c
 * Author: kevin
 *
 * Created on 5 de mayo de 2020, 11:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct persona {
    int numID;
    char nombre[35];
    int edad;
    int anioNac;
    int estatura;
    int peso;
    struct persona *siguiente;
};

int menu();
void consulta(struct persona *personas, struct persona *personasB);
void ingresarPersona(struct persona **personas, int anioActual, struct persona *pB);
void consultaGeneral(struct persona *personas);
void consultaNumID(struct persona *personas, struct persona *personasB);
void borrar(struct persona *p);
void consultaProm(struct persona *personas);
void pasarAListaB(struct persona **personas, struct persona **personasB);
void consultaEliminada(struct persona *personasB);
int avanzarTiempo(struct persona **personas, int *anioActual, struct persona **personasB);
int validacionIngreso(char cadena[], int op);
int validacionID(char cadena[], struct persona *personas);

/*
 * 
 */
int main(int argc, char** argv) {
    int op, b, anioActual = 2000;
    struct persona *personas = NULL;
    struct persona *personasBorradas = NULL;
    do {
        op = 0, b = 0;
        op = menu();
        switch (op) {
            case 1:
                ingresarPersona(&personas, anioActual, personasBorradas);
                break;
            case 2:
                b = avanzarTiempo(&personas, &anioActual, &personasBorradas);
                if (b == 1) {
                    pasarAListaB(&personas, &personasBorradas);
                }
                break;
            case 3:
                consulta(personas, personasBorradas);
                break;
            case 4:
                borrar(personas);
                borrar(personasBorradas);
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nOpcion invalida\n\n");
        }
    } while (op != 4);
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
        b = 0;
        opA[0] = '\0';
        printf("\nSimulacion de la vida real\n[1] Nuevo nacimiento\n[2] Avanzar tiempo\n[3] Consultas\n[4] Terminar\nOpcion: ");
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
 * Introduce en la primera posicion de la lista informacion sobre una nueva persona
 * @param personas
 * @param anioActual
 */
void ingresarPersona(struct persona **personas, int anioActual, struct persona *pB) {
    struct persona *aux = *personas;
    char iD[25], estat[25], peso[25];
    int b;
    *personas = (struct persona *) malloc(sizeof (struct persona));
    printf("\nIngresando nueva persona");
    do {
        b = 0;
        iD[0] = '\0';
        printf("\nIngrese el numero de identificacion:");
        scanf("%[^\n]", iD);
        while (getchar() != '\n');
        b = validacionIngreso(iD, 1);
        if (b == 0) {
            b = validacionID(iD, aux);
            if (b == 0) {
                b = validacionID(iD, pB);
            }
        }
        if (b == -1 || strlen(iD) == 0) {
            printf("\nOpcion invalida para numero de identificacion\n");
            b = -1;
        }
    } while (b == -1 || b == -2);
    do {
        b = 0;
        (*personas)->nombre[0] = '\0';
        printf("\nIngrese el nombre de la persona:");
        scanf("%[^\n]", (*personas)->nombre);
        while (getchar() != '\n');
        b = validacionIngreso((*personas)->nombre, 2);
        if (b == -1 || strlen((*personas)->nombre) == 0) {
            printf("\nOpcion invalida para nombre de persona\n");
            b = -1;
        }
    } while (b == -1);
    do {
        b = 0;
        estat[0] = '\0';
        printf("\nIngrese la estatura:");
        scanf("%[^\n]", estat);
        while (getchar() != '\n');
        b = validacionIngreso(estat, 1);
        if (b == -1 || strlen(estat) == 0 || atoi(estat) > 200 || atoi(estat) == 0) {
            printf("\nOpcion invalida ingrese una estatura correctamente con enteros y que no exceda de 200cm\n");
            b = -1;
        }
    } while (b == -1);
    do {
        b = 0;
        peso[0] = '\0';
        printf("\nIngrese el peso:");
        scanf("%[^\n]", peso);
        while (getchar() != '\n');
        b = validacionIngreso(peso, 1);
        if (b == -1 || strlen(peso) == 0 || atoi(peso) > 100 || atoi(peso) == 0) {
            printf("\nOpcion invalida ingrese un peso correctamente con enteros y que no sea mayor de 100kg\n");
            b = -1;
        }
    } while (b == -1);
    printf("\nRegistro completado\n");
    (*personas)->numID = atoi(iD);
    (*personas)->edad = 0;
    (*personas)->anioNac = anioActual;
    (*personas)->estatura = atoi(estat);
    (*personas)->peso = atoi(peso);
    (*personas)->siguiente = aux;
}

/**
 * Simulacion de que el tiempo avanza y las personas sufren cambios de peso y estatura, asi tambien como de su edad
 * segun el tiempo que se desea avanzar proporcionado por el usuario
 * @param personas
 * @param anioActual
 * @param personasB
 */
int avanzarTiempo(struct persona **personas, int *anioActual, struct persona **personasB) {
    struct persona *aux;
    char anioN[20];
    int b, avance, tipo;
    if (*personas == NULL) {
        printf("\nNo se puede avanzar el tiempo porque la lista de personas se encuentra vacia\n");
    } else {
        do {
            printf("\nEl año actual es:%d", *anioActual);
            b = 0;
            anioN[0] = '\0';
            printf("\nIngrese los años a avanzar:");
            scanf("%[^\n]", anioN);
            while (getchar() != '\n');
            b = validacionIngreso(anioN, 1);
            if (b == -1 || strlen(anioN) == 0 || atoi(anioN) == 0) {
                printf("\nOpcion invalida de año ingresada para avanzar, solo ingrese numeros enteros\n");
                b = -1;
            }
        } while (b == -1);
        *anioActual += atoi(anioN);
        aux = *personas;
        while (aux != NULL) {
            avance = 0, b = 0;
            while (avance < atoi(anioN) && b == 0 && aux->edad < 20) {
                aux->edad++;
                tipo = 1 + rand() % 2;
                if (tipo == 2) { //bajo de peso
                    if (aux->peso > 10) {
                        aux->peso -= 1 + rand() % 10;
                    } else if (aux->peso > 1) { //el peso no puede ser menor a 1
                        aux->peso -= 1 + rand() % (aux->peso - 1);
                    } else {//aumento de peso
                        aux->peso += 1 + rand() % 10;
                    }
                } else { //aumenta de peso
                    if (aux->peso <= 90) {
                        aux->peso += 1 + rand() % 10;
                    } else if (aux->peso < 100) {
                        aux->peso += 1 + rand() % (100 - aux->peso);
                    }
                }
                if (aux->estatura <= 195) {
                    aux->estatura += 1 + rand() % 5;
                } else if (aux->estatura < 200) {
                    aux->estatura += 1 + rand() % (200 - aux->estatura);
                }
                avance++;
            }
            if (aux->edad == 20) {
                b = 1;
            }
            aux = aux->siguiente;
        }
    }
    return b;
}

/**
 * Realiza un traspaso a la lista de personas borradas a aquellas que ya cumplen con el rango de edad de 20
 * @param personas
 * @param personasB
 */
void pasarAListaB(struct persona **personas, struct persona **personasB) {
    struct persona *aux, *auxB, *auxC;
    int b = 0;
    aux = *personas; //guardo el primer nodo de personas
    auxB = *personasB; //guardo la direccion del primer nodo de las personas eliminadas
    while (aux != NULL && b == 0) {
        if (aux->edad == 20) {
            *personasB = aux; //Nodo eliminado ahora es el primero de esta lista
            *personas = NULL; //El nodo inicial en adelante puede tener nulo o continuar con personas con 20 años
            b = 1;
        } else if (aux->siguiente != NULL && aux->siguiente->edad == 20) {
            *personasB = aux->siguiente; //Nodo eliminado ahora es el primero de esta lista
            aux->siguiente = NULL; //Elimino el nodo que conecta con la lista personas puesto a que los siguientes de ese tambien cuentan con 20 años
            b = 1;
        } else {
            aux = aux->siguiente;
        }
    }
    if (b == 1) {
        auxC = *personasB;
        b = 0;
        while (auxC != NULL && b == 0) {
            if (auxC->siguiente == NULL) {
                b = 1;
            } else {
                auxC = auxC->siguiente;
            }
        }
        auxC->siguiente = auxB; //El siguiente del nodo eliminado es el nodo que antes era el primero de la lista eliminada
    }
}

/**
 * Menu de consulta para visualizar la informacion ingresada en la lista y en la lista de personas borradas
 * @param personas
 * @param personasB
 */
void consulta(struct persona *personas, struct persona *personasB) {
    char opA[15];
    int b;
    do {
        opA[0] = '\0';
        b = 0;
        printf("\nMENU DE CONSULTAS\n[1] Consulta general\n[2] Consulta por numero de identificacion\n[3] Mostrar el promedio de edad, estatura y peso\n[4] Consulta general de personas eliminadas\n[5] Regresar\nOPCION: ");
        scanf("%[^\n]", opA);
        while (getchar() != '\n');
        if (strlen(opA) > 1) {
            printf("\nOpcion invalida\n\n");
            b = -1;
        } else {
            switch (atoi(opA)) {
                case 1:
                    consultaGeneral(personas);
                    break;
                case 2:
                    consultaNumID(personas, personasB);
                    break;
                case 3:
                    consultaProm(personas);
                    break;
                case 4:
                    consultaEliminada(personasB);
                    break;
                case 5:
                    printf("\nRegresando al menu principal\n");
                    break;
                default:
                    printf("\nOpcion invalida\n\n");
            }
        }
    } while (atoi(opA) != 5);

}

/**
 * Muestra todos los datos de las personas de la lista
 * @param personas
 */
void consultaGeneral(struct persona *personas) {
    struct persona *aux;
    if (personas == NULL) {
        printf("\nLa lista de personas se encuentra vacia\n");
    } else {
        for (aux = personas; aux != NULL; aux = aux->siguiente) {
            printf("\nNumero de identificacion:#%d\nNombre:%s\nAño de nacimiento:%d\nEdad:%d\nPeso:%d Kg\nEstatura:%d cm\n", aux->numID, aux->nombre, aux->anioNac, aux->edad, aux->peso, aux->estatura);
        }
    }
}

/**
 * Muestra toda la información de la persona con el número de identificación ingresado si es que existe de lo contrario manda mensaje de no encontrado
 * @param personas
 */
void consultaNumID(struct persona *personas, struct persona *personasB) {
    struct persona *aux;
    char iD[25];
    int b;
    if (personas == NULL && personasB == NULL) {
        printf("\nLa lista de personas y personas borradas se encuentran vacias\n");
    } else {
        do {
            b = 0;
            iD[0] = '\0';
            printf("\nIngrese el numero de identificacion: ");
            scanf("%[^\n]", iD);
            while (getchar() != '\n');
            b = validacionIngreso(iD, 1);
            if (b == -1 || strlen(iD) == 0) {
                printf("\nOpcion invalida para numero de identificacion\n");
                b = -1;
            }
        } while (b == -1);
        b = -3;
        aux = personas; //Busqueda en lista de personas 
        while (aux != NULL && b == -3) {
            if (atoi(iD) == aux->numID) {
                b = 1;
            } else {
                aux = aux->siguiente;
            }
        }
        if (b == -3) {
            aux = personasB; //Busqueda en lista de personas eliminadas
            while (aux != NULL && b == -3) {
                if (atoi(iD) == aux->numID) {
                    b = 1;
                } else {
                    aux = aux->siguiente;
                }
            }
        }
        if (b == 1) {
            printf("\nNumero de identificacion:#%d\nNombre:%s\nAño de nacimiento:%d\nEdad:%d\nPeso:%d Kg\nEstatura:%d cm\n", aux->numID, aux->nombre, aux->anioNac, aux->edad, aux->peso, aux->estatura);

        } else {
            printf("\nEl numero de identificacion ingresado no corresponde a alguna persona dentro de alguna lista\n");
        }
    }
}

/**
 * Muestra la informacion calculada del promedio de las personas de la lista de sus datos como edad,estatura y peso
 * @param personas
 */
void consultaProm(struct persona *personas) {
    struct persona *aux;
    int cant = 0;
    float promEdad, promEstatura, promPeso;
    if (personas == NULL) {
        printf("\nLa lista de personas se encuentra vacia\n");
    } else {
        for (aux = personas; aux != NULL; aux = aux->siguiente) {
            promEdad += aux->edad;
            promEstatura += aux->estatura;
            promPeso += aux->peso;
            cant++;
        }
        printf("\n--Promedios--\nEdad:%.2f\nEstatura:%.2f\nPeso:%.2f\n", promEdad / cant, promEstatura / cant, promPeso / cant);
    }
}

/**
 * Muestra la informacion de la lista de las personas que se encuentran borradas
 * @param personasB
 */
void consultaEliminada(struct persona *personasB) {
    struct persona *aux;
    if (personasB == NULL) {
        printf("\nLa lista de personas eliminadas se encuentra vacia\n");
    } else {
        printf("\nPERSONAS ELIMINADAS");
        for (aux = personasB; aux != NULL; aux = aux->siguiente) {
            printf("\nNumero de identificacion:#%d\nNombre:%s\nAño de nacimiento:%d\nEdad:%d\nPeso:%d Kg\nEstatura:%d cm\n", aux->numID, aux->nombre, aux->anioNac, aux->edad, aux->peso, aux->estatura);
        }
    }
}

/**
 * Elimina la informacion de la lista ingresada
 * @param p
 */
void borrar(struct persona *p) {
    struct persona *aux;
    for (aux = p; aux != NULL; aux = aux->siguiente) {
        free(aux);
    }
}

/**
 * Valida los valores ingresados por el usuario cuando ingresa una persona a la lista
 * @param cadena
 * @param op
 * @return 
 */
int validacionIngreso(char cadena[], int op) {
    int i = 0, b = 0;
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
    }
    return b;
}

/**
 * Valida que el numero de identificacion no se repita con alguno anteriormente ingresado
 * @param cadena
 * @param personas
 * @return 
 */
int validacionID(char cadena[], struct persona *personas) {
    int b = 0;
    struct persona *aux;
    aux = personas;
    while (aux != NULL && b == 0) {
        if (atoi(cadena) == aux->numID) {
            printf("\nEl numero de identificacion se repite con otra persona\n");
            b = -2;
        }
        aux = aux->siguiente;
    }
    return b;
}