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
        printf("5. Go Back to Login/SignUp Page\n");
        printf("6. Exit\n");
        printf("Enter 1-6:\n");

        scanf("%d",&input);
        
        switch (input)
        {
            case 1:
                add_record(u);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                see_record(u);
                break;
            case 5:
                return;
            case 6:
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