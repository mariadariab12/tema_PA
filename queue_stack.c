#include"queue_stack.h"

//list
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

//check
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

//queue
/*
QGame* createQueue_Game(){
	QGame **q;
	(*q)=(QGame *)malloc(sizeof(QGame));
	if ((*q)==NULL) return NULL;
	(*q)->front=(*q)->rear=NULL;

	return (*q);
}
*/

void enQueue(QGame **q, Team team_1, Team team_2){
	Node_Game* newNode=(Node_Game*)malloc(sizeof(Node_Game));
	newNode->team1=team_1;
    newNode->team2=team_2;
	newNode->next=NULL;
	if ((*q)->rear==NULL) (*q)->rear=newNode;
	else{
		((*q)->rear)->next=newNode;
		((*q)->rear)=newNode;
	}
	if ((*q)->front==NULL) (*q)->front=(*q)->rear;
}

int isEmpty_queue(QGame* q){
	return (q->front==NULL);
}

void deQueue(QGame *q, Team* team_1, Team* team_2) //team_1 si team_2 trebuie transmise prin referinta
{
	Node_Game* aux;
	if (isEmpty_queue(q)) return;

	aux=q->front;
	(*team_1)=aux->team1;
    (*team_2)=aux->team2;
	q->front=(q->front)->next;
	free(aux);
}

void deleteQueue(QGame **q){
	Node_Game* aux;
	while (!isEmpty_queue(*q)){
		aux=(*q)->front;
		(*q)->front=(*q)->front->next;
		free(aux);
	}

}

void displayQueue(QGame *q) {
    Node_Game* aux = q->front;
    Team team_1, team_2;
    int i = 1;

    if (isEmpty_queue(q)) {
        printf("The queue is empty!\n");
        return;
    }

    while (aux != NULL) {
        team_1 = aux->team1;
        team_2 = aux->team2;
        printf("Meciul %d:\n", i);
        i++;
        printf("Echipa 1: %s\n", team_1.nume_echipa);
        printf("Echipa 2: %s\n", team_2.nume_echipa);
        aux = aux->next;
    }
}

//stack

int isEmpty_stack(Node* top){
	return top==NULL;
}

Data top(Node *top){
	if (isEmpty_stack(top)) printf("is empty!");
    else{
	return top->val;
    }
}

void push(Node**top, Data v) {
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->val=v;
	newNode->next=*top;
	*top=newNode;
}

Data pop(Node**top) {
	if (isEmpty_stack(*top)) printf("is empty!");
    else{
	Node *temp=(*top);
	Data aux=temp->val;
	*top=(*top)->next;
	//free(temp);
	return aux;
    }
}

void deleteStack(Node**top)
{
	Node  *temp;
	while (!isEmpty_stack(*top))
    {
		temp=*top;
		*top=(*top)->next;
		free(temp);
    }
}

void display_stack(Node *top)
{
    if(isEmpty_stack(top)) printf("is empty!");
    while(!isEmpty_stack(top))
    {
        printf("%s\n", (pop(&top)).nume_echipa);
    }

}

/*
int isEmpty_stack(Node_Game* top){
    return top==NULL;
}

Data top(Node_Game *top, Team* team_1, Team* team_2){
    if (isEmpty_stack(top)) printf("is empty!");
    else{
    (*team_1)=top->team1;
    (*team_2)=top->team2;
    }
}

void push(Node_Game** top, Team team_1, Team team_2) {
    Node_Game* newNode=(Node_Game*)malloc(sizeof(Node_Game));
    newNode->team1=team_1;
    newNode->team2=team_2;
    newNode->next=*top;
    *top=newNode;
}

void pop(Node_Game**top, Team* team_1, Team* team_2) {
    if (isEmpty_stack(*top)) return;
    Node_Game *temp=(*top);
    (*team_1)=temp->team1;
    (*team_2)=temp->team2;
    *top=(*top)->next;
    free(temp);
}

void deleteStack(Node_Game** top){
    Node_Game  *temp;
    while (!isEmpty_stack(*top))
        temp=*top;
        *top=(*top)->next;
        free(temp);
    }
*/
