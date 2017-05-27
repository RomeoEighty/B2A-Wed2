/*
 * 540479c
 * Ryutaro Yamaguchi
 * kadai02.c
 * "linear list"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char sourcefile[] = "./namelist.txt";
const char logfile[] = "./log2.txt";

typedef struct person {
    char   name[20];
    int    age;
    double weight;
    double height;
    struct person *next;
} person_t;

person_t *first = NULL;
FILE *fp;
FILE *logfp;

void create_personlist(void);
void add_newperson(void);
void print_allmem(void);

int main(void)
{
    if ((fp = fopen(sourcefile, "r")) == NULL) {
        perror(sourcefile);
        return 1;
    }
    if ((logfp = fopen(logfile, "w")) == NULL) {
        perror(logfile);
        return 1;
    }


    create_personlist();
    add_newperson();
    print_allmem();

    fclose(fp);
    fclose(logfp);
    return 0;
}
    
void create_personlist(void)
{
    char namebuf[20];
    first = (person_t *)malloc(sizeof(person_t));
    if (first == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    memset(namebuf, '\0', 20);

    fscanf(fp, "%[^,],%d,%lf,%lf\r\n", namebuf, &first->age, &first->height, &first->weight);
    strcpy(first->name, namebuf);
    first->next = NULL;
}

void add_newperson(void)
{
    char namebuf[20];
    int agebuf;
    double weightbuf;
    double heightbuf;
    int ret;
    person_t *new;
    person_t *prev = first;

    memset(namebuf, '\0', 20);
    while ((ret = fscanf(fp, "%[^,],%d,%lf,%lf\r\n", namebuf, &agebuf, &heightbuf, &weightbuf)) != EOF) {
//      printf("fuga");
//      puts(namebuf);
        new = (person_t *)malloc(sizeof(person_t));
        if (new == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        strcpy(new->name, namebuf);
        new->age = agebuf;
        new->weight = weightbuf;
        new->height = heightbuf;
        new->next = NULL;
        prev->next = new;
        prev = new;
    }
}

void print_allmem(void)
{
    for (person_t *p1 = first; p1 != NULL; p1 = p1->next) {
        fprintf(logfp, "Name  : %s\nAge   : %d\nWeight: %lf\nHeight: %lf\n\n", p1->name, p1->age, p1->weight, p1->height);
    }
}
