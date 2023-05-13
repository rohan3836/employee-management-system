#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Declare a structure to store employee data
struct employee {
    char name[50]; int id; int salary; char job_title[50];
};

// Function to validate integer input
int is_integer(char *input) {
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if (!isdigit(input[i])) {return 0;}
    } return 1;
}
char *strget() {
    char buffer[1000];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // remove trailing newline (if present)
    return strdup(buffer);
}
int intget() {
    char input[50];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (is_integer(input)) {
        return atoi(input);
    } else {
        printf("Error: invalid input.\n");
        return -1;
    }
}
int add_employee(struct employee emp[], int *n){
    printf("\nEnter employee name: ");
    char *input = strget();
    printf("Enter employee ID: ");
    int id = intget();
    // Check for ID clashes
    int id_found = 0;
    for (int i = 0; i < *n; i++) {
        if (emp[i].id == id) {
            printf("Error: ID %d already exists for employee %s.\n", id, emp[i].name);
            id_found = 1;
            return 0;
        }
    }
    // If ID found, return to main menu
    if (id_found) {
        return 0;
    }

    printf("Enter employee salary: ");
    int salary = intget();

    printf("Enter employee job title: ");
    char *jt = strget();

    // Add employee to array
    strcpy(emp[*n].name, input); emp[*n].id = id; emp[*n].salary = salary; strcpy(emp[*n].job_title, jt);
    (*n)++;
    return 1;
}
int edit_employee(struct employee emp[], int n){
    printf("Enter employee ID to edit: ");
    int id_to_edit = intget();
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (emp[i].id == id_to_edit) {
            found = 1;
            printf("\nEnter new employee name: ");
            fgets(emp[i].name, sizeof(emp[i].name), stdin);
            emp[i].name[strcspn(emp[i].name, "\n")] = '\0'; // remove newline character
            printf("Enter new employee salary: ");
            emp[i].salary = intget();
            printf("Enter new employee job title: ");
            fgets(emp[i].job_title, sizeof(emp[i].job_title), stdin);
            emp[i].job_title[strcspn(emp[i].job_title, "\n")] = '\0'; // remove newline character
            return id_to_edit;
        }
    }
    if (!found) {
        printf("\nError: employee with ID %d not found.\n\n", id_to_edit);
    }
    return 0;
}
void delete_employee(struct employee emp[], int n) {
    if (n == 0) {
        printf("\nNo employees to delete.\n\n");
        return;
    }
    printf("Enter employee ID to delete: ");
    int id_to_delete = intget();
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (emp[i].id == id_to_delete) {
            found = 1;
            for (int j = i; j < n - 1; j++) {
                emp[j] = emp[j + 1];
            }
            printf("\nEmployee with ID %d deleted.\n\n", id_to_delete);
            break;
        }
    }
    if (!found) {
        printf("\nError: employee with ID %d not found.\n\n", id_to_delete);
    }
}
void save_data(struct employee emp[], int n) {
    FILE *fp;
    fp = fopen("data.csv", "w");
    if (fp == NULL) {
        printf("Error: could not open file for writing.\n"); return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s,%d,%d,%s\n", emp[i].name, emp[i].id, emp[i].salary, emp[i].job_title);
    }
    if (fclose(fp) != 0) {
        printf("Error: could not close file.\n"); return;
    }
    printf("Employee data saved to file.\n");
}

int load_data(struct employee emp[]) {
    FILE *fp;
    int index = 0;
    fp = fopen("data.csv", "r");
    if (fp == NULL) {
        printf("Error: could not open file for reading.\n"); return 0;
    }
    while (!feof(fp)) {
        fscanf(fp, "%[^,],%d,%d,%[^\n]\n", emp[index].name, &emp[index].id, &emp[index].salary, emp[index].job_title);
        index++;
    }
    if (fclose(fp) != 0) {
        printf("Error: could not close file.\n"); return 0;
    }
    printf("Employee data loaded from file.\n");
    return index;
}

// Function to display employee data
void display_data(struct employee emp[], int n) {
    printf("%-40s %-10s %-10s %s\n", "Name", "ID", "Salary", "Job Title");
    for (int i = 0; i < n; i++) {
        printf("%-40s %-10d %-10d %s\n", emp[i].name, emp[i].id, emp[i].salary, emp[i].job_title);
    } printf("\n");
}

// Function to search for employee data by name
void search_employee(struct employee emp[], int n) {
    char search_name[50];
    printf("Enter name to search for: ");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = '\0'; // remove newline character
    // Convert search string to lowercase for case-insensitive search
    char search_lower[50];
    int search_len = strlen(search_name);
    for (int i = 0; i < search_len; i++) {
        search_lower[i] = tolower(search_name[i]);
    }
    search_lower[search_len] = '\0';
    printf("\nResults\n");
    printf("%-40s %-20s %-20s %s\n", "Name", "ID", "Salary", "Job Title");
    for (int i = 0; i < n; i++) {
        // Convert employee name to lowercase for case-insensitive search
        char name_lower[50];
        int name_len = strlen(emp[i].name);
        for (int j = 0; j < name_len; j++) {
            name_lower[j] = tolower(emp[i].name[j]);
        }
        name_lower[name_len] = '\0';
        // Check if name starts with search string (case-insensitive)
        if (strncmp(name_lower, search_lower, search_len) == 0) {
            printf("%-40s %-20d %-20d %s\n", emp[i].name, emp[i].id, emp[i].salary, emp[i].job_title);
        }
    }
}
