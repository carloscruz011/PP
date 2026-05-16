//Carlos David Cruz Santiesteban 379909
// Practica 1: Cola de impresion en C
#include "p1.h"
#include <windows.h>

#define MAX_USER 32
#define MAX_DOC 48
#define MS_PER_PAG 500

typedef enum
{
    NORMAL = 0,
    URGENTE = 1
} Prioridad_t;

typedef enum
{
    EN_COLA = 0,
    IMPRIMIENDO = 1,
    COMPLETADO = 2,
    CANCELADO = 3
} Estado_t;

typedef struct printq
{
    int id;
    char usuario[MAX_USER];
    char documento[MAX_DOC];
    int paginas_total;
    int paginas_restantes;
    Prioridad_t prioridad;
    Estado_t estado;
} PrintJob_t;

typedef struct Node_t
{
    PrintJob_t job;
    struct Node_t *next;
} Node_t;

typedef struct
{
    struct Node_t *head;
    struct Node_t *tail;
    int size;
} QueueDynamic_t;

void menu();
int msgs();
void qd_init(QueueDynamic_t *q);
Node_t *create_node(int id);
int qd_is_empty(const QueueDynamic_t q);
int qd_enqueue(QueueDynamic_t *q, int id);
int qd_peek(QueueDynamic_t *q, Node_t **out);
int qd_dequeue(QueueDynamic_t *q, Node_t **out);
void qd_print(QueueDynamic_t *q);
void qd_destroy(QueueDynamic_t *q);
void qd_sim(QueueDynamic_t *q);
int qd_cancel(QueueDynamic_t *q, int id);

int main()
{
    menu();
    return 0;
}

void menu()
{
    int op;
    int id;
    int cont_id = 1;
    char *end;
    char id_s[6];
    QueueDynamic_t queue;
    qd_init(&queue);
    Node_t *out = NULL;
    do
    {
        op = msgs();
        switch (op)
        {
        case 1:
            qd_enqueue(&queue, cont_id++);

            printf("AGREGADO A id = %d\n", cont_id);
            system("PAUSE");
            break;
        case 2:
            if (qd_peek(&queue, &out))
            {
                printf("Siguiente -> [id = %d, user = %s, doc = %s, pags = %d, ", out->job.id, out->job.usuario, out->job.documento, out->job.paginas_total);
                if (out->job.prioridad)
                {
                    printf("prioridad = URGENTE]\n");
                }
                else
                {
                    printf("prioridad = NORMAL]\n");
                }
                system("PAUSE");
            }
            else
            {
                printf("ERROR: La lista esta vacia\n");
                system("PAUSE");
            }
            break;
        case 3:
            if (qd_dequeue(&queue, &out))
            {
                printf("Procesando -> [id = %d, user = %s, doc = %s, pags = %d, ", out->job.id, out->job.usuario, out->job.documento, out->job.paginas_total);
                if (out->job.prioridad)
                {
                    printf("prioridad = URGENTE]\n");
                }
                else
                {
                    printf("prioridad = NORMAL]\n");
                }
                free(out);
                system("PAUSE");
            }
            else
            {
                printf("ERROR: La lista esta vacia\n");
                system("PAUSE");
            }
            break;
        case 4:
            qd_print(&queue);
            break;
        case 5:
            qd_sim(&queue);
            break;
        case 6:
            printf("Escribe el numero total de paginas: ");
            my_gets(id_s, 6);
            id = strtol(id_s, &end, 10);
            if (qd_cancel(&queue, id))
            {
                printf("TRABAJO ELIMINADO CORRECTAMENTE\n");
                system("PAUSE");
            }
            else
            {
                printf("ERROR: No se pudo eliminar el trabajo\n");
                system("PAUSE");
            }
            break;
        }
    } while (op != 7);

    qd_destroy(&queue);
}

int msgs()
{
    system("CLS");
    printf("- - - M E N U - - -\n");
    printf("1.- Agregar trabajo\n");
    printf("2.- Ver siguiente trabajo\n");
    printf("3.- Procesar trabajo\n");
    printf("4.- Listar cola\n");
    printf("5.- Simular impresion de toda la cola\n");
    printf("6.- Cancelar un trabajo\n");
    printf("7.- Salir\n");
    return val_int(1, 7, "ELIGE UNA DE LAS OPCIONES ");
}

void qd_init(QueueDynamic_t *q)
{
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
}

Node_t *create_node(int id)
{
    Node_t *nuevo = (Node_t *)malloc(sizeof(Node_t));

    if (nuevo == NULL)
    {
        return NULL;
    }

    char aux[6];
    char *end;
    nuevo->job.id = id;

    printf("Escribe el usuario: ");
    my_gets(nuevo->job.usuario, MAX_USER);
    printf("Escribe el nombre del documento: ");
    my_gets(nuevo->job.documento, MAX_DOC);
    printf("Escribe el numero total de paginas: ");
    my_gets(aux, 6);
    nuevo->job.paginas_total = strtol(aux, &end, 10);
    nuevo->job.paginas_restantes = nuevo->job.paginas_total;
    nuevo->job.estado = EN_COLA;

    printf("\nEscribe el nivel de prioridad:\nNORMAL = 0\nURGENTE = 1\n");
    my_gets(aux, 6);
    nuevo->job.prioridad = strtol(aux, &end, 10);

    nuevo->next = NULL;

    return nuevo;
}

int qd_is_empty(const QueueDynamic_t q)
{
    return q.size == 0;
}

int qd_enqueue(QueueDynamic_t *q, int id)
{
    Node_t *nuevo = create_node(id);

    if (nuevo == NULL)
        return 0;

    if (qd_is_empty(*q))
    {
        q->head = nuevo;
        q->tail = nuevo;
        (q->size)++;
        return 1;
    }

    if (nuevo->job.prioridad == URGENTE)
    {
        nuevo->next = q->head;
        q->head = nuevo;
        (q->size)++;
        return 1;
    }

    q->tail->next = nuevo;
    q->tail = nuevo;
    (q->size)++;

    return 1;
}

int qd_peek(QueueDynamic_t *q, Node_t **out)
{
    if (q->size == 0)
        return 0;
    *out = q->head;
    return 1;
}

int qd_dequeue(QueueDynamic_t *q, Node_t **out)
{
    if (q->size == 0)
        return 0;
    *out = q->head;

    q->head = q->head->next;

    q->size--;
    return 1;
}

void qd_print(QueueDynamic_t *q)
{
    Node_t *actual;
    actual = q->head;
    system("CLS");
    for (int i = 0; i < q->size; i++)
    {
        printf("[id = %d, user = %s, doc = %s, pags = %d, ", actual->job.id, actual->job.usuario, actual->job.documento, actual->job.paginas_total);
        if (actual->job.prioridad)
        {
            printf("prioridad = URGENTE]\n");
        }
        else
        {
            printf("prioridad = NORMAL]\n");
        }
        actual = actual->next;
    }
    system("PAUSE");
}

void qd_destroy(QueueDynamic_t *q)
{
    Node_t *actual = q->head;
    Node_t *tmp;

    while (actual != NULL)
    {
        tmp = actual->next;
        free(actual);
        actual = tmp;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void qd_sim(QueueDynamic_t *q)
{
    Node_t *out = NULL;

    while (!qd_is_empty(*q))
    {
        if (qd_dequeue(q, &out))
        {
            out->job.estado = IMPRIMIENDO;
            printf("IMPRIMIENDO -> [id = %d, user = %s, doc = %s]\n", out->job.id, out->job.usuario, out->job.documento);

            while (out->job.paginas_restantes > 0)
            {
                out->job.paginas_restantes--;
                printf("Pagina %d/%d...", out->job.paginas_total - out->job.paginas_restantes, out->job.paginas_total);
                Sleep(MS_PER_PAG);
            }

            out->job.estado = COMPLETADO;
            printf("\nCOMPLETADO -> [id = %d]\n\n", out->job.id);
            free(out);
        }
    }
    system("PAUSE");
}

int qd_cancel(QueueDynamic_t *q, int id)
{
    if (qd_is_empty(*q))
        return 0;

    Node_t *actual = q->head;
    Node_t *aux = NULL;

    if (actual->job.id == id)
    {
        q->head = actual->next;
        free(actual);
        q->size--;
        if (q->head == NULL)
            q->tail = NULL;

        return 1;
    }

    while (actual->next != NULL)
    {
        if (actual->next->job.id == id)
        {
            aux = actual->next;
            actual->next = actual->next->next;
            free(aux);
            q->size--;

            if (actual->next == NULL)
                q->tail = actual;
            return 1;
        }
        actual = actual->next;
    }

    return 0;
}