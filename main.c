#include <stdio.h>
#include "des.h"


unsigned long long plain_text = 0x0123456789ABCDEFULL;
unsigned long long key = 0x133457799BBCDFF1ULL;

int main(void)
{
    Encrypt(plain_text, key);
}
