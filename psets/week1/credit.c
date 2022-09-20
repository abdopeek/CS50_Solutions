#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long num;
    do{
        num = get_long("No: ");
    }while(num <= 0); // Validate value of card

    int c1, c2, c3, c4, c5, c6, c7, c8;
    c1 = ((num%100)/10)*2;
    c2 = ((num%10000)/1000)*2;
    c3 = ((num%1000000)/100000)*2;
    c4 = ((num%100000000)/10000000)*2;
    c5 = ((num%10000000000)/1000000000)*2;
    c6 = ((num%1000000000000)/100000000000)*2;
    c7 = ((num%100000000000000)/10000000000000)*2;
    c8 = ((num%10000000000000000)/1000000000000000)*2;

    c1 = (c1 % 100/10) + (c1 % 10);
    c2 = (c2 % 100/10) + (c2 % 10);
    c3 = (c3 % 100/10) + (c3 % 10);
    c4 = (c4 % 100/10) + (c4 % 10);
    c5 = (c5 % 100/10) + (c5 % 10);
    c6 = (c6 % 100/10) + (c6 % 10);
    c7 = (c7 % 100/10) + (c7 % 10);
    c8 = (c8 % 100/10) + (c8 % 10);

    int sum1 = c1 + c2 + c3 + c4 + c5 + c6 +c7 +c8;

    int c9,c10,c11,c12,c13,c14,c15,c16;
    c9 =  (num%10);
    c10 = (num%1000)/100;
    c11 = (num%100000)/10000;
    c12 = (num%10000000)/1000000;
    c13 = (num%1000000000)/100000000;
    c14 = (num%100000000000)/10000000000;
    c15 = (num%10000000000000)/1000000000000;
    c16 = (num%1000000000000000)/100000000000000;

    int sum2 = c9 + c10 +c11+c12+c13+c14+c15+c16;

    int sum = sum1+sum2;
    if((sum%10) != 0){
        printf("INVALID\n");
        return 0;
    }


    long visa = num;
    long amex = num;
    long master = num;

    int length = 0;

    while(num>0){
        num = num / 10;
        length++;
    }

    while(visa >= 10){
        visa /= 10;
    }
    if(visa == 4 && (length ==13 || length == 16)){
        printf("VISA\n");
        return 0;
    }

    while(amex >=10000000000000){
        amex /=10000000000000;
    }
    if((amex == 34 || amex == 37) && length == 15){
        printf("AMEX\n");
        return 0;
    }

    while(master >= 100000000000000){
        master /= 100000000000000;
    }
    if(length == 16 && (master == 51 || master == 52 || master == 53 || master == 54 || master == 55)){
        printf("MASTERCARD\n");
        return 0;
    }
    else{
        printf("INVALID\n");
        return 0;
    }

}
