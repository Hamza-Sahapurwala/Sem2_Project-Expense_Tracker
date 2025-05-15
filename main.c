#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

void signup();
void newsignup(char u[]);
void login();
int logincheck(char u[], char p[]);
int signupcheck(char u[], char p[]);
void login_successful(char u[]);
void add_record(char u[]);
int category(char* c);
void see_record(char u[]);
void edit_record(char u[]);
void delete_record(char u[]);
void generate_bar_graph(char u[]);

int main(){
    
    printf("Welcome!!!\n");
    
    while(1){

    printf("What would you like to do?\n");
    printf("1. Login\n");
    printf("2. Sign-Up\n");
    printf("3. Exit\n");
    printf("Enter 1-3:\n");

    int inputforuser;

    scanf("%d",&inputforuser);

    switch(inputforuser){

        case 1:

        login();

        break;

        case 2:

        signup();

        break;

        case 3:

        printf("Return For Managing Your Expenses!\n");

        return 0;

        default:

        printf("Chose from 1-3:\n");

    }
    
}

}

void signup(){

    char username[100],password[100];
    printf("SignUp Screen:\n");
    printf("Enter Username:(No Spaces)\n");
    scanf("%s",username);

    printf("Enter password:(No Spaces)\n");
    scanf("%s",password);

    if (signupcheck(username, password)){

    FILE* sign = fopen("users.csv","a");

    fprintf(sign,"%s|%s\n", username, password);

    fclose(sign);

    newsignup(username);

    login_successful(username);
    }

    else
    printf("Try Signing Up Once Again!\n");
}

void newsignup(char u[]){

    char filename[100] = ".\\UserData\\";
    
    strcat(filename, u);

    strcat(filename, ".csv");

    FILE* newsign = fopen(filename, "a");

    fclose(newsign);

}

void login(){

    char username[100],password[100];

    printf("Login Screen:\n");
    printf("Enter Username:(no Spaces)\n");
    scanf("%s",username);

    printf("Enter password:(no Spaces)\n");
    scanf("%s",password);

    int found = logincheck(username,password);

    if (found){

        printf("Login Successful!\n");

        login_successful(username);

    }

    else{
        printf("Failed Login! Try Again.\n");
    }
}

int logincheck(char u[], char p[]){

    FILE *f = fopen("users.csv", "r");

    char line[100];

    while (fgets(line, 100, f)) {

        char username[50], password[50];

        line[strcspn(line, "\n")] = 0;

        char* token = strtok(line, "|");

        if (token != NULL) {

            strcpy(username, token);

            token = strtok(NULL, "|");

            if (token != NULL) {

                strcpy(password, token);

            }

            if (strcmp(u, username) == 0 && strcmp(p, password) == 0) {

                return 1;

            }
        }
    }
    
    fclose(f);
    return 0;
}

int signupcheck(char u[], char p[]){

    FILE *f = fopen("users.csv", "r");

    char line[100];

    if (strlen(u) == 0 || strlen(p) == 0) {

        printf("Username or password can't be empty.\n");

        return 0;
    }
    if (strlen(p) < 4) {

        printf("Password must be at least 4 characters.\n");

        return 0;
    }

    while (fgets(line, 100, f)) {

        char fileUsername[50];

        line[strcspn(line, "\n")] = 0;

        char* token = strtok(line, "|");

        if (token != NULL) {

            strcpy(fileUsername, token);

            if (strcmp(u, fileUsername) == 0) {

                printf("The UserName has already been taken!\n");

                return 0;

            }
        }
    }
    
    fclose(f);
    return 1;

}

void login_successful(char u[]){

    int input;

    printf("Welcome to the Expense Management System!\n");

    while (1)
    {   
        printf("What would you like to do?\n");
        
        printf("1. Add Record\n");
        printf("2. Delete Record\n");
        printf("3. Edit Record\n");
        printf("4. See Records\n");
        printf("5. See Bar Graph\n");
        printf("6. Go Back to Login/SignUp Page\n");
        printf("7. Exit\n");
        printf("Enter 1-7:\n");

        scanf("%d",&input);
        
        switch (input)
        {
            case 1:
                add_record(u);
                break;
            case 2:
                delete_record(u);
                break;
            case 3:
                edit_record(u);
                break;
            case 4:
                see_record(u);
                break;
            case 5:
                generate_bar_graph(u);
                break;
            case 6:
                return;
            case 7:
                printf("Return For Managing Your Expenses!\n");
                exit(0);
            default:
                printf("Choose between 1-5!\n");    
        }    
    }
}

int category(char* c){

    int choice;

    while(1){

    printf("Enter Your Category:\n");

    printf("1. Food\n");
    printf("2. Transport\n");
    printf("3. Clothing\n");
    printf("4. Miscellonous\n");

    scanf("%d",&choice);

    switch (choice)
    {
    case 1:
        strcpy(c,"Food");
        return 0;
    
    case 2:
        strcpy(c,"Transport");
        return 0;

    case 3:
        strcpy(c,"Clothing");
        return 0;

    case 4:
        strcpy(c,"Miscellonous");
        return 0;
    
    default:
        printf("Choose from the Options!\n");
    }
}

}

void add_record(char u[]){

    char filename[100] = ".\\UserData\\";

    int id;

    float amt;

    char date[100], cat[100],line[256];
    
    strcat(filename, u);

    strcat(filename, ".csv");

    FILE* addrecord = fopen(filename, "a+");

    printf("Enter Amount:\n");

    scanf("%f",&amt);

    printf("Enter Date:\n");

    scanf("%s", date);

    category(cat);

    while (fgets(line, 256, addrecord)) {
        int temp;
        if (sscanf(line, "%d,", &temp) == 1) {
            if (temp > id) {
                id = temp;
            }
        }
    }

    fprintf(addrecord, "%d|%.2f|%s|%s\n", id + 1, amt, date, cat);

    fclose(addrecord);

}

void see_record(char u[]){

    char filename[100] = ".\\UserData\\", line[100];

    strcat(filename, u);

    strcat(filename, ".csv");

    FILE* seerecord = fopen(filename, "r");

    while(fgets(line, 100, seerecord)){

        char* id = strtok(line, "|");

        char* amount = strtok(NULL, "|");

        char* date = strtok(NULL, "|");

        char* category = strtok(NULL, "\n");

        printf("ID:%s\tAmount:%s\tDate:%s\tCategory:%s\n", id, amount, date, category);

    }

    fclose(seerecord);

}

void edit_record(char u[]){

    char filename[100] = ".\\UserData\\";
    strcat(filename, u);
    strcat(filename, ".csv");

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }

    int ids[100], count = 0;
    float amounts[100];
    char dates[100][50], categories[100][50];
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d|%f|%[^|]|%[^\n]", &ids[count], &amounts[count], dates[count], categories[count]);
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No records to edit.\n");
        return;
    }

    int id_to_edit, found = 0;
    printf("Enter the ID of the record to edit: ");
    scanf("%d", &id_to_edit);

    for (int i = 0; i < count; i++) {
        if (ids[i] == id_to_edit) {
            found = 1;
            int choice;
            printf("What do you want to edit?\n");
            printf("1. Amount\n2. Date\n3. Category\nEnter 1-3: ");
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Enter new Amount: ");
                scanf("%f", &amounts[i]);
            } else if (choice == 2) {
                printf("Enter new Date: ");
                scanf("%s", dates[i]);
            } else if (choice == 3) {
                category(categories[i]);
            } else {
                printf("Invalid choice.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Record with ID %d not found.\n", id_to_edit);
        return;
    }

    file = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%.2f|%s|%s\n", ids[i], amounts[i], dates[i], categories[i]);
    }
    fclose(file);

    printf("Record edited successfully!\n");
}

void delete_record(char u[]){

    char filename[100] = ".\\UserData\\";
    strcat(filename, u);
    strcat(filename, ".csv");

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }

    int ids[100], count = 0, found = 0;
    float amounts[100];
    char dates[100][50], categories[100][50];
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d|%f|%[^|]|%[^\n]", &ids[count], &amounts[count], dates[count], categories[count]);
        count++;
    }
    fclose(file);

    int id_to_delete;
    printf("Enter the ID of the record to delete: ");
    scanf("%d", &id_to_delete);

    file = fopen(filename, "w");
    int new_id = 1;
    for (int i = 0; i < count; i++) {
        if (ids[i] != id_to_delete) {
            fprintf(file, "%d|%.2f|%s|%s\n", new_id, amounts[i], dates[i], categories[i]);
            new_id++;
        } else {
            found = 1;
        }
    }
    fclose(file);

    if (found) {
        printf("Record deleted successfully and IDs updated!\n");
    } else {
        printf("Record with ID %d not found.\n", id_to_delete);
    }

}

void generate_bar_graph(char u[]) {
    char filename[100] = ".\\UserData\\";
    strcat(filename, u);
    strcat(filename, ".csv");

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No records to generate graph.\n");
        return;
    }

    float food = 0, transport = 0, clothing = 0, misc = 0;
    char line[256], category[100];
    float amount;
    int id;
    char date[100];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d|%f|%[^|]|%[^\n]", &id, &amount, date, category);

        if (strcmp(category, "Food") == 0)
            food += amount;
        else if (strcmp(category, "Transport") == 0)
            transport += amount;
        else if (strcmp(category, "Clothing") == 0)
            clothing += amount;
        else if (strcmp(category, "Miscellonous") == 0)
            misc += amount;
    }
    fclose(file);

    FILE* data = fopen("graphdata.dat", "w");
    fprintf(data, "Category Amount\n");
    fprintf(data, "Food %.2f\n", food);
    fprintf(data, "Transport %.2f\n", transport);
    fprintf(data, "Clothing %.2f\n", clothing);
    fprintf(data, "Miscellonous %.2f\n", misc);
    fclose(data);

    FILE* gnuplot = _popen("gnuplot -persistent", "w");

    if (gnuplot) {
        fprintf(gnuplot,
            "set title 'Expenses by Category'\n"
            "set style data histograms\n"
            "set style fill solid 1.0\n"
            "set boxwidth 0.5\n"
            "set xlabel 'Category'\n"
            "set ylabel 'Amount'\n"
            "plot 'graphdata.dat' using 2:xtic(1) title 'Expense'\n"
        );
        _pclose(gnuplot);
    } else {
        printf("Failed to launch Gnuplot.\n");
    }
}