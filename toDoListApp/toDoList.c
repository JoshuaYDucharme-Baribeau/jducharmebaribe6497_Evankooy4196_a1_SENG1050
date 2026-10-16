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
 *	RETURNS		: pointer of a taskToDo struct
 */
taskToDo* AddTask()
{
	//allocate memory for this new task
	taskToDo* newTask = (taskToDo*)malloc(sizeof(taskToDo));

	//validate the memory
	if (newTask == NULL)
	{
		printf("Memory allocation failed.");
		exit(EXIT_FAILURE);
	}

	//assign the id to the task
	//newTask->taskId = xyz; 
	char 
	//get input of name for the task (max 30 chars plus null)
	newTask->name = "hardcoded_name";

	//get description of name for the task (max 50 chars plus null)
	newTask->description = "hardcoded_description";

	//set the next task (there is none since this is the most recent node)
	newTask->nextTask = NULL;

	//set the previous task to null
	newTask->prevTask = NULL;
	
	return newTask;

	

}

/*
 *	FUNCTION	: AddTask
 *	DESCRIPTION	: Creates and adds a task to the collection (doubly linked list) of tasks
 *
 *
 *	PARAMETERS	:
 *
 *
 *
 *	RETURNS		: pointer of a taskToDo struct
 */
void AddNodeToEnd(taskToDo** head, taskToDo** tail, int taskId, char* name, char* description)
{
	//create the new task and store it as the new node
	taskToDo* newTaskNode = AddTask(taskId, name, description);
	
	//if there is no tail, it is because this is the first node
	if (*tail == NULL)
	{
		*head = newTaskNode;
		*tail = newTaskNode;
	}

	//make this new node's previous task point to the last tail
	newTaskNode->prevTask = *tail;
	//update the tail to point to this new task's memory address
	(*tail)->nextTask = newTaskNode;

}




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