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
-



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
-

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