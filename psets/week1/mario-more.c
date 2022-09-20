#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Height: ");
    int i, j, s, k, f, n;
    while (height < 1 || height >8) {
        height = get_int("Height: ");
    }
    for(i=1; i<=height; i++) {
        for(j = 1; j <= (height-i); j++){
            printf(" ");
        }
        for(k=1; k<=i; k++){
            printf("#");
        }
        for(s=0; s<2; s++){
            printf(" ");
        }
        for(n=1; n<=i; n++) {
            printf("#");
        }
        printf("\n");
    }
}
