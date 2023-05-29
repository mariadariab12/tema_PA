//task 1
typedef struct Player{
    char* firstName;
    char* secondName;
    int points;
}Player;

typedef struct Team{
    int nr_juc;
    char* nume_echipa;
    struct Player* jucator;
    float punctaj_echipa;
}Team;

typedef Team Data;

typedef struct Node{
	Data val;
	struct Node *next;
}Node;

//task 3

typedef struct Node_Game{
    struct Team team1;
    struct Team team2;
    struct Node_Game* next;
}Node_Game;

typedef struct QGame{
   Node_Game *front, *rear; 
}QGame;

//task 4
typedef struct Node_tree{
    int h;
    Data val;
    struct Node_tree *left, *right;
}Node_tree;

