#ifndef TODO_LIST_H
#define TODO_LIST_H
// Defining so that we dont run errors
typedef struct taskToDo {
	int taskId;
	char name[31];
	char description[51];
	struct taskToDo* nextTask;
	struct taskToDo* prevTask;
} taskToDo;

#define descriptionSize 51
#define nameSize 31

// Function prototypes, define here so program doesnt get mad --- simple make the actual function later
void PrintTasks(taskToDo** head);

void FindTaskViaId(taskToDo** head);
void FindTaskWithText(taskToDo** head);


void CreateTaskNode(taskToDo** head, taskToDo** tail, int* minID, int* maxID);
int FindInsertionPoint(taskToDo** head, taskToDo* newTask);
int AddTaskToTail(taskToDo** head, taskToDo** tail, taskToDo* newTask);

int getInputInt(taskToDo** head, const char* prompt, size_t bufferSize);
char* getInputString(const char* prompt, size_t bufferSize);


void DeleteTaskById(taskToDo** head, taskToDo** tail, int* minID, int* maxID);


void FreeAllTasks(taskToDo** head, taskToDo** tail, int* minID, int* maxID);



#endif
