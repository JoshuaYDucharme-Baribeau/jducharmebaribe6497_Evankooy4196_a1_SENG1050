#ifndef TODO_LIST_H
#define TODO_LIST_H
// Defiing so that we dont run errors
typedef struct taskToDo {
	int taskId;
	char name[31];
	char description[51];
	struct taskToDo* nextTask;
	struct taskToDo* prevTask;
} taskToDo;
// Function prototypes, define here so program doesnt get mad --- simple make the actual function later
int AddTask();
void PrintTasks();
void FindTaskViaId();
void FindTaskWithText();
void DeleteTaskById();
void FreeAllTasks();
#endif
