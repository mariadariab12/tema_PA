#include"queue_stack.h"

//task1
void addAtBeginning(Node **head, Data v);
void addAtEnd(Node** head, Data v);
void lista_null(Node* head_list);
void fisier_null(FILE* read_file);
void atribuire_juc(FILE *read_file, Team echipa, int j);
int team_file_read(FILE *read_file, Node** head_list);
void display_list(Node* head);
int task1(FILE* read_file, Node** head_list);

//task2
int calculare_N(int nr_echipe);
void calcul_punctaj_echipa(Node** head_list);
float punctaj_min(Node* head_list);
void eliminare_primul(Node** head_list);
void eliminare_echipa(Node** nod_anterior);
void task2(Node** head_list, int nr_echipe);

//task3
void creare_meciuri(QGame **q, Node* head_list);
int winner(Team team_1, Team team_2);
void add_pct_winner(Team *team);
void runda(QGame *q, Node** top_win, Node** top_lose);