/* 
 * ------------------------
 * 16/11/02
 * kadai02
 * 540479c
 * Ryutaro Yamaguchi
 * "pointer to pointer"
 * ------------------------
 */

#include <stdio.h>
#include <stdlib.h>

void print_matrix(double **);
void inverse(double **);

int main(int argc, char *argv[])
{
    if (argc != 5) {
        printf("The number of values is not valid\n");
    }

    double **matrix = (double **) malloc(sizeof(double*) * 4);
//  double matrix_[2][2] = {{1.0, 2.0}, {3.0, 4.0}};

//  for (int i = 0; i < 4; i++) {
//      matrix[i] = &matrix_[i / 2][i % 2];
//  }
    for (int i = 0; i < 4; i++) {
        *(matrix+i) = (double *)malloc(sizeof(double));
        *matrix[i] = atof(argv[i + 1]);
    }

    print_matrix(matrix);

    inverse(matrix);

    print_matrix(matrix);

    for (int i = 0; i < 4; i++) {
        free(*(matrix + i));
    }
    free(matrix);
    return 0;
}

void print_matrix(double **matrix)
{
    puts("");
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            printf("( ");
        }
        printf("%2.3f ", *matrix[i]);
        if (i % 2 == 1) {
            puts(")");
        }
    }
    puts("");
}

void inverse(double **matrix)
{
    double determinant = (*matrix[0])*(*matrix[3]) - (*matrix[1])*(*matrix[2]);
    double tmp;

    tmp = *matrix[3];
    *matrix[3] = *matrix[0] / determinant;
    *matrix[0] = tmp / determinant;
    *matrix[1] = -*matrix[1] / determinant;
    *matrix[2] = -*matrix[2] / determinant;
}
