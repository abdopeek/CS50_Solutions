#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BLOCKSIZE 512
int main(int argc, char *argv[])
{
    int counter = 0;
    typedef uint8_t BYTE;
    // Check for command-line interface input:
    if (argc != 2)
    {
        printf("Usage: ./recover file_name\n");
        return 1;
    }
    // Open the file:

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File can't be opened\n");
        return 1;
    }

    // Read:
    BYTE buffer[BLOCKSIZE];
    FILE *output = NULL;
    char filename[8];
    while (fread(buffer, sizeof(BYTE), BLOCKSIZE, file) || feof(file) == 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (output != NULL)
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", counter);
            output = fopen(filename, "w");
            counter++;
        }
        if (output != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, output);
        }
    }
    if (file != NULL)
    {
        fclose(file);
    }
    if (output != NULL)
    {
        fclose(output);
    }

}
