#include"library.h"

int main()
{
    Node* head_list;
    FILE* read_file, *write_file;
    read_file = fopen("d.in", "r");
    write_file = fopen("r.out", "w");

    int nr_echipe;

    nr_echipe = task1(read_file, &head_list, write_file);

    calcul_punctaj_echipa(&head_list);

    
    task2(&head_list, &nr_echipe, write_file);


    QGame *q;

    creare_meciuri(&q, head_list, write_file);
    displayQueue(q);
    //printf("%d", (q->front == NULL));
    Node* top_win;
    Node *top_lose;
    runda(q, &top_win, &top_lose);
    display_stack(top_win);
    //printf("\n lose:\n");
    //display_stack(top_lose);
    //printf("%d\n", (q->front == NULL));

    task3(&q, &nr_echipe, &top_win, write_file);

    fclose(read_file);
    fclose(write_file);
    return 0;

}
