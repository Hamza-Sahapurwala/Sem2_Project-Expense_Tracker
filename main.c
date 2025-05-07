#include<stdio.h>
#include<conio.h>
#include<string.h>

void signup();
void login();
int logincheck(char u[], char p[]);

int main(){
    
    printf("Welcome!!!\n");
    
    while(1){

    printf("What would you like to do?\n");
    printf("1.Login\n");
    printf("2.Sign-Up\n");
    printf("3.Exit\n");
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
    printf("Enter Username:(No Spaces)\n");
    scanf("%s",username);

    printf("Enter password:(No Spaces)\n");
    scanf("%s",password);

    printf("%s\n",username);
    printf("%s\n",password);

    FILE* sign = fopen("users.csv","a+");

    fprintf(sign,"%s|%s\n", username, password);

    fclose(sign);

}

void login(){

    char username[100],password[100];

    printf("Enter Username:(no Spaces)\n");
    scanf("%s",username);

    printf("Enter password:(no Spaces)\n");
    scanf("%s",password);

    int found = logincheck(username,password);

    if (found){

        printf("Login Successful!\n");

    }

    else{
        printf("Failed Login! Try Again.\n");
    }
}

int logincheck(char u[], char p[]){

    FILE *f = fopen("users.csv", "r");

    char line[100];

    while (fgets(line, 100, f)) {

        char fileUsername[50], filePassword[50];

        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, "|");

        if (token != NULL) {

            strcpy(fileUsername, token);

            token = strtok(NULL, "|");

            if (token != NULL) {

                strcpy(filePassword, token);

            }

            if (strcmp(u, fileUsername) == 0 && strcmp(p, filePassword) == 0) {

                return 1;

            }
            else{

                return 0;

            }
        }
    }

    fclose(f);
}