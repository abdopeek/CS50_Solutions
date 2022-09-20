// Implements a dictionary's functionality
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
unsigned int counter = 0;
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_value = hash(word);
    node *tmp = table[hash_value];
    while (tmp != 0)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the file
    unsigned int hash_value;
    FILE *file = fopen(dictionary, "r");

    // Error checking
    if (file == NULL)
    {
        printf("File cannot be opened!\n");
        return false;
    }

    // Add words into node:
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        hash_value = hash(word);
        // Checking placement in bucket of hash table

        n->next = table[hash_value];
        table[hash_value] = n;
        counter++;

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (counter > 0)
    {
        return counter;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to this each bucket location
        node *cursor = table[i];
        // If cursor is not NULL, free
        while (cursor != NULL)
        {
            // Create temp
            node *tmp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            // Free up temp
            free(tmp);
        }
        // If cursor is NULL
        if (cursor == NULL && i == N-1)
        {
            return true;
        }
    }
    return false;
}
