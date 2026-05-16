//Carlos David Cruz Santiesteban 379909
// Practica 1: Cola de impresion en C
#include "p1.h"

#define MAX_USER 32
#define MAX_DOC 48

typedef enum
{
    NORMAL = 0,
    URGENTE = 1
} Prioridad_t;

typedef struct printq
{
    int id;
    char usuario[MAX_USER];
    char documento[MAX_DOC];
    int paginas_total;
    Prioridad_t prioridad;
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

int main()
{
    menu();
    return 0;
}

void menu()
{
    int op;
    int cont_id = 1;
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
                    printf("prioridad = URGENTE]");
                }
                else
                {
                    printf("prioridad = NORMAL]");
                }
                printf(" (%p)\n", &out);
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
                    printf("prioridad = URGENTE]");
                }
                else
                {
                    printf("prioridad = NORMAL]");
                }
                printf(" (%p)\n", &out);
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
        }
    } while (op != 5);

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
    printf("5.- Salir\n");
    return val_int(1, 5, "ELIGE UNA DE LAS OPCIONES ");
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
            printf("prioridad = URGENTE]");
        }
        else
        {
            printf("prioridad = NORMAL]");
        }
        printf(" (%p)\n", &actual);
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