#include<stdio.h>

void signup();
void login();

int main(){

    while(1){
    
    printf("Welcome!!!\n");
    printf("What would like to do?\n");
    printf("1.Login\n");
    printf("2.Sign-Up\n");
    printf("3.Exit\n");
    printf("Enter 1-3:\n");

    int inputforuser;

    scanf("%d",&inputforuser);

    switch(inputforuser){

        case 1:

        printf("1\n");

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
    printf("Enter Username:\n");
    scanf("%[^\n]s",username);
    getchar();

    printf("Enter password:\n");
    scanf("%[^\n]s",password);
    getchar();

    printf("%s\n",username);
    printf("%s\n",password);

}