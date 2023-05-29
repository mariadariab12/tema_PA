#include"queue_stack.h"

void vector_cerinte(FILE *cerinte_file, int cerinte[]);

//task1
void atribuire_juc(FILE *read_file, Team echipa, int j);
int team_file_read(FILE *read_file, Node** head_list);
void display_list(Node* head);
void f_display_list(Node *head, FILE* write_file);
void proba_display_list(Node *head);
int task1(FILE *read_file, Node **head_list, FILE *write_file, int cerinte[]);
//task2
int calculare_N(int nr_echipe);
void calcul_punctaj_echipa(Node** head_list);
float punctaj_min(Node* head_list);
void eliminare_primul(Node** head_list);
void eliminare_urmator(Node** nod_anterior);
void task2(Node **head_list, int *nr_echipe, FILE* write_file, int cerinte[]);

//task3
void creare_meciuri(QGame **q, Node *head_list, FILE* write_file, int cerinte[]);
int winner(Team team_1, Team team_2);
void add_pct_winner(Team *team);
void runda(QGame *q, Node** top_win, Node** top_lose, int i, FILE* write_file);
void move_win_to_queue_and_fdisplay(QGame **q, Node **top_win, FILE* write_file, int cerinte[]);
void afisare_winners(Team team, FILE* write_file);
void afisare_win_round(Node *top_win, int i, FILE* write_file, int cerinte[]);
void copiere_stiva(Node *top, Node **top_copy);
Team maxim(Node *head_list);
void eliminare(Node **head_list, Team max);
void top_n(Node **head_list, int n, FILE* write_file, int cerinte[]);
void task3(QGame **q, int *nr_echipe, Node **top_win, FILE* write_file, Node **tree_list, int cerinte[]);

//task4
void creare_bst(Node *tree_list, Node_tree **root);
void top_descresc(Node_tree **root, int n_top, FILE *write_file, int cerinte[], Node** head_task5);

//task5
Node* find_node(Node *head_list, int i); //gaseste al i-lea nod
Node_tree* add_left(Node_tree *node_curent, int i_curent, Node* head_task5);
Node_tree* add_right(Node_tree *node_curent, int i_curent, Node* head_task5);
void parcurgere_nivel(Node_tree *root, FILE* write_file);
void avl_tree(Node_tree** root_avl, Node *tree_list, int nr_top);
void task5(Node_tree *root, FILE* write_file, int cerinte[]);