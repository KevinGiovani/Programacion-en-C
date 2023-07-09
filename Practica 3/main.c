/**
 * El alumno desarrollará el popular juego de mesa llamado “Conecta 4”, para
 *competir contra la computadora, haciendo uso de los distintos tipos de funciones
 *mostradas en clase. Para iniciar el juego, se requerirá pasar como argumentos en
 *consola (al momento de correr el programa) el nombre del jugador, un 0 si inicia él o
 *1 si inicia la computadora y el nombre de la computadora.
 */

/* 
 * File:   main.c
 * Author: Inzunza R. Kevin Giovani
 *
 * Created on 12 de marzo de 2020, 12:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void generarTablero(char [][7]);
void tomarIniciales(char nombreJugador[], char*inicialJugador, char nombreCPU[], char *inicialCPU, int *validarNombre);
void validarPosicionAJugar(int* pos, char []);
void jugarTurno(int, char nombreJugador[], char nombreCPU[], char inicialJugador, char inicialCPU, char [][7], int turno, int *fichaCPU, int *fichaJugador, int *ganarCPU, int *ganarJugador);
void imprimirTablero(char tablero[][7]);
void turnoJugador(char tablero[][7], char fichaJugador, int columna);
void turnoCPU(char tablero[][7], char inicialCPU, char inicialJugador, int *columna);
void verificarLimite(char tablero[][7], char fichaPos[], int *b);
void posiblesJugadasCPU(char tablero[][7], char inicialCPU, char inicialTipo, int *b, int *columna);
void comprobar(char tablero[][7], char ficha, int *ganar);
void msjFinal(int ganarCPU, int ganarJugador, int turno, char jugador[], char cpu[]);

/*
 * Funcion main del programa
 */
int main(int argc, char** argv) {
    char tablero[6][7], inicialCPU, inicialJugador;
    int pos = -1, turno = 1, fichaCPU = 0, fichaJugador = 0, ganarCPU = -1, ganarJugador = 0, validarNombre = 0;
    system("clear");
    if (argc == 4) {
        generarTablero(tablero);
        tomarIniciales(argv[1], &inicialJugador, argv[3], &inicialCPU, &validarNombre);
        if (validarNombre == 1) {
            validarPosicionAJugar(&pos, argv[2]);
            if (pos != -1) {
                do {
                    system("clear");
                    jugarTurno(pos, argv[1], argv[3], inicialJugador, inicialCPU, tablero, turno, &fichaCPU, &fichaJugador, &ganarCPU, &ganarJugador);
                    if (pos == 1) {
                        pos--;
                    } else {
                        pos++;
                    }
                    turno++;
                } while (turno < 43 && ganarCPU == -1 && ganarJugador == 0);
                system("clear");
                imprimirTablero(tablero);
                msjFinal(ganarCPU, ganarJugador, turno, argv[1], argv[3]);
            }
        }
    } else if (argc > 4) {
        printf("Demasiados argumentos\n\nIngrese:\n\tNOMBREJUGADOR 0-1 NOMBRECOMPUTADORA\n\n0=inicia jugador\t\t1=inicia computadora");

    } else {
        printf("Argumentos faltantes\n\nIngrese:\n\tNOMBREJUGADOR 0-1 NOMBRECOMPUTADORA\n\n0=inicia jugador\t\t1=inicia computadora");
    }
    while (getchar() != '\n');

    return 0;
}

/**
 * Genera los puntos dentro del tablero que simularan las posicion en las cuales el usuario dispone para lanzar su ficha
 * @param tablero
 */
void generarTablero(char tablero[][7]) {
    int i, j;
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 7; i++) {
            tablero[j][i] = '.';
        }
    }
}

/**
 * Muestra en pantalla el tablero en el que se visualizara por primera vez y las constantes actualizaciones que se hagan por cada ficha ingresada
 * @param tablero
 */
void imprimirTablero(char tablero[][7]) {
    int i, j;
    printf("\t  CONECTA 4\n");
    for (j = 0; j < 6; j++) {
        printf("\t");
        for (i = 0; i < 7; i++) {
            printf("%c ", tablero[j][i]);
        }
        printf("\n");
    }
    printf("\t1 2 3 4 5 6 7");
}

/**
 * Escoge la letra de los nombres que servira de ficha para jugar en el tablero para el jugador y computadora, si en dado caso se encuentran la misma 
 *  letra en los dos nombres en sus iniciales, se recorre los nombres letra por letra hasta encontrar alguna letra diferente
 * @param nombreJugador
 * @param inicialJugador
 * @param nombreCPU
 * @param inicialCPU
 * @param validarNombre
 */
void tomarIniciales(char nombreJugador[], char* inicialJugador, char nombreCPU[], char* inicialCPU, int *validarNombre) {
    int i = 0, j = 0;
    while (nombreJugador[i] != '\0' && *validarNombre == 0) {
        if (isdigit(nombreJugador[i]) > 0) {
            *validarNombre = -1;
        }
        i++;
    }
    while (nombreCPU[j] != '\0' && *validarNombre == 0) {
        if (isdigit(nombreCPU[j]) > 0) {
            *validarNombre = -1;
        }
        j++;
    }
    j = 0, i = 0;
    while (nombreJugador[i] != '\0' && *validarNombre == 0) {
        while (nombreCPU[j] != '\0' && *validarNombre == 0) {
            if (toupper(nombreJugador[i]) != toupper(nombreCPU[j])) {
                *validarNombre = 1;
                *inicialJugador = toupper(nombreJugador[i]);
                *inicialCPU = toupper(nombreCPU[j]);
            }
            j++;
        }
        j = 0;
        i++;
    }
    if (*validarNombre == 0) {
        printf("\nNo se ha podido escoger las iniciales del jugador/computadora para identificarse.\nNOTA:Para poder jugar procura que por lo menos tenga 1 letra diferente al otro nombre(Computadora/Jugador) de alguno para poder iniciar\n");
    } else if (*validarNombre == -1) {
        printf("\nIngrese solo letras en el apartado que le corresponde a cada nombre");
    }
}

/**
 * Verifica que la posicion de quien inicia primera la partida sea valida
 * @param pos
 * @param lugar
 */
void validarPosicionAJugar(int* pos, char lugar[]) {
    if (strcmp(lugar, "0") == 0) {
        printf("\nSe ha escogido que el jugador inicie la partida\n");
        *pos = 0;
        while (getchar() != '\n');
    } else if (strcmp(lugar, "1") == 0) {
        printf("\nSe ha escogido que la computadora inicie la partida\n");
        *pos = 1;
        while (getchar() != '\n');
    } else {
        printf("\nError:Escoja una opcion de posicion valida para iniciar a jugar\n\n\t0 es JUGADOR\t\t1 es COMPUTADORA");
    }
}

/**
 * Muestra la informacion del juego de manera actual y la instruccion del turno que esta en juego
 * @param pos
 * @param nombreJugador
 * @param nombreCPU
 * @param inicialJugador
 * @param inicialCPU
 * @param tablero
 * @param turno
 * @param fichaCPU
 * @param fichaJugador
 * @param ganarCPU
 * @param ganarJugador
 */
void jugarTurno(int pos, char nombreJugador[], char nombreCPU[], char inicialJugador, char inicialCPU, char tablero[][7], int turno, int *fichaCPU, int *fichaJugador, int *ganarCPU, int *ganarJugador) {
    int fichaPos, b, b1 = 0, columna;
    char fichaAux[15];
    do {
        b = 0;
        imprimirTablero(tablero);
        printf("\n\nFicha de jugador:%c\tFicha de CPU:%c", inicialJugador, inicialCPU);
        printf("\nJugador:%s\nFichas colocadas del jugador:%d\nTurno actual:%d\nComputadora:%s\nFichas de la computadora:%d\n", nombreJugador, *fichaJugador, turno, nombreCPU, *fichaCPU);
        if (pos == 0) {
            fichaAux[0] = '\0';
            printf("\nIngrese la columna para lanzar la ficha:");
            scanf("%[^\n]", fichaAux);
            while (getchar() != '\n');
            verificarLimite(tablero, fichaAux, &b);
        }
    } while (b == 1);
    if (pos == 0) {
        fichaPos = atoi(fichaAux);
        turnoJugador(tablero, inicialJugador, fichaPos - 1);
        (*fichaJugador)++;
        b1 = *ganarJugador;
        comprobar(tablero, inicialJugador, &b1);
        *ganarJugador = b1;
    } else {
        printf("\nIngrese enter para lanzar la ficha de la computadora...");
        while (getchar() != '\n');
        (*fichaCPU)++;
        turnoCPU(tablero, inicialCPU, inicialJugador, &columna);
        system("clear");
        imprimirTablero(tablero);
        printf("\n\nFicha de jugador:%c\tFicha de CPU:%c", inicialJugador, inicialCPU);
        printf("\nJugador:%s\nFichas colocadas del jugador:%d\nTurno actual:%d\nComputadora:%s\nFichas de la computadora:%d\nFicha colocada en la columna:%d\n", nombreJugador, *fichaJugador, turno, nombreCPU, *fichaCPU, columna + 1);
        printf("\nIngrese enter para finalizar el turno...");
        while (getchar() != '\n');
        system("clear");
        b1 = *ganarCPU;
        comprobar(tablero, inicialCPU, &b1);
        *ganarCPU = b1;
    }
}

/**
 * Ingresa en el tablero la ficha que el jugador ingreso 
 * @param tablero
 * @param fichaJugador
 * @param columna
 */
void turnoJugador(char tablero[][7], char fichaJugador, int columna) {
    int j = 5, b = 0;
    while (j >= 0 && b == 0) {
        if (tablero[j][columna] == '.') {
            tablero[j][columna] = fichaJugador;
            b = 1;
        }
        j--;
    }
}

/**
 * Ingresa en el tablero la ficha si cumple con alguna de estas condiciones 1.-El jugador puede ganar,2.-La computadora puede ganar.
 * La ficha es colocada segun sea el caso donde pueda ocurrir alguna de esas condiciones.
 * @param tablero
 * @param inicialCPU
 * @param inicialTipo
 * @param b
 * @param columna
 */
void posiblesJugadasCPU(char tablero[][7], char inicialCPU, char inicialTipo, int *b, int *columna) {
    int j = 5, i = 0, cont = 0, k, l;
    while (i < 7 && *b == 0) {
        while (j >= 0 && *b == 0) {
            if (tablero[j][i] == '.' && cont == 3) //Le da prioridad a la zona donde tiene posibilidad de ganar en forma vertical
            {
                tablero[j][i] = inicialCPU;
                *b = 1;
                *columna = i;
            } else if (tablero[j][i] == inicialTipo) {
                cont++;
            } else {
                cont = 0;
            }
            j--;
        }
        cont = 0;
        j = 5;
        i++;
    }
    i = 0;
    cont = 0;
    if (*b == 0) {
        while (j >= 0 && *b == 0) {
            while (i < 7 && *b == 0) {
                if (tablero[j][i] == '.' && cont == 3 || tablero[j][i] == '.' && tablero[j][i + 1] == inicialTipo && cont == 2 || tablero[j][i] == '.' && tablero[j][i + 1] == inicialTipo && tablero[j][i + 2] == inicialTipo && cont == 1 || tablero[j][i] == '.' && tablero[j][i + 1] == inicialTipo && tablero[j][i + 2] == inicialTipo && tablero[j][i + 3] == inicialTipo && cont == 0) //Le da prioridad a la zona donde tiene posibilidad de ganar en forma horizontal
                {
                    if (j == 5) {
                        tablero[j][i] = inicialCPU;
                        *b = 1;
                        *columna = i;
                    } else if (tablero[j + 1][i] != '.') {
                        tablero[j][i] = inicialCPU;
                        *b = 1;
                        *columna = i;
                    }
                } else if (tablero[j][i] == inicialTipo) {
                    cont++;
                } else {
                    cont = 0;
                }
                i++;
            }
            cont = 0;
            i = 0;
            j--;
        }
    }
    i = 0;
    j = 2;
    l = 0;
    cont = 0;
    if (*b == 0) {
        while (j >= 0 && *b == 0 && l <= 3) {
            k = j;
            while ((i < 6 - j && *b == 0 && l == 0) || (i <= 7 - j && *b == 0 && l > 0)) {
                if (tablero[k][i] == '.' && cont == 3 || tablero[k][i] == '.' && tablero[k + 1][i + 1] == inicialTipo && cont == 2 || tablero[k][i] == '.' && tablero[k + 1][i + 1] == inicialTipo && tablero[k + 2][i + 2] == inicialTipo && cont == 1 || tablero[k][i] == '.' && tablero[k + 1][i + 1] == inicialTipo && tablero[k + 2][i + 2] == inicialTipo && tablero[k + 3][i + 3] == inicialTipo && cont == 0) //Le da prioridad a la zona donde tiene posibilidad de ganar en forma diagonal de izq-der
                {
                    if (k == 5) {
                        tablero[k][i] = inicialCPU;
                        *b = 1;
                        *columna = i;
                    } else
                        if (tablero[k + 1][i] != '.') {
                        tablero[k][i] = inicialCPU;
                        *b = 1;
                        *columna = i;
                    }
                } else if (tablero[k][i] == inicialTipo) {
                    cont++;
                } else {
                    cont = 0;
                }
                k++;
                i++;
            }
            if (j == 0 && l == 0) {
                l = 1;
                j = 0;
                i = 1;
                cont = 0;
            } else if (l == 0) {
                j--;
                i = 0;
                cont = 0;
            } else if (l > 0) {
                j = 0;
                i = 1 + l;
                l++;
                cont = 0;
            }
        }
    }
    i = 6;
    j = 2;
    l = 0;
    cont = 0;
    if (*b == 0) {
        while (j < 6 && *b == 0 && l <= 3) {
            k = j;
            while (i >= 0 - j && *b == 0) {
                if (tablero[k][i] == '.' && cont == 3 || tablero[k][i] == '.' && tablero[k + 1][i - 1] == inicialTipo && cont == 2 || tablero[k][i] == '.' && tablero[k + 1][i - 1] == inicialTipo && tablero[k + 2][i - 2] == inicialTipo && cont == 1 || tablero[k][i] == '.' && tablero[k + 1][i - 1] == inicialTipo && tablero[k + 2][i - 2] == inicialTipo && tablero[k + 3][i - 3] == inicialTipo && cont == 0) //Le da prioridad a la zona donde tiene posibilidad de ganar en forma diagonal de der-izq
                {
                    if (k == 5) {
                        tablero[k][i] = inicialCPU;
                        *b = 1;
                        *columna = i;
                    } else
                        if (tablero[k + 1][i] != '.') {
                        tablero[k][i] = inicialCPU;
                        *b = 1;
                        *columna = i;
                    }
                } else if (tablero[k][i] == inicialTipo) {
                    cont++;
                } else {
                    cont = 0;
                }
                k++;
                i--;
            }
            if (j == 0 && l == 0) {
                l = 1;
                j = 0;
                i = 5;
                cont = 0;
            } else if (l == 0) {
                j--;
                i = 6;
                cont = 0;
            } else if (l > 0) {
                j = 0;
                i = 5 - l;
                l++;
                cont = 0;
            }
        }
    }
}

/**
 * Opciones que puede realizar la computadora mientras es su turno de juego
 * @param tablero
 * @param inicialCPU
 * @param inicialJugador
 */
void turnoCPU(char tablero[][7], char inicialCPU, char inicialJugador, int *columna) {
    int j = 5, b = 0, r, b1;
    posiblesJugadasCPU(tablero, inicialCPU, inicialCPU, &b, &b1); ///Verificar si puede ganar la partida la CPU
    if (b == 0) {
        posiblesJugadasCPU(tablero, inicialCPU, inicialJugador, &b, &b1); ///Verificar si puede ganar la partida el jugador para negarselo
    }
    if (b == 1) {
        *columna = b1;
    } else if (b == 0) //Significa que no se cumplio ninguna condicion sobre las posibles en las que el jugador estuviera ganando o la computadora pudiera ganar
    {
        do {
            r = rand() % 7;
            j = 5;
            while (j >= 0 && b == 0) {
                if (tablero[j][r] == '.') {
                    tablero[j][r] = inicialCPU;
                    b = 1;
                    *columna = r;
                }
                j--;
            }
        } while (b == 0);
    }
}

/**
 * Comprueba si el jugador o la computadora han ganado el juego
 * @param tablero
 * @param ficha
 * @param ganar
 */
void comprobar(char tablero[][7], char ficha, int *ganar) {
    int j = 5, i = 0, cont = 0, k, l;
    while (i < 7 && *ganar != 1) { //VERTICAL
        while (j >= 0 && *ganar != 1) {
            if (tablero[j][i] == ficha) {
                cont++;
            } else {
                cont = 0;
            }
            if (cont == 4) {
                *ganar = 1;
            }
            j--;
        }
        cont = 0;
        j = 5;
        i++;
    }
    i = 0;
    cont = 0;
    if (*ganar != 1) {
        while (j >= 0 && *ganar != 1) {
            while (i < 7 && *ganar != 1) {
                if (tablero[j][i] == ficha) {
                    cont++;
                } else {
                    cont = 0;
                }
                if (cont == 4) {
                    *ganar = 1;
                }
                i++;
            }
            cont = 0;
            i = 0;
            j--;
        }
    }
    i = 0;
    j = 2;
    l = 0;
    cont = 0;
    if (*ganar != 1) {
        while (j >= 0 && *ganar != 1 && l <= 3) {
            k = j;
            while ((i < 6 - j && *ganar != 1 && l == 0) || (i <= 7 - j && *ganar != 1 && l > 0)) {
                if (tablero[k][i] == ficha) {
                    cont++;
                } else {
                    cont = 0;
                }
                if (cont == 4) {
                    *ganar = 1;
                }
                k++;
                i++;
            }
            if (j == 0 && l == 0) {
                l = 1;
                j = 0;
                i = 1;
                cont = 0;
            } else if (l == 0) {
                j--;
                i = 0;
                cont = 0;
            } else if (l > 0) {
                j = 0;
                i = 1 + l;
                l++;
                cont = 0;
            }
        }
    }
    i = 6;
    j = 2;
    l = 0;
    cont = 0;
    if (*ganar != 1) {
        while (j < 6 && *ganar != 1 && l <= 3) {
            k = j;
            while (i >= 0 - j && *ganar != 1) {
                if (tablero[k][i] == ficha) {
                    cont++;
                } else {
                    cont = 0;
                }
                if (cont == 4) {
                    *ganar = 1;
                }
                k++;
                i--;
            }
            if (j == 0 && l == 0) {
                l = 1;
                j = 0;
                i = 5;
                cont = 0;
            } else if (l == 0) {
                j--;
                i = 6;
                cont = 0;
            } else if (l > 0) {
                j = 0;
                i = 5 - l;
                l++;
                cont = 0;
            }
        }
    }
}

/**
 * Muestra el mensaje con el se terminara el juego segun la condicion con la cual la partida halla acabado
 * @param ganarCPU
 * @param ganarJugador
 * @param turno
 * @param jugador
 * @param cpu
 */
void msjFinal(int ganarCPU, int ganarJugador, int turno, char jugador[], char cpu[]) {
    if (ganarCPU == 1) {
        printf("\n\n\t%s TE HA DERROTADO\n", cpu);
    } else if (ganarJugador == 1) {
        printf("\n\n\tFELICIDADES %s, HAZ GANADO\n", jugador);
    } else if (turno == 43) {
        printf("\n\n\t%s y %s HAN EMPATADO\n", jugador, cpu);
    }
}

/**
 * Comprueba que la ficha que puede lanzar el jugador si corresponda a una posicion dentro del tablero de forma horizontal y que la posicion donde es lanzada
 * no sobrepase el limite establecido de forma vertical
 * @param tablero
 * @param fichaPos
 * @param b
 */
void verificarLimite(char tablero[][7], char fichaPos[], int *b) {
    int pos;
    if (strlen(fichaPos) != 1 || atoi(fichaPos) <= 0 || atoi(fichaPos) > 7) {
        printf("\nIngrese solo alguna posicion en el tablero entre 1-7\n");
        *b = 1;
    }
    if (*b == 0) {
        pos = atoi(fichaPos) - 1;
        if (tablero[0][pos] != '.') {
            printf("\nTodos los campos de la columna %d estan ocupados, escoja otro\n", pos + 1);
            *b = 1;
        }
    }
    if (*b == 1) {
        while (getchar() != '\n');
        system("clear");
    }
}