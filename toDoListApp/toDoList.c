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
 *	DESCRIPTION	: Creates a new task node by calling different functions to get valid taskinfo
 *
 *
 *	PARAMETERS	:
 *
 *
 *
 *	RETURNS		:
 */
taskToDo* CreateTaskNode(taskToDo** head, taskToDo** tail, int* minID, int* maxID)
{
	char taskName[nameSize];
	char taskDesc[descriptionSize];
	int taskIdInput;
	int insertionStatus = 0;

	//allocate memory for this new task/node
	taskToDo* newTask = (taskToDo*)malloc(sizeof(taskToDo));

	//validate the memory for the new node struct
	if (newTask == NULL)
	{
		printf("Memory allocation failed :( Emergency exit!");
		printf("Error code: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	//get a valid task id
		//only checks if the id is unique, not where it lands in the list.
		//returns an integer of a validated id
	newTask->taskId = getInputInt(head, "Enter task ID: ", sizeof(taskIdInput));

	//get a valid task name and copy it to the newtask's name
	//strncpy([thing to assign to], [thing to copy from[calls function which returns char*]], [max number of characters to copy])
	strncpy(newTask->name, getInputString("Enter task name: ", sizeof(taskName)), sizeof(taskName) - 1);
	//ensure the last character is a null terminator to prevent buffer overflow
	newTask->name[sizeof(taskName) - 1] = '\0';

	//get a valid task description and copy it to the newtask's description
	strncpy(newTask->description, getInputString("Enter task description: ", sizeof(taskDesc)), sizeof(taskDesc) - 1);
	//ensure the last character is a null terminator to prevent buffer overflow
	newTask->description[sizeof(taskDesc) - 1] = '\0';


	//i need to check if there are existing nodes, and if not the new node needs to become the head and tail

	//if this is the latest ID in the list
	if (newTask->taskId > *maxID) 
	{
		//insert at tail
		insertionStatus = AddTaskToTail(head, tail, newTask);

	}
	//otherwise, find and insert from the head
	else
	{
		//insert at head or middle
		insertionStatus = FindInsertionPoint(head, newTask);
	}


	//determine where to insrt the new node
	switch (insertionStatus)
	{
		case 0 :
			//inserted at tail
			printf("\nTask with ID %d inserted successfully at the end!\n", newTask->taskId);
		case 1:
			//inserted in middle
			printf("\nTask with ID %d inserted successfully!\n", newTask->taskId);
		case 2:
			//inserted at head
			printf("\nTask with ID %d inserted successfully at the top!\n", newTask->taskId);
		default:
			printf("An unexpected error has occurred and insertion failed.\nExiting.");
			printf("Error code: %d\n", errno);
			exit(EXIT_FAILURE);
	}

	//determine if the min or max ID's need to be updated
	if (newTask->taskId < *minID)
	{
		*minID = newTask->taskId;
	}
	if (newTask->taskId > *maxID)
	{
		*maxID = newTask->taskId;
	}
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
int AddTaskToTail(taskToDo** head, taskToDo** tail, taskToDo* newTask)
{
	int insertionMode = 0; // 0 for successful tail insertion or -1 for error
	
	//start at the tail since we are inserting at the end
	taskToDo* current = *tail;

	//if there is no head and no tail, the first node can be inserted and updated as both the head and tail
	if (*head == NULL && *tail == NULL)
	{
		//update the linked list's head and tail pointers to point to the new node
		*head = newTask;
		*tail = newTask;
		
		//update the new node's pointers to NULL since there are no other nodes
		newTask->prevTask = NULL;
		newTask->nextTask = NULL;
		insertionMode = 0; // successful tail insertion
	}
	else
	{
		//update the current node's next pointer to point to the new node
		current->nextTask = newTask;
		// set the new node's previous pointer to the current node and next pointer to NULL since it is the end of the list
		newTask->prevTask = current;
		newTask->nextTask = NULL;
		
		//update the list's tail pointer to point to the new node
		*tail = newTask;
		insertionMode = 0; // successful tail insertion

	}
	return insertionMode;
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
char* getInputString(const char* prompt, size_t bufferSize)
{
	char* outputString = (char*)malloc(bufferSize);
	if (outputString == NULL) {
		printf("Memory allocation failed.");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("%s", prompt);
		if (fgets(outputString, bufferSize, stdin) == NULL) {
			// Read error; prompt again
			outputString[0] = '\0';
			printf("Error reading input. Please try again.\n");
			
			
			continue;
		}
		size_t len = strlen(outputString);
		if (len > 0 && outputString[len - 1] == '\n') {
			// remove trailing newline
			outputString[len - 1] = '\0';
		} else {
			// input was longer than buffer; flush remaining characters
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}

		// If the resulting string is empty, re-prompt
		if (outputString[0] == '\0') {
			printf("The input was invalid. Please try again.\nThe maximum number of characters is allowed is %lu.\n", bufferSize - 1);
			outputString[0] = '\0'; // set the output to an empty string just in case
			continue;
		}

		return outputString;
	}
}


int getInputInt(taskToDo** head, const char* prompt, size_t bufferSize)
{
	int outputInt;
	while (getchar() != '\n'); // Clear the input buffer in case of previous inputs
	while (1) 
	{
		int duplicate_id = 0; // flag for re-entering a new id (0 if no duplicate, 1 if duplicate)
		
		printf("%s", prompt);
		//if the input is a valid integer
		if ((scanf("%d", &outputInt) == 1) && outputInt > 0) {

			// clear the buffer at the beginning of the loop
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF); //clear the buffer fully

			//check if the ID already exists in the linked list
			taskToDo* current = *head;
			while (current != NULL) 
			{
				if (current->taskId == outputInt) {
					//id already exists, loop again to enter a unique ID
					printf("Task ID: %d already exists as \"%s\"\n", current->taskId, current->name);
					printf("Please enter a unique task ID.\n");

					duplicate_id = 1;
					break; //exit the immediate while loop to re-enter a new ID
				}
				//check the next node
				current = current->nextTask;
			}

			//when all nodes have been checked or if a duplicate was found, check the flag to see if we need a new input or to return the unique ID
			if (duplicate_id == 1) 
			{
				//need to reloop to enter a new ID
				continue; //skip the remaining code
			}
			else
			{
				//successfully stored a unique ID, break
				break;
			}
		}
		else {
			printf("Invalid input. Please enter an integer larger than 0.\n");
			while (getchar() != '\n'); // Clear the input buffer       
		}
	}
	//return the unique ID
	return outputInt;
}

//find insertion point for the new node, return 0 for tail, 1 for head or middle
int FindInsertionPoint(taskToDo** head, taskToDo* newTask)
{
	int insertionMode = 0; // 0 for tail, 1 for head or middle
	//iterate through each node
	taskToDo* current = *head;
	while (current != NULL)
	{

		//else if the new id is unique, and is already checked to not be larger than the max or smaller than the min
		if (current->taskId != newTask->taskId)
		{

				if (current->taskId < newTask->taskId && newTask->taskId < current->nextTask->taskId)
			{
					//the new node doesn't belong between the current and next, move on
				}
				else if (current->taskId < newTask->taskId && newTask->taskId > current->nextTask->taskId)
				{
					//this is where we need to insert the new node
					// because the new id is smaller than the next and larger than the current, there will be no duplicates

					//update the new node's next and previous pointers to point to the current and next nodes
					newTask->prevTask = current;
					newTask->nextTask = current->nextTask;
					//change the current node's next pointer to point to the new node
					current->nextTask = newTask;
					//change the next node's previous pointer to point to the new node
					//reaching through the currrent node's "next" pointer to update its previous pointer to the new node
					current->nextTask->prevTask = newTask;

					//change the insertion mode to 1
					insertionMode = 1;
					if (newTask->prevTask == NULL)
					{
						//task was inserted at the head 
						// update the linked list's head pointer to point to the new node 
						*head = newTask;

						// and change the insertion mode to 2 since we inserted at the head
						insertionMode = 2;
					}
					//thus we can break the loop early since the updates are complete
					break;
			}
			
		}
		//SHOULD NOT OCCUR, id was already verified as unique prior to function call
		else if (current->taskId == newTask->taskId)
		{
			insertionMode = -1; //error code
			break; //exit the immediate while loop to re-enter a new ID
		}
	}
	return insertionMode;
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
void PrintTasks(taskToDo** head) {
	if (head == NULL) {
		printf("No tasks to display.\n");
		return;
	}
	taskToDo* current = *head;
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
void FindTaskViaId(taskToDo** head) {
	int searchID;
	printf("Enter the ID of the task to find: ");
	if (scanf("%d", &searchID) != 1) {
		printf("Invalid input.\n");
		while (getchar() != '\n'); // Clear the input buffer
		return;
	}
	while (getchar() != '\n');
	taskToDo* current = *head;
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
void FindTaskWithText(taskToDo** head) {
	char searchText[51];
	while (getchar() != '\n'); // Clear the input buffer in case of previous inputs
	
	printf("Enter the text to search for: ");
	fgets(searchText, sizeof(searchText), stdin);
	searchText[strcspn(searchText, "\n")] = 0; // Remove newline character
	taskToDo* current = *head;
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
void DeleteTaskById(taskToDo** head, taskToDo** tail, int* minID, int* maxID) {
	int deleteID;
	printf("Enter the ID of the task to delete: ");
	if (scanf("%d", &deleteID) != 1) {
		printf("Invalid input.\n");
		while (getchar() != '\n'); // Clear the input buffer
		return;
	}
	while (getchar() != '\n');
	taskToDo* current = *head;
	while (current != NULL) {
		if (current->taskId == deleteID) {
			if (current->prevTask != NULL) {
				current->prevTask->nextTask = current->nextTask;
			}
			else {
				*head = current->nextTask; // Update head if first task is deleted
				*maxID = 0; // set maxID to 0 if the last task is deleted
			}
			if (current->nextTask != NULL) {
				current->nextTask->prevTask = current->prevTask;
			}
			else {
				*tail = current->prevTask; // Update tail if last task is deleted
				*minID = 0; // set minID to 0 if the last task is deleted
			}
			free(current);
			printf("Task with ID %d deleted successfully.\n", deleteID);
			return;
		}
		current = current->nextTask;
	}
	printf("Task not found.\n");
}
void FreeAllTasks(taskToDo** head, taskToDo** tail, int* minID, int* maxID) {
	taskToDo* current = *head;
	while (current != NULL) {
		taskToDo* nextNode = current->nextTask;
		free(current);
		current = nextNode;
	}
	*head = NULL;
	*tail = NULL;
	free(minID);
	free(maxID);
}