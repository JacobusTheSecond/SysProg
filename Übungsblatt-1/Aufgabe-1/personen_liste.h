#ifndef PERSONEN_LISTE
#define PERSONEN_LISTE

typedef struct node {
        struct node* next;
        struct node* prev;
        char* vorname;
        char* nachname;
} node;


void freeNode(node* person);
void destroyList(node* head);
void printNode(node* person);
void printList(node* head);
void insertSorted(node* head,node* person);
void createSortedDLL(char const* const fileName);

#endif
