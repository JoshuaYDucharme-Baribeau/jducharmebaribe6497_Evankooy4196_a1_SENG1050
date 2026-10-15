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