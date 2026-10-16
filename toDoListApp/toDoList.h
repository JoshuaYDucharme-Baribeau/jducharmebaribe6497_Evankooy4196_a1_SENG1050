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
void PrintTasks(taskToDo** head);

void FindTaskViaId(taskToDo** head);
void FindTaskWithText(taskToDo** head);


taskToDo* CreateTaskNode(int taskId, char* name, char* description);
void AddTaskToTail(taskToDo** head, taskToDo** tail);


void DeleteTaskById(taskToDo** head, taskToDo** tail);


void FreeAllTasks(taskToDo** head, taskToDo** tail);


char* getInputString(const char* prompt, char* outputString, size_t bufferSize);
int getInputInt(taskToDo** head, const char* prompt, int* outputInt, size_t bufferSize);

#endif
