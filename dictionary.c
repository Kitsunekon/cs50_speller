// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include "dictionary.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    for (node *tmp = table[index]; tmp->next != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int index = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        index += tolower(word[i]);
    }
    return (index % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // read from dictionary.
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf ("No available memory");
        return false;
    }
    
    char buffer[LENGTH + 1];
    // read words from dictionary until the end of the file.
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // creates a node for buffer word.
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf ("No available memory.\n");
            return false;
        }
        
        // copy string into new node.
        strcpy(new_node->word, buffer);
        new_node->next = NULL;
        
        // hash index and insert node into hash table.
        int index = hash(buffer);
        if (table[index] == NULL)
        {
            table[index] = new_node;
        }
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }
        word_count++;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *trv = head;
        node *tmp = head;
        
        while (trv != NULL)
        {
            trv = trv->next;
            free(tmp);
            tmp = trv;
        }
    }
    return true;
}
