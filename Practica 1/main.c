/*
 * Problema:
 * La aplicación de reproducción musical requiere de un sistema de software que permita
 *gestionar la biblioteca musical disponible para los usuarios, actualizar el número de
 *reproducciones de cada canción y en base a ello crear un listado de canciones recomendadas
 *de la semana. Como programador deberá implementar este sistema en base a las
 *especificaciones del cliente.
 */

/* 
 * File:   main.c
 * Author: Inzunza Rodriguez Kevin Giovani
 *
 * Created on 12 de febrero de 2020, 08:32 AM
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

/*
 * 
 */
int main(int argc, char** argv) {
    char opc, opcAux[2], tituloC[20][41], artista[20][41], genero[20][5], album[20][41], tituloAux[41], generoAux[5], albumAux[41], pal[3], artistaPar[5][41], tituloPar[5][41], albumPar[5][41], aux[41];
    int clave[20], anio[20], rep[20], cont = 0, i = 0, j = 0, resp, claveAux = 0, aux2, anioAux, b, enc[20], repAux, clavePar[5], repPar[3] = {0, 0, 0}, cont2 = 0;
    float durac[20], duracAux;

    printf("-Sponshify");
    do {
        opcAux[0]='\0';
        printf("\nSeleccione una opcion con el caracter que le corresponde:");
        printf("\nA.Registrar cancion\nB.Eliminar cancion\nC.Modificar cancion\nD.Busqueda\n");
        printf("E.Actualizar reproducciones\nF.Recomendaciones de la semana\nG.Salir\nOpcion: ");
        scanf("%[^\n]", opcAux);
        i = strlen(opcAux);
        if (strlen(opcAux) == 1) {
            opc = opcAux[0];
            opc = toupper(opc);
            switch (opc) {
                case 'A': //Registrar
                    if (cont < 20) {
                        do {
                            b = 0;
                            printf("\nClave: ");
                            while (getchar() != '\n');
                            scanf("%[^\n]", aux);
                            for (i = 0; aux[i] != '\0'; i++) {
                                if (isdigit(aux[i]) == 0) {
                                    b = 1;
                                }
                            }
                            if (b == 1 || atoi(aux) == 0) {
                                printf("\nSolo se permite el ingreso de numeros\n");
                            }
                        } while (b == 1 || atoi(aux) == 0);
                        claveAux = atoi(aux);
                        for (i = 0; i < cont; i++) {
                            if (clave[i] == claveAux) {
                                b = 1;
                            }
                        }
                        if (b == 0) {
                            i = 0;
                            clave[cont] = claveAux;
                            while (claveAux != 0) {
                                i++;
                                claveAux = claveAux / 10;
                            }
                            if (i <= 7) {
                                do {
                                    aux[0] = '\0';
                                    b = 0;
                                    printf("Titulo de la cancion: ");
                                    while (getchar() != '\n');
                                    scanf("%[^\n]", aux);
                                    if (strlen(aux) > 40 || strlen(aux) == 0) {
                                        printf("\nSolo se permiten cadenas con longitud maxima de 40 caracteres\n\n");
                                        b = 1;
                                    }
                                } while (b == 1);
                                strcpy(tituloC[cont], aux);
                                do {
                                    b = 0;
                                    aux[0] = '\0';
                                    printf("Artista: ");
                                    while (getchar() != '\n');
                                    scanf("%[^\n]", aux);

                                    if (strlen(aux) > 40 || strlen(aux) == 0) {
                                        printf("\nSolo se permiten cadenas con longitud maxima de 40 caracteres\n\n");
                                        b = 1;
                                    }
                                } while (b == 1);
                                strcpy(artista[cont], aux);
                                do {
                                    b = 0;
                                    aux[0] = '\0';
                                    printf("Año de lanzamiento: ");
                                    while (getchar() != '\n');
                                    scanf("%[^\n]", aux);
                                    for (i = 0; aux[i] != '\0'; i++) {
                                        if (isdigit(aux[i]) == 0) {
                                            b = 1;
                                        }
                                    }
                                    anioAux = atoi(aux);
                                    if (anioAux <= 0 || anioAux > 2020 || strlen(aux) == 0) {
                                        printf("\nSolo se permiten numeros positivos y no mayores al año actual\n\n");
                                        b = 1;
                                    }
                                } while (b == 1);
                                anio[cont] = anioAux;
                                do {
                                    b = 0;
                                    aux[0] = '\0';
                                    printf("Genero:\n1.Rock\n2.Pop\n3.Jazz\nOpcion:");
                                    while (getchar() != '\n');
                                    scanf("%[^\n]", aux);
                                    for (i = 0; aux[i] != '\0'; i++) {
                                        if (isdigit(aux[i]) == 0) {
                                            b = 1;
                                        }
                                    }
                                    if (b == 1) {
                                        printf("\nSolo se permite el ingreso de numeros\n");
                                    }
                                    aux2 = atoi(aux);
                                    if (aux2 <= 0 || aux2 > 3 || strlen(aux) == 0) {
                                        b = 1;
                                    }
                                    switch (aux2) {
                                        case 1:
                                            strcpy(genero[cont], "Rock");
                                            break;
                                        case 2:
                                            strcpy(genero[cont], "Pop");
                                            break;
                                        case 3:
                                            strcpy(genero[cont], "Jazz");
                                            break;
                                        default:
                                            printf("\nEscoja una de las opciones disponibles\n");
                                            break;
                                    }
                                } while (b == 1);
                                do {
                                    aux[0] = '\0';
                                    b = 0;
                                    i = 0;
                                    printf("Duracion: ");
                                    while (getchar() != '\n');
                                    scanf("%[^\n]", aux);
                                    for (j = 0; aux[j] != '\0'; j++) {
                                        if (isdigit(aux[j]) == 0) {
                                            if (aux[j] != '.') {
                                                b = 1;
                                            } else {
                                                i++; //Valida que no ingrese varios puntos decimales
                                            }
                                        }
                                    }
                                    duracAux = atof(aux);
                                    if (duracAux < 0 || strlen(aux) == 0 || i > 1) {
                                        b = 1;
                                    }

                                    if (b == 1) {
                                        printf("\nNo se permiten numeros negativos o una duracion de cero segundos\n");
                                    }

                                } while (b == 1);
                                durac[cont] = duracAux;
                                do {
                                    aux[0] = '\0';
                                    b = 0;
                                    printf("Titulo del album: ");
                                    while (getchar() != '\n');
                                    scanf("%[^\n]", aux);
                                    if (strlen(album[cont]) > 40 || strlen(aux) == 0) {
                                        printf("\nSolo se permiten cadenas con longitud maxima de 40 caracteres\n\n");
                                        b = 1;
                                    }
                                } while (b == 1);
                                strcpy(album[cont], aux);
                                rep[cont] = 0;
                                cont++;
                            } else {
                                printf("\nNo se permiten mas de 7 digitos en la clave\n");
                            }
                        } else {
                            printf("\nNo se permiten claves repetidas\n");
                        }
                    } else {
                        printf("La cantidad de canciones registradas ya ha llegado a su limite");
                    }
                    break;
                case 'B': //Eliminar
                    aux[0] = '\0';
                    if (cont > 0) {
                        b = 0;
                        do {
                            j = 0;
                            printf("\nClave de cancion a eliminar: ");
                            while (getchar() != '\n');
                            scanf("%[^\n]", aux);
                            for (i = 0; aux[i] != '\0'; i++) {
                                if (isdigit(aux[i]) == 0) {
                                    j = 1;
                                }
                            }
                            if (j == 1) {
                                printf("\nError de ingreso\n");
                            }
                        } while (j == 1);
                        resp = atoi(aux);
                        for (i = 0; i < cont; i++) {
                            if (clave[i] == resp) {
                                b = 1;
                                aux2 = i;
                            }
                        }
                        if (b == 1) {
                            b = 0;
                            for (j = 0; j < cont; j++) {
                                if (resp == clavePar[j]) {
                                    b = 1;
                                }
                            }
                            if (b == 0) {
                                do {
                                    printf("Se encontro la cancion¿Desea realizar la accion de eliminar?");
                                    while (getchar() != '\n');
                                    scanf("%s", pal);
                                    j = 0;
                                    b = 0;
                                    while (pal[j] != '\0') {
                                        pal[j] = toupper(pal[j]);
                                        j++;
                                    }
                                    if (strcmp(pal, "SI") == 0 || strcmp(pal, "NO") == 0) {
                                        b = 1;
                                    } else {
                                        printf("\nSolo se permite como respuesta 'si' o 'no'\n\n");
                                    }
                                } while (b != 1);
                                if (strcmp(pal, "SI") == 0) {
                                    while (aux2 <= cont) {
                                        clave[aux2] = clave[aux2 + 1];
                                        strcpy(tituloC[aux2], tituloC[aux2 + 1]);
                                        strcpy(artista[aux2], artista[aux2 + 1]);
                                        anio[aux2] = anio[aux2 + 1];
                                        strcpy(genero[i], genero[aux2 + 1]);
                                        durac[aux2] = durac[aux2 + 1];
                                        strcpy(album[aux2], album[aux2 + 1]);
                                        rep[aux2] = rep[aux2 + 1];
                                        aux2++;
                                    }
                                    printf("\nEliminacion exitosa\n");
                                    cont--;
                                } else {
                                    printf("\nNo se realizo la eliminacion\n");
                                }
                            } else {
                                printf("\nLa cancion no se puede eliminar porque se encuentra entre las recomendaciones de la semana\n");
                            }
                        } else {
                            printf("\nNo se encontro la cancion\n");
                        }
                    } else {
                        printf("\nNo hay canciones registradas para eliminar\n");
                    }
                    break;
                case 'C': //Modificar cancion
                    if (cont > 0) {
                        aux[0] = '\0';
                        printf("\n-Modificar cancion:\n");
                        do {
                            b = 0;
                            printf("\nClave: ");
                            while (getchar() != '\n');
                            scanf("%[^\n]", aux);
                            for (i = 0; aux[i] != '\0'; i++) {
                                if (isdigit(aux[i]) == 0) {
                                    b = 1;
                                }
                            }
                            if (b == 1 || atoi(aux) == 0) {
                                printf("\nError de ingreso\n");
                            }
                        } while (b == 1 || atoi(aux) == 0);
                        claveAux = atoi(aux);
                        b = 0;
                        for (aux2 = 0; aux2 < cont; aux2++) {
                            if (claveAux == clave[aux2]) {
                                i = aux2;
                                b = 1;
                            }
                        }
                        if (b == 1) {
                            aux[0] = '\0';
                            resp = 0;
                            printf("\nCancion encontrada\nClave\tTitulo       Artista    Año   Genero   Duracion   Album   Reproducciones\n");
                            printf("%-7d %-12s %-10s %-5d %-8s %-10.2f %-12s %-16d\n", clave[i], tituloC[i], artista[i], anio[i], genero[i], durac[i], album[i], rep[i]);
                            printf("\nOpcion a modificar\n");
                            printf("1.Titulo de la cancion\n2.Año de lanzamiento\n3.Genero\n4.Duracion\n5.Artista\n6.Titulo del album\n ");
                            do {
                                b = 0;
                                printf("\nOpcion: ");
                                while (getchar() != '\n');
                                scanf("%[^\n]", aux);
                                for (aux2 = 0; aux[aux2] != '\0'; aux2++) {
                                    if (isdigit(aux[aux2]) == 0) {
                                        b = 1;
                                    }
                                }
                                if (b == 1 || atoi(aux) == 0) {
                                    printf("\nError de ingreso\n");
                                }
                            } while (b == 1 || atoi(aux) == 0);
                            resp = atoi(aux);
                            switch (resp) {
                                case 1:
                                    do {
                                        tituloAux[0] = '\0';
                                        b = 0;
                                        printf("\nTitulo de la cancion: ");
                                        while (getchar() != '\n');
                                        scanf("%[^\n]", tituloAux);
                                        if (strlen(tituloAux) > 40) {
                                            printf("\nSolo se permiten cadenas con longitud maxima de 40 caracteres\n\n");
                                            b = 1;
                                        }
                                    } while (b == 1);
                                    if (strlen(tituloAux) != 0) {
                                        do {
                                            printf("¿Deseas guardar el cambio?");
                                            while (getchar() != '\n');
                                            scanf("%s", pal);
                                            j = 0;
                                            b = 0;
                                            while (pal[j] != '\0') {
                                                pal[j] = toupper(pal[j]);
                                                j++;
                                            }
                                            if (strcmp(pal, "SI") == 0 || strcmp(pal, "NO") == 0) {
                                                b = 1;
                                            } else {
                                                printf("\nSolo se permite como respuesta 'si' o 'no'\n\n");
                                            }
                                        } while (b != 1);
                                        if (strcmp(pal, "SI") == 0) {
                                            strcpy(tituloC[i], tituloAux);
                                            for (j = 0; j < cont2; j++) {
                                                if (clave[i] == clavePar[j]) {
                                                    strcpy(tituloPar[j], tituloAux);
                                                }
                                            }
                                            printf("\nSu cambio se ha realizado exitosamente\n");

                                        } else {
                                            printf("\nNo se realizaron cambios\n");
                                        }
                                    } else {
                                        printf("\nSe ha escogido dejar el valor original\n");
                                    }
                                    break;
                                case 2:
                                    anioAux = 0;
                                    do {
                                        b = 0;
                                        aux[0] = '\0';
                                        printf("\nAño de lanzamiento: ");
                                        while (getchar() != '\n');
                                        scanf("%[^\n]", aux);
                                        for (j = 0; aux[j] != '\0'; j++) {
                                            if (isdigit(aux[j]) == 0) {
                                                b = 1;
                                            }
                                        }
                                        anioAux = atoi(aux);
                                        if (anioAux > 2020) {
                                            b = 1;
                                        }
                                        if (b == 1) {
                                            printf("\nSolo se permiten numeros positivos y no mayores al año 2020(actual)\n");
                                        }
                                    } while (b == 1);
                                    if (anioAux != 0) {
                                        do {
                                            printf("¿Deseas guardar el cambio?");
                                            while (getchar() != '\n');
                                            scanf("%s", pal);
                                            j = 0;
                                            b = 0;
                                            while (pal[j] != '\0') {
                                                pal[j] = toupper(pal[j]);
                                                j++;
                                            }
                                            if (strcmp(pal, "SI") == 0 || strcmp(pal, "NO") == 0) {
                                                b = 1;
                                            } else {
                                                printf("\nSolo se permite como respuesta 'si' o 'no'\n\n");
                                            }
                                        } while (b != 1);
                                        if (strcmp(pal, "SI") == 0) {
                                            anio[i] = anioAux;
                                            printf("\nSu cambio se ha realizado exitosamente\n");
                                        } else {
                                            printf("\nNo se realizaron cambios\n");
                                        }
                                    } else {
                                        printf("\nSe ha escogido dejar el valor original\n");
                                    }
                                    break;
                                case 3:
                                    do {
                                        b = 0;
                                        aux[0] = '\0';
                                        printf("\nGenero:\n1.Rock\n2.Pop\n3.Jazz\nOpcion:");
                                        while (getchar() != '\n');
                                        scanf("%[^\n]", aux);
                                        for (j = 0; aux[j] != '\0'; j++) {
                                            if (isdigit(aux[j]) == 0) {
                                                b = 1;
                                            }
                                        }
                                        if (atoi(aux) > 0) {
                                            opc = atoi(aux);
                                            switch (opc) {
                                                case 1:
                                                    strcpy(generoAux, "Rock");
                                                    break;
                                                case 2:
                                                    strcpy(generoAux, "Pop");
                                                    break;
                                                case 3:
                                                    strcpy(generoAux, "Jazz");
                                                    break;
                                                default:
                                                    printf("\nIngrese solo las opciones disponibles\n");
                                            }
                                            if (opc < 0 || opc > 3) {
                                                b = 1;
                                            }
                                        }
                                    } while (b == 1);
                                    if (atoi(aux) != 0) {
                                        do {
                                            printf("¿Deseas guardar el cambio?");
                                            while (getchar() != '\n');
                                            scanf("%[^\n]", pal);
                                            j = 0;
                                            b = 0;
                                            while (pal[j] != '\0') {
                                                pal[j] = toupper(pal[j]);
                                                j++;
                                            }
                                            if (strcmp(pal, "SI") == 0 || strcmp(pal, "NO") == 0) {
                                                b = 1;
                                            } else {
                                                printf("\nSolo se permite como respuesta 'si' o 'no'\n\n");
                                            }
                                        } while (b != 1);
                                        if (strcmp(pal, "SI") == 0) {
                                            strcpy(genero[i], generoAux);
                                            printf("\nSu cambio se ha realizado exitosamente\n");
                                        } else {
                                            printf("\nNo se realizaron cambios\n");
                                        }
                                    } else {
                                        printf("\nSe ha escogido dejar el valor original\n");
                                    }
                                    break;
                                case 4:
                                    do {
                                        duracAux = 0;
                                        b = 0;
                                        aux[0] = '\0';
                                        resp = 0;
                                        printf("\nDuracion: ");
                                        while (getchar() != '\n');
                                        scanf("%[^\n]", aux);
                                        for (j = 0; aux[j] != '\0'; j++) {
                                            if (isdigit(aux[j]) == 0) {
                                                if (aux[j] != '.') {
                                                    b = 1;
                                                } else {
                                                    resp++; //Valida que no ingrese varios puntos decimales
                                                }
                                            }
                                        }
                                        duracAux = atof(aux);
                                        if (duracAux < 0 || resp > 1) {
                                            b = 1;
                                        }
                                        if (b == 1) {
                                            printf("\nNo se permiten numeros negativos o una duracion de cero segundos\n");
                                        }
                                    } while (b == 1);
                                    if (duracAux != 0) {
                                        do {
                                            printf("¿Deseas guardar el cambio?");
                                            while (getchar() != '\n');
                                            scanf("%s", pal);
                                            j = 0;
                                            b = 0;
                                            while (pal[j] != '\0') {
                                                pal[j] = toupper(pal[j]);
                                                j++;
                                            }
                                            if (strcmp(pal, "SI") == 0 || strcmp(pal, "NO") == 0) {
                                                b = 1;
                                            } else {
                                                printf("\nSolo se permite como respuesta 'si' o 'no'\n\n");
                                            }
                                        } while (b != 1);
                                        if (strcmp(pal, "SI") == 0) {
                                            durac[i] = duracAux;
                                            printf("\nSu cambio se ha realizado exitosamente\n");

                                        } else {
                                            printf("\nNo se realizaron cambios\n");
                                        }
                                    } else {
                                        printf("\nSe ha escogido dejar el valor original\n");
                                    }
                                    break;
                                case 5:
                                    do {
                                        b = 0;
                                        aux[0] = '\0';
                                        printf("Artista: ");
                                        while (getchar() != '\n');
                                        scanf("%[^\n]", aux);
                                        if (strlen(aux) > 40) {
                                            printf("\nSolo se permiten cadenas con longitud maxima de 40 caracteres\n\n");
                                            b = 1;
                                        }
                                    } while (b == 1);
                                    if (strlen(aux) != 0) {
                                        do {
                                            printf("¿Deseas guardar el cambio?");
                                            while (getchar() != '\n');
                                            scanf("%s", pal);
                                            j = 0;
                                            b = 0;
                                            while (pal[j] != '\0') {
                                                pal[j] = toupper(pal[j]);
                                                j++;
                                            }
                                            if (strcmp(pal, "SI") == 0 || strcmp(pal, "NO") == 0) {
                                                b = 1;
                                            } else {
                                                printf("\nSolo se permite como respuesta 'si' o 'no'\n\n");
                                            }
                                        } while (b != 1);
                                        if (strcmp(pal, "SI") == 0) {
                                            strcpy(artista[i], aux);
                                            for (j = 0; j < cont2; j++) {
                                                if (clave[i] == clavePar[j]) {
                                                    strcpy(artistaPar[j], aux);
                                                }
                                            }
                                            printf("\nSu cambio se ha realizado exitosamente\n");

                                        } else {
                                            printf("\nNo se realizaron cambios\n");
                                        }
                                    } else {
                                        printf("\nSe ha escogido dejar el valor original\n");
                                    }
                                    break;
                                case 6:
                                    do {
                                        b = 0;
                                        albumAux[0] = '\0';
                                        printf("Titulo del album: ");
                                        while (getchar() != '\n');
                                        scanf("%[^\n]", albumAux);
                                        if (strlen(albumAux) > 40) {
                                            printf("\nSolo se permiten cadenas con longitud maxima de 40 caracteres\n\n");
                                            b = 1;
                                        }
                                    } while (b == 1);
                                    if (strlen(albumAux) != 0) {
                                        do {
                                            printf("¿Deseas guardar el cambio?");
                                            while (getchar() != '\n');
                                            scanf("%s", pal);
                                            j = 0;
                                            b = 0;
                                            while (pal[j] != '\0') {
                                                pal[j] = toupper(pal[j]);
                                                j++;
                                            }
                                            if (strcmp(pal, "SI") == 0 || strcmp(pal, "NO") == 0) {
                                                b = 1;
                                            } else {
                                                printf("\nSolo se permite como respuesta 'si' o 'no'\n\n");
                                            }
                                        } while (b != 1);
                                        if (strcmp(pal, "SI") == 0) {
                                            strcpy(album[i], albumAux);
                                            for (j = 0; j < cont2; j++) {
                                                if (clave[i] == clavePar[j]) {
                                                    strcpy(albumPar[j], albumAux);
                                                }
                                            }
                                            printf("\nSu cambio se ha realizado exitosamente\n");
                                        } else {
                                            printf("\nNo se realizaron cambios\n");
                                        }
                                    } else {
                                        printf("\nSe ha escogido dejar el valor original\n");
                                    }
                                    break;
                                default:
                                    printf("\nLa opcion ingresado no es valida\n");
                                    break;
                            }
                        } else {
                            printf("\nLa cancion no ha sido encontrada\n");
                        }

                    } else {
                        printf("\nNo hay canciones registradas para eliminar\n");
                    }
                    break;
                case 'D': //Busqueda
                    if (cont > 0) {
                        aux2 = 0;
                        aux[0] = '\0';
                        printf("\nOpcion de busqueda\n1.Busqueda especifica por clave de cancion\n2.Consulta general");
                        printf("\n3.Busqueda por album\n4.Busqueda por artista\n");
                        do {
                            b = 0;
                            printf("\nOpcion: ");
                            while (getchar() != '\n');
                            scanf("%[^\n]", aux);
                            for (i = 0; aux[i] != '\0'; i++) {
                                if (isdigit(aux[i]) == 0) {
                                    b = 1;
                                }
                            }
                            if (b == 1 || atoi(aux) == 0) {
                                printf("\nSolo se permiten numeros\n");
                            }
                        } while (b == 1 || atoi(aux) == 0);
                        aux2 = atoi(aux);
                        switch (aux2) {
                            case 1:
                                aux[0] = '\0';
                                resp = 0;
                                printf("\nBusqueda especifica\n");
                                do {
                                    b = 0;
                                    printf("\nClave: ");
                                    while (getchar() != '\n');
                                    scanf("%[^\n]", aux);
                                    for (i = 0; aux[i] != '\0'; i++) {
                                        if (isdigit(aux[i]) == 0) {
                                            b = 1;
                                        }
                                    }
                                    if (b == 1 || atoi(aux) == 0) {
                                        printf("\nSolo se permiten numeros\n");
                                    }
                                } while (b == 1 || atoi(aux) == 0);
                                resp = atoi(aux);
                                b = 0;
                                for (i = 0; i < cont; i++) {
                                    if (clave[i] == resp) {
                                        b = 1;
                                        printf("\nCancion encontrada\nClave\tTitulo       Artista    Año   Genero   Duracion   Album   Reproducciones\n");
                                        printf("%-7d %-12s %-10s %-5d %-8s %-10.2f %-12s %-16d\n", clave[i], tituloC[i], artista[i], anio[i], genero[i], durac[i], album[i], rep[i]);
                                    }
                                }
                                if (b == 0) {
                                    printf("\nLa clave de la cancion no ha sido registrada\n");
                                }
                                break;
                            case 2:
                                printf("Busqueda general\n");
                                printf("Clave\tTitulo       Artista    Año   Genero      Album   Reproducciones\n");
                                for (i = 0; i < cont; i++) {
                                    printf("%-7d %-12s %-10s %-5d %-8s  %-12s %-16d\n", clave[i], tituloC[i], artista[i], anio[i], genero[i], album[i], rep[i]);
                                }
                                break;
                            case 3:
                                printf("\nBusqueda por album");
                                printf("\nIngrese album : ");
                                while (getchar() != '\n');
                                scanf("%[^\n]", albumAux);
                                printf("Artista: ");
                                while (getchar() != '\n');
                                scanf("%[^\n]", aux);
                                j = 0;
                                b = 0;
                                for (i = 0; i < cont; i++) {
                                    if (strcasecmp(albumAux, album[i]) == 0 && strcasecmp(aux, artista[i]) == 0) {
                                        enc[j] = i;
                                        j++;
                                        b = 1;
                                    }
                                }
                                if (b == 1) {
                                    printf("\nAlbum encontrado\nClave\tTitulo   Reproducciones\n");
                                    while (j > 0) {
                                        j--;
                                        b = enc[j];
                                        printf("%-7d %-12s %-16d\n", clave[b], tituloC[b], rep[b]);
                                    }
                                } else {
                                    printf("\nNo existen canciones de este album con respecto al artista que usted escribio\n");
                                }
                                break;
                            case 4:
                                printf("Busqueda por artista");
                                printf("\nArtista: ");
                                while (getchar() != '\n');
                                scanf("%[^\n]", aux);
                                j = 0;
                                b = 0;
                                for (i = 0; i < cont; i++) {
                                    if (strcasecmp(aux, artista[i]) == 0) {
                                        enc[j] = i;
                                        j++;
                                        b = 1;
                                    }
                                }
                                if (b == 1) {
                                    printf("\nArtista encontrado\nTitulo    Año   Album   Reproducciones\n");
                                    while (j > 0) {
                                        j--;
                                        b = enc[j];
                                        printf("%-9s %-4d  %-12s %-16d\n", tituloC[b], anio[b], album[b], rep[b]);
                                    }
                                } else {
                                    printf("\nNo existen canciones registradas de este artista\n");
                                }
                                break;
                            default:
                                printf("\nEscoja una de las opciones disponibles\n");
                        }
                    } else {
                        printf("\nNo se ha registrado ninguna cancion  para comenzar algun tipo de busqueda\n");
                    }
                    break;
                case 'E': //Actualizar recomendaciones de la semana
                    if (cont != 0) {
                        aux[0] = '\0';
                        resp = 0;
                        printf("\nActualizar reproducciones");
                        do {
                            b = 0;
                            printf("\nClave: ");
                            while (getchar() != '\n');
                            scanf("%[^\n]", aux);
                            for (aux2 = 0; aux[aux2] != '\0'; aux2++) {
                                if (isdigit(aux[aux2]) == 0) {
                                    b = 1;
                                }
                            }
                            if (b == 1 || atoi(aux) == 0) {
                                printf("\nError de ingreso\n");
                            }
                        } while (b == 1 || atoi(aux) == 0);
                        resp = atoi(aux);
                        i = 0;
                        b = 0;
                        for (j = 0; j < cont; j++) {
                            if (clave[j] == resp) {
                                i = j;
                                b = 1;
                            }
                        }
                        if (b == 1) {
                            printf("\nCancion encontrada\nClave\tTitulo       Artista    Año   Genero   Duracion   Album   Reproducciones\n");
                            printf("%-7d %-12s %-10s %-5d %-8s %-10.2f %-12s %-16d\n", clave[i], tituloC[i], artista[i], anio[i], genero[i], durac[i], album[i], rep[i]);
                            printf("\nNota:Si no desea modificar deje un espacio en blanco");
                            do {
                                b = 0;
                                aux[0] = '\0';
                                printf("\nNuevo valor de reproduccion: ");
                                while (getchar() != '\n');
                                scanf("%[^\n]", aux);
                                repAux = atoi(aux);
                                for (j = 0; aux[j] != '\0'; j++) {
                                    if (isdigit(aux[j]) == 0) {
                                        b = 1;
                                    }
                                }
                                if (repAux <= rep[i] && atoi(aux) != 0) {
                                    b = 1;
                                }
                                if (b == 1) {
                                    printf("\nSolo se permite un numero mayor al valor actual de reproducciones de esta cancion para que sea guardado\n");
                                }
                            } while (b == 1);
                            if (atoi(aux) != 0) {
                                rep[i] = repAux;
                                b = 0;
                                for (j = 0; j < cont2; j++) {
                                    if (clave[i] == clavePar[j]) {
                                        repPar[j] = rep[i];
                                        b = 1;
                                    }
                                }
                                if (b == 0) {
                                    j = cont2;

                                    if (cont2 == 3) {
                                        cont2--;
                                    }
                                    if (repAux >= repPar[cont2]) {
                                        clavePar[cont2] = clave[i];
                                        strcpy(tituloPar[cont2], tituloC[i]);
                                        strcpy(artistaPar[cont2], artista[i]);
                                        repPar[cont2] = rep[i];
                                        strcpy(albumPar[cont2], album[i]);
                                        cont2++;
                                    } else {
                                        cont2++;
                                    }
                                    b = 1;
                                }
                                if (b == 1) {
                                    for (i = 1; i < cont2; i++) {
                                        for (j = 0; j < cont2 - i; j++) {
                                            if (repPar[j] < repPar[j + 1]) {
                                                repAux = repPar[j + 1];
                                                repPar[j + 1] = repPar[j];
                                                repPar[j] = repAux;
                                                claveAux = clavePar[j + 1];
                                                clavePar[j + 1] = clavePar[j];
                                                clavePar[j] = claveAux;
                                                strcpy(tituloAux, tituloPar[j + 1]);
                                                strcpy(tituloPar[j + 1], tituloPar[j]);
                                                strcpy(tituloPar[j], tituloAux);
                                                strcpy(albumAux, albumPar[j + 1]);
                                                strcpy(albumPar[j + 1], albumPar[j]);
                                                strcpy(albumPar[j], albumAux);
                                                strcpy(aux, artistaPar[j + 1]);
                                                strcpy(artistaPar[j + 1], artistaPar[j]);
                                                strcpy(artistaPar[j], aux);
                                            }
                                        }
                                    }
                                }
                            }

                        } else {
                            printf("\nLa clave de la cancion no ha sido registrada\n");
                        }
                        break;
                        case 'F': //Recomendaciones
                        if (cont2 > 0) {
                            printf("\nRecomendaciones de la semana\nClave\tTitulo       Artista   Album   Reproducciones\n");
                            for (i = 0; i < cont2; i++) {
                                printf("%-7d %-12s %-10s %-12s %-16d\n", clavePar[i], tituloPar[i], artistaPar[i], albumPar[i], repPar[i]);
                            }
                        } else {
                            printf("\nNinguna cancion registrada ha sido reproducida\n");
                        }
                        break;
                        case 'G':
                        printf("\nSe ha escogido salir\n");
                        break;
                        default:
                        printf("\nEscoja una de las opciones disponibles\n");
                    } else {
                        printf("\nNo hay canciones registradas para eliminar\n");
                    }
            }
        } else {
            printf("\nEscoja una de las opciones disponibles\n");
        }
        while (getchar() != '\n');
    } while (opc != 'G');
}



