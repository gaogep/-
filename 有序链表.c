#include <stdio.h>
#include <stdlib.h>

struct num {
    int value;
    struct num *next;
};

struct num *first = NULL; 

struct num *add_num(struct num *initial, int n);
struct num *insert(struct num *list, struct num *new_num);


int main()
{
    struct num *new1;
    struct num *new2;
    first = add_num(first, 20);
    first = add_num(first, 10);
    
    new1 = malloc(sizeof(struct num));
    new1->value = 5;
    
    new2 = malloc(sizeof(struct num));
    new2->value = 15;
    
    first = insert(first, new1);
    first = insert(first, new2);

    return 0;
}


struct num *insert(struct num *list, struct num *new_num)
{
    struct num *cur = list, *prev = NULL;

    while (cur->value <= new_num->value) {      
        prev = cur;
        cur = cur->next;
        if (cur == NULL) break;
    }

    if (prev == NULL) {
        new_num->next =cur;
        list = new_num;
        return list;
    }

    prev->next = new_num;
    new_num->next = cur;
    return list;
}


struct num *add_num(struct num *initial, int n)
{
    struct num *new_num;

    new_num = malloc(sizeof(struct num));

    if (new_num == NULL) {
        printf("---< malloc failure >---");
        exit(EXIT_FAILURE);
    }

    new_num->value = n;
    new_num->next = initial;
    return new_num;
}

