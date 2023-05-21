#include"library.h"

int main()
{
    Node* head_list;
    FILE* read_file;
    read_file = fopen("d.in", "r");

    int nr_echipe;

    nr_echipe = task1(read_file, &head_list);

    calcul_punctaj_echipa(&head_list);

    
    task2(&head_list, &nr_echipe);


    QGame *q;

    creare_meciuri(&q, head_list);
    displayQueue(q);
    //printf("%d", (q->front == NULL));
    Node* top_win;
    Node *top_lose;
    runda(q, &top_win, &top_lose);
    display_stack(top_win);
    //printf("\n lose:\n");
    //display_stack(top_lose);
    //printf("%d\n", (q->front == NULL));

    task3(&q, &nr_echipe, &top_win);

    fclose(read_file);
    return 0;

}
