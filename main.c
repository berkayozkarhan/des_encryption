#include <stdio.h>
#include "des.h"


unsigned long long plain_text = 0x0123456789ABCDEFULL;
unsigned long long test_message = 0x1987abdfe8cfcaea;
unsigned long long test_msg_1 =   0x1122334455664455;
unsigned long long key = 0x133457799BBCDFF1ULL;

int main(void)
{
    unsigned long long encrypted_message = Encrypt(test_msg_1, key);
    unsigned long long encrypted_message2 = Encrypt(encrypted_message, key);
    unsigned long long encrypted_message3 = Encrypt(encrypted_message2, key);
    printf("encrypted message : 0x%llx\n", encrypted_message);
    printf("encrypted message2 : 0x%llx\n", encrypted_message2);
    printf("encrypted message3 : 0x%llx\n", encrypted_message3);
}
