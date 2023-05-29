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

void root_null(Node_tree *root)
{
	if (root == NULL)
    {
        printf("Failed to allocate memory for head_list\n");
        exit(1);
    }
}

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

//bst
Node_tree* newNode(Data data) 
{
	Node_tree* node = (Node_tree*)malloc(sizeof(Node_tree));
	node->val = data;
	node->left = node->right = NULL;
	return node;
}

Node_tree* insert(Node_tree *node, Data key) 
{
	if (node == NULL) return newNode(key);

	if (key.punctaj_echipa < node->val.punctaj_echipa)
		node->left  = insert(node->left, key);
	else if (key.punctaj_echipa > node->val.punctaj_echipa)
		node->right = insert(node->right, key);
    else
        if(strcmp(key.nume_echipa, node->val.nume_echipa) < 0)
            node->left  = insert(node->left, key);
        else node->right = insert(node->right, key);

    return node;
}

void preorder(Node_tree *root) 
{
	if (root != NULL) 
	{
		printf("%s ",root->val.nume_echipa);
		preorder(root->left);
		preorder(root->right);
	}
}

Node_tree* search(Node_tree* root, Data key) 
{
	if (root == NULL || root->val.punctaj_echipa == key.punctaj_echipa)
		return root;
	if (root->val.punctaj_echipa < key.punctaj_echipa)
		return search(root->right, key);
	if (root->val.punctaj_echipa > key.punctaj_echipa)
        return search(root->left, key);
    if(strcmp(key.nume_echipa, root->val.nume_echipa) < 0)
		return search(root->right, key);
    return search(root->left, key); 

	return 0;
}

Node_tree *min_value(Node_tree *root)
{
	Node_tree * aux = root ; // cauta nodul cel mai din stanga
	while ( aux->left != NULL )
		aux = aux->left;
	return aux ;
}

Node_tree *max_value(Node_tree *root)
{
	Node_tree * aux = root; // cauta nodul cel mai din dreapta
	while ( aux->right != NULL )
		aux = aux->right;
	return aux ;
}

void delete_node(Node_tree **root, Data key) 
{
    if (*root == NULL)
        return;

    if (key.punctaj_echipa < (*root)->val.punctaj_echipa)
        delete_node(&((*root)->left), key);
    else if (key.punctaj_echipa > (*root)->val.punctaj_echipa)
        delete_node(&((*root)->right), key);
    else if (strcmp(key.nume_echipa, (*root)->val.nume_echipa) < 0)
        delete_node(&((*root)->left), key);
    else if (strcmp(key.nume_echipa, (*root)->val.nume_echipa) > 0)
        delete_node(&((*root)->right), key);
    else {
        if ((*root)->left == NULL && (*root)->right == NULL) {
            // Nodul este o frunză
            free(*root);
            *root = NULL;
        } else if ((*root)->left == NULL) {
            // Nodul are doar un copil pe partea dreaptă
            Node_tree *temp = *root;
            *root = (*root)->right;
            free(temp);
        } else if ((*root)->right == NULL) {
            // Nodul are doar un copil pe partea stângă
            Node_tree *temp = *root;
            *root = (*root)->left;
            free(temp);
        } else {
            // Nodul are doi copii
            Node_tree *min_right = min_value((*root)->right);
            (*root)->val = min_right->val;
            delete_node(&((*root)->right), min_right->val);
        }
    }
}
