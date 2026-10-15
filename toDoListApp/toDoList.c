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
AddTask()
{
	//allocate memory for this new task
	taskToDo* newTask = (taskToDo*)malloc(sizeof(taskToDo))

	//get input of name for the task (max 30 chars plus null)


	//get description of name for the task (max 50 chars plus null)


	//update the tail to point to this new task's memory address


	//free the memory of the


}



 /*
  *	FUNCTION	: PrintTasks
  *	DESCRIPTION	: Prints all tasks in the collection (doubly linked list) of tasks
  *
  *
  *	PARAMETERS	:
  *
  *
  *
  *	RETURNS		: void
*/
-



/*
* Function: FindTaskViaId
* Description: Finds a task in the collection (doubly linked list) of tasks by its ID
*
* Parameters:
*
*
*
* Returns: void
*/
-


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