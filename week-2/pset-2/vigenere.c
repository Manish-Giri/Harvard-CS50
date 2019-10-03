#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
const string INCORRECT_USAGE = "Usage: ./vigenere keyword";

int shift(char c)
{
    // calculate shift value of char c
    return isupper(c) ? c - 'A' : c - 'a';
}

bool validate_cmdline(string arg)
{
    // validate command line arguments
    for (int i = 0; i < strlen(arg); i++)
    {
        if (!isalpha(arg[i]))
        {
            return false;
        }
    }
    return true;
}

string encrypt(string plaintext, string keyword)
{
    int key_len = strlen(keyword);
    int last_valid_idx = -1;
    // encrypt plaintext to ciphertext
    for (int i = 0; i < strlen(plaintext); i++)
    {

        // ALGO -
        // 1. get index of pi -> i
        // 2. get pos of corresponding letter in key -> int pos = i mod key_len
        // 3. key is pos

        char pi = plaintext[i];
        char base, ci;
        int pos;
        if (isalpha(pi))
        {
            pos = ++last_valid_idx % key_len;
            int key = shift(keyword[pos]);

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
            string k = argv[1];
            string plaintext = get_string("plaintext: ");
            string ciphertext = encrypt(plaintext, k);
            //printf("Success\n%i\n", k);
            printf("ciphertext: %s\n", ciphertext);
            return 0;
        }
        else
        {
            printf("%s\n", INCORRECT_USAGE);
            return 1;
        }

    }
    else
    {
        printf("%s\n", INCORRECT_USAGE);
        return 1;
    }
}
