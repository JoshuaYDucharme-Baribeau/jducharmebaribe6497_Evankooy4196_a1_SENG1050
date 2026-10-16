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
		printf("Task ID: %d\n", current->id);
		printf("Task: %s\n", current->task);
		printf("Priority: %d\n", current->priority);
		printf("Due Date: %s\n", current->dueDate);
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
		if (current->id == searchID) {
			printf("Task ID: %d\n", current->id);
			printf("Task: %s\n", current->task);
			printf("Priority: %d\n", current->priority);
			printf("Due Date: %s\n", current->dueDate);
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