#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toDoList.h"


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
void CreateTaskNode(taskToDo** head, taskToDo** tail, int* minID, int* maxID)
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
		printf("\n\nMemory allocation failed :( Emergency exit!");
		printf("Error code: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	//get a valid task id
		//only checks if the id is unique, not where it lands in the list.
		//returns an integer of a validated id
	newTask->taskId = getInputInt(head, "\nEnter new task's ID (positive int only): ", sizeof(taskIdInput));

	//get a valid task name and copy it to the newtask's name
	//strncpy([thing to assign to], [thing to copy from[calls function which returns char*]], [max number of characters to copy])
	strncpy(newTask->name, getInputString("\nEnter new task's name (max 30 chars): ", sizeof(taskName)), sizeof(taskName) - 1);
	//ensure the last character is a null terminator to prevent buffer overflow
	newTask->name[sizeof(taskName) - 1] = '\0';

	//get a valid task description and copy it to the newtask's description
	strncpy(newTask->description, getInputString("\nEnter new task's description (max 30 chars): ", sizeof(taskDesc)), sizeof(taskDesc) - 1);
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

	
	//determine where to insert the new node
	switch (insertionStatus)
	{
		case 0 :
			//inserted at tail
			printf("\nTask with ID \"%d\" inserted successfully at the end!\n", newTask->taskId);
			break;
		case 1:
			//inserted in middle
			printf("\nTask with ID \"%d\" inserted successfully!\n", newTask->taskId);
			break;
		case 2:
			//inserted at head
			printf("\nTask with ID \"%d\" inserted successfully at the top!\n", newTask->taskId);
			break;
		default:
			printf("\n\nAn unexpected error has occurred and insertion failed.\nExiting.");
			printf("Error code: %d\n", errno);
			exit(EXIT_FAILURE);
			break;
	}

	//determine if the min or max ID's need to be updated
	if (newTask->taskId < *minID || newTask->taskId == 0)
	{
		*minID = newTask->taskId;
	}
	if (newTask->taskId > *maxID)
	{
		*maxID = newTask->taskId;
	}
	return;
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
		printf("\n\nMemory allocation failed. Exiting\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("%s", prompt);
		if (fgets(outputString, bufferSize, stdin) == NULL) {
			// Read error; prompt again
			outputString[0] = '\0';
			printf("\n\nError reading input. Please try again.\n");
			
			
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
			printf("\n\nThe input was invalid. Please try again.\nThe maximum number of characters is allowed is %lu.\n", bufferSize - 1);
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
					printf("\n\nTask ID: %d already exists with the name \"%s\"\n", current->taskId, current->name);
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
			printf("\n\nInvalid input. Please enter an integer larger than 0.\n");
			while (getchar() != '\n'); // Clear the input buffer       
		}
	}
	//return the unique ID
	return outputInt;
}

//find insertion point for the new node, return 0 for tail, 1 for head or middle
int FindInsertionPoint(taskToDo** head, taskToDo* newTask)
{
	int insertionMode = 0; // 0 for tail, 1 for middle, 2 for head

	// check if the memory location for the head was null
	if (head == NULL)
	{
		//return with an error -1 since the head pointer was passed incorrectly
		return -1;
	}
	//at this point, the memory location for the head is valid
	//if the head is null, 
	if (*head == NULL) {
		//this task is the first node in the list, make it the head and tail
        newTask->prevTask = NULL;
        newTask->nextTask = NULL;
        *head = newTask;
        return 0;
    }

	//since there is already a node in the list, iterate through the list starting at the head
	taskToDo* current = *head;
	//before walking through, check if the new task ID is smaller than the current listhead's id
	if (newTask->taskId < current->taskId)
	{
		//insert new task at the head
		newTask->prevTask = NULL;
		newTask->nextTask = current;
		current->prevTask = newTask;
		*head = newTask;
		return 2; // return insertion mode as "at head"
	}

	// walk the list until we find insertion point (stop at last node or where next's id is >= new id)
	while (current->nextTask != NULL && current->nextTask->taskId < newTask->taskId)
	{
		current = current->nextTask;
	}
	while (current != NULL)
	{
		if (current->taskId < newTask->taskId)
		{
			if (current->nextTask->taskId > newTask->taskId)
			{
				// insertion point is between current and next
				newTask->prevTask = current;
				newTask->nextTask = current->nextTask;
				current->nextTask = newTask;
				//if insertion was not at the tail (should always happen, as tail insert is checked prior to call)
				if (newTask->nextTask != NULL)
				{
					//update the next node's previous task to be the new task
					newTask->nextTask->prevTask = newTask;
					insertionMode = 1; //inserted somewhere in the middle
					break; //exit loop to return
				}
			}
		}
		//we haven't reached the insertion point, move on
		current = current->nextTask;
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
	if (*head == NULL) {
		printf("\nNo tasks to display.\n");
		return;
	}
	taskToDo* current = *head;
	printf("\n");
	while (current != NULL) {
		printf("\tTask ID\t\t: %d\n", current->taskId);
		printf("\tTask\t\t: %s\n", current->name);
		printf("\tDescription\t: %s\n", current->description);
		printf("\n");
		current = current->nextTask;
	}
	return;
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
	if (*head == NULL) {
		printf("\n\nThere are no tasks to find! Add one first.\n");
		return;
	}

	printf("Enter the ID of the task to find: ");
	if (scanf("%d", &searchID) != 1) {
		printf("\n\nInvalid input.\n");
		while (getchar() != '\n'); // Clear the input buffer
		return;
	}
	while (getchar() != '\n');
	taskToDo* current = *head;
	while (current != NULL) {
		if (current->taskId == searchID) {
			printf("\n\nTask Found!\n");
			printf("\tTask ID\t\t: %d\n", current->taskId);
			printf("\tTask\t\t: %s\n", current->name);
			printf("\tDescription\t: %s\n", current->description);
			return;
		}
		current = current->nextTask;
	}
	printf("\n\nTask not found.\n");
	return;
}


/*
* Function: FindTaskWithText
* Description: Finds a task in the collection (doubly linked list) of tasks by the search text
*				The search IS CASE SENSITIVE
*
* Parameters:
*
*
*
* Returns: void
*/
void FindTaskWithText(taskToDo** head) {
	while (getchar() != '\n'); // Clear the input buffer in case of previous inputs
	char searchText[51];
	if (*head == NULL) {
		printf("\n\nThere are no tasks to find! Add one first.\n");
		return;
	}
		
	printf("\nEnter the text to search for: ");
	fgets(searchText, sizeof(searchText), stdin);
	searchText[strcspn(searchText, "\n")] = 0; // Remove newline character
	
	if (searchText[0] == '\0') 
	{
		printf("\nThe search term you entered was empty. Returning to menu.\n");
		return;
	}
	taskToDo* current = *head;
	int found = 0;
	while (current != NULL) {
		if (strstr(current->name, searchText) != NULL || strstr(current->description, searchText) != NULL) {
			
			printf("\n\nTask(s) found matching \"%s\"!\n", searchText);
			printf("\tTask ID\t\t: %d\n", current->taskId);
			printf("\tTask\t\t: %s\n", current->name);
			printf("\tDescription\t: %s\n", current->description);
			printf("\n");
			found = 1;
		}
		current = current->nextTask;
	}
	if (!found) {
		printf("\n\nNo tasks found with text matching\"%s\".\n", searchText);
	}
	return;
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
	if (*minID == 0 && *maxID == 0) {
		printf("\n\nThere are no tasks to delete! Add one first.\n");
		return;
	}
	printf("\nEnter the ID of the task to delete: ");
	if (scanf("%d", &deleteID) != 1) {
		printf("\n\nInvalid input.\n");
		while (getchar() != '\n'); // Clear the input buffer
		return;
	}
	while (getchar() != '\n');
	taskToDo* current = *head;
	while (current != NULL) {
		//if this is the node to delete
		if (current->taskId == deleteID) {
			
			//if this is NOT the head
			if (current->prevTask != NULL) {
				//update the previous node's next task to be the one after the one we are deleting
				current->prevTask->nextTask = current->nextTask;
			}
			//if it is the head that we are deleting,
			else {
				
				*head = current->nextTask; // Update head of the list, will be NULL if this there was only one node, since the nextTask would have been NULL
				//if this wasn't the only node in the list
				if (*head != NULL)
				{
					//update the new list head's previous task to point to NULL
					(*head)->prevTask = NULL;
					//update the minimum ID in the list to be this new head's id
					*minID = (*head)->taskId;
				}
				//if there was only one node in the list
				else
				{
					//reset the min and max ID's to 0
					*minID = 0;
					*maxID = 0;
				}

			}

			//if this is NOT the tail
			if (current->nextTask != NULL) {
				//update the next node's previous task to be the one before the one we are deleting
				current->nextTask->prevTask = current->prevTask;
			}
			//if it is the tail being deleted
			else {
				*tail = current->prevTask; // Update tail of the list, will be NULL if there is no previous node since prevTask would point to NULL

				//if this wasn't the only node in the list
				if (*tail != NULL)
				{
					//update the new list tail's next task to point to NULL
					(*tail)->nextTask = NULL;
					//update the maximum ID in the list to be this new tail's id
					*maxID = (*tail)->taskId;
				}
				//if there was only one node in the list
				else
				{
					//reset the min and max ID's to 0
					*minID = 0;
					*maxID = 0;
				}
			}
			free(current);
			printf("Task with ID %d deleted successfully.\n", deleteID);
			return;
		}
		current = current->nextTask;
	}
	printf("\n\nTask with ID \"%d\" not found.\n", deleteID);
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