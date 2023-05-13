#include "employee.h"

int main() {
    int choice, n = 0;
    struct employee emp[50];
    char input[50];
    while (1) {
        printf("Employee Management System\n");
        printf("--------------------------\n");
        printf("1. Add employee\n");
        printf("2. Edit employee\n");
        printf("3. Delete employee\n");
        printf("4. Save employee data to file\n");
        printf("5. Load employee data from file\n");
        printf("6. Display employee data\n");
        printf("7. Search for employee data\n"); // added option
        printf("8. Exit\n"); // changed option number
        printf("\nEnter your choice: ");
        choice = intget();
        switch (choice) {
            case 1:
                if(add_employee(emp, &n)){
                    printf("\nEmployee added successfully\n\n");
                }
                break;
            case 2:
                if(edit_employee(emp, n) != 0){
                    printf("\nEmployee successfully edited.\n\n");
                } break;
            case 3:
                delete_employee(emp, n);
                n--;
                break;
            case 4:
                save_data(emp, n); break;
            case 5:
                n = load_data(emp); break;
            case 6:
                display_data(emp, n); break;
            case 7:
                search_employee(emp, n); break;
            case 8:
                printf("Exiting program...\n"); exit(0);
            default:
                printf("Error: invalid choice.\n"); break;
        }
    }
    return 0;
}
