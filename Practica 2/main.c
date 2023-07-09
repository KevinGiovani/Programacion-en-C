/*
 *La facultad de idiomas requiere evaluar el nivel de léxico en los estudiantes. Para esto se
 *realiza un examen virtual donde acceden los estudiantes y contestan la traducción de palabras
 *en un idioma determinado (inglés, italiano, francés, portugués o alemán) al español. Como
 *programador creará una aplicación que permita llenar un banco de palabras en otros idiomas con
 *su respectiva traducción al español, para que los alumnos las traduzcan contestando el examén.
 *La aplicación permitirá agregar palabras al banco, verificar las palabras dentro del banco y aplicar
 *el examen.
 */

/* 
 * File:   main.c
 * Author: kevin
 *
 * Created on 27 de febrero de 2020, 09:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <wctype.h>
#include <string.h>

/*
 * 
 */
int main(int argc, char** argv) {
    wchar_t banco[100][81], aux[81], aux2[81], a[81], aux3[81], aux4[81], aux5[81], aux6[81], aux7[81], aux8[81];
    int op, i, i1, i2, i3, j, k, l, p, b, cont = 5, m, b1 = 1, b2 = 0, b3 = 1, b4 = 0, b5 = 1, b6 = 1, ac = 0, e = 0, r[5], c, q, matricula;
    char op2, aux9[25];
    wcscpy(banco[0],L"1?esp&Teclado");
    wcscpy(banco[1],L"1?eng&Keyboard");
     wcscpy(banco[2],L"1?fra&Clavier");
      wcscpy(banco[3],L"2?esp&Popote%pajilla%Sorbete");
       wcscpy(banco[4],L"2?por&palha");
      
    
    setlocale(LC_ALL, "");
    do {
        op = 0;
        aux9[0] = '\0';
        wprintf(L"\nExamen de idiomas\nElija una opcion:\n1.-Agregar palabra\n2.-Consulta general del banco de palabras\n3.-Consulta especifica por idioma");
        wprintf(L"\n4.-Aplicar examen\n5.-Salir\nOpcion: ");
        scanf("%[^\n]", aux9);
        if (strlen(aux9) == 1) {
            op = atoi(aux9);
            switch (op) {
                case 1:
                    b = 0, j = 0, i = 0, k = 0, p = 0;
                    aux[0] = L'\0';
                    aux2[0] = L'\0';
                    wprintf(L"\nAgregar palabra\n");
                    while (getchar() != L'\n');
                    scanf("%l[^\n]", aux);
                    if (wcslen(aux) < 81) {
                        while (aux[i] != L'\0' && b != -1) {
                            if (aux[0] == L'?') {
                                b = -1;
                            }
                            if (b == 0) {
                                a[j] = aux[i];
                                j++;
                                if (aux[i] == L'?') {
                                    a[j - 1] = L'\0';
                                    b = 1;
                                    j = 0;
                                } else if (isdigit(aux[i]) == 0) {
                                    b = -1;
                                    wprintf(L"\nError\nNota:Solo se permite numeros en el primer apartado que es clave\n");
                                }
                            } else if (b == 1) {
                                aux2[j] = aux[i];
                                j++;
                                if (aux[i] == L'&') {
                                    aux2[j - 1] = L'\0';
                                    if (wcscasecmp(aux2, L"ESP") == 0 || wcscasecmp(aux2, L"ENG") == 0 || wcscasecmp(aux2, L"ITA") == 0 || wcscasecmp(aux2, L"POR") == 0 || wcscasecmp(aux2, L"DEU") == 0 || wcscasecmp(aux2, L"FRA") == 0) {
                                        b = 2;
                                        j = 0;
                                        
                                    } else {
                                        b = -1;
                                        wprintf(L"\nIdioma ingresado no existente\n");
                                    }
                                } else if (iswalpha(aux[i]) == 0) {
                                    b = -1;
                                    wprintf(L"\nNota:ERROR en el segundo apartado que es idioma\n");
                                }
                            } else if (b == 2) {
                                if (aux[i + 1] == L'%' && isspace(aux[i]) || aux[i - 1] == L'%' && isspace(aux[i])) {
                                    wprintf(L"\nError de ingreso,no se permite espacio al finalizar o iniciar una palabra/sinonimo\n");
                                    b = -1;
                                } else if (aux[i - 1] == L'&' && isspace(aux[i])) {
                                    wprintf(L"\nError de ingreso\n");
                                    b = -1;
                                } else if (aux[i] == L'%' || aux[i + 1] == L'\0' && iswalpha(aux[i]) != 0 || isspace(aux[i])) {
                                    if (aux[i] == L'%') {
                                        k++;
                                    } else {
                                        b = 3;
                                    }
                                } else if (iswalpha(aux[i]) == 0) {
                                    b = -1;
                                    wprintf(L"\nERROR en el apartado palabra/sinonimo");
                                }
                                if (k > 2) {
                                    wprintf(L"\nError\nNota:Solo se permiten maximo 2 sinonimos por palabra");

                                    b = -1;
                                }
                                j++;
                            
                            }
                            i++;
                        }
                        if (isspace(aux[i - 1]) && b != -1) {
                            b = -1;
                            wprintf(L"\nNo se permite ingresar al final un espacio como perteneciente a la palabra/sinonimo\n");
                        }
                        if (b == 3) {
                            i = 0;
                            j = 0;
                            while (i < cont && b != -1) {
                                b = 0;
                                p = 0;
                                k = 0;
                                while (b < 2) {
                                    if (b == 0) {
                                        aux3[k] = banco[i][k];
                                        if (banco[i][k] == L'?') {
                                            aux3[k] = L'\0';
                                            b = 1;
                                        }
                                    } else if (b == 1) {
                                        aux4[p] = banco[i][k];
                                        if (banco[i][k] == L'&') {
                                            aux4[p] = L'\0';
                                            b = 2;
                                        }
                                        p++;
                                    }
                                    k++;
                                }
                                if (wcscasecmp(aux2, aux4) == 0 && wcscasecmp(a, aux3) == 0) {
                                    wprintf(L"\nLa clave seleccionada ya contaba con este idioma\n");
                                    b = -1;
                                }
                                i++;
                            }
                            if (b != -1) {
                                /*Tener control de la cantidad de palabras que hay en cada idioma*/
                                if (wcscasecmp(aux2, L"ESP") == 0) {
                                    b5++;
                                } else if (wcscasecmp(aux2, L"ENG") == 0) {
                                    b1++;
                                } else if (wcscasecmp(aux2, L"ITA") == 0) {
                                    b2++;
                                } else if (wcscasecmp(aux2, L"POR") == 0) {
                                    b3++;
                                } else if (wcscasecmp(aux2, L"DEU") == 0) {
                                    b4++;
                                } else if (wcscasecmp(aux2, L"FRA") == 0) {
                                    b6++;
                                }
                                wcscpy(banco[cont], aux); //Se guarda la palabra en el banco
                                cont++;
                            }
                        } else {
                            wprintf(L"\nError de valores ingresados o no cumple con todas las caracteristicas, la palabra no se guardara\nNota:El formato debe ser:\n<Clave numerica>?<idioma>&<palabra>%<sinonimo1>%<sinonimo2>\n");
                        }
                    } else {
                        wprintf(L"\nSolo se permiten maximo 80 caracteres\n");
                    }
                    break;
                case 2:
                    if (cont > 0) {
                        wprintf(L"\n CONSULTA GENERAL DEL BANCO DE PALABRAS\n");
                        wprintf(L"  Clave:     Idioma:       Palabra:\n");
                        j = 1;
                        for (i = 0; i < cont; i++) {
                            aux[0] = L'\0';
                            aux3[0] = L'\0';
                            aux4[0] = L'\0';
                            b = 0;
                            p = 0;
                            k = 0;
                            while (banco[i][k] != L'\0') {
                                if (b == 0) {
                                    aux3[k] = banco[i][k];
                                    if (banco[i][k] == L'?') {
                                        aux3[k] = L'\0';
                                        b = 1;
                                    }
                                } else if (b == 1) {
                                    aux4[p] = banco[i][k];
                                    p++;
                                    if (banco[i][k] == L'&') {
                                        aux4[p - 1] = L'\0';
                                        b = 2;
                                        p = 0;
                                    }

                                } else if (b == 2) {
                                    aux[p] = banco[i][k];
                                    if (banco[i][k] == L'%') {
                                        aux[p] = L',';
                                    }
                                    p++;
                                }
                                k++;
                            }
                            aux[p] = L'\0';
                            wprintf(L"%d] %-10ls%-15ls%-15ls\n", j++, aux3, aux4, aux);
                        }
                    } else {
                        wprintf(L"\nNo existen palabras registradas\n");
                    }
                    break;
                case 3:
                    if (cont > 0) {
                        do {
                            op2 = '\0';
                            aux9[0] = '\0';
                            wprintf(L"\nTipo de busqueda por idioma:\n");
                            wprintf(L"A-Palabras en ingles\nB-Palabras en Español\nC-Palabras en aleman\nD-Palabras en italiano\nE-Palabras en portugues\nF-Palabras en frances\nG-Regresar\nOpcion: ");
                            while (getchar() != '\n');
                            scanf("%[^\n]", aux9);
                            if (strlen(aux9) == 1) {
                                op2 = aux9[0];
                                op2 = toupper(op2);
                                switch (op2) {
                                    case 'A':
                                        if (b1 > 0) {
                                            j = 1;
                                            for (i = 0; i < cont; i++) {
                                                aux[0] = L'\0';
                                                aux2[0] = L'\0';
                                                aux3[0] = L'\0';
                                                aux4[0] = L'\0';
                                                b = 0, p = 0, k = 0, l = 0, m = 0;
                                                while (banco[i][k] != L'\0') {
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k] == L'&') {
                                                            aux4[p - 1] = L'\0';
                                                            b = 2;
                                                            p = 0;
                                                        }

                                                    } else if (b == 2) {
                                                        if (l == 0) {
                                                            aux[p] = banco[i][k];
                                                            p++;
                                                        } else {
                                                            aux2[m] = banco[i][k];
                                                            m++;
                                                        }
                                                        if (banco[i][k] == L'%') {
                                                            if (l != 0) {
                                                                aux2[m - 1] = L',';
                                                                l++;
                                                            } else {
                                                                l = 1;
                                                            }
                                                        }
                                                    }
                                                    k++;
                                                }
                                                aux2[m] = L'\0';
                                                if (l == 0) {
                                                    aux[p] = L'\0';
                                                    wcscpy(aux2, L"(Ninguno)");
                                                } else {
                                                    aux[p - 1] = L'\0';
                                                }
                                                if (wcscasecmp(aux4, L"ENG") == 0) {
                                                    wprintf(L"%d] Clave:%-8lsPalabra(s):%-10lsSinonimo(s):%-5ls\n", j++, aux3, aux, aux2);
                                                }
                                            }
                                        } else {
                                            wprintf(L"\nNo existen palabras registradas del idioma ingles\n");
                                        }
                                        break;
                                    case 'B':
                                        if (b5 > 0) {
                                            j = 1;
                                            for (i = 0; i < cont; i++) {
                                                aux[0] = L'\0';
                                                aux2[0] = L'\0';
                                                aux3[0] = L'\0';
                                                aux4[0] = L'\0';
                                                b = 0, p = 0, k = 0, l = 0, m = 0;
                                                while (banco[i][k] != L'\0') {
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k] == L'&') {
                                                            aux4[p - 1] = L'\0';
                                                            b = 2;
                                                            p = 0;
                                                        }

                                                    } else if (b == 2) {
                                                        if (l == 0) {
                                                            aux[p] = banco[i][k];
                                                            p++;
                                                        } else {
                                                            aux2[m] = banco[i][k];
                                                            m++;
                                                        }
                                                        if (banco[i][k] == L'%') {
                                                            if (l != 0) {
                                                                aux2[m - 1] = L',';
                                                                l++;
                                                            } else {
                                                                l = 1;
                                                            }
                                                        }
                                                    }
                                                    k++;
                                                }
                                                aux2[m] = L'\0';
                                                if (l == 0) {
                                                    aux[p] = L'\0';
                                                    wcscpy(aux2, L"(Ninguno)");
                                                } else {
                                                    aux[p - 1] = L'\0';
                                                }
                                                if (wcscasecmp(aux4, L"ESP") == 0) {
                                                    wprintf(L"%d] Clave:%-8lsPalabra(s):%-10lsSinonimo(s):%-5ls\n", j++, aux3, aux, aux2);
                                                }
                                            }
                                        } else {
                                            wprintf(L"\nNo existen palabras registradas del idioma español\n");
                                        }
                                        break;
                                    case 'C':
                                        if (b4 > 0) {
                                            j = 1;
                                            for (i = 0; i < cont; i++) {
                                                aux[0] = L'\0';
                                                aux2[0] = L'\0';
                                                aux3[0] = L'\0';
                                                aux4[0] = L'\0';
                                                b = 0, p = 0, k = 0, l = 0, m = 0;
                                                while (banco[i][k] != L'\0') {
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k] == L'&') {
                                                            aux4[p - 1] = L'\0';
                                                            b = 2;
                                                            p = 0;
                                                        }
                                                    } else if (b == 2) {
                                                        if (l == 0) {
                                                            aux[p] = banco[i][k];
                                                            p++;
                                                        } else {
                                                            aux2[m] = banco[i][k];
                                                            m++;
                                                        }
                                                        if (banco[i][k] == L'%') {
                                                            if (l != 0) {
                                                                aux2[m - 1] = L',';
                                                                l++;
                                                            } else {
                                                                l = 1;
                                                            }
                                                        }
                                                    }
                                                    k++;
                                                }
                                                aux2[m] = L'\0';
                                                if (l == 0) {
                                                    aux[p] = L'\0';
                                                    wcscpy(aux2, L"(Ninguno)");
                                                } else {
                                                    aux[p - 1] = L'\0';
                                                }
                                                if (wcscasecmp(aux4, L"DEU") == 0) {
                                                    wprintf(L"%d] Clave:%-8lsPalabra(s):%-10lsSinonimo(s):%-5ls\n", j++, aux3, aux, aux2);
                                                }
                                            }
                                        } else {
                                            wprintf(L"\nNo existen palabras registradas del idioma aleman\n");
                                        }
                                        break;
                                    case 'D':
                                        if (b2 > 0) {
                                            j = 1;
                                            for (i = 0; i < cont; i++) {
                                                aux[0] = L'\0';
                                                aux2[0] = L'\0';
                                                aux3[0] = L'\0';
                                                aux4[0] = L'\0';
                                                b = 0, p = 0, k = 0, l = 0, m = 0;
                                                while (banco[i][k] != L'\0') {
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k] == L'&') {
                                                            aux4[p - 1] = L'\0';
                                                            b = 2;
                                                            p = 0;
                                                        }
                                                    } else if (b == 2) {
                                                        if (l == 0) {
                                                            aux[p] = banco[i][k];
                                                            p++;
                                                        } else {
                                                            aux2[m] = banco[i][k];
                                                            m++;
                                                        }
                                                        if (banco[i][k] == L'%') {
                                                            if (l != 0) {
                                                                aux2[m - 1] = L',';
                                                                l++;
                                                            } else {
                                                                l = 1;
                                                            }
                                                        }
                                                    }
                                                    k++;
                                                }
                                                aux2[m] = L'\0';
                                                if (l == 0) {
                                                    aux[p] = L'\0';
                                                    wcscpy(aux2, L"(Ninguno)");
                                                } else {
                                                    aux[p - 1] = L'\0';
                                                }
                                                if (wcscasecmp(aux4, L"ITA") == 0) {
                                                    wprintf(L"%d] Clave:%-8lsPalabra(s):%-10lsSinonimo(s):%-5ls\n", j++, aux3, aux, aux2);
                                                }
                                            }
                                        } else {
                                            wprintf(L"\nNo existen palabras registradas del idioma italiano\n");
                                        }
                                        break;
                                    case 'E':
                                        if (b3 > 0) {
                                            j = 1;
                                            for (i = 0; i < cont; i++) {
                                                aux[0] = L'\0';
                                                aux2[0] = L'\0';
                                                aux3[0] = L'\0';
                                                aux4[0] = L'\0';
                                                b = 0, p = 0, k = 0, l = 0, m = 0;
                                                while (banco[i][k] != L'\0') {
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k] == L'&') {
                                                            aux4[p - 1] = L'\0';
                                                            b = 2;
                                                            p = 0;
                                                        }

                                                    } else if (b == 2) {
                                                        if (l == 0) {
                                                            aux[p] = banco[i][k];
                                                            p++;
                                                        } else {
                                                            aux2[m] = banco[i][k];
                                                            m++;
                                                        }
                                                        if (banco[i][k] == L'%') {
                                                            if (l != 0) {
                                                                aux2[m - 1] = L',';
                                                                l++;
                                                            } else {
                                                                l = 1;
                                                            }
                                                        }
                                                    }
                                                    k++;
                                                }
                                                aux2[m] = L'\0';
                                                if (l == 0) {
                                                    aux[p] = L'\0';
                                                    wcscpy(aux2, L"(Ninguno)");
                                                } else {
                                                    aux[p - 1] = L'\0';
                                                }
                                                if (wcscasecmp(aux4, L"POR") == 0) {
                                                    wprintf(L"%d] Clave:%-8lsPalabra(s):%-10lsSinonimo(s):%-5ls\n", j++, aux3, aux, aux2);
                                                }
                                            }
                                        } else {
                                            wprintf(L"\nNo existen palabras registradas del idioma portugues\n");
                                        }
                                        break;
                                    case 'F':
                                        if (b6 > 0) {
                                            j = 1;
                                            for (i = 0; i < cont; i++) {
                                                aux[0] = L'\0';
                                                aux2[0] = L'\0';
                                                aux3[0] = L'\0';
                                                aux4[0] = L'\0';
                                                b = 0, p = 0, k = 0, l = 0, m = 0;
                                                while (banco[i][k] != L'\0') {
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k] == L'&') {
                                                            aux4[p - 1] = L'\0';
                                                            b = 2;
                                                            p = 0;
                                                        }

                                                    } else if (b == 2) {
                                                        if (l == 0) {
                                                            aux[p] = banco[i][k];
                                                            p++;
                                                        } else {
                                                            aux2[m] = banco[i][k];
                                                            m++;
                                                        }
                                                        if (banco[i][k] == L'%') {
                                                            if (l != 0) {
                                                                aux2[m - 1] = L',';
                                                                l++;
                                                            } else {
                                                                l = 1;
                                                            }
                                                        }
                                                    }
                                                    k++;
                                                }
                                                aux2[m] = L'\0';
                                                if (l == 0) {
                                                    aux[p] = L'\0';
                                                    wcscpy(aux2, L"(Ninguno)");
                                                } else {
                                                    aux[p - 1] = L'\0';
                                                }
                                                if (wcscasecmp(aux4, L"FRA") == 0) {
                                                    wprintf(L"%d] Clave:%-8lsPalabra(s):%-10lsSinonimo(s):%-5ls\n", j++, aux3, aux, aux2);
                                                }
                                            }
                                        } else {
                                            wprintf(L"\nNo existen palabras registradas del idioma frances\n");
                                        }
                                        break;
                                    case 'G':
                                        wprintf(L"\nRegresando...\n");
                                        break;
                                    default:
                                        wprintf(L"\nOpcion invalida\n");
                                        break;
                                }
                            }
                        } while (strcasecmp(aux9, "G") != 0);
                    } else {
                        wprintf(L"\nNo existen palabras registradas\n");
                    }
                    break;
                case 4:
                    if (cont > 0) {

                        do {
                            op2 = '\0';
                            aux9[0] = '\0';
                            wprintf(L"\nAplicar examen de idioma:\n");
                            wprintf(L"A-Examen de ingles\nB-Examen de frances\nC-Examen de aleman\nD-Examen de italiano\nE-Examen de portugues\nF-Regresar\nOpcion:");
                            while (getchar() != '\n');
                            scanf("%[^\n]", aux9);
                            if (strlen(aux9) == 1) {
                                op2 = aux9[0];
                                op2=toupper(op2);
                                switch (op2) {
                                    case 'A':
                                        ac = 0;
                                        e = 0;
                                        l = 0;
                                        if (b1 != 0) {
                                            for (i = 0; i < cont; i++) {
                                                aux3[0] = L'\0';
                                                b = 0;
                                                p = 0;
                                                k = 0;
                                                while (banco[i][k] != L'&') { //Obtengo la palabra
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k + 1] == L'&') {
                                                            aux4[p] = L'\0';
                                                        }
                                                    }
                                                    k++;
                                                }
                                                if (wcscasecmp(aux4, L"ENG") == 0) {
                                                    m = 0;
                                                    while (m < cont) {
                                                        aux[0] = L'\0';
                                                        aux2[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        b = 0;
                                                        p = 0;
                                                        k = 0;
                                                        while (banco[m][k] != L'&') {
                                                            if (b == 0) {
                                                                aux[k] = banco[m][k];
                                                                if (banco[m][k] == L'?') {
                                                                    aux[k] = L'\0';
                                                                    b = 1;
                                                                }
                                                            } else if (b == 1) {
                                                                aux2[p] = banco[m][k];
                                                                p++;
                                                            }
                                                            k++;
                                                        }
                                                        aux2[p] = L'\0';
                                                        if (wcscasecmp(aux3, aux) == 0 && wcscasecmp(aux2, L"ESP") == 0) {
                                                            l++;
                                                        }
                                                        m++;
                                                    }
                                                }
                                            }
                                        } else {
                                            wprintf(L"Aun no se ha registrado ninguna palabra en este idioma");
                                        }
                                        if (l >= 5) //5 PALABRAS CON SU TRADUCCION EN ESPAÑOL
                                        {
                                            do {
                                                aux9[0] = '\0';
                                                b = 0;
                                                wprintf(L"\nIngrese su matricula para aplicar el examen de ingles:");
                                                while (getchar() != '\n');
                                                scanf("%[^\n]", aux9);
                                                for (i = 0; aux9[i] != '\0'; i++) {
                                                    if (isdigit(aux9[i]) == 0) {
                                                        b = 1;
                                                    }
                                                }
                                                if (b == 1) {
                                                    wprintf(L"\nSolo se permite el ingreso de numeros\n");
                                                }
                                            } while (b == 1 || strlen(aux9) == 0);
                                            matricula = atoi(aux9);
                                            i = 1;
                                            c = 0;
                                            wprintf(L"\nBienvenido al examen de inglés, se le mostrará en pantalla 5 palabras en inglés que deberá traducir al español.\n");
                                            wprintf(L"\t\t\tExamen de ingles\n");
                                            do {
                                                do {
                                                    do {//Valida que no se repitan las palabras dentro de la ronda de 5
                                                        b = 0;
                                                        m = rand() % cont;
                                                        aux2[0] = L'\0';
                                                        aux3[0] = L'\0';
                                                        a[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        for (q = 0; q < c; q++) {
                                                            if (m == r[q]) {
                                                                b = -1;
                                                            }
                                                        }
                                                        i1 = 0;
                                                        i2 = 0;
                                                        i3 = 0;
                                                        while (banco[m][i1] != L'\0' && b != -1) {
                                                            if (b == 0) {
                                                                while (banco[m][i1] != L'?') {
                                                                    a[i1] = banco[m][i1]; //Guarda el numero
                                                                    i1++;
                                                                }
                                                                if (banco[m][i1] == L'?') {
                                                                    b = 1;
                                                                    a[i1] = L'\0';
                                                                }
                                                            } else if (b == 1) {
                                                                while (banco[m][i1] != L'&'){
                                                                    aux3[i2] = banco[m][i1];
                                                                    i2++;
                                                                    i1++;
                                                                }
                                                                aux3[i2] = L'\0';
                                                                if (wcscasecmp(aux3, L"ENG") == 0) {
                                                                    b = 2;
                                                                    i2 = 0;
                                                                } else {
                                                                    b = -1;
                                                                }
                                                            } else if (b == 2) {
                                                                if (i3 == 0) {
                                                                    aux2[i2] = banco[m][i1];
                                                                    i2++;
                                                                } else {
                                                                    aux5[i2] = banco[m][i1];
                                                                    i2++;
                                                                }
                                                                if (banco[m][i1] == L'%') {
                                                                    if (i3 != 0) {
                                                                        aux5[i2 - 1] = L',';
                                                                    } else {
                                                                        i3 = 1;
                                                                        aux2[i2 - 1] = L'\0';
                                                                        i2 = 0;
                                                                    }
                                                                }
                                                            }
                                                            i1++;
                                                        }

                                                        if (i3 == 0) {
                                                            aux2[i2] = L'\0';
                                                        }
                                                        aux5[i2] = L'\0';
                                                        if (aux5[0] == L'\0') {
                                                            wcscpy(aux5, L"(Ninguno)");
                                                        }
                                                    } while (b == -1);

                                                    i3 = 0;
                                                    b = 0;
                                                    l = 0;
                                                    while (i3 < cont && b != 1) {
                                                        aux3[0] = L'\0';
                                                        i2 = 0;
                                                        i1 = 0;

                                                        while (banco[i3][i2] != L'?') {
                                                            aux3[i2] = banco[i3][i2];
                                                            i2++;
                                                        }
                                                        aux3[i2] = L'\0';
                                                        i2++;
                                                        while (banco[i3][i2] != L'&') {
                                                            aux6[i1] = banco[i3][i2];
                                                            i2++;
                                                            i1++;
                                                        }
                                                        aux6[i1] = L'\0';
                                                        if (wcscasecmp(aux3, a) == 0 && wcscasecmp(aux6, L"Esp") == 0) {
                                                            b = 1;
                                                        }
                                                        if (b != 1) {
                                                            i3++;
                                                        }
                                                    }
                                                } while (b != 1);
                                                r[c] = m;
                                                c++;
                                                aux4[0] = L'\0';
                                                wprintf(L"Matricula:%-10dAcertadas:%-5dEquivocadas:%-5d\n", matricula, ac, e);
                                                wprintf(L"Palabra %d) %ls\nSinonimos en ingles:%ls\n", i, aux2, aux5);
                                                do {
                                                    wprintf(L"Ingrese traduccion al español:");
                                                    while (getchar() != L'\n');
                                                    scanf("%l[^\n]", aux4);
                                                } while (aux4[0] == L'\0');

                                                i1 = 0;
                                                i2++;
                                                aux7[0] = L'\0';
                                                aux8[0] = L'\0';
                                                while (banco[i3][i2] != L'\0') {
                                                    if (l == 0) {
                                                        aux7[i1] = banco[i3][i2];
                                                        i1++;
                                                    } else {
                                                        aux8[i1] = banco[i3][i2];
                                                        i1++;
                                                    }
                                                    if (banco[i3][i2] == L'%') {
                                                        if (l != 0) {
                                                            aux8[i1 - 1] = L',';
                                                            l++;
                                                        } else {
                                                            aux7[i1 - 1] = L'\0';
                                                            l = 1;
                                                            i1 = 0;
                                                        }
                                                    }
                                                    i2++;
                                                }
                                                if (l == 0) {
                                                    aux7[i1] = L'\0';
                                                }
                                                aux8[i1] = L'\0'; //Sinonimos
                                                b = 0;
                                                if (wcscasecmp(aux7, aux4) == 0) {
                                                    wprintf(L"\n\t\t\tRespuesta correcta\n");
                                                    ac++;
                                                    b = 1;
                                                } else {
                                                    l = 0;
                                                    i2 = 0;
                                                    i1 = 0;
                                                    aux2[0] = L'\0';
                                                    aux3[0] = L'\0';
                                                    if (aux8[0] != L'\0') {
                                                        while (aux8[i1] != L'\0' && b == 0) {
                                                            if (l == 0) {
                                                                aux2[i1] = aux8[i1];
                                                                if (aux8[i1] == L',') {
                                                                    aux2[i1] = L'\0';
                                                                    l = 1;
                                                                }
                                                            } else {
                                                                aux3[i2] = aux8[i1];
                                                                i2++;
                                                            }
                                                            i1++;
                                                        }
                                                        if (l == 0) {
                                                            aux2[i1] = L'\0';
                                                        } else {
                                                            aux3[i2] = L'\0';
                                                        }

                                                        if (wcscasecmp(aux2, aux4) == 0 || wcscasecmp(aux3, aux4) == 0) {
                                                            ac++;
                                                            b = 1;
                                                        }
                                                    }

                                                    if (b == 0) {
                                                        wprintf(L"\n\t\t\tRespuesta incorrecta");
                                                        wprintf(L"\nRespuesta:%ls\n", aux7);
                                                        e++;
                                                    }
                                                }
                                                i++;
                                            } while (i <= 5); //5 RONDAS DE PALABRAS
                                            wprintf(L"\n\t\t\tRESULTADOS DEL EXAMEN\n");
                                            wprintf(L"\nTraducciones acertadas: %d\nTraducciones equivocadas:%d\n", ac, e);
                                            wprintf(L"Calificacion de %d : %d\n", matricula, ac * 20);
                                        } else {
                                            wprintf(L"\nSon por lo menos 5 traducciones de este idioma al español para poder aplicar el examen\n");
                                        }
                                        break;
                                    case 'B':
                                        ac = 0;
                                        e = 0;
                                        l = 0;
                                        if (b1 != 0) {
                                            for (i = 0; i < cont; i++) {
                                                aux3[0] = L'\0';
                                                b = 0;
                                                p = 0;
                                                k = 0;
                                                while (banco[i][k] != L'&') { //Obtengo la palabra
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k + 1] == L'&') {
                                                            aux4[p] = L'\0';
                                                        }
                                                    }
                                                    k++;
                                                }
                                                if (wcscasecmp(aux4, L"FRA") == 0) {
                                                    m = 0;
                                                    while (m < cont) {
                                                        aux[0] = L'\0';
                                                        aux2[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        b = 0;
                                                        p = 0;
                                                        k = 0;
                                                        while (banco[m][k] != L'&') {
                                                            if (b == 0) {
                                                                aux[k] = banco[m][k];
                                                                if (banco[m][k] == L'?') {
                                                                    aux[k] = L'\0';
                                                                    b = 1;
                                                                }
                                                            } else if (b == 1) {
                                                                aux2[p] = banco[m][k];
                                                                p++;
                                                            }
                                                            k++;
                                                        }
                                                        aux2[p] = L'\0';
                                                        if (wcscasecmp(aux3, aux) == 0 && wcscasecmp(aux2, L"ESP") == 0) {
                                                            l++;
                                                        }
                                                        m++;
                                                    }
                                                }
                                            }
                                        } else {
                                            wprintf(L"Aun no se ha registrado ninguna palabra en este idioma");
                                        }
                                        if (l >= 5) //5 PALABRAS CON SU TRADUCCION EN ESPAÑOL
                                        {
                                            do {
                                                aux9[0] = '\0';
                                                b = 0;
                                                wprintf(L"\nIngrese su matricula para aplicar el examen de frances:");
                                                while (getchar() != '\n');
                                                scanf("%[^\n]", aux9);
                                                for (i = 0; aux9[i] != '\0'; i++) {
                                                    if (isdigit(aux9[i]) == 0) {
                                                        b = 1;
                                                    }
                                                }
                                                if (b == 1) {
                                                    wprintf(L"\nSolo se permite el ingreso de numeros\n");
                                                }
                                            } while (b == 1 || strlen(aux9) == 0);
                                            matricula = atoi(aux9);
                                            i = 1;
                                            c = 0;
                                            wprintf(L"\nBienvenido al examen de frances, se le mostrará en pantalla 5 palabras en frances que deberá traducir al español.\n");
                                            wprintf(L"\t\t\tExamen de frances\n");
                                            do {
                                                do {
                                                    do {//Valida que no se repitan las palabras dentro de la ronda de 5
                                                        b = 0;
                                                        m = rand() % cont;
                                                        aux2[0] = L'\0';
                                                        aux3[0] = L'\0';
                                                        a[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        for (q = 0; q < c; q++) {
                                                            if (m == r[q]) {
                                                                b = -1;
                                                            }
                                                        }
                                                        i1 = 0;
                                                        i2 = 0;
                                                        i3 = 0;
                                                        while (banco[m][i1] != L'\0' && b != -1) {
                                                            if (b == 0) {
                                                                while (banco[m][i1] != L'?') {
                                                                    a[i1] = banco[m][i1]; //Guarda el numero
                                                                    i1++;
                                                                }
                                                                if (banco[m][i1] == L'?') {
                                                                    b = 1;
                                                                    a[i1] = L'\0';
                                                                }
                                                            } else if (b == 1) {
                                                                while (banco[m][i1] != L'&') {
                                                                    aux3[i2] = banco[m][i1];
                                                                    i2++;
                                                                    i1++;
                                                                }
                                                                aux3[i2] = L'\0';
                                                                if (wcscasecmp(aux3, L"FRA") == 0) {
                                                                    b = 2;
                                                                    i2 = 0;
                                                                } else {
                                                                    b = -1;
                                                                }
                                                            } else if (b == 2) {
                                                                if (i3 == 0) {
                                                                    aux2[i2] = banco[m][i1];
                                                                    i2++;
                                                                } else {
                                                                    aux5[i2] = banco[m][i1];
                                                                    i2++;
                                                                }
                                                                if (banco[m][i1] == L'%') {
                                                                    if (i3 != 0) {
                                                                        aux5[i2 - 1] = L',';
                                                                    } else {
                                                                        i3 = 1;
                                                                        aux2[i2 - 1] = L'\0';
                                                                        i2 = 0;
                                                                    }
                                                                }
                                                            }
                                                            i1++;
                                                        }
                                                        if (i3 == 0) {
                                                            aux2[i2] = L'\0';
                                                        }
                                                        aux5[i2] = L'\0';
                                                        if (aux5[0] == L'\0') {
                                                            wcscpy(aux5, L"(Ninguno)");
                                                        }
                                                    } while (b == -1);
                                                    i3 = 0;
                                                    b = 0;
                                                    l = 0;
                                                    while (i3 < cont && b != 1) {
                                                        aux3[0] = L'\0';
                                                        i2 = 0;
                                                        i1 = 0;

                                                        while (banco[i3][i2] != L'?') {
                                                            aux3[i2] = banco[i3][i2];
                                                            i2++;
                                                        }
                                                        aux3[i2] = L'\0';
                                                        i2++;
                                                        while (banco[i3][i2] != L'&') {
                                                            aux6[i1] = banco[i3][i2];
                                                            i2++;
                                                            i1++;
                                                        }
                                                        aux6[i1] = L'\0';
                                                        if (wcscasecmp(aux3, a) == 0 && wcscasecmp(aux6, L"Esp") == 0) {
                                                            b = 1;
                                                        }
                                                        if (b != 1) {
                                                            i3++;
                                                        }
                                                    }
                                                } while (b != 1);
                                                r[c] = m;
                                                c++;
                                                aux4[0] = L'\0';
                                                wprintf(L"Matricula:%-10dAcertadas:%-5dEquivocadas:%-5d\n", matricula, ac, e);
                                                wprintf(L"Palabra %d) %ls\nSinonimos en frances:%ls\n", i, aux2, aux5);
                                                do {
                                                    wprintf(L"Ingrese traduccion al español:");
                                                    while (getchar() != L'\n');
                                                    scanf("%l[^\n]", aux4);
                                                } while (aux4[0] == L'\0');
                                                i1 = 0;
                                                i2++;
                                                aux7[0] = L'\0';
                                                aux8[0] = L'\0';
                                                while (banco[i3][i2] != L'\0') {
                                                    if (l == 0) {
                                                        aux7[i1] = banco[i3][i2];
                                                        i1++;
                                                    } else {
                                                        aux8[i1] = banco[i3][i2];
                                                        i1++;
                                                    }
                                                    if (banco[i3][i2] == L'%') {
                                                        if (l != 0) {
                                                            aux8[i1 - 1] = L',';
                                                            l++;
                                                        } else {
                                                            aux7[i1 - 1] = L'\0';
                                                            l = 1;
                                                            i1 = 0;
                                                        }
                                                    }
                                                    i2++;
                                                }
                                                if (l == 0) {
                                                    aux7[i1] = L'\0';
                                                }
                                                aux8[i1] = L'\0'; //Sinonimos
                                                b = 0;
                                                if (wcscasecmp(aux7, aux4) == 0) {
                                                    wprintf(L"\n\t\t\tRespuesta correcta\n");
                                                    ac++;
                                                    b = 1;
                                                } else {
                                                    l = 0;
                                                    i2 = 0;
                                                    i1 = 0;
                                                    aux2[0] = L'\0';
                                                    aux3[0] = L'\0';
                                                    if (aux8[0] != L'\0') {
                                                        while (aux8[i1] != L'\0' && b == 0) {
                                                            if (l == 0) {
                                                                aux2[i1] = aux8[i1];
                                                                if (aux8[i1] == L',') {
                                                                    aux2[i1] = L'\0';
                                                                    l = 1;
                                                                }
                                                            } else {
                                                                aux3[i2] = aux8[i1];
                                                                i2++;
                                                            }
                                                            i1++;
                                                        }
                                                        if (l == 0) {
                                                            aux2[i1] = L'\0';
                                                        } else {
                                                            aux3[i2] = L'\0';
                                                        }

                                                        if (wcscasecmp(aux2, aux4) == 0 || wcscasecmp(aux3, aux4) == 0) {
                                                            ac++;
                                                            b = 1;
                                                        }
                                                    }
                                                    if (b == 0) {
                                                        wprintf(L"\n\t\t\tRespuesta incorrecta");
                                                        wprintf(L"\nRespuesta:%ls\n", aux7);
                                                        e++;
                                                    }
                                                }
                                                i++;
                                            } while (i <= 5); //5 RONDAS DE PALABRAS
                                            wprintf(L"\n\t\t\tRESULTADOS DEL EXAMEN\n");
                                            wprintf(L"\nTraducciones acertadas: %d\nTraducciones equivocadas:%d\n", ac, e);
                                            wprintf(L"Calificacion de %d : %d\n", matricula, ac * 20);
                                        } else {
                                            wprintf(L"\nSon por lo menos 5 traducciones de este idioma al español para poder aplicar el examen\n");
                                        }
                                        break;
                                    case 'C':
                                        ac = 0;
                                        e = 0;
                                        l = 0;
                                        if (b1 != 0) {
                                            for (i = 0; i < cont; i++) {
                                                aux3[0] = L'\0';
                                                b = 0;
                                                p = 0;
                                                k = 0;
                                                while (banco[i][k] != L'&') { //Obtengo la palabra
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k + 1] == L'&') {
                                                            aux4[p] = L'\0';
                                                        }
                                                    }
                                                    k++;
                                                }
                                                if (wcscasecmp(aux4, L"DEU") == 0) {
                                                    m = 0;
                                                    while (m < cont) {
                                                        aux[0] = L'\0';
                                                        aux2[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        b = 0;
                                                        p = 0;
                                                        k = 0;
                                                        while (banco[m][k] != L'&') {
                                                            if (b == 0) {
                                                                aux[k] = banco[m][k];
                                                                if (banco[m][k] == L'?') {
                                                                    aux[k] = L'\0';
                                                                    b = 1;
                                                                }
                                                            } else if (b == 1) {
                                                                aux2[p] = banco[m][k];
                                                                p++;
                                                            }
                                                            k++;
                                                        }
                                                        aux2[p] = L'\0';
                                                        if (wcscasecmp(aux3, aux) == 0 && wcscasecmp(aux2, L"ESP") == 0) {
                                                            l++;
                                                        }
                                                        m++;
                                                    }
                                                }
                                            }
                                        } else {
                                            wprintf(L"Aun no se ha registrado ninguna palabra en este idioma");
                                        }
                                        if (l >= 5) //5 PALABRAS CON SU TRADUCCION EN ESPAÑOL
                                        {
                                            do {
                                                aux9[0] = '\0';
                                                b = 0;
                                                wprintf(L"\nIngrese su matricula para aplicar el examen de aleman:");
                                                while (getchar() != '\n');
                                                scanf("%[^\n]", aux9);
                                                for (i = 0; aux9[i] != '\0'; i++) {
                                                    if (isdigit(aux9[i]) == 0) {
                                                        b = 1;
                                                    }
                                                }
                                                if (b == 1) {
                                                    wprintf(L"\nSolo se permite el ingreso de numeros\n");
                                                }
                                            } while (b == 1 || strlen(aux9) == 0);
                                            matricula = atoi(aux9);
                                            i = 1;
                                            c = 0;
                                            wprintf(L"\nBienvenido al examen de aleman, se le mostrará en pantalla 5 palabras en aleman que deberá traducir al español.\n");
                                            wprintf(L"\t\t\tExamen de aleman\n");
                                            do {
                                                do {
                                                    do {//Valida que no se repitan las palabras dentro de la ronda de 5
                                                        b = 0;
                                                        m = rand() % cont;
                                                        aux2[0] = L'\0';
                                                        aux3[0] = L'\0';
                                                        a[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        for (q = 0; q < c; q++) {
                                                            if (m == r[q]) {
                                                                b = -1;
                                                            }
                                                        }
                                                        i1 = 0;
                                                        i2 = 0;
                                                        i3 = 0;
                                                        while (banco[m][i1] != L'\0' && b != -1) {
                                                            if (b == 0) {
                                                                while (banco[m][i1] != L'?') {
                                                                    a[i1] = banco[m][i1]; //Guarda el numero
                                                                    i1++;
                                                                }
                                                                if (banco[m][i1] == L'?') {
                                                                    b = 1;
                                                                    a[i1] = L'\0';
                                                                }
                                                            } else if (b == 1) {
                                                                while (banco[m][i1] != L'&') {
                                                                    aux3[i2] = banco[m][i1];
                                                                    i2++;
                                                                    i1++;
                                                                }
                                                                aux3[i2] = L'\0';
                                                                if (wcscasecmp(aux3, L"DEU") == 0) {
                                                                    b = 2;
                                                                    i2 = 0;
                                                                } else {
                                                                    b = -1;
                                                                }
                                                            } else if (b == 2) {
                                                                if (i3 == 0) {
                                                                    aux2[i2] = banco[m][i1];
                                                                    i2++;
                                                                } else {
                                                                    aux5[i2] = banco[m][i1];
                                                                    i2++;
                                                                }
                                                                if (banco[m][i1] == L'%') {
                                                                    if (i3 != 0) {
                                                                        aux5[i2 - 1] = L',';
                                                                    } else {
                                                                        i3 = 1;
                                                                        aux2[i2 - 1] = L'\0';
                                                                        i2 = 0;
                                                                    }
                                                                }
                                                            }
                                                            i1++;
                                                        }
                                                        if (i3 == 0) {
                                                            aux2[i2] = L'\0';
                                                        }
                                                        aux5[i2] = L'\0';
                                                        if (aux5[0] == L'\0') {
                                                            wcscpy(aux5, L"(Ninguno)");
                                                        }
                                                    } while (b == -1);
                                                    i3 = 0;
                                                    b = 0;
                                                    l = 0;
                                                    while (i3 < cont && b != 1) {
                                                        aux3[0] = L'\0';
                                                        i2 = 0;
                                                        i1 = 0;

                                                        while (banco[i3][i2] != L'?') {
                                                            aux3[i2] = banco[i3][i2];
                                                            i2++;
                                                        }
                                                        aux3[i2] = L'\0';
                                                        i2++;
                                                        while (banco[i3][i2] != L'&') {
                                                            aux6[i1] = banco[i3][i2];
                                                            i2++;
                                                            i1++;
                                                        }
                                                        aux6[i1] = L'\0';
                                                        if (wcscasecmp(aux3, a) == 0 && wcscasecmp(aux6, L"Esp") == 0) {
                                                            b = 1;
                                                        }
                                                        if (b != 1) {
                                                            i3++;
                                                        }
                                                    }
                                                } while (b != 1);
                                                r[c] = m;
                                                c++;
                                                aux4[0] = L'\0';
                                                wprintf(L"Matricula:%-10dAcertadas:%-5dEquivocadas:%-5d\n", matricula, ac, e);
                                                wprintf(L"Palabra %d) %ls\nSinonimos en aleman:%ls\n", i, aux2, aux5);
                                                do {
                                                    wprintf(L"Ingrese traduccion al español:");
                                                    while (getchar() != L'\n');
                                                    scanf("%l[^\n]", aux4);
                                                } while (aux4[0] == L'\0');
                                                i1 = 0;
                                                i2++;
                                                aux7[0] = L'\0';
                                                aux8[0] = L'\0';
                                                while (banco[i3][i2] != L'\0') {
                                                    if (l == 0) {
                                                        aux7[i1] = banco[i3][i2];
                                                        i1++;
                                                    } else {
                                                        aux8[i1] = banco[i3][i2];
                                                        i1++;
                                                    }
                                                    if (banco[i3][i2] == L'%') {
                                                        if (l != 0) {
                                                            aux8[i1 - 1] = L',';
                                                            l++;
                                                        } else {
                                                            aux7[i1 - 1] = L'\0';
                                                            l = 1;
                                                            i1 = 0;
                                                        }
                                                    }
                                                    i2++;
                                                }
                                                if (l == 0) {
                                                    aux7[i1] = L'\0';
                                                }
                                                aux8[i1] = L'\0'; //Sinonimos
                                                b = 0;
                                                if (wcscasecmp(aux7, aux4) == 0) {
                                                    wprintf(L"\n\t\t\tRespuesta correcta\n");
                                                    ac++;
                                                    b = 1;
                                                } else {
                                                    l = 0;
                                                    i2 = 0;
                                                    i1 = 0;
                                                    aux2[0] = L'\0';
                                                    aux3[0] = L'\0';
                                                    if (aux8[0] != L'\0') {
                                                        while (aux8[i1] != L'\0' && b == 0) {
                                                            if (l == 0) {
                                                                aux2[i1] = aux8[i1];
                                                                if (aux8[i1] == L',') {
                                                                    aux2[i1] = L'\0';
                                                                    l = 1;
                                                                }
                                                            } else {
                                                                aux3[i2] = aux8[i1];
                                                                i2++;
                                                            }
                                                            i1++;
                                                        }
                                                        if (l == 0) {
                                                            aux2[i1] = L'\0';
                                                        } else {
                                                            aux3[i2] = L'\0';
                                                        }
                                                        if (wcscasecmp(aux2, aux4) == 0 || wcscasecmp(aux3, aux4) == 0) {
                                                            ac++;
                                                            b = 1;
                                                        }
                                                    }
                                                    if (b == 0) {
                                                        wprintf(L"\n\t\t\tRespuesta incorrecta");
                                                        wprintf(L"\nRespuesta:%ls\n", aux7);
                                                        e++;
                                                    }
                                                }
                                                i++;
                                            } while (i <= 5); //5 RONDAS DE PALABRAS
                                            wprintf(L"\n\t\t\tRESULTADOS DEL EXAMEN\n");
                                            wprintf(L"\nTraducciones acertadas: %d\nTraducciones equivocadas:%d\n", ac, e);
                                            wprintf(L"Calificacion de %d : %d\n", matricula, ac * 20);
                                        } else {
                                            wprintf(L"\nSon por lo menos 5 traducciones de este idioma al español para poder aplicar el examen\n");
                                        }
                                        break;
                                    case 'D':
                                        ac = 0;
                                        e = 0;
                                        l = 0;
                                        if (b1 != 0) {
                                            for (i = 0; i < cont; i++) {
                                                aux3[0] = L'\0';
                                                b = 0;
                                                p = 0;
                                                k = 0;
                                                while (banco[i][k] != L'&') { //Obtengo la palabra
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k + 1] == L'&') {
                                                            aux4[p] = L'\0';
                                                        }
                                                    }
                                                    k++;
                                                }
                                                if (wcscasecmp(aux4, L"ITA") == 0) {
                                                    m = 0;
                                                    while (m < cont) {
                                                        aux[0] = L'\0';
                                                        aux2[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        b = 0;
                                                        p = 0;
                                                        k = 0;
                                                        while (banco[m][k] != L'&') {
                                                            if (b == 0) {
                                                                aux[k] = banco[m][k];
                                                                if (banco[m][k] == L'?') {
                                                                    aux[k] = L'\0';
                                                                    b = 1;
                                                                }
                                                            } else if (b == 1) {
                                                                aux2[p] = banco[m][k];
                                                                p++;
                                                            }
                                                            k++;
                                                        }
                                                        aux2[p] = L'\0';
                                                        if (wcscasecmp(aux3, aux) == 0 && wcscasecmp(aux2, L"ESP") == 0) {
                                                            l++;
                                                        }
                                                        m++;
                                                    }
                                                }
                                            }
                                        } else {
                                            wprintf(L"Aun no se ha registrado ninguna palabra en este idioma");
                                        }
                                        if (l >= 5) //5 PALABRAS CON SU TRADUCCION EN ESPAÑOL
                                        {
                                            do {
                                                aux9[0] = '\0';
                                                b = 0;
                                                wprintf(L"\nIngrese su matricula para aplicar el examen de italiano:");
                                                while (getchar() != '\n');
                                                scanf("%[^\n]", aux9);
                                                for (i = 0; aux9[i] != '\0'; i++) {
                                                    if (isdigit(aux9[i]) == 0) {
                                                        b = 1;
                                                    }
                                                }
                                                if (b == 1) {
                                                    wprintf(L"\nSolo se permite el ingreso de numeros\n");
                                                }
                                            } while (b == 1 || strlen(aux9) == 0);
                                            matricula = atoi(aux9);
                                            i = 1;
                                            c = 0;
                                            wprintf(L"\nBienvenido al examen de italiano, se le mostrará en pantalla 5 palabras en inglés que deberá traducir al español.\n");
                                            wprintf(L"\t\t\tExamen de italiano\n");
                                            do {
                                                do {
                                                    do {//Valida que no se repitan las palabras dentro de la ronda de 5

                                                        b = 0;
                                                        m = rand() % cont;
                                                        aux2[0] = L'\0';
                                                        aux3[0] = L'\0';
                                                        a[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        for (q = 0; q < c; q++) {
                                                            if (m == r[q]) {
                                                                b = -1;
                                                            }
                                                        }
                                                        i1 = 0;
                                                        i2 = 0;
                                                        i3 = 0;
                                                        while (banco[m][i1] != L'\0' && b != -1) {
                                                            if (b == 0) {
                                                                while (banco[m][i1] != L'?') {
                                                                    a[i1] = banco[m][i1]; //Guarda el numero
                                                                    i1++;
                                                                }
                                                                if (banco[m][i1] == L'?') {
                                                                    b = 1;
                                                                    a[i1] = L'\0';
                                                                }
                                                            } else if (b == 1) {
                                                                while (banco[m][i1] != L'&') {
                                                                    aux3[i2] = banco[m][i1];
                                                                    i2++;
                                                                    i1++;
                                                                }
                                                                aux3[i2] = L'\0';
                                                                if (wcscasecmp(aux3, L"ITA") == 0) {
                                                                    b = 2;
                                                                    i2 = 0;
                                                                } else {
                                                                    b = -1;
                                                                }
                                                            } else if (b == 2) {
                                                                if (i3 == 0) {
                                                                    aux2[i2] = banco[m][i1];
                                                                    i2++;
                                                                } else {
                                                                    aux5[i2] = banco[m][i1];
                                                                    i2++;
                                                                }
                                                                if (banco[m][i1] == L'%') {
                                                                    if (i3 != 0) {
                                                                        aux5[i2 - 1] = L',';
                                                                    } else {
                                                                        i3 = 1;
                                                                        aux2[i2 - 1] = L'\0';
                                                                        i2 = 0;
                                                                    }
                                                                }
                                                            }
                                                            i1++;
                                                        }

                                                        if (i3 == 0) {
                                                            aux2[i2] = L'\0';
                                                        }
                                                        aux5[i2] = L'\0';
                                                        if (aux5[0] == L'\0') {
                                                            wcscpy(aux5, L"(Ninguno)");
                                                        }
                                                    } while (b == -1);

                                                    i3 = 0;
                                                    b = 0;
                                                    l = 0;
                                                    while (i3 < cont && b != 1) {
                                                        aux3[0] = L'\0';
                                                        i2 = 0;
                                                        i1 = 0;

                                                        while (banco[i3][i2] != L'?') {
                                                            aux3[i2] = banco[i3][i2];
                                                            i2++;
                                                        }
                                                        aux3[i2] = L'\0';
                                                        i2++;
                                                        while (banco[i3][i2] != L'&') {
                                                            aux6[i1] = banco[i3][i2];
                                                            i2++;
                                                            i1++;
                                                        }
                                                        aux6[i1] = L'\0';
                                                        if (wcscasecmp(aux3, a) == 0 && wcscasecmp(aux6, L"Esp") == 0) {
                                                            b = 1;
                                                        }
                                                        if (b != 1) {
                                                            i3++;
                                                        }
                                                    }
                                                } while (b != 1);
                                                r[c] = m;
                                                c++;
                                                aux4[0] = L'\0';
                                                wprintf(L"Matricula:%-10dAcertadas:%-5dEquivocadas:%-5d\n", matricula, ac, e);
                                                wprintf(L"Palabra %d) %ls\nSinonimos en italiano:%ls\n", i, aux2, aux5);
                                                do {
                                                    wprintf(L"Ingrese traduccion al español:");
                                                    while (getchar() != L'\n');
                                                    scanf("%l[^\n]", aux4);
                                                } while (aux4[0] == L'\0');

                                                i1 = 0;
                                                i2++;
                                                aux7[0] = L'\0';
                                                aux8[0] = L'\0';
                                                while (banco[i3][i2] != L'\0') {
                                                    if (l == 0) {
                                                        aux7[i1] = banco[i3][i2];
                                                        i1++;
                                                    } else {
                                                        aux8[i1] = banco[i3][i2];
                                                        i1++;
                                                    }
                                                    if (banco[i3][i2] == L'%') {
                                                        if (l != 0) {
                                                            aux8[i1 - 1] = L',';
                                                            l++;
                                                        } else {
                                                            aux7[i1 - 1] = L'\0';
                                                            l = 1;
                                                            i1 = 0;
                                                        }
                                                    }
                                                    i2++;
                                                }
                                                if (l == 0) {
                                                    aux7[i1] = L'\0';
                                                }
                                                aux8[i1] = L'\0'; //Sinonimos
                                                b = 0;
                                                if (wcscasecmp(aux7, aux4) == 0) {
                                                    wprintf(L"\n\t\t\tRespuesta correcta\n");
                                                    ac++;
                                                    b = 1;
                                                } else {
                                                    l = 0;
                                                    i2 = 0;
                                                    i1 = 0;
                                                    aux2[0] = L'\0';
                                                    aux3[0] = L'\0';
                                                    if (aux8[0] != L'\0') {
                                                        while (aux8[i1] != L'\0' && b == 0) {
                                                            if (l == 0) {
                                                                aux2[i1] = aux8[i1];
                                                                if (aux8[i1] == L',') {
                                                                    aux2[i1] = L'\0';
                                                                    l = 1;
                                                                }
                                                            } else {
                                                                aux3[i2] = aux8[i1];
                                                                i2++;
                                                            }
                                                            i1++;
                                                        }
                                                        if (l == 0) {
                                                            aux2[i1] = L'\0';
                                                        } else {
                                                            aux3[i2] = L'\0';
                                                        }
                                                        if (wcscasecmp(aux2, aux4) == 0 || wcscasecmp(aux3, aux4) == 0) {
                                                            ac++;
                                                            b = 1;
                                                        }
                                                    }
                                                    if (b == 0) {
                                                        wprintf(L"\n\t\t\tRespuesta incorrecta");
                                                        wprintf(L"\nRespuesta:%ls\n", aux7);
                                                        e++;
                                                    }
                                                }
                                                i++;
                                            } while (i <= 5); //5 RONDAS DE PALABRAS
                                            wprintf(L"\n\t\t\tRESULTADOS DEL EXAMEN\n");
                                            wprintf(L"\nTraducciones acertadas: %d\nTraducciones equivocadas:%d\n", ac, e);
                                            wprintf(L"Calificacion de %d : %d\n", matricula, ac * 20);
                                        } else {
                                            wprintf(L"\nSon por lo menos 5 traducciones de este idioma al español para poder aplicar el examen\n");
                                        }
                                        break;
                                    case 'E':
                                        ac = 0;
                                        e = 0;
                                        l = 0;
                                        if (b1 != 0) {
                                            for (i = 0; i < cont; i++) {
                                                aux3[0] = L'\0';
                                                b = 0;
                                                p = 0;
                                                k = 0;
                                                while (banco[i][k] != L'&') { //Obtengo la palabra
                                                    if (b == 0) {
                                                        aux3[k] = banco[i][k];
                                                        if (banco[i][k] == L'?') {
                                                            aux3[k] = L'\0';
                                                            b = 1;
                                                        }
                                                    } else if (b == 1) {
                                                        aux4[p] = banco[i][k];
                                                        p++;
                                                        if (banco[i][k + 1] == L'&') {
                                                            aux4[p] = L'\0';
                                                        }
                                                    }
                                                    k++;
                                                }
                                                if (wcscasecmp(aux4, L"POR") == 0) {
                                                    m = 0;
                                                    while (m < cont) {
                                                        aux[0] = L'\0';
                                                        aux2[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        b = 0;
                                                        p = 0;
                                                        k = 0;
                                                        while (banco[m][k] != L'&') {
                                                            if (b == 0) {
                                                                aux[k] = banco[m][k];
                                                                if (banco[m][k] == L'?') {
                                                                    aux[k] = L'\0';
                                                                    b = 1;
                                                                }
                                                            } else if (b == 1) {
                                                                aux2[p] = banco[m][k];
                                                                p++;
                                                            }
                                                            k++;
                                                        }
                                                        aux2[p] = L'\0';
                                                        if (wcscasecmp(aux3, aux) == 0 && wcscasecmp(aux2, L"ESP") == 0) {
                                                            l++;
                                                        }
                                                        m++;
                                                    }
                                                }
                                            }
                                        } else {
                                            wprintf(L"Aun no se ha registrado ninguna palabra en este idioma");
                                        }
                                        if (l >= 5) //5 PALABRAS CON SU TRADUCCION EN ESPAÑOL
                                        {
                                            do {
                                                aux9[0] = '\0';
                                                b = 0;
                                                wprintf(L"\nIngrese su matricula para aplicar el examen de portugues:");
                                                while (getchar() != '\n');
                                                scanf("%[^\n]", aux9);
                                                for (i = 0; aux9[i] != '\0'; i++) {
                                                    if (isdigit(aux9[i]) == 0) {
                                                        b = 1;
                                                    }
                                                }
                                                if (b == 1) {
                                                    wprintf(L"\nSolo se permite el ingreso de numeros\n");
                                                }
                                            } while (b == 1 || strlen(aux9) == 0);
                                            matricula = atoi(aux9);
                                            i = 1;
                                            c = 0;
                                            wprintf(L"\nBienvenido al examen de portugues, se le mostrará en pantalla 5 palabras en portugues que deberá traducir al español.\n");
                                            wprintf(L"\t\t\tExamen de portugues\n");
                                            do {
                                                do {
                                                    do {//Valida que no se repitan las palabras dentro de la ronda de 5
                                                        b = 0;
                                                        m = rand() % cont;
                                                        aux2[0] = L'\0';
                                                        aux3[0] = L'\0';
                                                        a[0] = L'\0';
                                                        aux5[0] = L'\0';
                                                        for (q = 0; q < c; q++) {
                                                            if (m == r[q]) {
                                                                b = -1;
                                                            }
                                                        }
                                                        i1 = 0,i2 = 0,i3 = 0;
                                                        while (banco[m][i1] != L'\0' && b != -1) {
                                                            if (b == 0) {
                                                                while (banco[m][i1] != L'?') {
                                                                    a[i1] = banco[m][i1]; //Guarda el numero
                                                                    i1++;
                                                                }
                                                                if (banco[m][i1] == L'?') {
                                                                    b = 1;
                                                                    a[i1] = L'\0';
                                                                }
                                                            } else if (b == 1) {
                                                                while (banco[m][i1] != L'&') {
                                                                    aux3[i2] = banco[m][i1];
                                                                    i2++;
                                                                    i1++;
                                                                }
                                                                aux3[i2] = L'\0';
                                                                if (wcscasecmp(aux3, L"POR") == 0) {
                                                                    b = 2;
                                                                    i2 = 0;
                                                                } else {
                                                                    b = -1;
                                                                }
                                                            } else if (b == 2) {
                                                                if (i3 == 0) {
                                                                    aux2[i2] = banco[m][i1];
                                                                    i2++;
                                                                } else {
                                                                    aux5[i2] = banco[m][i1];
                                                                    i2++;
                                                                }
                                                                if (banco[m][i1] == L'%') {
                                                                    if (i3 != 0) {
                                                                        aux5[i2 - 1] = L',';
                                                                    } else {
                                                                        i3 = 1;
                                                                        aux2[i2 - 1] = L'\0';
                                                                        i2 = 0;
                                                                    }
                                                                }
                                                            }
                                                            i1++;
                                                        }
                                                        if (i3 == 0) {
                                                            aux2[i2] = L'\0';
                                                        }
                                                        aux5[i2] = L'\0';
                                                        if (aux5[0] == L'\0') {
                                                            wcscpy(aux5, L"(Ninguno)");
                                                        }
                                                    } while (b == -1);
                                                    i3 = 0,b = 0,l = 0;
                                                    while (i3 < cont && b != 1) {
                                                        aux3[0] = L'\0';
                                                        i2 = 0,i1 = 0;
                                                        while (banco[i3][i2] != L'?') {
                                                            aux3[i2] = banco[i3][i2];
                                                            i2++;
                                                        }
                                                        aux3[i2] = L'\0';
                                                        i2++;
                                                        while (banco[i3][i2] != L'&') {
                                                            aux6[i1] = banco[i3][i2];
                                                            i2++;
                                                            i1++;
                                                        }
                                                        aux6[i1] = L'\0';
                                                        if (wcscasecmp(aux3, a) == 0 && wcscasecmp(aux6, L"Esp") == 0) {
                                                            b = 1;
                                                        }
                                                        if (b != 1) {
                                                            i3++;
                                                        }
                                                    }
                                                } while (b != 1);
                                                r[c] = m;
                                                c++;
                                                aux4[0] = L'\0';
                                                wprintf(L"Matricula:%-10dAcertadas:%-5dEquivocadas:%-5d\n", matricula, ac, e);
                                                wprintf(L"Palabra %d) %ls\nSinonimos en portugues:%ls\n", i, aux2, aux5);
                                                do {
                                                    wprintf(L"Ingrese traduccion al español:");
                                                    while (getchar() != L'\n');
                                                    scanf("%l[^\n]", aux4);
                                                } while (aux4[0] == L'\0');
                                                i1 = 0;
                                                i2++;
                                                aux7[0] = L'\0';
                                                aux8[0] = L'\0';
                                                while (banco[i3][i2] != L'\0') {
                                                    if (l == 0) {
                                                        aux7[i1] = banco[i3][i2];
                                                        i1++;
                                                    } else {
                                                        aux8[i1] = banco[i3][i2];
                                                        i1++;
                                                    }
                                                    if (banco[i3][i2] == L'%') {
                                                        if (l != 0) {
                                                            aux8[i1 - 1] = L',';
                                                            l++;
                                                        } else {
                                                            aux7[i1 - 1] = L'\0';
                                                            l = 1;
                                                            i1 = 0;
                                                        }
                                                    }
                                                    i2++;
                                                }
                                                if (l == 0) {
                                                    aux7[i1] = L'\0';
                                                }
                                                aux8[i1] = L'\0'; //Sinonimos
                                                b = 0;
                                                if (wcscasecmp(aux7, aux4) == 0) {
                                                    wprintf(L"\n\t\t\tRespuesta correcta\n");
                                                    ac++;
                                                    b = 1;
                                                } else {
                                                    l = 0,i2=0,i1=0;
                                                    aux2[0] = L'\0';
                                                    aux3[0] = L'\0';
                                                    if (aux8[0] != L'\0') {
                                                        while (aux8[i1] != L'\0' && b == 0) {
                                                            if (l == 0) {
                                                                aux2[i1] = aux8[i1];
                                                                if (aux8[i1] == L',') {
                                                                    aux2[i1] = L'\0';
                                                                    l = 1;
                                                                }
                                                            } else {
                                                                aux3[i2] = aux8[i1];
                                                                i2++;
                                                            }
                                                            i1++;
                                                        }
                                                        if (l == 0) {
                                                            aux2[i1] = L'\0';
                                                        } else {
                                                            aux3[i2] = L'\0';
                                                        }
                                                        if (wcscasecmp(aux2, aux4) == 0 || wcscasecmp(aux3, aux4) == 0) {
                                                            ac++;
                                                            b = 1;
                                                        }
                                                    }
                                                    if (b == 0) {
                                                        wprintf(L"\n\t\t\tRespuesta incorrecta");
                                                        wprintf(L"\nRespuesta:%ls\n", aux7);
                                                        e++;
                                                    }
                                                }
                                                i++;
                                            } while (i <= 5); //5 RONDAS DE PALABRAS
                                            wprintf(L"\n\t\t\tRESULTADOS DEL EXAMEN\n");
                                            wprintf(L"\nTraducciones acertadas: %d\nTraducciones equivocadas:%d\n", ac, e);
                                            wprintf(L"Calificacion de %d : %d\n", matricula, ac * 20);
                                        } else {
                                            wprintf(L"\nSon por lo menos 5 traducciones de este idioma al español para poder aplicar el examen\n");
                                        }
                                        break;                                  
                                    case 'F':
                                        wprintf(L"\nRegresando...\n");
                                        break;
                                    default:
                                        wprintf(L"Opcion invalida");
                                        break;
                                }
                            }
                        } while (strcasecmp(aux9, "F") != 0);
                        break;
                        case 5:
                        wprintf(L"\nSe ha escogido salir\n");
                        break;
                        default:
                        wprintf(L"\nEscoja una opcion disponible\n");
                    } else {
                        wprintf(L"\nNo existen palabras registradas\n");
                    }
            }
        } else {
            wprintf(L"\nOpcion invalida\n");
        }
        while (getchar() != '\n');
    } while (op != 5);
}

