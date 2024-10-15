#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "queue.h"

/*
   Print queue
*/

static void print_queue(const Queue *queue) {
	ListNode *node;
	char data[20];
	int size, i;

	fprintf(stdout, "El tama�o de la fila es %d\n", size = queue_size(queue));

	i = 0;
	node = list_head(queue);

	while (i < size) {
		strcpy(data, (char *)list_data(node));
		fprintf(stdout, "queue[%03d]=%s, %p -> %p\n", i, data, node, node->next);
		node = list_next(node);
	 	i++;
	}
	return;
}

int main(int argc, char const *argv[]) {
	Queue queue;
	int i;
	char **data, *d;

	// Iniciando la fila
	queue_init(&queue, free);


	for (i = 1; i < argc; i++) {
	   	if((data = (char **)malloc(sizeof(char*))) == NULL)
	   		return -1;
		if((*data = (char *)malloc(20*sizeof(char))) == NULL)
	   		return -2;
			   		   
		strcpy(*data,argv[i]);
		if (queue_enqueue(&queue, *data) != 0)
	    	return 1;
	}
	print_queue(&queue);
	fprintf(stdout, "\nPopeando 2 elementoss\n");

	for (i = 0; i < 2; i++) {
        if (queue_dequeue(&queue, (void **)&data) == 0) {
            free(data);
    	}else {
            return 1;
        }
    }
    print_queue(&queue);

	fprintf(stdout, "\nPushing \"Goku\" y \"Bardock\"\n");
	if((d = (char *)malloc(20*sizeof(char))) == NULL)
	   	return -2;
	strcpy(d,"Gokuisthestrongest");
	if (queue_enqueue(&queue, d) != 0)
		return 1;

	if((d = (char *)malloc(20*sizeof(char))) == NULL)
	   	return -2;
	strcpy(d,"Bardockelmejorapa");
	if (queue_enqueue(&queue, d) != 0)
		return 1;
	print_queue(&queue);

	if ((d = queue_peek(&queue)) != NULL)
		fprintf(stdout, "\nChequeando el elemento del fondo [value]=%s\n", d);
	else
		fprintf(stdout, "\nChequeando el elemento del fondot [value]=NULL\n");
	print_queue(&queue);

	fprintf(stdout, "\nPopeando todos los elementos\n");
	while (queue_size(&queue) > 0) {
		if (queue_dequeue(&queue, (void **)&data) == 0)
			free(data);
	}
	if ((d = queue_peek(&queue)) != NULL)
		fprintf(stdout, "\nChequeando el elemento del fondo [value]=%s\n", d);
	else
		fprintf(stdout, "\nChequeando el elemento del fondo [value]=NULL\n");
	print_queue(&queue);

	fprintf(stdout, "\nDestruyendo la fila\n");
	queue_destroy(&queue);
	
	return 0;
}
