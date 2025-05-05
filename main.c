#include<stdio.h>
#include<conio.h>
#include<string.h>

void signup();
void login();
int checkCredentials(const char *username, const char *password);

int main(){
    
    printf("Welcome!!!\n");
    
    while(1){

    printf("What would like to do?\n");
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

        printf("3\n");

        return 0;

        default:

        printf("Chose from 1-3:\n");

    }
    
}

}

void signup(){

    char username[100],password[100];
    printf("Enter Username:(No Spaces)");
    scanf("%s",username);
    getchar();

    printf("Enter password:(No Spaces)");
    scanf("%s",password);
    getchar();

    printf("%s\n",username);
    printf("%s\n",password);

    FILE* sign = fopen("users.csv","a+");

    fprintf(sign,"%s | %s\n", username, password);

    fclose(sign);

}

void login(){

    char username[100],password[100];
    printf("Enter Username:(no spaces)");
    scanf("%s",username);
    getchar();

    printf("Enter password:(no spaces)");
    scanf("%s",password);
    getchar();

    FILE* login = fopen("users.csv","r");

    // * doesn't do shit from here onwards

    char line[1024];
    while (fgets(line, 1024, login)) {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ",");
        while (token != NULL) {
            printf("%s ", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }

    fclose(login);
    
}
