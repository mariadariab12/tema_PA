#include"library.h"

//inceput task5
//gaseste al i-lea nod
Node* find_node(Node *head_list, int i)
{
    int k=1;
    Node* aux;
    while(head_list != NULL && k<=i)
    {
        aux = head_list;
        head_list = head_list->next;
        k++;
    }

    return aux;
}

Node_tree* add_left(Node_tree *node_curent, int i_curent, Node* head_task5)
{
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

//parcurgerea nivelului cerut
void parcurgere_nivel(Node_tree *root, FILE* write_file, int nivel) 
{
    if (root != NULL) 
	{
        if(root->h == nivel)
            fprintf(write_file, "%s\n", root->val.nume_echipa);
		parcurgere_nivel(root->right, write_file, nivel);
		parcurgere_nivel(root->left, write_file, nivel);
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
    
    //eliberare memorie
    free(head_task5);
}

void free_root(Node_tree **root)
{
    if (*root != NULL) 
	{
		free_root(&(*root)->right);
		free_root(&(*root)->left);
	}

}
void task5(Node_tree *root, FILE* write_file, int cerinte[], int nivel)
{
    if(cerinte[4] == 1)
    {
        fprintf(write_file, "\nTHE LEVEL 2 TEAMS ARE:\n");
        parcurgere_nivel(root, write_file, nivel);
    }

    //eliberare memorie
    free_root(&root);
}