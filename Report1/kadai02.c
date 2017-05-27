/*
 * 540479c
 * Ryutaro Yamaguchi
 * Report kadai02
 * "Iterated conditional modes (ICM)"
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "xorshift.h"


//#define DEBUG


#ifdef DEBUG

#define IOLog1(...) { printf(__VA_ARGS__); fflush(stdout); }
//#define IOLog2(args...) { printf(args...); fflush(stdout); }

#endif /* DEBUG */

#ifndef IOLog1
#define IOLog1(args...)
#endif
//#ifndef IOLog2
//#define IOLog2(args...) 
//#endif


typedef enum {
    unix,
    dos,
    mac,
} filetype_t;


/* Global variables */
filetype_t filetype = unix;

int c_num = 0;
int l_num = 0;

double coefficent = 2.;


/* remove CR and CL */
void rm_nl(char *str);

int energy_func_sub1(int i, int x_i, char *image);
int energy_func_sub2(int i, int x_i, char *image);

double energy_func(int i, int x_i, char *image);

void remove_noise(char *image);


int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3) {
        printf("usage:%s [noisedfile] [coefficent]\n", argv[0]);
        puts("\t[noisedfile]: pbm format file");
        exit(1);
    }

    if (argc == 3) {
        coefficent = atof(argv[2]);
    }
    FILE *pbm_fp;
    FILE *ofp;

    /* open source file */
    if ((pbm_fp = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }


    /* open output file */
    char *noise_reducted_file = (char *)malloc(sizeof(char) * (strlen(argv[1]) + strlen("noise_reducted_") + 1));
    if (noise_reducted_file == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    memset(noise_reducted_file, '\0', strlen(argv[1]) + strlen("noise_reducted_") + 1);
    strcat(noise_reducted_file, "noise_reducted_");
    strcat(noise_reducted_file, argv[1]);
    if ((ofp = fopen(noise_reducted_file, "w")) == NULL) {
        perror(argv[1]);
        exit(1);
    }


    /* check filetype */
    char buf[16];
    memset(buf, '\0', 16);
    fgets(buf, sizeof(buf), pbm_fp);
    fputs(buf, ofp);

    rm_nl(buf);

    if (strcmp(buf, "P1") != 0) {
        puts("error: filetype is not supported. this program supports portable bitmap encoded in ASCII(P1) only.");
        fclose(pbm_fp);
        fclose(ofp);
        remove(noise_reducted_file);
        free(noise_reducted_file);
        exit(1);
    }
    free(noise_reducted_file);


    /* get column and line numbers */
    fscanf(pbm_fp, "%d %d\n", &c_num, &l_num);
    /* energy_func_sub1 exceeds c_num*l_num */
    char *image = (char*)malloc(sizeof(char) * c_num * (l_num + 2) + 2);
    if (image == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    fprintf(ofp, "%d %d\n", c_num, l_num);
//  switch (filetype) {
//  case dos:
//      fprintf(ofp, "%d %d\r\n", c_num, l_num); /* filetype dos */
//      break;
//  case mac:
//      fprintf(ofp, "%d %d\r", c_num, l_num); /* filetype mac */
//      break;
//  case unix:
//      fprintf(ofp, "%d %d\n", c_num, l_num); /* filetype unix */
//      break;
//  default:
//      printf("unknown filetype\n");
//      exit(1);
//  } 


    /* import image */
    int i = c_num + 1; /* energy_func_sub1 exceeds c_num*l_num */
    char ch;
    while ((ch = fgetc(pbm_fp)) != EOF) {
        if (ch == '0' || ch == '1') {
            image[i++] = ch - '0';
        }
    }

    /* noise reduction */
    remove_noise(image);

    /* file output */
    for (int j = 0; j < c_num * l_num; j++) {
        fputc(image[j] + '0', ofp);
        if (j % c_num == c_num - 1) {
            fputc('\n', ofp); // 
//          switch (filetype) {
//          case dos:
//              fprintf(ofp, "\r\n"); /* filetype dos */
//              break;
//          case mac:
//              fprintf(ofp, "\r"); /* filetype mac */
//              break;
//          case unix:
//              fprintf(ofp, "\n"); /* filetype unix */
//              break;
//          default:
//              printf("unknown filetype\n");
//              exit(1);
//          } 
        } else {
            fputc(' ', ofp);
        }
    }


    free(image);
    /* close files */
    fclose(pbm_fp);
    fclose(ofp);

    return 0;
}

void rm_nl(char *str)
{
    char *ch;
    bool cr = false;
    bool cl = false;

    ch = strchr(str, '\n');
    if (ch) {
        *ch = '\0';
        cr = true;
    }

    ch = strchr(str, '\r');
    if (ch) {
        *ch = '\0';
        cl = true;
    }

    if (cr && cl) {
        filetype = dos;
    } else if (!(cr) && cl) {
        filetype = mac;
    } else if (cr && !(cl)) {
        filetype = unix;
    }
}

int energy_func_sub1(int i, int x_i, char *image)
{
    int top = 1;
    int bottom = 1;
    int left = 1;
    int right = 1;

    if (i / c_num == 0) top = 0;
    if (i / c_num == l_num - 1) bottom = 0;
    if (i % c_num == 0) left = 0;
    if (i % c_num == c_num - 1) right = 1;

    return (2 * x_i - 1) * (( - 1 + 2 * image[i - c_num - 1]) * left  * top    +
                            ( - 1 + 2 * image[i - c_num])     * top            +
                            ( - 1 + 2 * image[i - c_num + 1]) * right * top    +
                            ( - 1 + 2 * image[i - 1])         * left           +
                            ( - 1 + 2 * image[i + 1])         * right          +
                            ( - 1 + 2 * image[i + c_num - 1]) * left  * bottom + 
                            ( - 1 + 2 * image[i + c_num])     * bottom         +
                            ( - 1 + 2 * image[i + c_num + 1]) * right * bottom
                            );
}

int energy_func_sub2(int i, int x_i, char *image)
{
    return (2 * x_i - 1) * (2 * image[i] - 1);
}

double energy_func(int i, int x_i, char *image)
{
    return -1. * (double)energy_func_sub1(i, x_i, image) - coefficent * (double)energy_func_sub2(i, x_i, image);
}

void remove_noise(char *image)
{
    int num;
    int indicator = 0;
    unsigned int count;
    unsigned int max_trials = UINT_MAX;
    unsigned int max_count  = 100000;
    int y_i;
    puts("removing noise...\n");

    for (unsigned int i = 0; i < max_trials; i++) {
        /* image data contains from image[c_num + 1] */
        num = random_integer(c_num * l_num) + c_num + 1;
        y_i = image[num];
        IOLog1("num%d", num);
        image[num] = (energy_func(num, 0, image) >= energy_func(num, 1, image)) ? 1 : 0;

        if (y_i != image[num]) {
            count = 0;
        } else {
            count++;
        }
        if ((double)count / max_count >= (double) indicator / 100) {
            printf("\r%d%%", indicator++);
            fflush(stdout);
        }
        if (count > max_count) break;
    }
}
