/*
 * 540479c
 * Ryutaro Yamaguchi
 * "Hash"
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    BUFSIZE = 1000,
    HASHSIZE = 1000,
};

typedef struct member {
    char   name[20];
    int    age;
    double height;
    double weight;
    struct member *next;
} member_t;

member_t *root_array[HASHSIZE];

char filename[] = "namelist.txt";

int hash(char *);
void add_member(FILE *fp);
void init_root(member_t **);
void print_root(int);

int main(void)
{
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        perror(filename);
        exit(1);
    }

    init_root(root_array);
    add_member(fp);
    while(1) {
        int num;
        puts("Enter Hash index:");
        scanf("%d", &num);
        print_root(num);
    }

    return 0;
}

int hash(char *s)
{
    unsigned int val;
    for (val = 0; *s != '\0'; s++) {
        val = *s + (31 * val);
    }
    return (int)(val % HASHSIZE);
}

void add_member(FILE *fp)
{
    char namebuf[20];
    int agebuf;
    double heightbuf;
    double weightbuf;
    int ret;

    while ((ret = fscanf(fp, "%[^,],%d,%lf,%lf\r\n", namebuf, &agebuf, &heightbuf, &weightbuf)) != EOF) {
        member_t *new = malloc(sizeof(member_t));
        if (new == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        strcpy(new->name, namebuf);
        new->age = agebuf;
        new->weight = weightbuf;
        new->height = heightbuf;
        new->next = NULL;

        const int val = hash(namebuf);
        member_t *p;
        p = root_array[val];
        if (p != NULL) {
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = new;
        } else {
            root_array[val] = new;
        }
    }
}

void init_root(member_t **root_array)
{
    for (int i = 0; i < HASHSIZE; i++) {
        root_array[i] = NULL;
    }
}

void print_root(int num)
{
    member_t *p;
    for (p = root_array[num]; p != NULL; p = p->next) {
        printf("name   :%s\n"
               "age    :%d\n"
               "weight :%lf\n"
               "height :%lf\n"
               "\n", p->name, p->age, p->weight, p->height);
    }
}
