#include"library.h"

//inceput task2
//se calculeaza media aritmetica a punctajelor jucatorilor
void calcul_punctaj_echipa(Node **head_list)
{
    Node *aux = (*head_list);

    int i, s;

    while (aux != NULL)
    {
        s = 0;

        for (i = 0; i < (aux->val).nr_juc; i++)
        {
            s = s + (aux->val).jucator[i].points;
        }

        (aux->val).punctaj_echipa = (float)s / (aux->val).nr_juc;

        aux = aux->next;
    }
}

float punctaj_min(Node *head_list)
{
    float min = (head_list->val).punctaj_echipa;
    int i;
    head_list = head_list->next;
    char nume_ech[50];

    while (head_list != NULL)
    {
        if (min > (head_list->val).punctaj_echipa)
        {
            min = (head_list->val).punctaj_echipa;
            strcpy(nume_ech, (head_list->val).nume_echipa);
        }
        head_list = head_list->next;
    }
    return min;
}

void free_echipa(Node **head_list)
{
    if(*head_list != NULL)
    {
        free((*head_list)->val.jucator->firstName);
        free((*head_list)->val.jucator->secondName);
        free(*head_list);
    }
}

void eliminare_primul(Node **head_list)
{
    Node *primul_nod = (*head_list);
    (*head_list) = (*head_list)->next;
    //free_echipa(&primul_nod);
    free(primul_nod);
}

void eliminare_urmator(Node **nod_anterior)
{
    if (*nod_anterior != NULL && (*nod_anterior)->next != NULL)
    {
        Node *nod_el = (*nod_anterior)->next;
        (*nod_anterior)->next = nod_el->next;
        //free_echipa(&nod_el);
        free(nod_el);
    }
}

//calc cel mai mic N astfel incat 2^N <= nr_echipe
int calculare_N(int nr_echipe)
{
    int maxim = 1;
    int j = 0;
    while (maxim <= nr_echipe)
    {
        maxim *= 2;
        j++;
    }

    return j - 1;
}

int if_seg_fault(Node *aux)
{
    if (aux->next == NULL)
    {
        return 0;
    } else if (aux->next->next == NULL)
    {
        return 0;
    }
}

void task2(Node **head_list, int *nr_echipe, FILE* write_file, int cerinte[])
{
    int N = calculare_N((*nr_echipe));
    int nr_ech_el = (*nr_echipe) - pow(2, N);
    int contor_ech_el = 0, i;
    float min;
    int contor_minim = 1;
    while (contor_ech_el < nr_ech_el)
    {
        min = punctaj_min(*head_list);

        // cazul in care primul element trebuie eliminat
        if ((*head_list)->val.punctaj_echipa == min)
        {
            eliminare_primul(head_list);
            contor_ech_el++;
            (*nr_echipe)--;
        }

        Node *aux = *head_list;

        for (i = 0; i < (*nr_echipe) && contor_ech_el < nr_ech_el; i++)
        {
            while (aux->next->val.punctaj_echipa == min)
            {
                eliminare_urmator(&aux);
                contor_ech_el++;
                (*nr_echipe)--;

                if(if_seg_fault(aux) == 0) break;
            }

            if(if_seg_fault(aux) == 0) break;

            aux = aux->next;
        }
    }
    if(cerinte[1] == 1)
        f_display_list(*head_list, write_file);
}