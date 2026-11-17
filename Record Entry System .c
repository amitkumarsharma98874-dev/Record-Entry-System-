/***************************************************
Application: Record Entry System 
Compatible with: VS Code (GCC / Clang / MinGW)
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void dataentry(void);
void selectAdminOption(void);
void getData(int option);
void clearScreen();
int showAdminMenu;
long int size;

struct employee {
    char firstname[30];
    char lastname[30];
    char password[30];
    int empid;
    int loginhour;
    int loginmin;
    int loginsec;
    int logouthour;
    int logoutmin;
    int logoutsec;
    int yr;
    int mon;
    int day;
};

int main(void)
{
    char choice[10];
    int cancelOption = 0;

    while (cancelOption == 0)
    {
        clearScreen();
        printf("=========================================\n");
        printf("   DAILY EMPLOYEE TIME RECORDING SYSTEM  \n");
        printf("=========================================\n");
        printf(" Please Select an Action:\n");
        printf(" [1] Daily Time Record (Login / Logout)\n");
        printf(" [2] Data Entry (Admin Interface)\n");
        printf(" [3] Close Application\n");
        printf("=========================================\n");
        printf("Enter your choice (1-3): ");
        
        if (scanf("%s", choice) != 1) continue;
        while (getchar() != '\n');

        if (strcmp(choice, "1") == 0)
        {
            clearScreen();
            printf("=========================================\n");
            printf("       DAILY EMPLOYEE TIME RECORD        \n");
            printf("=========================================\n");
            printf(" [1] Employee Log In\n");
            printf(" [2] Employee Log Out\n");
            printf(" [3] Return to Main Menu\n");
            printf("Enter option (1-3): ");
            
            char subChoice[10];
            scanf("%s", subChoice);
            while (getchar() != '\n');

            if (strcmp(subChoice, "1") == 0)
                getData(5);
            else if (strcmp(subChoice, "2") == 0)
                getData(6);
        }
        else if (strcmp(choice, "2") == 0)
        {
            dataentry();
        }
        else if (strcmp(choice, "3") == 0)
        {
            cancelOption = 1;
        }
        else
        {
            printf("\nInvalid Option! Please choose either 1, 2 or 3.\n");
            printf("Press Enter to continue...");
            getchar();
        }
    }

    clearScreen();
    printf("The Application will Close Now. Thanks!\n");
    return 0;
}

// Cross-platform clear screen
void clearScreen()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

// Data Entry & Admin Interface Logic
void dataentry(void)
{
    char adminName[20], passwd[20];
    int validUserNameOption = 0, validUserPwdOption = 0;

    while (validUserPwdOption == 0)
    {
        while (validUserNameOption == 0)
        {
            clearScreen();
            printf("=== IT SOFTWARE DATA ENTRY SYSTEM - ADMIN INTERFACE ===\n");
            printf("Info: Type 'return' to go back to the main screen.\n\n");
            printf("Enter Administrator Name: ");
            scanf("%s", adminName);
            while (getchar() != '\n');

            if (strcmp(adminName, "return") == 0)
            {
                return;
            }

            if (strcmp(adminName, "admin") != 0)
            {
                printf("\nAdministrator Name is Invalid. Press Enter to try again.");
                getchar();
            }
            else
            {
                validUserNameOption = 1;
            }
        }

        printf("Enter Password: ");
        scanf("%s", passwd);
        while (getchar() != '\n');

        if (strcmp(passwd, "admin12") != 0) 
        {
            printf("\nYou have Entered a Wrong Password. Please Try Again.\n");
            printf("Press Enter to continue...");
            getchar();
            validUserPwdOption = 0;
            validUserNameOption = 0;
        }
        else
        {
            clearScreen();
            printf("You Have Successfully Logged In.\n");
            printf("Press Enter to Continue...");
            getchar();
            validUserPwdOption = 1;
            validUserNameOption = 1;
            showAdminMenu = 0;

            while (showAdminMenu == 0)
            {
                clearScreen();
                printf("================ ADMIN OPTIONS ================\n");
                printf(" 1. Add New Employee\n");
                printf(" 2. Show Daily Entries (View All)\n");
                printf(" 3. Search Employee Record\n");
                printf(" 4. Remove Employee\n");
                printf(" 5. Close / Return to Main Menu\n");
                printf("===============================================\n");
                printf("Please enter your choice: ");
                selectAdminOption();
            }
        }
    }
}

/* Handle Administrator Options */
void selectAdminOption(void)
{
    char chc[10];
    scanf("%s", chc);
    while (getchar() != '\n');

    if (strcmp(chc, "1") == 0)
    {
        getData(1);
    }
    else if (strcmp(chc, "2") == 0)
    {
        getData(2);
    }
    else if (strcmp(chc, "3") == 0)
    {
        getData(3);
    }
    else if (strcmp(chc, "4") == 0)
    {
        getData(4);
    }
    else if (strcmp(chc, "5") == 0)
    {
        showAdminMenu = 1;
    }
    else
    {
        printf("\nInvalid Input! Press Enter to continue.");
        getchar();
    }
}

/* Database Operations for Employees */
void getData(int option)
{
    FILE *db, *tempdb;
    char anotherEmp = 'y';
    int searchId;
    char confirmDelete;
    struct employee empData;
    size = sizeof(struct employee);

    db = fopen("empbase.dat", "rb+");
    if (db == NULL)
    {
        db = fopen("empbase.dat", "wb+");
        if (db == NULL)
        {
            printf("The File could not be opened or created.\n");
            return;
        }
    }

    switch (option)
    {
        case 1: /* Add New Employee */
        {
            while (anotherEmp == 'y' || anotherEmp == 'Y')
            {
                clearScreen();
                printf("=== ADD A NEW EMPLOYEE ===\n");
                printf("Warning: Password must contain alphanumeric digits.\n\n");
                
                printf("Enter First Name: ");
                scanf("%s", empData.firstname);
                printf("Enter Last Name: ");
                scanf("%s", empData.lastname);
                printf("Enter Password (up to 6 chars): ");
                scanf("%s", empData.password);
                while (getchar() != '\n');

                rewind(db);
                int maxId = 1999;
                struct employee readEmp;
                while (fread(&readEmp, size, 1, db) == 1)
                {
                    if (readEmp.empid > maxId)
                    {
                        maxId = readEmp.empid;
                    }
                }
                empData.empid = maxId + 1;

                printf("\nSave Employee Information? (y/n): ");
                char checkSave = getchar();
                while (getchar() != '\n');

                if (checkSave == 'y' || checkSave == 'Y')
                {
                    empData.loginhour = -1;
                    empData.logouthour = -1;
                    empData.day = 0;
                    fseek(db, 0, SEEK_END);
                    fwrite(&empData, size, 1, db);
                    printf("Employee successfully added! Assigned ID: %d\n", empData.empid);
                }

                printf("\nWould you like to add another employee? (y/n): ");
                anotherEmp = getchar();
                while (getchar() != '\n');
            }
            break;
        }

        case 2: /* View All Employees */
        {
            clearScreen();
            printf("=== VIEW EMPLOYEE INFORMATION ===\n\n");
            printf("%-10s | %-25s | %-15s | %-15s\n", "ID", "Employee Name", "Log In", "Log Out");
            printf("-------------------------------------------------------------------\n");
            
            rewind(db);
            while (fread(&empData, size, 1, db) == 1)
            {
                empData.firstname[0] = toupper(empData.firstname[0]);
                empData.lastname[0] = toupper(empData.lastname[0]);
                
                printf("%-10d | %s %-24s | ", empData.empid, empData.firstname, empData.lastname);
                if (empData.loginhour == -1) printf("%-15s | ", "Not Logged In");
                else printf("%02d:%02d:%02d        | ", empData.loginhour, empData.loginmin, empData.loginsec);

                if (empData.logouthour == -1) printf("%-15s\n", "Not Logged Out");
                else printf("%02d:%02d:%02d\n", empData.logouthour, empData.logoutmin, empData.logoutsec);
            }
            printf("\nPress Enter to continue...");
            getchar();
            break;
        }

        case 3: /* Search Employee */
        {
            int found = 0;
            clearScreen();
            printf("=== SEARCH EMPLOYEE INFORMATION ===\n");
            printf("Enter Employee ID to Search: ");
            scanf("%d", &searchId);
            while (getchar() != '\n');

            rewind(db);
            while (fread(&empData, size, 1, db) == 1)
            {
                if (empData.empid == searchId)
                {
                    found = 1;
                    printf("\nEmployee Information Found:\n");
                    printf("Name: %s %s\n", empData.firstname, empData.lastname);
                    if (empData.loginhour == -1) printf("Log In Time: Not Logged In\n");
                    else printf("Log In Time: %02d:%02d:%02d\n", empData.loginhour, empData.loginmin, empData.loginsec);
                    
                    if (empData.logouthour == -1) printf("Log Out Time: Not Logged Out\n");
                    else printf("Log Out Time: %02d:%02d:%02d\n", empData.logouthour, empData.logoutmin, empData.logoutsec);
                }
            }
            if (!found) printf("\nEmployee Information is not available.\n");
            printf("\nPress Enter to continue...");
            getchar();
            break;
        }

        case 4: /* Remove Employee */
        {
            int found = 0;
            clearScreen();
            printf("=== REMOVE AN EMPLOYEE ===\n");
            printf("Enter Employee ID to Delete: ");
            scanf("%d", &searchId);
            while (getchar() != '\n');

            rewind(db);
            while (fread(&empData, size, 1, db) == 1)
            {
                if (empData.empid == searchId)
                {
                    found = 1;
                    printf("Found: %s %s\n", empData.firstname, empData.lastname);
                }
            }

            if (found)
            {
                printf("Do you want to Delete the Employee? (y/n): ");
                confirmDelete = getchar();
                while (getchar() != '\n');

                if (confirmDelete == 'y' || confirmDelete == 'Y')
                {
                    tempdb = fopen("tempo.dat", "wb");
                    rewind(db);
                    while (fread(&empData, size, 1, db) == 1)
                    {
                        if (empData.empid != searchId)
                        {
                            fwrite(&empData, size, 1, tempdb);
                        }
                    }
                    fclose(tempdb);
                    fclose(db);
                    remove("empbase.dat");
                    rename("tempo.dat", "empbase.dat");
                    db = fopen("empbase.dat", "rb+");
                    printf("Employee deleted successfully.\n");
                }
            }
            else
            {
                printf("Employee Information not available.\n");
            }
            printf("\nPress Enter to continue...");
            getchar();
            break;
        }

        case 5: /* Employee Login */
        {
            int found = 0;
            clearScreen();
            printf("=== DAILY EMPLOYEE TIME RECORDING SYSTEM (LOGIN) ===\n");
            printf("Enter Your ID to Login: ");
            scanf("%d", &searchId);
            while (getchar() != '\n');

            rewind(db);
            while (fread(&empData, size, 1, db) == 1)
            {
                if (empData.empid == searchId)
                {
                    found = 1;
                    char pass[20];
                    printf("Enter Your Password: ");
                    scanf("%s", pass);
                    while (getchar() != '\n');

                    if (strcmp(empData.password, pass) != 0)
                    {
                        printf("\nYou Have Supplied a Wrong Password.\n");
                        break;
                    }

                    time_t t = time(NULL);
                    struct tm *tm_info = localtime(&t);

                    empData.loginhour = tm_info->tm_hour;
                    empData.loginmin = tm_info->tm_min;
                    empData.loginsec = tm_info->tm_sec;
                    empData.day = tm_info->tm_mday;
                    empData.mon = tm_info->tm_mon + 1;
                    empData.yr = tm_info->tm_year + 1900;

                    fseek(db, -size, SEEK_CUR);
                    fwrite(&empData, size, 1, db);

                    printf("\nYou have successfully Logged In the System!\n");
                    printf("Welcome, %s %s\n", empData.firstname, empData.lastname);
                    printf("Log In Time: %02d:%02d:%02d\n", empData.loginhour, empData.loginmin, empData.loginsec);
                }
            }
            if (!found) printf("\nEmployee Information is not available.\n");
            printf("\nPress Enter to continue...");
            getchar();
            break;
        }

        case 6: /* Employee Logout */
        {
            int found = 0;
            clearScreen();
            printf("=== DAILY EMPLOYEE TIME RECORDING SYSTEM (LOGOUT) ===\n");
            printf("Enter Your ID to Logout: ");
            scanf("%d", &searchId);
            while (getchar() != '\n');

            rewind(db);
            while (fread(&empData, size, 1, db) == 1)
            {
                if (empData.empid == searchId)
                {
                    found = 1;
                    char pass[20];
                    printf("Enter Password: ");
                    scanf("%s", pass);
                    while (getchar() != '\n');

                    if (strcmp(empData.password, pass) != 0)
                    {
                        printf("\nYou Have Supplied a Wrong Password.\n");
                        break;
                    }

                    time_t t = time(NULL);
                    struct tm *tm_info = localtime(&t);

                    empData.logouthour = tm_info->tm_hour;
                    empData.logoutmin = tm_info->tm_min;
                    empData.logoutsec = tm_info->tm_sec;

                    fseek(db, -size, SEEK_CUR);
                    fwrite(&empData, size, 1, db);

                    printf("\nYou have successfully Logged Out of the System!\n");
                    printf("Employee Name: %s %s\n", empData.firstname, empData.lastname);
                    printf("Log Out Time: %02d:%02d:%02d\n", empData.logouthour, empData.logoutmin, empData.logoutsec);
                }
            }
            
            if (!found) printf("\nEmployee Information is not available.\n");
            printf("\nPress Enter to continue...");
            getchar();
            break;
        }

    }


    if (db != NULL) fclose(db);
}