#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "queue_stu.h"


void fillQueue(FILE* inp, queue_t* q) {
	shops_t temp;
	while (fscanf(inp, " %s %lf", temp.shopName, &temp.sale) != EOF)
		insert(q, temp);
}

void displayQueue(queue_t q) {
	shops_t temp;
	printf("\nThe List of All Shops: \n");
	printf("Shop Name      Sale Amount\n");
	printf("****************************\n");
	while (!isEmptyQ(&q))
	{
		temp = remove(&q);
		printf("%-20s %7.2f\n", temp.shopName, temp.sale);
	}
	printf("\n");
}

void shopOfTheDay(queue_t q) {
	shops_t theShop, temp;
	theShop = remove(&q);
	while (!isEmptyQ(&q))
	{
		temp = remove(&q);
		if (theShop.sale < temp.sale)
			theShop = temp;
	}

	printf("The Shop of the Day\n");
	printf("*****************************\n");
	printf("%-20s %7.2f\n\n", theShop.shopName, theShop.sale);
}

void removeAShop(queue_t* q) {
	queue_t Qtemp;
	initializeQ(&Qtemp);

	shops_t temp;
	int stat = 0;

	char name[25];
	printf("Enter a shop name to delete: ");
	scanf(" %[^\n]", name);
	
	while (!isEmptyQ(q))
	{
		temp = remove(q);
		if (strcmp(temp.shopName, name) != 0)
			insert(&Qtemp, temp);
		else
			stat = 1;
	}

	while (!isEmptyQ(&Qtemp))
		insert(q, remove(&Qtemp));

	if (stat = 1)
	{
		printf("\*** The Shop was Deleted\n");
		displayQueue(*q);
	}
	else
		printf("\nThere is no shop\n");
}

int main(void)
{
	FILE* inp;
	inp = fopen("shops.txt", "r");
	if (inp == NULL)
		printf("Error");
	else
	{
		queue_t q;
		initializeQ(&q);

		fillQueue(inp, &q);
		fclose(inp);

		displayQueue(q);
		shopOfTheDay(q);
		removeAShop(&q);
	}
	return 0;
}