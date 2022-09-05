#include <stdio.h>
#include <math.h>
#include <string.h>

void read_values(double arr[100], int * array_size);
void read_polynom(char BUFFER[1000]);
void divider(char BUFFER[1000], char array[100][10], int * size);
void update(char array[100][10], int size);
int is_pow(char arr[10]);
int is_single_degrees(char arr[10]);
int main() {
    FILE * fp;
    fp = fopen("evaluations.txt", "w");
    char BUFFER[1000], array[100][10], c, a;
    double arr[100], sum = 0, temp, temp2;
    int size, counter, i, j;
    read_values(arr, & counter);
    read_polynom(BUFFER);
    divider(BUFFER, array, & size);
    update(array, size);
    for (i = 0; i < counter; i++) {
        sum = 0;
        for (j = 0; j < size; j++) {
            if (is_pow(array[j]) == 1) {
                sscanf(array[j], "%lf %c %c %lf", & temp, & c, & a, & temp2);
                sum += temp * pow(arr[i], temp2);
            }
            //the process of finding the values of polynomials
            else {
                if (is_single_degrees(array[j]) == 1) {
                    sscanf(array[j], "%lf", & temp);
                    sum += temp * arr[i];
                } else {
                    sscanf(array[j], "%lf", & temp);
                    sum += temp;
                }
            }
        }
        fprintf(fp, "%.2lf\n", sum);
    }
    return 0;
}
void update(char array[100][10], int size) {
    int i = 0, j = 0, counter = 0;
    char temp[10], temp2[10], temp3[10];
    for (i = 0; i < size; i++) {
        if (array[i][0] == 'x') {
            temp[0] = '1';
            for (j = 1; j < array[i][counter] != '\0'; j++) {
                temp[j] = array[i][counter];
                counter++;
            }
            temp[j] = '\0';
            strcpy(array[i], temp);
            counter = 0;
        }
        if (array[i][0] == '+' && array[i][1] == 'x') {
            temp2[0] = '+';
            temp2[1] = '1';
            for (j = 2; j < array[i][counter] != '\0'; j++) {
                temp2[j] = array[i][counter + 1];
                counter++;
            }
            temp2[j] = '\0';
            strcpy(array[i], temp2);
            counter = 0;
        }
        if (array[i][0] == '-' && array[i][1] == 'x') {
            temp3[0] = '-';
            temp3[1] = '1';
            for (j = 2; j < array[i][counter] != '\0'; j++) {
                temp3[j] = array[i][counter + 1];
                counter++;
            }
            temp3[j] = '\0';
            strcpy(array[i], temp3);
            counter = 0;
        }
    }
}
int is_pow(char arr[10]) {
    int i, flag = 0;
    for (i = 0; i < arr[i] != '\0'; i++) {
        if (arr[i] == '^')
            flag = 1;
    }                             //process of checking for pow
    if (flag == 1)
        return 1;

    return 0;
}
int is_single_degrees(char arr[10]) {
    int i, flag = 0;
    for (i = 0; i < arr[i] != '\0'; i++) {
        if (arr[i] == 'x')
            flag = 1;                      //the process of checking whether there is a single degree
    }
    if (flag == 1)
        return 1;

    return 0;
}
void divider(char BUFFER[1000], char array[100][10], int * size) {
    int j = 0, k = 0, i;
    for (i = 0; i < BUFFER[i] != '\0'; i++) {
        if (BUFFER[i] == '+' || BUFFER[i] == '-' || BUFFER[i] == '\0') {
            array[j][k] = '\0';
            k = 0;
            j++;
            array[j][k] = BUFFER[i];
            k++;
            //polynom separation process
        } else {
            array[j][k] = BUFFER[i];
            k++;
        }
    }
    array[j][k] = '\0';
    j++;
    * size = j;
}
void read_polynom(char BUFFER[1000]) {
    int i = 0, count = 0, sayac = 0, j = 0, k = 0;
    char ch[1000];
    char * pch;
    double sum, multiply, divide, subtract, pow;
    for (int i = 0; i < 1000; i++) {
        ch[i] = ' ';
    }
    FILE * fp;
    fp = fopen("polynomial.txt", "r");
    fgets(ch, 1000, fp);
    pch = strtok(ch, " ");
    i = 0;                             //The process of getting rid of space characters
    while (pch != NULL) {
        for (count = 0; pch[count] != '\0'; count++) {
            BUFFER[i] = pch[count];
            i++;
        }
        pch = strtok(NULL, " ");
    }
    BUFFER[i] = '\0';
}
void read_values(double arr[100], int * array_size) {
    int i = 0, counter = 0;
    FILE * fp;
    fp = fopen("values.txt", "r");

    while (!feof(fp)) {                     //operation to read numbers in the values file
        fscanf(fp, "%lf", & arr[i]);
        i++;
        counter++;
    }
    * array_size = counter;
}