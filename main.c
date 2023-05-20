#include"library.h"

int main()
{
    Node* head_list;
    FILE* read_file;
    read_file = fopen("d.in", "r");

    int nr_echipe;
    nr_echipe = task1(read_file, &head_list);

    calcul_punctaj_echipa(&head_list);

    task2(&head_list, nr_echipe);

    fclose(read_file);

    QGame *q;
    q = createQueue_Game();
    creare_meciuri(q, head_list);
    displayQueue(q);
    printf("%d", isEmpty_queue(q));
    Node* top_win;
    Node *top_lose;
    //meciuri(q, &top_win, &top_lose);
    //display_stack(top_win);
    //display_stack(top_lose);

    return 0;

}
