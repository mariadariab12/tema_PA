#include "library.h"

void addAtBeginning(Node **head, Data v)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = v;
    newNode->next = *head;
    *head = newNode;
}

void addAtEnd(Node **head, Data v)
{
    Node *aux = *head;
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = v;
    if (*head == NULL)
        addAtBeginning(&*head, v);
    else
    {
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = newNode;
        newNode->next = NULL;
    }
}

void lista_null(Node *head_list)
{
    if (head_list == NULL)
    {
        printf("Failed to allocate memory for head_list\n");
        exit(1);
    }
}

void fisier_null(FILE *read_file)
{
    if (read_file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
}

void atribuire_juc(FILE *read_file, Team echipa, int j)
{
    int points;
    char secondN[50], firstN[50];

    fscanf(read_file, "%s %s %d", secondN, firstN, &points);

    echipa.jucator[j].secondName = (char *)malloc((strlen(secondN) + 1) * sizeof(char));
    echipa.jucator[j].firstName = (char *)malloc((strlen(firstN) + 1) * sizeof(char));
    echipa.jucator[j].points = points;

    strcpy(echipa.jucator[j].secondName, secondN);
    strcpy(echipa.jucator[j].firstName, firstN);
}

int team_file_read(FILE *read_file, Node **head_list)
{
    fisier_null(read_file); // check fis

    int nr_echipe;
    fscanf(read_file, "%d", &nr_echipe);
    printf("Nr echipe: %d\n", nr_echipe);

    (*head_list) = (Node *)malloc(sizeof(Node));
    lista_null(*head_list); // check list
    *head_list = NULL;

    char line[100];
    int i, j;
    struct Team echipa;

    for (i = 0; i < nr_echipe; i++)
    {
        int nr_juc;
        char nume_echipa[50];
        fscanf(read_file, "%d %[^\n]", &nr_juc, nume_echipa);

        echipa.nume_echipa = (char *)malloc((strlen(nume_echipa) + 1) * sizeof(char));

        echipa.nr_juc = nr_juc;
        strcpy(echipa.nume_echipa, nume_echipa);

        echipa.jucator = (struct Player *)malloc(echipa.nr_juc * sizeof(struct Player));

        for (j = 0; j < echipa.nr_juc; j++)
        {
            atribuire_juc(read_file, echipa, j);
        }

        addAtBeginning(head_list, echipa);
        fgets(line, 100, read_file);
    }

    return nr_echipe;
}

void display_list(Node *head)
{
    int j;
    while (head != NULL)
    {

        printf("%d ", head->val.nr_juc);
        puts(head->val.nume_echipa);

        for (j = 0; j < head->val.nr_juc; j++)
        {
            printf("%s", head->val.jucator[j].secondName);
            printf(" %s", head->val.jucator[j].firstName);
            printf(" %d\n", head->val.jucator[j].points);
        }

        printf("\n");
        head = head->next;
    }
}

int task1(FILE *read_file, Node **head_list)
{
    int nr_echipe = team_file_read(read_file, head_list);

    // display_list(*head_list);

    return nr_echipe;
}

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

void eliminare_primul(Node **head_list)
{
    Node *primul_nod = (*head_list);
    (*head_list) = (*head_list)->next;
    free(primul_nod);
}

void eliminare_echipa(Node **nod_anterior)
{
    if (*nod_anterior != NULL && (*nod_anterior)->next != NULL)
    {
        Node *nod_el = (*nod_anterior)->next;
        (*nod_anterior)->next = nod_el->next;
        free(nod_el);
    }
}

int calculare_N(int nr_echipe)
{
    int maxim = 1;
    int j = 0;
    while (maxim < nr_echipe)
    {
        maxim *= 2;
        j++;
    }

    return j - 1;
}

void task2(Node **head_list, int nr_echipe)
{
    int N = calculare_N(nr_echipe);

    int nr_ech_el = nr_echipe - pow(2, N);

    int contor_ech_el = 0, i;

    float min;

    while (contor_ech_el < nr_ech_el)
    {
        min = punctaj_min(*head_list);

        // cazul in care primul element trebuie eliminat
        if ((*head_list)->val.punctaj_echipa == min)
        {
            eliminare_primul(head_list);
            contor_ech_el++;
            nr_echipe--;
        }

        Node *aux = *head_list;

        for (i = 0; i < nr_echipe && contor_ech_el < nr_ech_el; i++)
        {

            if (aux->next->val.punctaj_echipa == min)
            {
                eliminare_echipa(&aux);
                contor_ech_el++;
                nr_echipe--;
            }

            if (aux->next->next == NULL)
            {
                break;
            }

            aux = aux->next;
        }
    }

    display_list(*head_list);

    printf("\n nr echipe: %d\n", nr_echipe);
}

// task3

void creare_meciuri(QGame *q, Node *head_list)
{
    while (head_list != NULL)
    {
        enQueue(q, head_list->val, head_list->next->val);
        if (head_list->next->next == NULL)
        {
            break;
            printf("break");
        }

        head_list = (head_list->next)->next;
    }
}

int winner(Team team_1, Team team_2)
{
    if(team_1.punctaj_echipa >= team_2.punctaj_echipa)
        return 1;
    
    return 2;
}

void add_pct_winner(Team *team)
{
    int i;
    for(i=0; i<(*team).nr_juc; i++)
    {
        (*team).jucator[i].points++;
    }

    (*team).punctaj_echipa++;

}

void runda(QGame *q, Node** top_win, Node** top_lose)
{
    Node_Game* aux;
	if (isEmpty_queue(q)) return;
    QGame *aux_q=q;
    Team team_1, team_2;
    //int i=1;

    (*top_win) = (Node *)malloc(sizeof(Node));
    lista_null(*top_win); // check
    *top_win = NULL;

    (*top_lose) = (Node *)malloc(sizeof(Node));
    lista_null(*top_lose); // check
    *top_lose = NULL;

	while(aux_q->front != NULL)
    {
    aux=aux_q->front;
	team_1=aux->team1;
    team_2=aux->team2;
	aux_q->front=(aux_q->front)->next;
    //printf("Meciul %d:\n", i);
    //i++;

    if(winner(team_1, team_2) == 1) 
    {
        add_pct_winner(&team_1);
        push(top_win, team_1);
        push(top_lose, team_2);
    }
    else
    {
        add_pct_winner(&team_2);
        push(top_win, team_2);
        push(top_lose, team_1);
    }
    }

    //deleteStack(&top_lose);

}

/*
void eliminare_lose(QGame *q, Node *top_lose)
{
    while()    
}


void task3(QGame *q, int nr_echipe)
{
    Node *top_win, *top_lose;
    while(nr_echipe != 1)
    {
        runda(q, &top_win, &top_lose);

        nr_echipe /= 2;
    }

}
*/