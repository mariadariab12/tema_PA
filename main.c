#include"library.h"

int main(int argc, char *argv[])
{
    int cerinte[5];
    FILE *cerinte_file = fopen("c.in", "r");
    vector_cerinte(cerinte_file, cerinte);
    //task 1
    Node* head_list;
    FILE *read_file, *write_file;
    read_file = fopen("d.in", "r");
    write_file = fopen("r.out", "w");
    int nr_echipe = task1(read_file, &head_list, write_file, cerinte);
    
    //task 2
    calcul_punctaj_echipa(&head_list);
    task2(&head_list, &nr_echipe, write_file, cerinte);
    
    //task 3
    QGame *q;
    creare_meciuri(&q, head_list, write_file, cerinte);
    Node* top_win, *top_lose, *tree_list;
    task3(&q, &nr_echipe, &top_win, write_file, &tree_list, cerinte);

    //task4
    Node_tree* root;
    creare_bst(tree_list, &root);
    int n_top=8;
    top_descresc(&root, n_top, write_file, cerinte);

    fclose(read_file);
    fclose(write_file);
    return 0;

}
