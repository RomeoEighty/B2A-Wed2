#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char SOURCEFILE[] = "int_matrix_file.txt";

void get_linecol(FILE *fp, int *line_num, int *col_num, int *col_data_num)
{
    char ch;
    int line_counter = 0;
    int col_counter_tmp = 0;
    int col_counter = 0;
    int col_data_counter = 0;
    int col_data_counter_tmp = 0;
    fseek(fp, 0L, SEEK_SET);
    while ((ch = fgetc(fp)) != EOF) {
        col_counter_tmp++;
        if (ch == ' ') {
            col_data_counter_tmp++;
        }
        if (ch == '\n') {
            line_counter++;
            if (col_data_counter <= col_data_counter_tmp) {
                col_data_counter = col_data_counter_tmp;
            }
            if (col_counter <= col_counter_tmp) {
                col_counter = col_counter_tmp;
            }
            col_counter_tmp = 0;
            col_data_counter_tmp = 1;
        }
    }
    fseek(fp, 0L, SEEK_SET);
    *line_num = line_counter;
    *col_num = col_counter;
    *col_data_num = col_data_counter;
}
void get_data(FILE *fp, int *data_container, int col_num)
{
    fseek(fp, 0L, SEEK_SET);
    char *str = (char*)malloc(sizeof(char) * col_num);
    int i = 0;
    char *num_buf;
    char delimiter[] = " ";
    char *null;
    memset(str, '\0', col_num);
    while (fgets(str, col_num, fp) != NULL) {
        if ((null = strchr(str, '\n')) != NULL) {
            *null = '\0';
        }
//        printf("%s\n", str);
        num_buf = strtok(str, delimiter);
//        printf("%s ", num_buf);
        while (num_buf) {
            //printf(":%s ", num_buf);
            data_container[i++] = atoi(num_buf);
//            printf("::%d", data_container[i]);
            //memset(num_buf, '\0', 16);
            num_buf = strtok(NULL, delimiter);
//            if (num_buf == NULL) {
//                printf("NULLLLLLL");
//            }
        }
//        puts("");
    }
    free(str);
    fseek(fp, 0L, SEEK_SET);
}
int main(void)
{
    FILE *fpr;
    int line_num;
    int col_num;
    int col_data_num;

    if ((fpr = fopen(SOURCEFILE, "r")) == NULL) {
        printf("source file cannot open.\n");
        return 1;
    }

    get_linecol(fpr, &line_num, &col_num, &col_data_num);

    //printf("line:%d col:%d col_data:%d\n", line_num, col_num, col_data_num);

    int* datas = (int *)malloc(sizeof(int) * line_num * col_data_num);
//  int** datas_ptr = (int **)malloc(sizeof(int *) * line_num * col_data_num);
//  for (int i = 0; i < line_num * col_data_num; i++) {
//      datas[i] = 111;
//      datas_ptr[i] = &datas[i];
//  }

//  for (int i = 0; i < line_num; i++) {
//      data[i] = &datas[i * col_data_num];
//  }

    get_data(fpr, datas, col_num);
    for (int i = 0; i < line_num; i++) {
        for (int j = 0; j < col_data_num; j++) {
            printf("%d ", datas[i * col_data_num + j]);
        }
        puts("");
    }

    fclose(fpr);
    return 0;
}
