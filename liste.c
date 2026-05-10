//#include <stdio.h>
//#include <stdlib.h>
//
//struct node {
//	int value;
//	struct node* next;
//};
//typedef struct node nod;
//
//void afisare(nod* head) {
//	nod* temp = head;
//
//	while (temp != NULL) {
//		printf("%d - ", temp->value);
//		temp = temp->next;
//	}
//	printf("\n");
//}
//
//int main() {
//	nod n1, n2, n5, n6;
//	nod* head;
//
//	n1.value = 10;
//	n2.value = 20;
//	n5.value = 55;
//	n6.value = 60;
//
//	head = &n1;
//	n1.next = &n2;
//	n2.next = &n5;
//	n5.next = &n6;
//	n6.next = NULL;
//
//	afisare(head);
//
//	return 0;
//}