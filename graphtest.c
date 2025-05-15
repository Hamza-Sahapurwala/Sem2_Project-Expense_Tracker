#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

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

int main(){

    generate_bar_graph("a");

}