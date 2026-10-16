#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "toDoList.h"

int main() {
//variable for the head and tail of the linked list
	taskToDo* head = NULL;
	taskToDo* tail = NULL;
	int minID = 0;
	int maxID = 0;

	int choice;
	while (1) {
		printf("To-Do List Application\n");
		printf("1. Add Task\n");
		printf("2. Print Tasks\n");
		printf("3. Find Task by ID\n");
		printf("4. Find Task by Text\n");
		printf("5. Delete Task by ID\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		
		if (scanf("%d", &choice) != 1) {
			printf("Invalid input. Please enter a number.\n");
			while (getchar() != '\n'); // Clear the input buffer
			continue;
		}
		switch (choice) {
		case 1:
			CreateTaskNode(&head, &tail, &minID, &maxID);
			break;
		case 2:
			PrintTasks(&head);
			break;
		case 3:
			FindTaskViaId(&head);
			break;
		case 4:
			FindTaskWithText(&head);
			break;
		case 5:
			DeleteTaskById(&head, &tail, &minID, &maxID);
			break;
		case 6:
			printf("Exiting and Freeing Allocated Memory.\n");
			FreeAllTasks(&head, &tail, &minID, &maxID);
			printf("Memory freed!\n");
			return 0;
		default:
			printf("Invalid choice. Please try again using the listed options.\n");
		}
	}
}