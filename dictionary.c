// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// unload one individual list (do for each hash index)
void unloadIndividualList(node *start);

// Choose number of buckets in hash table

/*
    IMPORTANT NOTE: running this on a local machine which tries to initiate
    a very large array on RAM may cause errors trying to find contiguous memory. 
    
    The dictionary is ~480000 elements so even
    a hash table which aims to have an word per hash element 
    (480000 element hash table) would be 480000 * sizeof(pointer), 
    which on a 64-bit machine would be: 480000 * 64 = ~30 million bytes. 
    this is still ~3% of a gigabyte so not to pressing for any computer 
    manufactured in the 21st century but still an important consideration.

    Running a version which requests bytes from a larger server, 
    optimal speed is 20000-50000 elements for the dictionary with ~480000 elements.
*/
const unsigned int N = 20000;

int SIZE = 0;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int bucket = hash(word);
    node *nxt = table[bucket]->next;

    while (nxt != NULL)
    {
        if (strcasecmp(nxt->word, word) == 0)
        {
            return true;
        }
        nxt = nxt->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 543210;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int charVal = toupper(word[i]) * (int) pow(3, sizeof(word) - i - 1);
        sum += charVal;
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        table[i]->next = NULL;
    }

    FILE *words = fopen(dictionary, "r");
    if (words == NULL)
    {
        printf("Error: could not open your dictionary.");
        return false;
    }

    char tWord[LENGTH + 1];
    while (fgets(tWord, LENGTH + 2, words) != NULL)
    {
        tWord[strcspn(tWord, "\n")] = 0; //get rid of newline character
        int bucket = hash(tWord);
        node *new = malloc(sizeof(node));
        strcpy(new->word, tWord);
        new->next = table[bucket]->next;
        table[bucket]->next = new;

        SIZE++;
    }

    fclose(words);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return SIZE;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        unloadIndividualList(table[i]->next);
        free(table[i]);
    }
    return true;
}

void unloadIndividualList(node *start)
{
    if (start == NULL)
    {
        return;
    }

    unloadIndividualList(start->next);

    free(start);
}
