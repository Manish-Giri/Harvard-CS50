#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool validate_cmdline(string arg)
{
    // validate command line arguments
    for (int i = 0; i < strlen(arg); i++)
    {
        if (!isdigit(arg[i]))
        {
            return false;
        }
    }
    return true;
}

string encrypt(string plaintext, int key)
{
    // encrypt plaintext to ciphertext
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char pi = plaintext[i];
        char base, ci;
        if (isalpha(pi))
        {

            // if uppercase
            if (isupper(pi))
            {
                base = 'A';
                ci = (((pi - base) + key) % 26) + base;
                // plaintext[i] = ci;
            }

            else
            {
                base = 'a';
                ci = (((pi - base) + key) % 26) + base;
            }

            plaintext[i] = ci;
        }
    }
    return plaintext;
}

int main(int argc, string argv[])
{
    // validate 2 args
    if (argc == 2)
    {
        if (validate_cmdline(argv[1]))
        {
            int k = atoi(argv[1]);
            string plaintext = get_string("plaintext: ");
            string ciphertext = encrypt(plaintext, k);
            //printf("Success\n%i\n", k);
            printf("ciphertext: %s\n", ciphertext);
            return 0;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
