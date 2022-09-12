#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>

char upper[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char lower [] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc != 2)
    {
        printf("Input a key!\n");
        return 1;
    }

    
    for (int i = 0; i < 26; i++)
    {
        if(isalpha(key[i]) == 0)
        {
            printf("No\n");
            return 1;
        }
    }

    
    for (int i = 0; i < 25; i++)
    {
        if (key[i] == key[i+1])
        {
            printf("No duplicates:(\n");
            return 1;
        }
    }

    
    if (strlen(argv[1]) != 26)
    {
        printf("Has to be 26 letters!\n");
        return 1;
    }

    string word = get_string("plaintext: ");
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        int index;
        if (isupper(word[i]) != 0)
        {
            for (int j = 0; j < 26; j++)
            {
                if (word[i] == upper[j])
                {
                    index = j;
                    word[i] = toupper(key[index]);
                    break;
                }
            }
        }
        else if (islower(word[i]) != 0)
        {
            for (int j = 0; j < 26; j++)
            {
                if (word[i] == lower[j])
                {
                    index = j;
                    word[i] = tolower(key[index]);
                    break;
                }
            }
        }
    }

    printf("ciphertext: %s", word);
    printf("\n");

}
