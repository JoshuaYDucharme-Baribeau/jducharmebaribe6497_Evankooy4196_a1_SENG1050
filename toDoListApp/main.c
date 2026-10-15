#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "toDoList.h"

int main() {
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
			AddTask();
			break;
		case 2:
			PrintTasks();
			break;
		case 3:
			FindTaskViaId();
			break;
		case 4:
			FindTaskWithText();
			break;
		case 5:
			DeleteTaskById();
			break;
		case 6:
			printf("Exiting and Freeing Allocated Memory.\n");
			FreeAllTasks();
			printf("Memory freed!\n");
			return 0;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
}