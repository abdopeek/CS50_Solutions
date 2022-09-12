#include <math.h>
#include <string.h>
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int count_letters(string word);
int count_words(string word);
int count_sentences(string word);

int main(void)
{
    int sentenceCount;
    int letterCount;
    int wordCount;
    int lpw;
    int spw;

    string text = get_string("Text: ");

    letterCount = count_letters(text);
    wordCount = count_words(text);
    sentenceCount = count_sentences(text);

    lpw = letterCount  * 100 / wordCount;
    spw = sentenceCount * 100 / wordCount  ;

    // Formula is index = 0.0588 * lpw - 0.296 * spw - 15.8
    float calculation = 0.0588 * lpw - 0.296 * spw - 15.8;
    int index = round(calculation);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1){
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}









int count_letters(string word)
{
    int count = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string word)
{
    int count = 0;
    bool foundletter = false;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == ' ')
        {
            foundletter = false;
        }
        else {
            if (foundletter == false)
            {
                count++;
                foundletter = true;
            }
        }
    }
    return count;
}

int count_sentences(string word)
{
    int count = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == '!' || word[i] == '?' || word[i] == '.')
        {
            count++;
        }
    }
    return count;
}
