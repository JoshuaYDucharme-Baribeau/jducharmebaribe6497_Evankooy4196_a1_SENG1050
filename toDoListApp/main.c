/*
 * FILE             : main.c
 * PROJECT          : Assignment 1 Data Structures 
 * PROGRAMMERS      : Joshua Ducharme-Baribeau & Erik vanKooy
 * FIRST VERSION    : October 15 2026
 * DESCRIPTION      : C Source file for "main.c" containing main menu logic.
 *                    Main entry for the application
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "toDoList.h"

int main() {
	//variable for the head and tail of the linked list, as well as the minimum and maximum id ints in the list (empty if they are 0)
	taskToDo* head = NULL;
	taskToDo* tail = NULL;
	int minID = 0;
	int maxID = 0;

	int choice;
	while (1) {
		printf("\n\nTo-Do List Application\n");
		printf("1. Add Task\n");
		printf("2. Print Tasks\n");
		printf("3. Find Task by ID\n");
		printf("4. Find Task by Text\n");
		printf("5. Delete Task by ID\n");
		printf("6. Exit\n");
		printf("\nEnter your choice: ");
		
		if (scanf("%d", &choice) != 1) {
			printf("\nInvalid input. Please enter a number.\n");
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
			printf("\n\nExiting and Freeing Allocated Memory.\n");
			FreeAllTasks(&head, &tail, &minID, &maxID);
			printf("Memory freed!\n");
			return 0;
		default:
			printf("\n\nInvalid choice. Please try again using the listed options.\n");
		}
	}
}