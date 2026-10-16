#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "toDoList.h"
//Global variable for the head and tail of the linked list
taskToDo* head = NULL;
taskToDo* tail = NULL;

/*
 *	FUNCTION	: AddTask
 *	DESCRIPTION	: Creates and adds a task to the collection (doubly linked list) of tasks
 *
 *
 *	PARAMETERS	:
 *
 *
 *
 *	RETURNS		: -1 if failure, 0 if success
 */




 /*
  *	FUNCTION	: PrintTasks
  *	DESCRIPTION	: Prints all tasks in the collection (doubly linked list) of tasks
  *
  *
  *	PARAMETERS	: None
  *
  *
  *
  *	RETURNS		: void
*/
void PrintTasks() {
	if (head == NULL) {
		printf("No tasks to display.\n");
		return;
}
	taskToDo* current = head;
	while (current != NULL) {
		printf("Task ID: %d\n", current->taskId);
		printf("Task: %s\n", current->name);
		printf("Description: %s\n", current->description);
		printf("\n");
		current = current->nextTask;
	}
}



/*
* Function: FindTaskViaId
* Description: Finds a task in the collection (doubly linked list) of tasks by its ID
*
* Parameters: None
*
*
*
* Returns: void
*/
void FindTaskViaId() {
	int searchID;
	printf("Enter the ID of the task to find: ");
	if (scanf("%d", &searchID) != 1) {
		printf("Invalid input.\n");
		while (getchar() != '\n'); // Clear the input buffer
		return;
	}
	while (getchar() != '\n');
	taskToDo* current = head;
	while (current != NULL) {
		if (current->taskId == searchID) {
			printf("Task ID: %d\n", current->taskId);
			printf("Task: %s\n", current->name);
			printf("Description: %s\n", current->description);
			return;
		}
		current = current->nextTask;
	}
	printf("Task not found.\n");
}


/*
* Function: FindTaskWithText
* Description: Finds a task in the collection (doubly linked list) of tasks by its text
*
* Parameters:
*
*
*
* Returns: void
*/
void FindTaskWithText() {
	char searchText[51];
	printf("Enter the text to search for: ");
	fgets(searchText, sizeof(searchText), stdin);
	searchText[strcspn(searchText, "\n")] = 0; // Remove newline character
	taskToDo* current = head;
	int found = 0;
	while (current != NULL) {
		if (strstr(current->name, searchText) != NULL || strstr(current->description, searchText) != NULL) {
			printf("Task ID: %d\n", current->taskId);
			printf("Task: %s\n", current->name);
			printf("Description: %s\n", current->description);
			printf("\n");
			found = 1;
		}
		current = current->nextTask;
	}
	if (!found) {
		printf("No tasks found with the given text.\n");
	}
}
/*
* Function: DeleteTaskById
* Description: Deletes a task in the collection (doubly linked list) of tasks by its ID
*
* Parameters:
*
*
*
* Returns: void
*/
void DeleteTaskById() {
	int deleteID;
	printf("Enter the ID of the task to delete: ");
	if (scanf("%d", &deleteID) != 1) {
		printf("Invalid input.\n");
		while (getchar() != '\n'); // Clear the input buffer
		return;
	}
	while (getchar() != '\n');
	taskToDo* current = head;
	while (current != NULL) {
		if (current->taskId == deleteID) {
			if (current->prevTask != NULL) {
				current->prevTask->nextTask = current->nextTask;
			}
			else {
				head = current->nextTask; // Update head if first task is deleted
			}
			if (current->nextTask != NULL) {
				current->nextTask->prevTask = current->prevTask;
			}
			else {
				tail = current->prevTask; // Update tail if last task is deleted
			}
			free(current);
			printf("Task with ID %d deleted successfully.\n", deleteID);
			return;
		}
		current = current->nextTask;
	}
	printf("Task not found.\n");
}
void FreeAllTasks() {
	taskToDo* current = head;
	while (current != NULL) {
		taskToDo* nextNode = current->nextTask;
		free(current);
		current = nextNode;
	}
	head = NULL;
	tail = NULL;
}