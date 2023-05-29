#include"library.h"

//inceput task4
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

    //eliberare memorie
    free(tree_list);

}

//afisare lista echipelor in ordine descrescatoare
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
            afisare_winners(max->val, write_file);
            addAtBeginning(head_task5, max->val);
            //eliberare memorie
            delete_node(root, max->val);
            n_top--;
        }
        while(n_top != 0);

    }
}
