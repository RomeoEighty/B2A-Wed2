/* 
 * ------------------------
 * 16/11/02
 * kadai03
 * 540479c
 * Ryutaro Yamaguchi
 * "divide polynomial into monomials"
 * ------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print_in_matrix(double *matrix, int num_row, int num_column);
void count_row_column(const char *str, int *num_row, int *num_column)
{
    int num_row_buf = 0;
    int num_column_buf = 1;
    bool column_num_cleared = false;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ',' && !(column_num_cleared)) {
            num_column_buf++;
            column_num_cleared = true;
        } else if (str[i] == ':') {
            num_row_buf++;
        }
    }
    printf("row:%d column:%d\n", num_row_buf, num_column_buf);
    *num_row = num_row_buf;
    *num_column = num_column_buf;
}

//void contain_matrix(double *matrix, char *src, int num_row, int num_column)
//{
//    char sep[] = ":,";
//    char buf[8] = {};
//
//    strtok(src, sep);
//
//    for (int i = 0; i < num_row * num_column; i++) {
//        matrix[i] = atof(buf);
//        strtok(NULL, sep);
//        memset(buf, '\0', 8);
//    }
//}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s [num00,num01...]:[num10,num11...]:...: [num00,num01...]:[num10,num11...]:..:", argv[0]);
        return 0;
    }
    int num_row[2];
    int num_column[2];
    char src_data[2][128];

    for (int i = 0; i < 2; i++) {
        strcpy(src_data[i], argv[i + 1]);
        printf("%s\n", src_data[i]);
    }

    count_row_column(src_data[0], &num_row[0], &num_column[0]);
    num_row[1] = num_column[0];
    num_column[1] = num_row[0];

    double *matrix[2];
    double *product;
    matrix[0] = (double *)malloc(sizeof(double) * num_row[0] * num_column[0]);
    matrix[1] = (double *)malloc(sizeof(double) * num_row[1] * num_column[1]);
    product = (double *)malloc(sizeof(double) * num_row[0] * num_column[1]);

    for (int i = 0; i < 2; i++) {
        char sep[] = ":,";
        char *buf;

        matrix[i][0] = atof(strtok(argv[i + 1], sep));

        for (int j = 1; j < num_row[i] * num_column[i]; j++) {
            matrix[i][j] = atof(strtok(NULL, sep));
        }
    }

    for (int i = 0; i < 2; i++) {
        if (!(i)) {
            printf("A =\n");
        } else {
            printf("B =\n");
        }
        print_in_matrix(matrix[i], num_row[i], num_column[i]);
    }

    for (int i = 0; i < num_row[0] * num_column[1]; i++) {
        product[i] = 0.;
    }
    for (int i = 0; i < num_row[0] * num_column[1]; i++) {
        for (int j = 0; j < num_column[0]; j++) {
            product[i] += matrix[0][i / num_column[1] * num_column[0] + j] * matrix[1][i % num_column[1] + j * num_column[1]];
        }
    }

    printf("A*B =\n");
    print_in_matrix(product, num_row[0], num_column[1]);

//  free
    free(product);
    free(matrix[1]);
    free(matrix[0]);
    return 0;
}

void print_in_matrix(double *matrix, int num_row, int num_column)
{
    for (int i = 0; i < num_row * num_column; i++) {
        if (i % num_column == 0) {
            printf("[");
        }
        printf("%f", matrix[i]);
        if (i % num_column != num_column - 1) {
            printf(",");
        } else {
            printf("]\n");
        }
    }
}
