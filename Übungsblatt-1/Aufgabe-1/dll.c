#include <stdio.h>
#include "mystring.h"
#include <stdlib.h>
#include "personen_liste.h"

//All rights reserver to Linus Torvald xDDD
int strcmp(const char *cs, const char *ct)
{
	unsigned char c1, c2;

	while (1) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
	}
	return 0;
}
void freeNode(node* destroyer){
	free(destroyer->vorname);
	free(destroyer->nachname);
	free(destroyer);
}
void destroyList(node* head){
	node* iterator = head->next;
	while(iterator != NULL){
		node* destroyer = iterator;
		iterator = iterator->next;
		freeNode(destroyer);
	}
	head->next = NULL;
}

void printNode(node* person){
	printf("Vorname : %s\n",person->vorname);
	printf("Nachname: %s\n",person->nachname);
}

void printList(node* head){
	node* iterator = head->next;
	while(iterator != NULL){
		printNode(iterator);
		iterator = iterator->next;
	}
}

int bigger(node* a, node* b){
	if(strcmp(a->nachname,b->nachname) == 0){
		return strcmp(a->vorname,b->vorname) > 0;
	}else{
		return strcmp(a->nachname,b->nachname) > 0;
	}
}

void insertSorted(node* head, node* new_node){
	node* iterator = head;
	while(iterator->next != NULL){
		//search for node, that is BEFORE the hole we want to insert new_node into
		if(bigger(new_node,iterator->next)){
			iterator = iterator->next;
		}else{
			break;
		}
	}
	//insert new_node after iterator;
	node* next_node = iterator->next;
	iterator->next = new_node;
	new_node->prev = iterator;
	new_node->next = next_node;
	if(next_node != NULL){
		next_node->prev = new_node;
	}

}

void fillNode(node* node, char* name){
	//find space
	int spacesep = 0;
	while(name[spacesep] != ' '){
		spacesep++;
	}
	//find null
	int eol = spacesep;
	while(name[eol]!= '\n'){
		eol++;
	}

	char* vorname = calloc(spacesep,sizeof(char));

	char* nachname = calloc(eol-spacesep-1,sizeof(char));
	//vorname
	for(int i=0;i<spacesep;++i){
		vorname[i] = name[i];
	}
	
	//nachname
	for(int i=0;i<eol-spacesep-1;++i){
		nachname[i] = name[spacesep+1+i];
	}
	node->vorname = vorname;
	node->nachname = nachname;
}

void createSortedDLL(char const* const fileName){
	FILE* file = fopen(fileName,"r");
	char line[256];
	node* head = calloc(1,sizeof(node));

	while (fgets(line,sizeof(line),file)){
		printf("%s\n",line);

		node* new_node = calloc(1,sizeof(node));
		fillNode(new_node,line);
		
		insertSorted(head,new_node);

	}

	printf("LISTOUTPUT:\n\n");
	printList(head);

	fclose(file);
	destroyList(head);
	free(head);
}




int main(int argc, char *argv[]){
	if(argc == 2){
		char const* const fileName = argv[1];
		createSortedDLL(fileName);
	}else{
		printf("Bitte geb einen Dateipfad als Argument mit ein!");
	}
}


