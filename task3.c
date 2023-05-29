#include"library.h"

//inceput task3
void creare_meciuri(QGame **q, Node *head_list, FILE* write_file, int cerinte[])
{
    (*q)=(QGame *)malloc(sizeof(QGame));
	if ((*q)==NULL) 
    {
        printf("Failed to allocate memory for head_list\n");
        exit(1);
    }

	(*q)->front=(*q)->rear=NULL;

    int nr=33;
    if(cerinte[2] == 1)
        fprintf(write_file, "\n\n--- ROUND NO:1\n");


    while (head_list != NULL)
    {
        enQueue(q, head_list->val, head_list->next->val);
        if (head_list->next == NULL)
        {
            break;
        }

        int nr_spatii = nr - strlen(head_list->val.nume_echipa); //pentru a fi conform fisierelor r.out
        if(cerinte[2] == 1){
        fprintf(write_file, "%s", head_list->val.nume_echipa);
        fprintf(write_file, "%*s", nr_spatii, " ");
        fprintf(write_file, "-");}

        if(cerinte[2] == 1){
        nr_spatii = nr - strlen(head_list->next->val.nume_echipa);
        fprintf(write_file, "%*s", nr_spatii, " ");
        fprintf(write_file, "%s", head_list->next->val.nume_echipa);
        fprintf(write_file, "\n");}

        head_list = (head_list->next)->next;
    }
}

int winner(Team team_1, Team team_2)
{
    if(team_1.punctaj_echipa > team_2.punctaj_echipa)
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

void runda(QGame *q, Node** top_win, Node** top_lose, int i, FILE* write_file)
{
    Node_Game* aux = q->front;
	if (isEmpty_queue(q)) return;
    QGame *aux_q=q;
    Team team_1, team_2;

    (*top_win) = (Node *)malloc(sizeof(Node)); //creare stiva castigatori
    lista_null(*top_win); // check
    *top_win = NULL;

    (*top_lose) = (Node *)malloc(sizeof(Node)); //creare stiva invinsi
    lista_null(*top_lose); // check
    *top_lose = NULL;

    while (aux != NULL) //modificare 
    {
	    team_1=aux->team1;
        team_2=aux->team2;
        aux = aux->next;

    
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

    deleteStack(top_lose); //se sterge, nu mai este nevoie de ea in continuarea problemei

}

void move_win_to_queue_and_fdisplay(QGame **q, Node **top_win, FILE* write_file, int cerinte[])
{
    (*q)=(QGame *)malloc(sizeof(QGame));
	if ((*q)==NULL) 
    {
        printf("Failed to allocate memory for head_list\n");
        exit(1);
    }

    Team add_team1, add_team2;
    int i=1, nr=33;

    while(!isEmpty_stack(*top_win))
    {
        add_team1 = pop(top_win);

        if(isEmpty_stack(*top_win) == 1) break;

        int nr_spatii = nr - strlen(add_team1.nume_echipa);
        if(cerinte[2] == 1){
        fprintf(write_file, "%s", add_team1.nume_echipa);
        fprintf(write_file, "%*s", nr_spatii, " ");
        fprintf(write_file, "-");}

        add_team2 = pop(top_win);

        nr_spatii = nr -strlen(add_team2.nume_echipa);
        if(cerinte[2] == 1){
        fprintf(write_file, "%*s", nr_spatii, " ");
        fprintf(write_file, "%s", add_team2.nume_echipa);
        fprintf(write_file, "\n");}

        enQueue(q, add_team1, add_team2);
    }

}

//functii pentru a facilita afisarea conform fisierelor r.out
void afisare_winners(Team team, FILE* write_file)
{
    int nr=34, nr_spatii;
    nr_spatii = nr -strlen(team.nume_echipa);
    fprintf(write_file, "%s", team.nume_echipa);
    fprintf(write_file, "%*s", nr_spatii, " ");
    fprintf(write_file, "-  ");
    fprintf(write_file, "%.2f\n", team.punctaj_echipa);
}

void afisare_win_round(Node *top_win, int i, FILE* write_file, int cerinte[])
{
    Team add_team1, add_team2, winner;
    int nr=33;

    if(cerinte[2] == 1) fprintf(write_file, "\nWINNERS OF ROUND NO:%d\n", i-1);

    while(!isEmpty_stack(top_win))
    {
        add_team1 = pop(&top_win);
        if(cerinte[2] == 1) afisare_winners(add_team1, write_file);

        if(isEmpty_stack(top_win) == 1) 
        {
            break;
        }
       
        add_team2 = pop(&top_win);
        if(cerinte[2] == 1) afisare_winners(add_team2, write_file);

    }

}

//necesara mai departe, pentru task 4
void copiere_stiva(Node *top, Node **top_copy)
{
    while(!isEmpty_stack(top))
    {
        addAtEnd(top_copy, pop(&top));
    }

}

void task3(QGame **q, int *nr_echipe, Node **top_win, FILE* write_file, Node **tree_list, int cerinte[])
{
    Node *top_lose;

    *tree_list = (Node *)malloc(sizeof(Node));
    lista_null(*tree_list); // check
    *tree_list = NULL;

    int i=2, n_top=8;
    (*nr_echipe) /= 2;
    Team team;

    while((*nr_echipe) != 0)
    {
        runda(*q, top_win, &top_lose, i, write_file);
        //eliberare memorie
        deleteQueue(q);

        if((*nr_echipe) == n_top)
        {
            copiere_stiva(*top_win, tree_list);
        }

        if(cerinte[2] == 1) afisare_win_round(*top_win, i, write_file, cerinte);

        if((*nr_echipe) == 1) break;

        if(cerinte[2] == 1) fprintf(write_file, "\n--- ROUND NO:%d\n", i);
        i++;

        move_win_to_queue_and_fdisplay(q, top_win, write_file, cerinte); 

        (*nr_echipe) /= 2;
    }

    //eliberare memorie
    deleteStack(top_win);
}

