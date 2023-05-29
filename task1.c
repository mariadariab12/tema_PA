#include"library.h"

//inceput task1
//citire date despre jucatorii fiecarei echipe
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

//citire nr echipe, nr de jucatori ai fiecarei echipe, plus numele acesteia
int team_file_read(FILE *read_file, Node **head_list)
{
    fisier_null(read_file); // check fis

    int nr_echipe;
    fscanf(read_file, "%d", &nr_echipe);

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
        if(echipa.nume_echipa[strlen(echipa.nume_echipa)- 2] == ' ')
            {
                echipa.nume_echipa[strlen(echipa.nume_echipa)-2] = '\0';
            }
        else 
            echipa.nume_echipa[strlen(echipa.nume_echipa)-1] = '\0';

        echipa.jucator = (struct Player *)malloc(echipa.nr_juc * sizeof(struct Player));

        for (j = 0; j < echipa.nr_juc; j++)
        {
            atribuire_juc(read_file, echipa, j);
        }

        addAtBeginning(head_list, echipa);

    }

    return nr_echipe;
}

//afisare lista
void f_display_list(Node *head, FILE* write_file)
{
    while (head->next != NULL)
    {
        fprintf(write_file, "%s", head->val.nume_echipa);
        fprintf(write_file, "\n");
        head = head->next;
    }
    fprintf(write_file, "%s", head->val.nume_echipa);
}

int task1(FILE *read_file, Node **head_list, FILE *write_file, int cerinte[])
{
    int nr_echipe = team_file_read(read_file, head_list);

    if(cerinte[0]==1 && cerinte[1]==0)
    {
        f_display_list(*head_list, write_file);
        fprintf(write_file, "\n");
    }

    return nr_echipe;
}
