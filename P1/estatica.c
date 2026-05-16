//Carlos David Cruz Santiesteban 379909
// Practica 1: Cola de impresion en C
#include "p1.h"

#define MAX_USER 32
#define MAX_DOC 48
#define MAX_JOBS 10

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

typedef struct
{
    PrintJob_t data[MAX_JOBS];
    int size;
} QueueStatic_t;

void menu();
int msgs();
void qs_init(QueueStatic_t *q);
int qs_is_empty(const QueueStatic_t q);
int qs_is_full(const QueueStatic_t q);
int qs_enqueue(QueueStatic_t *q, PrintJob_t job);
int qs_peek(QueueStatic_t *q, PrintJob_t *out);
int qs_dequeue(QueueStatic_t *q, PrintJob_t *out);
void qs_print(const QueueStatic_t *q);

int main()
{
    menu();
    return 0;
}

void menu()
{
    int op;
    int cont_id = 1;
    QueueStatic_t queue;
    qs_init(&queue);
    do
    {
        op = msgs();
        switch (op)
        {
        case 1:
            if (qs_is_full(queue))
            {
                printf("ERROR: La lista esta llena\n");
                system("PAUSE");
            }
            else
            {
                PrintJob_t job;
                char aux[6];
                char *end;
                job.id = cont_id++;
                printf("Escribe el usuario: ");
                my_gets(job.usuario, MAX_USER);
                printf("Escribe el nombre del documento: ");
                my_gets(job.documento, MAX_DOC);
                printf("Escribe el numero total de paginas: ");
                my_gets(aux, 6);
                job.paginas_total = strtol(aux, &end, 10);

                printf("\nEscribe el nivel de prioridad:\nNORMAL = 0\nURGENTE = 1\n");
                my_gets(aux, 6);
                job.prioridad = strtol(aux, &end, 10);

                qs_enqueue(&queue, job);
                if (qs_enqueue(&queue, job))
                {
                    printf("AGREGADO A id%d", job.id);
                    system("PAUSE");
                }
            }
            break;
        case 2:
            if (qs_is_empty(queue))
            {
                printf("ERROR: La lista esta vacia\n");
                system("PAUSE");
            }
            else
            {
                PrintJob_t out;
                if (qs_peek(&queue, &out))
                {
                    printf("Siguiente -> [id = %d, user = %s, doc = %s, pags = %d, ", out.id, out.usuario, out.documento, out.paginas_total);
                    if (out.prioridad)
                    {
                        printf("prioridad = URGENTE]\n");
                    }
                    else
                    {
                        printf("prioridad = NORMAL]\n");
                    }
                    system("PAUSE");
                }
            }
            break;
        case 3:
            PrintJob_t out;
            qs_dequeue(&queue, &out);
            printf("Procesando -> [id = %d, user = %s, doc = %s, pags = %d, ", out.id, out.usuario, out.documento, out.paginas_total);
            if (out.prioridad)
            {
                printf("prioridad = URGENTE]\n");
            }
            else
            {
                printf("prioridad = NORMAL]\n");
            }
            system("PAUSE");
            break;
        case 4:
            qs_print(&queue);
            break;
        }
    } while (op != 5);
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

void qs_init(QueueStatic_t *q)
{
    q->size = 0;
}

int qs_is_empty(const QueueStatic_t q)
{
    return q.size == 0;
}

int qs_is_full(const QueueStatic_t q)
{
    return q.size == MAX_JOBS;
}

int qs_enqueue(QueueStatic_t *q, PrintJob_t job)
{
    if (q->size == MAX_JOBS)
        return 0;
    q->data[q->size] = job;
    q->size++;
    return 1;
}

int qs_peek(QueueStatic_t *q, PrintJob_t *out)
{
    if (q->size == 0)
        return 0;
    *out = q->data[0];
    return 0;
}

int qs_dequeue(QueueStatic_t *q, PrintJob_t *out)
{
    if (q->size == 0)
        return 0;
    *out = q->data[0];

    for (int i = 1; i < q->size; i++)
    {
        q->data[i - 1] = q->data[i];
    }

    q->size--;
    return 1;
}

void qs_print(const QueueStatic_t *q)
{
    system("CLS");
    for (int i = 0; i < q->size; i++)
    {
        printf("[id = %d, user = %s, doc = %s, pags = %d, ", q->data[i].id, q->data[i].usuario, q->data[i].documento, q->data[i].paginas_total);
        if (q->data[i].prioridad)
        {
            printf("prioridad = URGENTE]\n");
        }
        else
        {
            printf("prioridad = NORMAL]\n");
        }
    }
    system("PAUSE");
}