#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>



#define DEBUG 0
#define _CRT_SECURE_NO_WARNINGS

struct node {
    int koeff;
    int power;
    struct node *next;
};

typedef struct node* list;

void createList(list *phead, char *name);
void enterListElems(list *phead);
int addToHead(list *phead, int koeff, int power);
int checkIfExist(list *phead, int power);
void printList(list *phead, char *name);
void del_node(list p, int delpower);
int Delete(list *phead, int delpower);
void Pop(list phead);

int main(void)
{
    list L1;
    int k;

    setlocale(LC_ALL, "RUSSIAN");

    createList(&L1, "L1");
    enterListElems(&L1);
    printf("\n------\n");
    printList(&L1, "L1");
    printf("------\n\n");
    printf("Введите степень, значения меньше которой следует удалить:");
    scanf("%d", &k);
    Delete(&L1, k);
    printList(&L1, "L1");

    system("pause");
    return 0;
}


void createList(list *phead, char *name)
{
    *phead = NULL;
    printf("\nСоздание %s\n", name);
}


int checkIfExist(list *phead, int power, int koeff)
{
    list p = *phead;
    while (p != NULL)
    {
        if (p->power == power)
        {
            p->koeff += koeff;
            return 1;
        }
        p = p->next;
    }
    return 0;
}


int addToHead(list *phead, int koeff, int power)
{
    list p;
    if (checkIfExist(phead, power, koeff))
    {
        printf("Такая степень уже есть %d\n", power);
        return 0;
    }
    p = malloc(sizeof(*p));
    p->koeff = koeff;
    p->power = power;
    p->next = *phead;
    *phead = p;
    printf("Добавлено: %dx^%d\n", p->koeff, p->power);
    return 1;
}


void enterListElems(list *phead)
{
    int i_koeff = 1, i_power = 1;
    while (i_koeff != 0)
    {
        printf("\nВвод\n");
        printf("Kоэффициент: ");
        scanf("%d", &i_koeff);
        if (i_koeff == 0)
            return;
        printf("Cтепень: ");
        scanf("%d", &i_power);
        addToHead(phead, i_koeff, i_power);
    }
}


void del_node(list p, int delpower)
{
    list a;
    a = p->next;
    while (p->next != NULL)
    {
        if (a->power < delpower)
        {
            a = p->next;
            p->next = a->next;
            free(a);
        }
        else
        {
            p = p->next;
            a = p->next;
        }
    }
}


int Delete(list *phead, int delpower)
{
    if (*phead == NULL)
        return 1;
    list p;
    p = *phead;
    while ((p != NULL) && (p->power < delpower))
        p = p->next;
    if (p != NULL)
    {
        del_node(p, p->power);
        *phead = p;
    }
    else
    {
        list a;
        p = *phead;
        while (p->next != NULL)
        {
            a = p;
            p = p->next;
            free(a);
        }
        *phead = NULL;
    }
    return 0;
}



void printList(list *phead, char *name)
{
    list p;
    printf("\nList %s:\n", name);
    for (p = *phead; p != NULL; p = p->next)
        printf("%dx^%d\n", p->koeff, p->power);
    printf("\n");
}
