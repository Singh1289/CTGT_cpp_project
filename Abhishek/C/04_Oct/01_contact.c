/*
     Write a menu-driven program with following features: 
     (a) Store Contact numbers of people, 
     (b) Search for the Contact numbers using their names, 
     (c) Search for the Contact numbers using their number, 
     (d) Delete a Contact number
     (e) Update a Contact number
*/
#include <stdio.h>
#include <string.h>

// sturcture for student details
struct student {
    char name[50];
    long number;
};

// function declaration
void registers();
void addstudent(struct student[], int *);
void displayall(struct student[], int);
void display(struct student[], int);
int search_student_by_name(struct student[], int);
int search_student_by_number(struct student[], int);
void delete_contact_no(struct student[], int *);
void update_contact_no(struct student[], int *);

int main() {
    registers();
    return 0;
}

// showing menu 
void registers() {
    struct student stu[50];
    int Snum = 0;
    int choice;

    do {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n|         ~ W E L C O M E ~         |");
        printf("\n|1 : Add a student                  |");
        printf("\n|2 : Display all records            |");
        printf("\n|3 : Search student by name         |");
        printf("\n|4 : Search student by number       |");  
        printf("\n|5 : Update contact number          |");
        printf("\n|6 : Delete contact number          |");
        printf("\n|7 : Exit                           |");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\n What would you like to do: ");
        scanf("%d", &choice);
        getchar(); // to avoid infinite loop
        switch (choice) {
            case 1:
                addstudent(stu, &Snum);
                break;
            case 2:
                displayall(stu, Snum);
                break;
            case 3:
                display(stu, search_student_by_name(stu, Snum));
                break;
            case 4:
                display(stu, search_student_by_number(stu, Snum));
                break;
            case 5:
                update_contact_no(stu, &Snum);
                break;
            case 6:
                delete_contact_no(stu, &Snum);
                break;
            case 7:
                printf("\n~~~~ T H A N K  Y O U  ~~~~~\n");
                break;
            default:
                printf("\n~~~~  Please choose another option  ~~~~\n");
                break;
        }
    } while (choice != 7);
}

// for adding student in the list
void addstudent(struct student stu[], int *count) {
    if (*count >= 50) {
        printf("Sorry, maximum capacity reached.\n");
        return;
    }

    printf("\nEnter name of the student: ");
    scanf(" %49[^\n]", stu[*count].name);  

    printf("Enter contact number: ");
    scanf("%ld", &stu[*count].number);

    (*count)++;
    printf("\nStudent added successfully!\n");
}

// display all records of students
void displayall(struct student stu[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nStudents:\n");
    for (int i = 0; i < count; i++) {
        printf("\nName: %s", stu[i].name);
        printf("\nNumber: %ld\n", stu[i].number);
    }
}

// show perticular student record
void display(struct student stu[], int index) {
    if (index == -1) {
        printf("\nSorry, there is no student found.\n");
        return;
    }

    printf("\nName: %s", stu[index].name);
    printf("\nNumber: %ld\n", stu[index].number);
}

// finding student by name
int search_student_by_name(struct student stu[], int count) {
    char name[50];
    printf("\nEnter name: ");
    scanf(" %49[^\n]", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(stu[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// finding student by number
int search_student_by_number(struct student stu[], int count) {
    long number;
    printf("\nEnter number: ");
    scanf("%ld", &number);

    for (int i = 0; i < count; i++) {
        if (stu[i].number == number) {
            return i;
        }
    }
    return -1;
}

// delete contact no of a student
void delete_contact_no(struct student stu[], int *count) {
    int index = search_student_by_name(stu, *count);
    if (index == -1) {
        printf("\nNo student found by that name.\n");
        return;
    }

    for (int i = index; i < (*count) - 1; i++) {
        stu[i] = stu[i + 1]; 
    }
    (*count)--; 
    printf("\nContact deleted successfully.\n");
}

// to update details of a student 
void update_contact_no(struct student stu[], int *count) {
    int index = search_student_by_name(stu, *count);
    if (index == -1) {
        printf("\nNo student found by that name.\n");
        return;
    }

    long new_number;
    printf("\nEnter new number: ");
    scanf("%ld", &new_number);
    stu[index].number = new_number;
    printf("\nNumber updated successfully.\n");
}
