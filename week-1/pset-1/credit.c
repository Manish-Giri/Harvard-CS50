#include<stdio.h>
#include<cs50.h>
#include<math.h>

long get_input() 
{
    long cc = get_long("Enter credit card number: ");
    return cc;
}

long get_digits(long cc) 
{
    return floor(log10(labs(cc))) + 1;
}

int get_first_digit(long cc) 
{
    // gets first digit of cc num
    long first = cc;
    while (first >= 10)
    {
        first /= 10;
    }
    return first;
}

int get_first_two_digits(long cc) 
{
    // gets first 2 digits
    long first_two = cc;
    while (first_two >= 100)
    {
        first_two /= 10;
    }
    return first_two;
}

int add_product_digits(int product) 
{
    // add digits of products
    int sum = 0;
    while (product > 0) 
    {
        sum += product % 10;
        product /= 10;
    }
    return sum;
}

void check_creditcard(long cc)
{
    // validate cc
    long digits = get_digits(cc);
    int last_sum = 0;
    int other_sum = 0;
    bool last_digit = true;
    int first = get_first_digit(cc);
    int first_two = get_first_two_digits(cc);
    while (cc > 0) 
    {
        int last = cc % 10;
        if (last_digit) 
        {
           last_sum += last; 
        }
        else 
        {
            int prod = last * 2;
            other_sum += add_product_digits(prod);
            
        }
        cc /= 10;
        last_digit = !last_digit;
    }
    int total = last_sum + other_sum;
    if (total % 10 == 0) 
    {
        if (digits == 15) 
        {
            if (first_two == 34 || first_two == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
            
        }
        else if (digits == 16 || digits == 13) 
        {
            if (first == 4) 
            {
                printf("VISA\n");
            }
            else if (first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 || first_two == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                 printf("INVALID\n");
            }
              
        }
    }
    else 
    {
        printf("INVALID\n");
    }
}
int main(void)
{
    long cc = get_long("Enter credit card number: ");
    int digits = get_digits(cc);
    if (digits < 13 || digits > 16) 
    {
        printf("INVALID\n");
    }
    else 
    {
        check_creditcard(cc);
    }
}
    