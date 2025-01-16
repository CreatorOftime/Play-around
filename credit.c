#include <cs50.h>
#include <stdio.h>

long check_sum(long cc);
char check_vendor(long cc);
long check_length(long cc);

int main(void)
{
    long cc; // cc means credit cards
    do       // Prompt user for their creditcard number
    {
        cc = get_long("Enter your Credit Card Number here: ");
    }
    while (cc < 0); // While checking for a number equal to, or grather than 13
    long checksum = check_sum(cc);
    char vendor = check_vendor(cc);
    if (checksum == 0)
    {
        if (vendor == 'V')
        {
            printf("VISA\n");
        }
        else if (vendor == 'A')
        {
            printf("AMEX\n");
        }
        else if (vendor == 'M')
        {
            printf("MASTERCARD\n");
        }
        else if (vendor == 'I')
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

long check_sum(long cc) // Script to preform the creditcard number check in Luhn's Algorhithm
{
    long sum = 0;      // Variable used to hold the total through the loop
    long product = 0;  // Variable used to hold the digit multiplication through the iteration
    long position = 0; // Variable to track the position of the long integer
    int card_length = 0;
    while (cc > 0)
    {
        long credit = cc % 10; // get the last digit in the long
        if (position % 2 == 1) // if the position is even, do below. (Side note, to check multiples
                               // of something, you need to have 'x' == 0, this is because whatever
                               // the multiple is, divided by itself leaves no remainder)
        {
            product = credit * 2;
            if (product < 10) // If the multipled digit doesn't have a tenths place
            {
                sum += product; // Adds odd positions multiplied digit
            }
            else // If the multiplied digit does have a tenths place
            {
                sum +=
                    (product / 10) +
                    (product % 10); // (Focuses on the tenths place) + (Focuses on the ones place)
            }
        }
        else // If the position is odd, do below
        {
            sum += credit; // adds the odds digits, no need to worry about a tenths place
        }
        cc /= 10;    // Moves to next digit
        position++;  // moves left one digit
        product = 0; // resets product to 0 for the next digit
    }
    sum = sum % 10; // for checking if the last digit is 0
    return sum;
}

char check_vendor(long cc)
{
    long td = 0;
    long calculate = 0;
    int length = check_length(cc);

    do
    {
        cc = cc / 10; // keeps dividing input by 10
        td = cc;
    }
    while (cc > 99); // stops when reaching double digits
    calculate += td; // Store in a variable
    if ((calculate >= 40 && calculate <= 49) &&
        (length == 13 || length == 16)) // if variable starts with 4, not optimized
    {
        return 'V'; // print Visa
    }
    else if ((calculate == 34 || calculate == 37) && (length == 15)) // else if variable = 34 or 37
    {
        return 'A'; // print AMEX
    }
    else if ((calculate >= 51 && calculate <= 55) &&
             (length == 16)) // else variable >= 51 or variable <= 55
    {
        return 'M'; // print Mastercard
    }
    else
    {
        return 'I'; // Invalid
    }
}

long check_length(long cc)
{
    int length = 0; // Will contain the number length

    do
    {
        length++;     // counts up by 1
        cc = cc / 10; // removes 1 digit per iteration
    }
    while (cc > 0); // once all numbers are gone, finish loop

    return length; // returns value to be used in check_vendor
}
