/*
 *La tienda de discos ‘UABC’ desea contratarlo para desarrollar una aplicación
 *que permita gestionar el catálogo de la tienda. Los productos que se venden en la
 *tienda son: CDs, audiolibros y software físicos.
 * 

/* 
 * File:   main.c
 * Author: Inzunza R. Kevin G
 * Created on 20 de abril de 2020, 11:04 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct CD {
    char artista[35];
    int anio;
};

struct AudioLibro {
    char autor[35];
    char editorial[35];
    float duracion;
};

struct SoftwareFisico {
    char desarrollador[35];
    char sistemaOperativo[35];
};

union Prod {
    struct CD cd;
    struct AudioLibro aLibro;
    struct SoftwareFisico sFisico;
};

struct datosGenerales {
    char claveProd[30];
    char titulo[35];
    float precio;
    int cant;
};

struct Producto {
    union Prod p;
    struct datosGenerales dG;
    int tipoProd;
};

typedef struct Producto Productos;
typedef struct datosGenerales datosG;


enum p {
    cD = 1, aL, sF
};

int menu();
void menuAlta(Productos productos[], int *cont);
void prodAlta(Productos productos[], int cont);
void menuConsulta(Productos productos[], int cont);
void consultarTipoProd(Productos productos[], int cont, int tipo);
void consultaEspecificaYBajaProd(Productos productos[], int *cont, int tipo);
void consultaPosibleBaja(Productos productos[], int cont);
void bajaProd(Productos productos[], int *cont, int pos);
void mostrarProducto(Productos producto, int j);
void ingresarClave(char prod[]);
void venderProd(Productos productos[], int cont);
int validacionIngreso(char cadena[], int op);
int validacionProducto(char cadena[], Productos productos[], int cont, int op);
int validacionProductoTicket(char cadena[], datosG ticket[], int cont);

/*
 * 
 */
int main(int argc, char** argv) {
    Productos productos[40];
    int contador = 0;
    int op;
    do {
        op = 0;
        op = menu();
        switch (op) {
            case 1:
                menuAlta(productos, &contador);
                break;
            case 2:
                consultaEspecificaYBajaProd(productos, &contador, 2);
                break;
            case 3:
                menuConsulta(productos, contador);
                break;
            case 4:
                venderProd(productos, contador);
                break;
            case 5:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nOpcion invalida\n\n");
        }
    } while (op != 5);
    return (EXIT_SUCCESS);
}

/**
 * Menu principal para efectuar diferentes opciones hacia la tienda de discos
 * @param op
 * @return 
 */
int menu() {
    char opA[10];
    int b;
    do {
        b = 0;
        opA[0] = '\0';
        printf("Tienda de discos UABC\nMENU:\n1.-Alta producto\n2.-Baja de producto\n3.-Consulta de productos\n4.-Vender producto\n5.-Salir\nOpcion: ");
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
 * Menu de registro de clave e ingreso de producto
 * @param productos
 * @param contador
 */
void menuAlta(Productos productos[], int *contador) {
    char opcA[10];
    int opc, b;
    do {
        productos[*contador].dG.claveProd[0]= '\0';
        printf("\nMenu de altas");
        ingresarClave(productos[*contador].dG.claveProd);
        b = validacionProducto(productos[*contador].dG.claveProd, productos, *contador, 1);
    } while (b == -2);
    do {
        b = 0;
        opc = 0;
        opcA[0] = '\0';
        printf("\nProducto a dar de alta:\n1.-CD\n2.-Audiolibro\n3.-Software fisico\nOPCION: ");
        scanf("%[^\n]", opcA);
        while (getchar() != '\n');
        if (strlen(opcA) > 1) {
            printf("\nOpcion invalida\n\n");
            b = -1;
        } else {
            opc = atoi(opcA);
            switch (opc) {
                case 1:
                    productos[*contador].tipoProd = cD;
                    prodAlta(productos, *contador);
                    (*contador)++;
                    break;
                case 2:
                    productos[*contador].tipoProd = aL;
                    prodAlta(productos, *contador);
                    (*contador)++;
                    break;
                case 3:
                    productos[*contador].tipoProd = sF;
                    prodAlta(productos, *contador);
                    (*contador)++;
                    break;
                default:
                    printf("\nOpcion Invalida\n");
                    b = -1;
            }
        }
    } while (b == -1);
}

/**
 * Dar de alta el producto con sus atributos segun el numero de especificacion
 * @param productos
 * @param cont
 */
void prodAlta(Productos productos[], int cont) {
    char  cant[14], anio[10], precio[10], durac[10];
    int b;
    do {
        b=0;
        productos[cont].dG.titulo[0] = '\0';
        printf("\nIngrese el titulo: ");
        scanf("%[^\n]", productos[cont].dG.titulo);
        while (getchar() != '\n');
        if (strlen(productos[cont].dG.titulo) == 0) {
            printf("\nIngrese un titulo valido\n");
            b = -1;
        }
    } while (b == -1);
    do {
        //precio[0] = '\0';
        printf("\nIngrese el precio: ");
        scanf("%[^\n]", precio);
        while (getchar() != '\n');
        b = validacionIngreso(precio, 5);
        if (strlen(precio) == 0 || b == -1|| atof(precio) <= 0.09) {
            printf("\nIngrese un precio valido\n");
            b = -1;
        }
    } while (b == -1);
    do {
        cant[0] = '\0';
        printf("\nIngrese la cantidad en inventario: ");
        scanf("%[^\n]", cant);
        while (getchar() != '\n');
        b = validacionIngreso(cant, 2);
        if (strlen(cant) == 0 || b == -1 || atoi(cant) == 0) {
            printf("\nIngrese una cantidad de inventario valido y mayor a 0\n");
            b = -1;
        }
    } while (b == -1);
    if (productos[cont].tipoProd == cD) {
        do {
            productos[cont].p.cd.artista[0] = '\0';
            printf("\nIngrese el artista: ");
            scanf("%[^\n]",productos[cont].p.cd.artista);
            while (getchar() != '\n');
            b = validacionIngreso(productos[cont].p.cd.artista, 3);
            if (strlen(productos[cont].p.cd.artista) == 0 || b == -1) {
                printf("\nIngrese un artista valido\n");
                b = -1;
            }
        } while (b == -1);
        do {
            anio[0] = '\0';
            printf("\nIngrese el año: ");
            scanf("%[^\n]", anio);
            while (getchar() != '\n');
            b = validacionIngreso(anio, 2);
            if (strlen(anio) == 0 || b == -1 || atoi(anio) <= 0) {
                printf("\nIngrese un año valido\n");
                b = -1;
            }
        } while (b == -1);
        productos[cont].p.cd.anio = atoi(anio);
    } else if (productos[cont].tipoProd == aL) {
        do {
            productos[cont].p.aLibro.autor[0] = '\0';
            printf("\nIngrese el autor: ");
            scanf("%[^\n]", productos[cont].p.aLibro.autor);
            while (getchar() != '\n');
            b = validacionIngreso(productos[cont].p.aLibro.autor, 3);
            if (strlen(productos[cont].p.aLibro.autor) == 0 || b == -1) {
                printf("\nIngrese un autor valido\n");
                b = -1;
            }
        } while (b == -1);
        do {
            productos[cont].p.aLibro.editorial[0] = '\0';
            printf("\nIngrese el editorial: ");
            scanf("%[^\n]", productos[cont].p.aLibro.editorial);
            while (getchar() != '\n');
            b = validacionIngreso(productos[cont].p.aLibro.editorial, 6);
            if (strlen(productos[cont].p.aLibro.editorial) == 0 || b == -1) {
                printf("\nIngrese un editorial valido\n");
                b = -1;
            }
        } while (b == -1);
        do {
            durac[0] = '\0';
            printf("\nIngrese la duracion: ");
            scanf("%[^\n]", durac);
            while (getchar() != '\n');
            b = validacionIngreso(durac, 5);
            if (strlen(durac) == 0 || b == -1) {
                printf("\nIngrese una duracion valida\n");
                b = -1;
            }
        } while (b == -1);
        productos[cont].p.aLibro.duracion = atof(durac);
    } else if (productos[cont].tipoProd == sF) {
        do {
            productos[cont].p.sFisico.desarrollador[0] = '\0';
            printf("\nIngrese un desarrollador: ");
            scanf("%[^\n]", productos[cont].p.sFisico.desarrollador);
            while (getchar() != '\n');
            b = validacionIngreso(productos[cont].p.sFisico.desarrollador, 6);
            if (strlen(productos[cont].p.sFisico.desarrollador) == 0 || b == -1) {
                printf("\nIngrese un desarrollador valido\n");
                b = -1;
            }
        } while (b == -1);
        do {
            productos[cont].p.sFisico.sistemaOperativo[0] = '\0';
            printf("\nIngrese un sistema operativo: ");
            scanf("%[^\n]",productos[cont].p.sFisico.sistemaOperativo);
            while (getchar() != '\n');
            b = validacionIngreso(productos[cont].p.sFisico.sistemaOperativo, 6);
            if (strlen(productos[cont].p.sFisico.sistemaOperativo) == 0 || b == -1) {
                printf("\nIngrese un sistema operativo valido\n");
                b = -1;
            }
        } while (b == -1);
    }
    productos[cont].dG.cant = atoi(cant);
    productos[cont].dG.precio = atof(precio);
    printf("\nPRODUCTO DADO DE ALTA\n\n");
}

/**
 * Eliminar el producto si la cantidad en mercancia es de 0 y el usuario asi lo desea de darlo de baja
 * @param productos
 * @param cont
 * @param pos
 */
void bajaProd(Productos productos[], int *cont, int pos) {
    char op[15];
    int b;
    do {
        b = 0;
        op[0] = '\0';
        printf("\n¿Deseas darlo de baja?[SI/NO]: ");
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
    if (b == 1) {
        (*cont)--;
        while (pos<*cont) {
            productos[pos] = productos[pos + 1];
            pos++;
        }
        printf("\nEliminacion exitosa\n\n");
    } else {
        printf("\nEl producto no se eliminara\n\n");
    }
}

/**
 *Menu para que el usuario escoja la opcion por la cual el desea visualizar los productos que se han registrado con toda su informacion disponible 
 * @param productos
 * @param cont
 */
void menuConsulta(Productos productos[], int cont) {
    char opcA[10];
    int b;
    if (cont > 0) {
        do {
            b = 0;
            opcA[0] = '\0';
            printf("\nMenu de consultas\nA.-Consulta especifica\nB.-Consulta general de CDs\nC.-Consulta general de Audiolibros\nD.-Consulta general de Software\nE.-Consulta de productos posibles a dar de baja\nF.-Regresar al menu principal\nOPCION: ");
            scanf("%[^\n]", opcA);
            while (getchar() != '\n');
            b = validacionIngreso(opcA, 4);
            if (strlen(opcA) > 1 || b == -1) {
                printf("\nOpcion invalida\n\n");
            } else {
                opcA[0] = toupper(opcA[0]);
                switch (opcA[0]) {
                    case 'A':
                        consultaEspecificaYBajaProd(productos, &cont, 1);
                        break;
                    case 'B':
                        consultarTipoProd(productos, cont, cD);
                        break;
                    case 'C':
                        consultarTipoProd(productos, cont, aL);
                        break;
                    case 'D':
                        consultarTipoProd(productos, cont, sF);
                        break;
                    case 'E':
                        consultaPosibleBaja(productos, cont);
                        break;
                    case 'F':
                        printf("\nRegresando al menu principal...\n\n");
                        break;
                    default:
                        printf("\nOpcion Invalida\n");
                }
            }
        } while (opcA[0] != 'F');
    } else {
        printf("\nNo existen productos para consultar\n\n");
    }
}

/**
 * Consulta la clave que le es ingresada para buscarlo en los registros ingresados - tipo = 1
 * Consulta la clave si existe y cuenta con inventario en cero para ser eliminado  - tipo = 2
 * @param productos
 * @param cont
 * @param tipo
 */
void consultaEspecificaYBajaProd(Productos productos[], int *cont, int tipo) {
    char prod[30];
    int b;
    if (*cont > 0) {
        prod[0]='\0';
        ingresarClave(prod);
        b = validacionProducto(prod, productos, *cont, 2);
        if (b != -3) {
            if (tipo == 1) {
                printf("\nProducto encontrado:\n");
                mostrarProducto(productos[b], 1);
            } else if (tipo == 2) {
                if (productos[b].dG.cant == 0) {
                    printf("\nProducto encontrado:\n");
                    mostrarProducto(productos[b], 1);
                    bajaProd(productos, &*cont, b);
                } else {
                    printf("\nLa clave pertenece a un producto con inventario mayor a cero\nCantidad en inventario=%d\n\n", productos[b].dG.cant);
                }
            }
        } else {
            printf("\nEl producto no se encontro\n\n");
        }
    } else {
        printf("\nNo existen productos para dar de baja\n\n");
    }
}

/**
 * Separar por divisiones de los productos del cual se desea consultar para ser visualizados
 * @param productos
 * @param cont
 * @param tipo
 */
void consultarTipoProd(Productos productos[], int cont, int tipo) {
    int i, j = 1;
    for (i = 0; i < cont; i++) {
        if (tipo == cD && productos[i].tipoProd == cD) {
            mostrarProducto(productos[i], j);
            j++;
        } else if (tipo == aL && productos[i].tipoProd == aL) {
            mostrarProducto(productos[i], j);
            j++;
        } else if (tipo == sF && productos[i].tipoProd == sF) {
            mostrarProducto(productos[i], j);
            j++;
        }
    }
    if (j == 1){
        printf("\nNo se ha registrado ningun producto de este tipo\n");
    }
}

/**
 * Consultar todos los productos los cuales su cantidad de inventario es igual a 0
 * @param productos
 * @param cont
 */
void consultaPosibleBaja(Productos productos[], int cont) {
    int i, j = 1;
    for (i = 0; i < cont; i++) {
        if (productos[i].dG.cant == 0) {
            if(j==1){
                 printf("\nProductos posibles a dar de baja por no tener inventario:\n");
            }
            mostrarProducto(productos[i], j);
            j++;
        }
    }
    if(j==1)
    {
         printf("\nNo hay productos con inventario igual a 0\n");
    }
}

/**
 * Muestra la informacion completa segun el producto consultado
 * @param producto
 * @param j
 */
void mostrarProducto(Productos producto, int j) {
    if (producto.tipoProd == cD) {
        printf("\nCD #%d\nClave del producto:%s\nTitulo:%s\nPrecio:$%.2f\nCantidad en inventario:%d", j, producto.dG.claveProd, producto.dG.titulo, producto.dG.precio, producto.dG.cant);
        printf("\nArtista:%s\nAño:%d\n", producto.p.cd.artista, producto.p.cd.anio);
        j++;
    } else if (producto.tipoProd == aL) {
        printf("\nAudiolibro #%d\nClave del producto:%s\nTitulo:%s\nPrecio:$%.2f\nCantidad en inventario:%d", j, producto.dG.claveProd, producto.dG.titulo, producto.dG.precio, producto.dG.cant);
        printf("\nAutor:%s\nEditorial:%s\nDuracion:%.2f\n", producto.p.aLibro.autor, producto.p.aLibro.editorial, producto.p.aLibro.duracion);
        j++;
    } else if (producto.tipoProd == sF) {
        printf("\nSoftware fisico #%d\nClave del producto:%s\nTitulo:%s\nPrecio:$%.2f\nCantidad en inventario:%d", j, producto.dG.claveProd, producto.dG.titulo, producto.dG.precio, producto.dG.cant);
        printf("\nDesarrollador:%s\nSistema operativo:%s\n", producto.p.sFisico.desarrollador, producto.p.sFisico.sistemaOperativo);
        j++;
    }
}

/**
 * Valida que la clave ingresada sea correctamente escrita
 * @param prod
 */
void ingresarClave(char prod[]) {
    int b;
    do {
        printf("\nIngrese la clave del producto : ");
        scanf("%[^\n]", prod);
        while (getchar() != '\n');
        b = validacionIngreso(prod, 1);
        if (strlen(prod) == 0 || b == -1) {
            printf("\nIngrese una clave valida\n");
            b = -1;
        }
    } while (b == -1);
}

/**
 * Da la posibilidad de compraar el producto si la clave existe y cuenta con inventario disponible segun la necesidad del usuario,
 * la opcion de comprar se mantendra mientras el usuario asi lo desee,al finalizar la compra se mostrara el ticket de lo que se compro con 
 * su subtotal y total de compra
 * @param productos
 * @param cont
 */
void venderProd(Productos productos[], int cont) {
    datosG ticket[cont];
    int b, contV = 0, b1, i;
    char  op[15], cant[10];
    float total = 0;
    if (cont > 0) {
        printf("\nVenta de productos");
        do {
            ticket[contV].claveProd[0] = '\0';
            ingresarClave(ticket[contV].claveProd);
            b = validacionProducto(ticket[contV].claveProd, productos, cont, 2);
            if (b != -3) { //Si existe el producto
                if (productos[b].dG.cant > 0) { //El producto tiene inventario mayor a 0
                    do {
                        cant[0] = '\0';
                        printf("\nNumero de copias a obtener:");
                        scanf("%[^\n]", cant);
                        while (getchar() != '\n');
                        b1 = validacionIngreso(cant, 2);
                        if (b1 == -1) {
                            printf("\nIngrese una opcion valida, si no desea obtener copias de este producto ingrese un 0 o presione enter\n");
                        } else {
                            if (productos[b].dG.cant >= atoi(cant) && atoi(cant) > 0) {
                                b1 = validacionProductoTicket(productos[b].dG.claveProd, ticket, contV);
                                if (b1 != -2) //Este producto ya se habia solicitado en el ticket
                                {
                                    ticket[b1].cant = ticket[b1].cant + atoi(cant);
                                    ticket[b1].precio = ticket[b1].cant * productos[b1].dG.precio;
                                    productos[b].dG.cant = productos[b].dG.cant - atoi(cant);
                                } else { //Primera vez que se escoge este producto
                                    ticket[contV].cant = atoi(cant);
                                    ticket[contV].precio = atoi(cant) * productos[b].dG.precio;
                                    strcpy(ticket[contV].titulo, productos[b].dG.titulo);
                                    productos[b].dG.cant = productos[b].dG.cant - atoi(cant);
                                    contV++;
                                }
                            } else if (atoi(cant) == 0 || strlen(cant) == 0) {
                                printf("\nSe ha descartado el producto solicitado\n");
                            } else {
                                printf("\nLa cantidad de copias a obtener es mayor a la cantidad en el inventario que es %d\n", productos[b].dG.cant);
                            }
                        }
                    } while (b1 == -1);
                } else {
                    printf("\nEl producto no tiene inventario mayor a 0\n");
                }
            } else {
                printf("\nEl producto no se encontro\n");
            }
            do {
                op[0] = '\0';
                printf("\n¿Desea ingresar otra clave de producto?Ingrese:[SI/NO]\nOpcion: ");
                scanf("%[^\n]", op);
                while (getchar() != '\n');
                if (strcasecmp(op, "SI") == 0) {
                    b = -1;
                } else if (strcasecmp(op, "NO") == 0) {
                    b = 2;
                } else {
                    printf("\nIngrese una opcion valida [SI/NO]\n\n");
                    b = -2;
                }
            } while (b == -2);
        } while (b == -1);
        if (contV == 0) {
            printf("\nLa compra fue cancelada al no comprar ningún producto.\n\n");
        } else {
            printf("\n\t\tTICKET DE COMPRA\n");
            for (i = 0; i < contV; i++) {
                printf("Producto #%d\nTitulo de producto:%-10sCantidad de producto:%-5dSubTotal:$%.2f\n", i + 1, ticket[i].titulo, ticket[i].cant, ticket[i].precio);
                total = total + ticket[i].precio;
            }
            printf("\n\t\tTOTAL A PAGAR:$%.2f\n\n", total);
        }
    } else {
        printf("\n\nNo existen productos para vender\n\n");
    }
}

/**
 * Valida que la clave se ingrese correctamente - op=1
 * Valida que la cantidad de inventario ingresada sea correcta - op=2
 * @param cadena
 * @param op
 * @return 
 */
int validacionIngreso(char cadena[], int op) {
    int i = 0, b = 0, k = 0;
    if (op == 1 || op == 6) { //Permitir solo el ingreso de numeros y letras sin o con espacios
        while (cadena[i] != '\0' && b == 0) {
            if (isalnum(cadena[i]) == 0) {
                if (op == 6) {
                    if (isspace(cadena[i]) == 0) {
                        b = -1;
                    }
                } else {
                    b = -1;
                }
            }
            i++;
        }
    } else if (op == 2 || op == 5) { //Permite solo el ingreso de numeros o numeros con decimales
        while (cadena[i] != '\0' && b == 0) {
            if (isdigit(cadena[i]) == 0) {
                if (op == 5) {
                    if (cadena[i] != '.') {
                        b = -1;
                    } else {
                        k++;
                    }
                    if (k > 1) //Se ingreso mas de 2 puntos decimales
                    {
                        b = -1;
                    }
                } else {
                    b = -1;
                }
            }
            i++;
        }
        if (op == 5 && b == 0) {
            if (cadena[i - 1] == '.') {//Valida que el ultimo no sea un punto
                b = -1;
            }
        }
    } else if (op == 3 || op == 4) { //Valida el ingreso de letras con o sin espacios
        while (cadena[i] != '\0' && b == 0) {
            if (isalpha(cadena[i]) == 0) {
                if (op == 3) {
                    if (isspace(cadena[i]) == 0) {
                        b = -1;
                    }
                } else {
                    b = -1;
                }
            }
            i++;
        }
        if (isspace(cadena[i - 1]) != 0 && b == 0) { //Valida que el ultimo no sea un espacio
            b = -1;
        }
    }
    return b;
}

/**
 * Verifica si la clave ingresa se encuentra en los productos ya ingresados
 * @param cadena
 * @param productos
 * @param cont
 * @param op
 * @return 
 */
int validacionProducto(char cadena[], Productos productos[], int cont, int op) {
    int i = 0, b = -3;
    while (i < cont && b == -3) {
        if (op == 1) {
            if (strcasecmp(productos[i].dG.claveProd, cadena) == 0) {
                printf("\nLa clave se repite con la de otro producto\n");
                b = -2;
            }
        } else if (op == 2) {
            if (strcasecmp(productos[i].dG.claveProd, cadena) == 0) {
                b = i;
            }
        }
        i++;
    }
    return b;
}

/**
 * Verifica si la clave del producto ya se ha utilizado anteriormente en el mismo ticket para no producir redundancia de datos
 * @param cadena
 * @param ticket
 * @param cont
 * @return 
 */
int validacionProductoTicket(char cadena[], datosG ticket[], int cont) {
    int i = 0, b = -2;
    while (i < cont && b == -2) {
        if (strcasecmp(ticket[i].claveProd, cadena) == 0) {
            b = i;
        }
        i++;
    }
    return b;
}
