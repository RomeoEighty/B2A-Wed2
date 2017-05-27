/*
 * 540479c
 * Ryutaro Yamaguchi
 * Report kadai01
 * "jamming .pbm image"
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "xorshift.h"


//#define DEBUG


#ifdef DEBUG

#define IOLog1(...) { printf(__VA_ARGS__); fflush(stdout); }
//#define IOLog2(args...) { printf(args...); fflush(stdout); }

#endif /* DEBUG */

#ifndef IOLog1
#define IOLog1(args...)
#endif
#ifndef IOLog2
#define IOLog2(args...) 
#endif


typedef enum {
    unix,
    dos,
    mac,
} filetype_t;

filetype_t filetype = unix;

/* remove CR and CL */
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

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage:%s [sourcefile] [noize_param]\n", argv[0]);
        puts("\t[sourcefile]: pbm format file");
        puts("\t[noize_param]: 0.0 - 1.0");
        exit(1);
    }

    FILE *pbm_fp;
    FILE *ofp;

    /* open source file */
    if ((pbm_fp = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }


    /* open output file */
    char *noised_file = (char *)malloc(sizeof(char) * (strlen(argv[1]) + strlen("noised_") + 1));
    if (noised_file == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    memset(noised_file, '\0', strlen(argv[1]) + strlen("noised_") + 1);
    strcat(noised_file, "noised_");
    strcat(noised_file, argv[1]);
    if ((ofp = fopen(noised_file, "w")) == NULL) {
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
        remove(noised_file);
        free(noised_file);
        exit(1);
    }
    free(noised_file);


    /* get column and line numbers */
    int c_num = 0;
    int l_num = 0;

    fscanf(pbm_fp, "%d %d\n", &c_num, &l_num);
    fprintf(ofp, "%d %d\r\n", c_num, l_num);
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


    /* generate noise */
    char ch;
    int p_clnum = 0;
    while ((ch = fgetc(pbm_fp)) != EOF) {
        if (ch == '0' || ch == '1') {
            if (random_double() <= atof(argv[2])) {
                ch = (ch == '0') ? '1' : '0';
            }
            p_clnum++;
        }
//      if (p_clnum == c_num) {
//          fputc('\n', ofp);
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
//      }
        fputc(ch, ofp);
    }


    /* close files */
    fclose(pbm_fp);
    fclose(ofp);

    return 0;
}
