#include <stdio.h>
#include "des.h"


unsigned long long plain_text = 0x0123456789ABCDEFULL;
unsigned long long test_message = 0x1987abdfe8cfcaea;
unsigned long long key = 0x133457799BBCDFF1ULL;

int main(void)
{
    unsigned long long encrypted_message = Encrypt(test_message, key);
    printf("encrypted message : 0x%lx\n", encrypted_message);
}
