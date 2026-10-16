#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "toDoList.h"
//Global variable for the head and tail of the linked list
//taskToDo* head = NULL;
//taskToDo* tail = NULL;

/*
 *	FUNCTION	: CreateTaskNode
 *	DESCRIPTION	: Creates a new task node
 *
 *
 *	PARAMETERS	:
 *
 *
 *
 *	RETURNS		: pointer of a taskToDo struct
 */
taskToDo* CreateTaskNode(int taskId, char* name, char* description)
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
	newTask->taskId = taskId;

	//copy the provided name and description into the fixed-size arrays
	//ensure null termination and avoid buffer overruns
	if (name != NULL) {
		strncpy(newTask->name, name, sizeof(newTask->name) - 1);
		newTask->name[sizeof(newTask->name) - 1] = '\0';
	}
	else {
		newTask->name[0] = '\0';
	}

	if (description != NULL) {
		strncpy(newTask->description, description, sizeof(newTask->description) - 1);
		newTask->description[sizeof(newTask->description) - 1] = '\0';
	}
	else {
		newTask->description[0] = '\0';
	}

	//set the next task (there is none since this is the most recent node)
	newTask->nextTask = NULL;

	//set the previous task to null
	newTask->prevTask = NULL;
	
	return newTask;

	

}

/*
 *	FUNCTION	: AddTaskToTail
 *	DESCRIPTION	: Calls a function to add a new task at the end of the linked list
 *
 *
 *	PARAMETERS	:
 *
 *
 *
 *	RETURNS		: 
 */
void AddTaskToTail(taskToDo** head, taskToDo** tail, int taskId)
{
	//create the new task and store it as the new node
	char taskName[31] = getInputString("Enter task name: ", taskName, sizeof(taskName));
	char taskDesc[51] = getInputString("Enter task description: ", taskDesc, sizeof(taskDesc));

	taskToDo* newTaskNode = CreateTaskNode(taskId, taskName, taskDesc);
	
	//if there is no tail, it is because this is the first node
	if (*tail == NULL)
	{
		*head = newTaskNode;
		*tail = newTaskNode;
	}
	else
	{
		//make this new node's previous task point to the last tail
		newTaskNode->prevTask = *tail;
		newTaskNode->nextTask = NULL;
		//link the previous tail to the new node
		(*tail)->nextTask = newTaskNode;
		//update the tail to point to this new task's memory address
		*tail = newTaskNode;
	}

}

/*
 *	FUNCTION	: 
 *	DESCRIPTION	: a helper function to get a string input from the user
 *		
 *	
 *	PARAMETERS	: 
 *	
 *	
 *	
 *	RETURNS		:
 */
char* getInputString(const char* prompt, char* outputString, size_t bufferSize)
{
	
	printf("%s", prompt);
	
	//if the termnial input is not null (and no error), copy inut to buffer
	if (fgets(outputString, bufferSize, stdin) != NULL) {
		// Remove newline character if there is one
		outputString[strcspn(outputString, "\n")] = 0;
	}
	else {
		// if an error occurred
		printf("Error reading input.\n");

		outputString[0] = '\0'; // empty string
	}
	return outputString;
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