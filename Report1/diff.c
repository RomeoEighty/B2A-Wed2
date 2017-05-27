/*
 * 540479c
 * Ryutaro Yamaguchi
 * Report diff.c
 * "get difference between two files"
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


typedef enum {
    unix,
    dos,
    mac,
} filetype_t;

filetype_t filetype = unix;


/* remove CR and CL */
void rm_nl(char *str);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage:%s [file1] [file2]\n", argv[0]);
        puts("\t[file*]: pbm format file");
        exit(1);
    }

    FILE *pbm_fp;
    FILE *pbm_fp2;

    /* open source file */
    if ((pbm_fp = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }

    if ((pbm_fp2 = fopen(argv[2], "r")) == NULL) {
        perror(argv[2]);
        exit(1);
    }



//  /* open output file */
//  char *noise_reducted_file = (char *)malloc(sizeof(char) * (strlen(argv[1]) + strlen("noise_reducted_") + 1));
//  if (noise_reducted_file == NULL) {
//      fprintf(stderr, "malloc error\n");
//      exit(1);
//  }
//  memset(noise_reducted_file, '\0', strlen(argv[1]) + strlen("noise_reducted_") + 1);
//  strcat(noise_reducted_file, "noise_reducted_");
//  strcat(noise_reducted_file, argv[1]);
//  if ((ofp = fopen(noise_reducted_file, "w")) == NULL) {
//      perror(argv[1]);
//      exit(1);
//  }


    /* check filetype */
    char buf[16];
    memset(buf, '\0', 16);
    fgets(buf, sizeof(buf), pbm_fp);

    rm_nl(buf);

    if (strcmp(buf, "P1") != 0) {
        puts("error: filetype is not supported. this program supports portable bitmap encoded in ASCII(P1) only.");
        fclose(pbm_fp);
        exit(1);
    }

    memset(buf, '\0', 16);
    fgets(buf, sizeof(buf), pbm_fp2);

    rm_nl(buf);

    if (strcmp(buf, "P1") != 0) {
        puts("error: filetype is not supported. this program supports portable bitmap encoded in ASCII(P1) only.");
        fclose(pbm_fp);
        exit(1);
    }


int c_num = 0;
int l_num = 0;
int c_num2 = 0;
int l_num2 = 0;


    /* get column and line numbers */
    fscanf(pbm_fp, "%d %d\n", &c_num, &l_num);
    fscanf(pbm_fp2, "%d %d\n", &c_num2, &l_num2);
    
    if (c_num != c_num2 || l_num != l_num2) {
        printf("These two files may not be the same at all. (Resolution is not the same)\n");
    }
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

    char *image = NULL;
    image = malloc(sizeof(char) * c_num * l_num);
    char *image2 = NULL;
    image2 = malloc(sizeof(char) * c_num * l_num);
    if (image == NULL || image2 == NULL) {
        printf("malloc error\n");
        exit(1);
    }

    /* import image */
    int i = 0; /* energy_func_sub1 exceeds c_num*l_num */
    char ch;
    while ((ch = fgetc(pbm_fp)) != EOF) {
        if (ch == '0' || ch == '1') {
            image[i++] = ch - '0';
        }
    }
    i = 0;
    while ((ch = fgetc(pbm_fp2)) != EOF) {
        if (ch == '0' || ch == '1') {
            image2[i++] = ch - '0';
        }
    }

    int count = 0;
    int max_count = c_num * l_num;

    for (int j = 0; j < c_num * l_num; j++) {
        if (image[j] == image2[j]) {
            count++;
        }
    }

    printf("%d/%d is match\n", count, max_count);
    printf("%lf%% is match\n", (double)count / max_count);


    free(image);
    free(image2);
    /* close files */
    fclose(pbm_fp);
    fclose(pbm_fp2);

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

