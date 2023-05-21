#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include"struct.h"

//list
void addAtBeginning(Node **head, Data v);
void addAtEnd(Node** head, Data v);

//check
void lista_null(Node* head_list);
void fisier_null(FILE* read_file);

//queue
//QGame* createQueue_Game();
void enQueue(QGame**q, Team team_1, Team team_2);
int isEmpty_queue(QGame* q);
void deQueue(QGame *q, Team* team_1, Team* team_2);
void deleteQueue(QGame **q);
void displayQueue(QGame *q);

//stack
int isEmpty_stack(Node*top);
Data top(Node *top);
void push(Node**top, Data v);
Data pop(Node**top);
void deleteStack(Node**top);
void display_stack(Node *top);
