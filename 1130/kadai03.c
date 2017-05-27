/*
 * 540479c
 * Ryutaro Yamaguchi
 * kadai03.c
 * "doubly-linked list"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char sourcefile[] = "./namelist.txt";
const char logfile[] = "./log3.txt";
const char logfile2[] = "./log3_output.txt";

typedef struct person {
    char   name[20];
    int    age;
    double weight;
    double height;
    struct person *next;
    struct person *prev;
} person_t;

person_t *first = NULL;
FILE *fp;

void create_personlist(void);
void add_newperson(void);
void print_allmem(FILE*);
void dump_all(char *);
int delete(char *);

int main(void)
{
    FILE *logfp;
    if ((fp = fopen(sourcefile, "r")) == NULL) {
        perror(sourcefile);
        return 1;
    }
    printf("Successfully load \"%s\"\n", sourcefile);
    if ((logfp = fopen(logfile, "w")) == NULL) {
        perror(logfile);
        return 1;
    }


    create_personlist();
    add_newperson();
    print_allmem(logfp);

    char name[20];
    char *p;
    do {
        printf("Input the name of the member you want to delete (type \"quit\" to exit)\n\t:");
        fgets(name, 20, stdin);
        if ((p = strchr(name, '\n')) != NULL) {
            *p = '\0';
        }
        if (strcmp(name, "quit") == 0) {
            puts("exit program");
            break;
        }
        if (delete(name) == EOF) {
            printf("error:\"%s\" is not found\n", name);
        } else {
            dump_all(name);
            printf("\tCreated the file \"%s\" which is the list of the member except for name:\"%s\".\n", name, name);
            printf("\tYou can see the difference by typing \"$ diff %s %s\"\n", name, logfile);
        }
    } while (1);

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
    first->prev = NULL;
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
        new->prev = prev;
        prev->next = new;
        prev = new;
    }
}

/*
 *                  [head]                 
 *    ,------.     ,------.     ,------.   
 *    | prev |  ,->| prev |  ,->| prev |<. 
 *    |------|  |  |------|  |  |------| | 
 *  ,>| next |<-'  | next |<-'  | next | | 
 *  | `------'     `------'     `------' | 
 *  '------------------------------------' 
 */
int delete(char *name)
{
    person_t *head;
    int result;

    for (head = first; head != NULL; head = head->next) {
        result = strcmp(head->name, name);
        if (result == 0) {
            break;
        }
    }

    if (head == NULL) {
        return EOF;
    } else {
        if (head->prev != NULL) { // head is not a pointer to head of list.
            if (head->next != NULL) {
                head->next->prev = head->prev;
            }
        } else {
            first = head->next;
            if (head->next != NULL) {
                head->next->prev = NULL;
            }
        }
        if (head->next != NULL) { // head is not a pointer to end of list.
            if (head->prev != NULL) {
                head->prev->next = head->next;
            }
        } else {
            if (head->prev != NULL) {
                head->prev->next = NULL;
            }
        }
    }
    free(head);
    return 0;
}

void print_allmem(FILE *fp)
{
    for (person_t *p1 = first; p1 != NULL; p1 = p1->next) {
        fprintf(fp, "Name  : %s\n"
                    "Age   : %d\n"
                    "Weight: %lf\n"
                    "Height: %lf\n\n", p1->name, p1->age, p1->weight, p1->height);
    }
}

void dump_all(char *filename)
{
    FILE *dumpfp;
    if ((dumpfp = fopen(filename, "w")) == NULL) {
        perror("dump_file");
        exit(1);
    }

    for (person_t *p1 = first; p1 != NULL; p1 = p1->next) {
        fprintf(dumpfp, "Name  : %s\nAge   : %d\nWeight: %lf\nHeight: %lf\n\n", p1->name, p1->age, p1->weight, p1->height);
    }

    fclose(dumpfp);
}
