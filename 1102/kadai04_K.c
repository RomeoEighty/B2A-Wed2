#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double** allocMat(int H, int W)
{
    double** ret = (double**)malloc(sizeof(double*) * H);

    for (int i = 0; i < H; i++) {
        ret[i] = (double*)malloc(sizeof(double) * W);
    }

    return ret;
}

void freeMat(double** mat, int I, int J)
{
    for (int i = 0; i < I; i++) {
        free(mat[i]);
    }

    free(mat);
}

double** readMat(char* str, int* I, int* J)
{
    int W = 0, H = 0;

    for (int i = 0; i < strlen(str); i++) {
        W += (str[i] == ',');
        H += (str[i] == ':');
    }

    W = W / H + 1;

    *I = H;
    *J = W;

    double** ret = allocMat(H, W);
    char substr[256];
    int count = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ',' || str[i] == ':') {
            ret[count / W][count % W] = atof(substr);
            memset(substr, '\0', sizeof(substr));
            count++;
        } else {
            sprintf(substr, "%s%c", substr, str[i]);
        }
    }

    return ret;
}

void printMat(double** mat, int I, int J)
{
    for (int i = 0; i < I; i++) {
        printf("[ ");

        for (int j = 0; j < J; j++) {
            printf("%lf%c", mat[i][j], (j + 1 == J ? ' ' : ','));
        }

        printf("]\n");
    }
}

double** productMat(double** A, double** B, int I, int J, int K)
{
    double** ret = allocMat(I, K);

    for (int i = 0; i < I; i++) {
        for (int k = 0; k < K; k++) {
            ret[i][k] = 0;

            for (int j = 0; j < J; j++) {
                ret[i][k] += A[i][j] * B[j][k];
            }
        }
    }

    return ret;
}

int main(int argc, char** args)
{
    int I, J, K;

    double** A = readMat(args[1], &I, &J);
    double** B = readMat(args[2], &J, &K);
    double** C = productMat(A, B, I, J, K);

    puts("A =");
    printMat(A, I, J);
    puts("B =");
    printMat(B, J, K);
    puts("A*B =");
    printMat(C, I, K);

    freeMat(A, I, J);
    freeMat(B, J, K);
    freeMat(C, I, K);

    return 0;
}
