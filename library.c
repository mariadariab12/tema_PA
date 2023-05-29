#include "library.h"

void vector_cerinte(FILE *cerinte_file, int cerinte[])
{
    fisier_null(cerinte_file); // check fis
    int i, n=5;
    for(i=0; i<n; i++)
    {
        fscanf(cerinte_file, "%d", &cerinte[i]);
    }
}

//task1
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
                //echipa.nume_echipa[strlen(echipa.nume_echipa)] = 'a';
            }
        else 
            echipa.nume_echipa[strlen(echipa.nume_echipa)-1] = '\0';

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

void proba_display_list(Node *head)
{
    printf("\n\n\n\n");
    while (head->next != NULL)
    {
        printf("%s %f", head->val.nume_echipa, head->val.punctaj_echipa);
        printf("\n");
        head = head->next;
    }
    printf("%s", head->val.nume_echipa);

    printf("\n\n\n\n");
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

void eliminare_urmator(Node **nod_anterior)
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
    while (maxim <= nr_echipe)
    {
        maxim *= 2;
        j++;
    }

    return j - 1;
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

                if (aux->next == NULL)
                {
                    break;
                } else if (aux->next->next == NULL)
                {
                    break;
                }
            }

            if (aux->next == NULL)
            {
                break;
            } else if (aux->next->next == NULL)
            {
                break;
            }


            aux = aux->next;
        }
    }

    if(cerinte[1] == 1)
        f_display_list(*head_list, write_file);
}

// task3

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

        int nr_spatii = nr - strlen(head_list->val.nume_echipa);
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

    (*top_win) = (Node *)malloc(sizeof(Node));
    lista_null(*top_win); // check
    *top_win = NULL;

    (*top_lose) = (Node *)malloc(sizeof(Node));
    lista_null(*top_lose); // check
    *top_lose = NULL;

    while (aux != NULL)
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

    deleteStack(top_lose);

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

void copiere_stiva(Node *top, Node **top_copy)
{
    while(!isEmpty_stack(top))
    {
        addAtEnd(top_copy, pop(&top));
    }

}

/*
Team maxim(Node *head_list)
{
    float max=0;
    Team team_max;
    
    while(head_list != NULL)
    {
        if(head_list->val.punctaj_echipa >= max)
        {
            team_max = head_list->val;
            max = head_list->val.punctaj_echipa;
        }

        head_list = head_list->next;
    }
    
    return team_max;

}

void eliminare(Node** head_list, Team max)
{
    Node *aux = *head_list;
    Node *anterior = NULL;

    while(aux != NULL)
    {
        if (strcmp(aux->val.nume_echipa, max.nume_echipa) == 0)
        {
            if(anterior == NULL)
            {
                eliminare_primul(head_list);
                aux = (*head_list);
            }
            else
            {
                eliminare_urmator(&anterior);
                aux = anterior->next;
            }

        }
        else
        {
            anterior = aux;
            aux = aux->next;
        }

    }

}

void top_n(Node **head_list, int n, FILE* write_file, int cerinte[])
{
    do{
    Team max1 = maxim(*head_list);
    if(cerinte[2] == 1) afisare_winners(max1, write_file);
    eliminare(head_list, max1);
    n--;
    }while(n!=0);

}
*/

void task3(QGame **q, int *nr_echipe, Node **top_win, FILE* write_file, Node **tree_list, int cerinte[])
{
    Node *top_lose;
    /*
    Node *top_copy;

    top_copy = (Node *)malloc(sizeof(Node));
    lista_null(top_copy); // check
    top_copy = NULL;
    */

    *tree_list = (Node *)malloc(sizeof(Node));
    lista_null(*tree_list); // check
    *tree_list = NULL;

    int i=2, n_top=8;
    (*nr_echipe) /= 2;
    Team team;

    while((*nr_echipe) != 0)
    {
        
        runda(*q, top_win, &top_lose, i, write_file);
        deleteQueue(q);

        if((*nr_echipe) == n_top)
        {
            //copiere_stiva(*top_win, &top_copy);
            copiere_stiva(*top_win, tree_list);
        }

        if(cerinte[2] == 1) afisare_win_round(*top_win, i, write_file, cerinte);

        if((*nr_echipe) == 1) break;

        if(cerinte[2] == 1) fprintf(write_file, "\n--- ROUND NO:%d\n", i);
        i++;

        move_win_to_queue_and_fdisplay(q, top_win, write_file, cerinte); 

        (*nr_echipe) /= 2;
    }

    //if(cerinte[2] == 1) fprintf(write_file, "\nTOP %d TEAMS:\n", n_top);
    //top_n(&top_copy, n_top, write_file, cerinte);

}

//task4
void creare_bst(Node *tree_list, Node_tree **root)
{
    (*root) = (Node_tree *)malloc(sizeof(Node_tree));
    root_null(*root); // check root
    *root = NULL;

    while(tree_list != NULL)
    {
        *root = insert(*root, tree_list->val);
        tree_list = tree_list->next;
    }

}

void top_descresc(Node_tree **root, int n_top, FILE *write_file, int cerinte[], Node** head_task5)
{
    
    (*head_task5) = (Node *)malloc(sizeof(Node));
    lista_null(*head_task5); // check head
    *head_task5 = NULL;

    if(cerinte[3] == 1)
    {
        fprintf(write_file, "\nTOP %d TEAMS:\n", n_top);
        Node_tree *max;
        do
        {
            max = max_value(*root);
            //if(cerinte[3] == 1) afisare_winners(max->val, write_file);
            afisare_winners(max->val, write_file);
            addAtBeginning(head_task5, max->val);
            delete_node(root, max->val);
            n_top--;
        }
        while(n_top != 0);

    }
}

//task5
Node* find_node(Node *head_list, int i) //gaseste al i-lea nod
{
    int k=1;
    Node* aux;
    //Node* parcurgere = *head_list;
    while(head_list != NULL && k<=i)
    {
        aux = head_list;
        head_list = head_list->next;
        k++;
    }

    //printf("%s head: %s\n\n\n", aux->val.nume_echipa, (head_list)->val.nume_echipa);
    return aux;
}


/*
void add_left_right(Node_tree **node_curent, int i_curent, int n,  Node* tree_list)
{
    Node *left, *right; 
    left = find_node(tree_list, i_curent - pow(2,n));
    (*node_curent)->left->val = left->val;
    right = find_node(tree_list, i_curent + pow(2,n));
    (*node_curent)->right->val = right->val;
}

void avl_tree(Node_tree** root_avl, Node *tree_list, int nr_top)
{
    int N = calculare_N(nr_top);

    (*root_avl) = (Node_tree *)malloc(sizeof(Node_tree));
    root_null(*root_avl); // check root
    *root_avl = NULL;

    Node* node_to_add;
    int i_curent = (nr_top/2)+1;
    node_to_add = find_node(tree_list, i_curent);
    (*root_avl)->val = node_to_add->val;

    int n = N-2;
    Node_tree *nod_curent;
    nod_curent = (*root_avl);

    while(n > 0)
    {
        add_left_right(&(nod_curent->left), i_curent, n, tree_list);
        add_left_right(&(nod_curent->right), i_curent, n, tree_list);
        n--;
    }

}
*/

Node_tree* add_left(Node_tree *node_curent, int i_curent, Node* head_task5)
{
    //i_curent = i_curent - pow(2,n);
    Node* left = find_node(head_task5, i_curent);
    node_curent->left = (Node_tree*) malloc(sizeof(Node_tree));
    node_curent->left->val = left->val;
    node_curent->left->h = node_curent->h + 1;
    node_curent->left->left = NULL;
    node_curent->left->right = NULL;
    return node_curent->left;
}

Node_tree* add_right(Node_tree *node_curent, int i_curent, Node* head_task5)
{
    Node* right = find_node(head_task5, i_curent);
    node_curent->right = (Node_tree*) malloc(sizeof(Node_tree));
    node_curent->right->val = right->val;
    node_curent->right->h = node_curent->h + 1;
    node_curent->right->left = NULL;
    node_curent->right->right = NULL;
    return node_curent->right;
}

void parcurgere_nivel(Node_tree *root, FILE* write_file) 
{
    if (root != NULL) 
	{
        if(root->h == 2)
            fprintf(write_file, "%s\n", root->val.nume_echipa);
		parcurgere_nivel(root->right, write_file);
		parcurgere_nivel(root->left, write_file);
	}
}

void avl_tree(Node_tree** root_avl, Node *head_task5, int nr_top)
{
    int N = calculare_N(nr_top);
    (*root_avl) = (Node_tree *)malloc(sizeof(Node_tree));
    root_null(*root_avl); // check root
    *root_avl = NULL;

    Node* node_to_add;
    int i_curent = (nr_top/2)+1;
    node_to_add = find_node(head_task5, i_curent);
    (*root_avl) = newNode(node_to_add->val);
    (*root_avl)->h = 0;

    Node_tree *nod_curent;
    nod_curent = (*root_avl);

    int n = N-2;
    //nivel1
    nod_curent->left = add_left(nod_curent, i_curent - pow(2,n), head_task5);
    nod_curent->right = add_right(nod_curent, i_curent + pow(2,n), head_task5);

    //nivel2
    nod_curent->left->left = add_left(nod_curent->left, i_curent - pow(2,n)-1, head_task5);
    nod_curent->right->right = add_right(nod_curent->left, i_curent - pow(2,n)+1, head_task5);
    nod_curent->right->left = add_left(nod_curent->right, i_curent + pow(2,n)-1, head_task5);
    nod_curent->right->right = add_right(nod_curent->right, i_curent + pow(2,n)+1, head_task5);

    //nivel3
    nod_curent->left->left->left = add_left(nod_curent->left->left, 1, head_task5);

}

void task5(Node_tree *root, FILE* write_file, int cerinte[])
{
    if(cerinte[4] == 1)
    {
        fprintf(write_file, "\nTHE LEVEL 2 TEAMS ARE:\n");
        parcurgere_nivel(root, write_file);
    }
}

/*
void avl_tree(Node_tree** root_avl, Node *tree_list, int nr_top)
{
    int N = calculare_N(nr_top);
    //printf("N: %d\n", N);
    (*root_avl) = (Node_tree *)malloc(sizeof(Node_tree));
    root_null(*root_avl); // check root
    //*root_avl = NULL;

    Node* node_to_add;
    int i_curent = (nr_top/2)+1;
    printf("i: %d\n", i_curent);
    node_to_add = find_node(tree_list, i_curent);

    (*root_avl) = newNode(node_to_add->val);
    //(*root_avl)->val = node_to_add->val;

    int n = N-2;
    //printf("%d", n);
    Node_tree *nod_curent;
    nod_curent = (*root_avl);

    //nod_curent->left = add_left(nod_curent, i_curent, n, tree_list);
    //nod_curent->right = add_right(nod_curent, i_curent, n, tree_list);
    //n--;

    while(n > -1)
    {
        nod_curent->left = add_left(nod_curent, i_curent, n, tree_list);
        nod_curent->right = add_right(nod_curent, i_curent, n, tree_list);
        //nod_curent->right->left = add_left(nod_curent->right, i_curent, n, tree_list);
        //nod_curent->right->right = add_right(nod_curent->right, i_curent, n, tree_list);

        n--;
    }

    preorder(*root_avl);
}
*/