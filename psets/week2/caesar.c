#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char rotate(char c, int n);

char lower[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char upper[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string key = (argv[1]);
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isdigit(key[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int k = atoi(key);
    string word = get_string("plaintext:  ");
    for (int i = 0; i < strlen(word); i++)
    {
        word[i] = rotate(word[i], k);
    }
    printf("ciphertext: %s\n", word);
    return 0;
}

char rotate(char c, int key)
{
    int location;
    if (isupper(c))
    {
        location = c - 'A';
        location = location + key % 26;
        if (location > 25)
        {
            location = location % 26;
        }
        c = upper[location];
    }
    if (islower(c))
    {
        location = c - 'a';
        location = location + key % 26;
        if (location > 25)
        {
            location = location % 26;
        }
        c = lower[location];
    }
    return c;
}

/*
1- Find the index of the character(int location) in the alphabet using (c - 'A') if it is an upper and (c - 'a') if lower.
2- Rotate the index using (index + key % 26).
3- Set the character to the char at the index found above.
4- Return found character to the function.
*/
