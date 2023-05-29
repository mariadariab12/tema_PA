#include"library.h"

int main(int argc, char *argv[])
{
    int cerinte[5];
    FILE *cerinte_file = fopen(argv[1], "r");
    vector_cerinte(cerinte_file, cerinte);
    //task 1
    Node* head_list;
    FILE *read_file, *write_file;
    read_file = fopen(argv[2], "r");
    write_file = fopen(argv[3], "w");
    int nr_echipe = task1(read_file, &head_list, write_file, cerinte);
    
    //task 2
    //fprintf(write_file, "N: %d\n", calculare_N(nr_echipe));
    calcul_punctaj_echipa(&head_list);
    task2(&head_list, &nr_echipe, write_file, cerinte);
    
    //task 3 
    QGame *q;
    creare_meciuri(&q, head_list, write_file, cerinte);
    Node* top_win, *top_lose, *tree_list;
    task3(&q, &nr_echipe, &top_win, write_file, &tree_list, cerinte);
    //printf("task 3 head: %s\n", tree_list->val.nume_echipa);

    //task4
    Node_tree* root;
    creare_bst(tree_list, &root);
    int n_top=8;
    Node* head_task5;
    top_descresc(&root, n_top, write_file, cerinte, &head_task5);
    //printf("task 4 head: %s\n", head_task5->val.nume_echipa);

    
    //task5
    if(cerinte[4]==1)
    {
    Node_tree* root_avl;
    avl_tree(&root_avl, head_task5, n_top);
    task5(root_avl, write_file, cerinte);
    }
    

    
    fclose(read_file);
    fclose(write_file);
    return 0;

}