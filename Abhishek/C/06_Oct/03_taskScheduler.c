/*
Program to implement a task scheduler where tasks are represented by a description and a deadline. The program should allow adding tasks, removing tasks, modifying tasks, sorting tasks, filtering tasks, and listing tasks by deadline. Use dynamic memory to manage the list of tasks.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 1048

typedef struct Task {
    char description[1000];
    char deadline[100];
} Task;

// Function to validate date format
int validateDate(const char *date) {
    if (strlen(date) != 10)
        return 0;
    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && date[i] != '-')
            return 0;
        if (i != 4 && i != 7 && !isdigit(date[i]))
            return 0;
    }
    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);
    return (year >= 1900 && month >= 1 && month <= 12 && day >= 1 && day <= 31);
}

// Function to create a new task
Task *createTask() {
    Task *newTask = (Task *)malloc(sizeof(Task));
    printf("Enter description: ");
    fgets(newTask->description, sizeof(newTask->description), stdin);
    newTask->description[strcspn(newTask->description, "\n")] = '\0';

    while (1) {
        printf("Enter deadline (YYYY-MM-DD): ");
        fgets(newTask->deadline, sizeof(newTask->deadline), stdin);
        newTask->deadline[strcspn(newTask->deadline, "\n")] = '\0';
        if (validateDate(newTask->deadline)) break;
        printf("Invalid date format. Please enter in YYYY-MM-DD.\n");
    }
    return newTask;
}

// Function to add a task to the list
void addTask(Task **tasks, int *count) {
    Task *newTask = createTask();
    *tasks = realloc(*tasks, (*count + 1) * sizeof(Task));
    (*tasks)[(*count)++] = *newTask;
    free(newTask);
}

// Function to remove a task from the list
void removeTask(Task **tasks, int *count, int index) {
    if (index >= 0 && index < *count) {
        for (int i = index; i < *count - 1; i++)
            (*tasks)[i] = (*tasks)[i + 1];
        (*count)--;
        *tasks = realloc(*tasks, (*count) * sizeof(Task));
    }
}

// Function to modify a task's description or deadline
void modifyTask(Task **tasks, int index, int *count) {
    if (index >= 0 && index < *count) {
        printf("Enter new description: ");
        fgets((*tasks)[index].description, sizeof((*tasks)[index].description), stdin);
        (*tasks)[index].description[strcspn((*tasks)[index].description, "\n")] = '\0';

        while (1) {
            printf("Enter new deadline (YYYY-MM-DD): ");
            fgets((*tasks)[index].deadline, sizeof((*tasks)[index].deadline), stdin);
            (*tasks)[index].deadline[strcspn((*tasks)[index].deadline, "\n")] = '\0';
            if (validateDate((*tasks)[index].deadline)) break;
            printf("Invalid date format. Please enter in YYYY-MM-DD.\n");
        }
    }
}

// Function to sort the tasks by deadline
void sortTasks(Task *tasks, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(tasks[j].deadline, tasks[j + 1].deadline) > 0) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

// Function to filter tasks by a specific deadline
void filterTasks(Task *tasks, int count, const char *deadline) {
    printf("Tasks with deadline '%s':\n", deadline);
    for (int i = 0; i < count; i++) {
        if (strcmp(tasks[i].deadline, deadline) == 0) {
            printf("%s - Deadline: %s\n", tasks[i].description, tasks[i].deadline);
        }
    }
}

// Function to search for a task by description
void searchTask(Task *tasks, int count, const char *description) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(tasks[i].description, description) == 0) {
            printf("Found task: '%s', Deadline: %s\n", tasks[i].description, tasks[i].deadline);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No tasks found with description '%s'\n", description);
    }
}

// Function to list all tasks
void listTasks(Task *tasks, int count) {
    printf("All tasks:\n");
    for (int i = 0; i < count; i++) {
        printf("%s - Deadline: %s\n", tasks[i].description, tasks[i].deadline);
    }
}

// Free the list of tasks
void freeTasks(Task *tasks) {
    free(tasks);
}

int main() {
    Task *tasks = NULL;
    int count = 0;
    int choice;

    do {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n|     ~ Task Manager ~    |");
        printf("\n|1: Add Task              |");
        printf("\n|2: Remove Task           |");
        printf("\n|3: Modify Task           |");
        printf("\n|4: Sort Tasks            |");
        printf("\n|5: Filter Tasks          |");
        printf("\n|6: Search Task           |");
        printf("\n|7: List All Tasks        |");
        printf("\n|8: Exit                  |");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nChoose an option: ");
        scanf("%d", &choice);
        getchar(); 

        int index;
        char buffer[1000];

        switch (choice) {
            case 1:
                addTask(&tasks, &count);
                break;
            case 2:
                printf("Enter task index to remove: ");
                scanf("%d", &index);
                getchar();
                removeTask(&tasks, &count, index);
                break;
            case 3:
                printf("Enter task index to modify: ");
                scanf("%d", &index);
                getchar();
                modifyTask(&tasks, index ,&count);
                break;
            case 4:
                sortTasks(tasks, count);
                printf("Tasks sorted by deadline.\n");
                break;
            case 5:
                printf("Enter deadline (YYYY-MM-DD) to filter: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                filterTasks(tasks, count, buffer);
                break;
            case 6:
                printf("Enter description to search: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                searchTask(tasks, count, buffer);
                break;
            case 7:
                listTasks(tasks, count);
                break;
            case 8:
                printf("\n~~~~ T H A N K  Y O U ~~~~~\n");
                freeTasks(tasks);
                break;
            default:
                printf("\n~~~~ Please choose a valid option ~~~~\n");
        }
    } while (choice != 8);

    return 0;
}
