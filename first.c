#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
    char name[MAX_NAME];
    int age;
    //...add stuff later, maybe
}person;

person *hash_table[TABLE_SIZE];

//hash function
unsigned int hash(char *name)
{
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;

    //add up all the ascii values of the string
    for (int i = 0; i < length; i++)
    {
        hash_value+= name[i];
        //multiply the sum each time by the name[i]
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

//fuction to setup the table
void init_hash_table()
{
    //set all pointers to NULL
    for(int i =0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    //table is empty
}

void print_table()
{
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else if(hash_table[i] == DELETED_NODE)
        {
            printf("\t%i\t---<deleted>\n", i);
        }
        else{
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("End\n");
}

//insert data into the table
bool hash_table_insert(person *p)
{
    if (p == NULL) return false;

    int index = hash(p->name);

    //linear probing
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (i + index) % TABLE_SIZE;
        //try find an open space in the table
        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE)
        {
            hash_table[try] = p;
            return true;
        }
    }
    return false;
    //check is the space is occupied
    /*if (hash_table[index] != NULL)
    {
        return false;
    }
    hash_table[index] = p;
    printf("inserted %s\n", hash_table[index]->name);
    return true;    */
}

//find person in the table by their name
person *hash_table_lookup(char *name)
{
    int index = hash(name);
    //linear probing
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE)
        {
            return false; //not here
        }
        if (hash_table[try] == DELETED_NODE) continue;
        if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0)
        {
            return hash_table[try];
        }
    }
    /*if (hash_table[index] != NULL && strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0)
    {
        return hash_table[index];
    }
    else
    {
        return NULL;
    }*/
    return NULL;
}

//deleting a person
person *hash_table_delete(char *name)
{
    int index = hash(name);
    //linear probing
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) return NULL;
        if (hash_table[try] == DELETED_NODE) continue;
        if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0)
        {
            person *tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
    /*if (hash_table[index] != NULL && strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0)
    {
        //make a copy of the pointer
        person *tmp = hash_table[index];
        hash_table[index] = NULL;

        printf("deleted\n");
        return tmp;
    }
    else{
        printf("Not\n");
        return NULL;
    }*/
}

int main()
{
    init_hash_table();
    print_table();

    person jacob = {.name="Jacob", .age=256};
    person kate = {.name="Kate", .age=27};
    person mpho = {.name="Mpho", .age=14};
    person sarah = {.name="Sarah", .age=25};
    person edna = {.name="Edna", .age=56};
    person maren = {.name="Maren", .age=50};
    person eliza = {.name="Eliza", .age=16};
    person robert = {.name="Robert", .age=26};
    person jane = {.name="Jane", .age=19};
    

    hash_table_insert(&jacob);
    hash_table_insert(&kate);
    hash_table_insert(&mpho);
    hash_table_insert(&sarah);
    hash_table_insert(&edna);
    hash_table_insert(&maren);
    hash_table_insert(&eliza);
    hash_table_insert(&robert);
    hash_table_insert(&jane);
    print_table();

    person *tmp = hash_table_lookup("Mpho");
    if (tmp == NULL)
    {
        printf("Not found\n");
    }
    else{
        printf("Found %s\n", tmp->name);
    }

    tmp = hash_table_lookup("Goerge");
    if (tmp == NULL)
    {
        printf("Not found\n");
    }
    else{
        printf("Found. %s\n", tmp->name);
    }

    hash_table_delete("Mpho");
    print_table();
    /*printf("Jacob => %u\n", hash("Jacob"));
    printf("Natalie => %u\n", hash("Natalie"));
    printf("sara => %u\n", hash("Sara"));
    printf("Mpho => %u\n", hash("Mpho"));
    printf("Tebogo => %u\n", hash("Tebogo"));
    printf("Ron => %u\n", hash("Ron"));
    printf("Jane => %u\n", hash("Jane"));
    printf("Maren => %u\n", hash("Maren"));
    printf("Bill => %u\n", hash("Bill"));
    printf("Joe => %u\n", hash("Joe")); */

    return 0;
}