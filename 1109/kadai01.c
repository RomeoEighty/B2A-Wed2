#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>

enum {
    BUFSIZE = 64,
    LINENUMS = 10000,
};

char NAMELIST[] = "namelist.txt";

double get_avg_i(const int *data, const int line_index)
{
    double sum = 0;
    for (int i = 0; i < line_index; i++) {
        sum += (double)data[i];
    }
    return sum / line_index;
}
double get_avg_d(const double *data, const int line_index)
{
    double sum = 0;
    for (int i = 0; i < line_index; i++) {
        sum += data[i];
    }
    return sum / line_index;
}
void get_max_min_i(const int *data, const int line_index, int* min, int* index_min, int* max, int* index_max)
{
    int index_min_buf = 0;
    int index_max_buf = 0;
    int min_buf = INT_MAX;
    int max_buf = INT_MIN;

    for (int i = 0; i < line_index; i++) {
        if (min_buf > data[i]) {
            min_buf = data[i];
            index_min_buf = i;
        }
        if (max_buf < data[i]) {
            max_buf = data[i];
            index_max_buf = i;
        }
    }
    *min = min_buf;
    *max = max_buf;
    *index_min = index_min_buf;
    *index_max = index_max_buf;
}
void get_max_min_d(const double *data, const int line_index, double* min, int* index_min, double* max, int* index_max)
{
    int index_min_buf = 0;
    int index_max_buf = 0;
    double min_buf = DBL_MAX;
    double max_buf = -DBL_MAX;

    for (int i = 0; i < line_index; i++) {
        if (min_buf > data[i]) {
            min_buf = data[i];
            index_min_buf = i;
        }
        if (max_buf < data[i]) {
            max_buf = data[i];
            index_max_buf = i;
        }
    }
    *min = min_buf;
    *max = max_buf;
    *index_min = index_min_buf;
    *index_max = index_max_buf;
}
double get_stdev_i(const int *data, const int datasize)
{
    double tmp_stdev = 0.;
    double avg = get_avg_i(data, datasize);
    for (int i = 0; i < datasize; i++) {
        tmp_stdev += ((double)data[i] - avg) * ((double)data[i] - avg);
    }
    return sqrt(tmp_stdev / datasize);
}
double get_stdev_d(const double *data, const int datasize)
{
    double tmp_stdev = 0.;
    double avg = get_avg_d(data, datasize);
    for (int i = 0; i < datasize; i++) {
        tmp_stdev += (data[i] - avg) * (data[i] - avg);
    }
    return sqrt(tmp_stdev / datasize);
}

void get_data(FILE *fp, int *line_index, char **names_ptr, int *ages, double *heights, double *weights)
{
    int line = 0;
    char buf[BUFSIZE];
    rewind(fp);
    while (fscanf(fp, "%[^,],%d,%lf,%lf\n", buf, &ages[line], &heights[line], &weights[line]) != EOF) {
        strcpy(names_ptr[line], buf);
        memset(buf, '\0', sizeof(char) * BUFSIZE);
        line++;
    }
    *line_index = line;
}

int main(void)
{
    FILE *fp;
    int line_index = 0;
    int min_i, max_i;
    double min, max;
    int min_index, max_index;

    char *names = (char*)malloc(sizeof(char) * LINENUMS * BUFSIZE);;
    char **names_ptr = (char **)malloc(sizeof(char *) * LINENUMS);
    int *ages = (int *)malloc(sizeof(int) * LINENUMS);
    double *heights = (double *)malloc(sizeof(double) * LINENUMS);
    double *weights = (double *)malloc(sizeof(double) * LINENUMS);

    memset(names, '\0', LINENUMS * BUFSIZE);
    if ((fp = fopen(NAMELIST, "r")) == NULL) {
        printf("source file cannot open\n");
        return 1;
    }

    for (int i = 0; i < LINENUMS; i++) {
        names_ptr[i] = &names[i * BUFSIZE];
    }

    get_data(fp, &line_index, names_ptr, ages, heights, weights);
    get_max_min_i(ages, line_index, &min_i, &min_index, &max_i, &max_index);
    printf("Age : (max,min,mean,stdev) = %d(%s), %d(%s), %f, %f\n", max_i, names_ptr[max_index], min_i, names_ptr[min_index], get_avg_i(ages, line_index), get_stdev_i(ages, line_index));
    get_max_min_d(heights, line_index, &min, &min_index, &max, &max_index);
    printf("Height : (max,min,mean,stdev) = %f(%s), %f(%s), %f, %f\n", max, names_ptr[max_index], min, names_ptr[min_index], get_avg_d(heights, line_index), get_stdev_d(heights, line_index));
    get_max_min_d(weights, line_index, &min, &min_index, &max, &max_index);
    printf("Weight: (max,min,mean,stdev) = %f(%s), %f(%s), %f, %f\n", max, names_ptr[max_index], min, names_ptr[min_index], get_avg_d(weights, line_index), get_stdev_d(weights, line_index));

    free(names_ptr);
    free(names);
    free(ages);
    free(heights);
    free(weights);
    fclose(fp);
    return 0;
}
