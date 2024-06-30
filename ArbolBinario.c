#include <stdio.h>
#include <stdlib.h>

// Definición del nodo del árbol binario
typedef struct Nodo {
    int dato;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

// Función para crear un nuevo nodo
Nodo* crearNodo(int dato) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->izquierdo = NULL;
    nuevoNodo->derecho = NULL;
    return nuevoNodo;
}

// Función para insertar un nuevo nodo en el árbol binario
Nodo* insertar(Nodo* raiz, int dato) {
    if (raiz == NULL) {
        return crearNodo(dato);
    }
    if (dato < raiz->dato) {
        raiz->izquierdo = insertar(raiz->izquierdo, dato);
    } else if (dato > raiz->dato) {
        raiz->derecho = insertar(raiz->derecho, dato);
    }
    return raiz;
}

// Función para mostrar el recorrido en preorden
void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dato);
        preorden(raiz->izquierdo);
        preorden(raiz->derecho);
    }
}

// Función para mostrar el recorrido en inorden
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierdo);
        printf("%d ", raiz->dato);
        inorden(raiz->derecho);
    }
}

// Función para mostrar el recorrido en postorden
void postorden(Nodo* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierdo);
        postorden(raiz->derecho);
        printf("%d ", raiz->dato);
    }
}

// Función para buscar un nodo en el árbol
Nodo* buscar(Nodo* raiz, int dato) {
    if (raiz == NULL || raiz->dato == dato) {
        return raiz;
    }
    if (dato < raiz->dato) {
        return buscar(raiz->izquierdo, dato);
    } else {
        return buscar(raiz->derecho, dato);
    }
}

// Función para encontrar el nodo padre de un dato dado
Nodo* encontrarPadre(Nodo* raiz, int dato) {
    if (raiz == NULL || raiz->dato == dato) {
        return NULL;
    }
    if ((raiz->izquierdo != NULL && raiz->izquierdo->dato == dato) ||
        (raiz->derecho != NULL && raiz->derecho->dato == dato)) {
        return raiz;
    }
    if (dato < raiz->dato) {
        return encontrarPadre(raiz->izquierdo, dato);
    } else {
        return encontrarPadre(raiz->derecho, dato);
    }
}

// Función para encontrar y mostrar los hijos de un nodo dado
void mostrarHijos(Nodo* raiz, int dato) {
    Nodo* nodo = buscar(raiz, dato);
    if (nodo != NULL) {
        printf("Hijos de %d: ", dato);
        if (nodo->izquierdo != NULL) {
            printf("%d ", nodo->izquierdo->dato);
        }
        if (nodo->derecho != NULL) {
            printf("%d ", nodo->derecho->dato);
        }
        if (nodo->izquierdo == NULL && nodo->derecho == NULL) {
            printf("No tiene hijos.");
        }
        printf("\n");
    } else {
        printf("Nodo no encontrado en el arbol.\n");
    }
}

// Función para encontrar y mostrar el hermano de un nodo dado
void mostrarHermano(Nodo* raiz, int dato) {
    Nodo* padre = encontrarPadre(raiz, dato);
    if (padre != NULL) {
        if (padre->izquierdo != NULL && padre->izquierdo->dato != dato) {
            printf("Hermano de %d: %d\n", dato, padre->izquierdo->dato);
        } else if (padre->derecho != NULL && padre->derecho->dato != dato) {
            printf("Hermano de %d: %d\n", dato, padre->derecho->dato);
        } else {
            printf("%d no tiene hermano.\n", dato);
        }
    } else {
        printf("%d no tiene hermano.\n", dato);
    }
}

// Función para mostrar la raíz del árbol
void mostrarRaiz(Nodo* raiz) {
    if (raiz != NULL) {
        printf("Raiz del arbol: %d\n", raiz->dato);
    } else {
        printf("El arbol esta vacio.\n");
    }
}

// Función para encontrar y mostrar los antecesores de un nodo dado
void mostrarAntecesores(Nodo* raiz, int dato) {
    Nodo* nodo = buscar(raiz, dato);
    if (nodo != NULL) {
        printf("Antecesores de %d: ", dato);
        Nodo* temp = raiz;
        while (temp != NULL && temp->dato != dato) {
            printf("%d ", temp->dato);
            if (dato < temp->dato) {
                temp = temp->izquierdo;
            } else {
                temp = temp->derecho;
            }
        }
        printf("\n");
    } else {
        printf("Nodo no encontrado en el arbol.\n");
    }
}

// Función para encontrar y mostrar los descendientes de un nodo dado
void mostrarDescendientes(Nodo* nodo) {
    if (nodo != NULL) {
        printf("%d ", nodo->dato);
        mostrarDescendientes(nodo->izquierdo);
        mostrarDescendientes(nodo->derecho);
    }
}

void encontrarDescendientes(Nodo* raiz, int dato) {
    Nodo* nodo = buscar(raiz, dato);
    if (nodo != NULL) {
        printf("Descendientes de %d: ", dato);
        mostrarDescendientes(nodo);
        printf("\n");
    } else {
        printf("Nodo no encontrado en el arbol.\n");
    }
}

// Función para calcular la altura de un nodo
int altura(Nodo* nodo) {
    if (nodo == NULL) {
        return -1;
    } else {
        int alturaIzq = altura(nodo->izquierdo);
        int alturaDer = altura(nodo->derecho);
        return (alturaIzq > alturaDer ? alturaIzq : alturaDer) + 1;
    }
}

// Función auxiliar para calcular la anchura en cada nivel del árbol
void calcularAnchura(Nodo* nodo, int* count, int nivel) {
    if (nodo != NULL) {
        count[nivel]++;
        calcularAnchura(nodo->izquierdo, count, nivel + 1);
        calcularAnchura(nodo->derecho, count, nivel + 1);
    }
}

// Función para calcular la anchura del árbol (número máximo de nodos a cualquier nivel)
int maxAnchura(Nodo* raiz) {
    if (raiz == NULL) return 0;

    int maxAnchura = 0;
    int h = altura(raiz) + 1;
    int* count = (int*)calloc(h, sizeof(int));

    calcularAnchura(raiz, count, 0);

    for (int i = 0; i < h; i++) {
        if (count[i] > maxAnchura) {
            maxAnchura = count[i];
        }
    }

    free(count);
    return maxAnchura;
}

void menu(Nodo* raiz) {
    int opcion, valor;

    do {
        printf("\nMenu:\n");
        printf("1. Mostrar recorrido en preorden\n");
        printf("2. Mostrar recorrido en inorden\n");
        printf("3. Mostrar recorrido en postorden\n");
        printf("4. Mostrar raiz del arbol\n");
        printf("5. Mostrar hijos de un nodo\n");
        printf("6. Mostrar hermano de un nodo\n");
        printf("7. Mostrar antecesores de un nodo\n");
        printf("8. Mostrar descendientes de un nodo\n");
        printf("9. Mostrar altura del arbol\n");
        printf("10. Mostrar anchura maxima del arbol\n");
        printf("11. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Recorrido en preorden: ");
                preorden(raiz);
                printf("\n");
                break;
            case 2:
                printf("Recorrido en inorden: ");
                inorden(raiz);
                printf("\n");
                break;
            case 3:
                printf("Recorrido en postorden: ");
                postorden(raiz);
                printf("\n");
                break;
            case 4:
                mostrarRaiz(raiz);
                break;
            case 5:
                printf("Ingrese el valor del nodo para mostrar sus hijos: ");
                scanf("%d", &valor);
                mostrarHijos(raiz, valor);
                break;
            case 6:
                printf("Ingrese el valor del nodo para mostrar su hermano: ");
                scanf("%d", &valor);
                mostrarHermano(raiz, valor);
                break;
            case 7:
                printf("Ingrese el valor del nodo para mostrar sus antecesores: ");
                scanf("%d", &valor);
                mostrarAntecesores(raiz, valor);
                break;
            case 8:
                printf("Ingrese el valor del nodo para mostrar sus descendientes: ");
                scanf("%d", &valor);
                encontrarDescendientes(raiz, valor);
                break;
            case 9:
                printf("Altura del arbol: %d\n", altura(raiz));
                break;
            case 10:
                printf("Anchura maxima del arbol: %d\n", maxAnchura(raiz));
                break;
            case 11:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 11);
}

int main() {
    Nodo* raiz = NULL;
    int valor;

    printf("Ingrese numeros para crear el arbol binario (ingrese -1 para terminar)\n");
        printf("Ingrese valor: ");
    do
    {
        scanf("%d", &valor);
        if (valor == -1) {
            break;
        }
        raiz = insertar(raiz, valor);
    } while (1);


    menu(raiz);
    return 0;
}

