#include "des.h"

#include <stdio.h>
#define DEBUG 0




unsigned long long mix_original_key(unsigned long long original_key)
{
    unsigned long long mixed_key = 0ULL;
    for(int i=0;i<56;i++)
    {
        unsigned long long bit = BIT(original_key, ( 64 - pc1[i] ) );
        #ifdef DEBUG
            printf("bit %llu : %x", bit, i);
        #endif // DEBUG
        mixed_key |= ( bit << (56 - i -1 ));
    }

    return mixed_key;
}

unsigned long long mix_with_pc2(unsigned long long cn_dn)
{
    unsigned long long result = 0ULL;
    for(int i=0;i<48;++i)
    {
        unsigned int shift = pc2[i];
        unsigned long long bit = BIT(cn_dn, ( 56 - shift ) );
        result |= ( bit << ( 48 - i - 1 ));
    }
    return result;
}

unsigned long long
Encrypt(unsigned long long data,
                            unsigned long long key)
{

    //int right = RIGHT(data);
    //int left = LEFT(data);

    unsigned long long mixed_key = mix_original_key(key);  // OK.

    unsigned long c_values[17] = {0};
    unsigned long d_values[17] = {0};
    unsigned int shift_table[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    d_values[0] = ( mixed_key ) & 0xFFFFFFF;
    c_values[0] = ( mixed_key >> 28 ) & 0xFFFFFFF;




    for(int n=0; n<16; n++)
    {
        unsigned int shift_val = shift_table[n];
        c_values[n+1] = ( ( c_values[n] << shift_val ) | ( c_values[n] >> (28-shift_val) ) ) & ( 0x0FFFFFFF );
        d_values[n+1] = ( ( d_values[n] << shift_val ) | ( d_values[n] >> (28-shift_val) ) ) & ( 0x0FFFFFFF );
    }

    printf("16lı keyler : \n");

    for(int i=0;i<16;i++)
    {
        printf("c[%d] : %lu - d[%d] : %lu\n", i, c_values[i] & 0xFFFFFFF, i, d_values[i] & 0xFFFFFFF);
    }


    unsigned long long K_values[16] = {0};
    for(int i=0;i<16;i++)
    {

        //unsigned long long cn_dn = ( ( c_values[i] << 28 ) | ( d_values[i] ) ) & ( 0xFFFFFFFFFFFFFF );
        unsigned long num = c_values[i+1];
        unsigned long long cn = num << 28;
        unsigned long long dn = d_values[i+1];
        unsigned long long cn_dn = cn + dn;


        K_values[i] = mix_with_pc2(cn_dn);
        //printf("c[%d]d[%d] : %llu\n", i, i, K_values[i]);
        printf("input : %16llx, output : %16llx\n", cn_dn, K_values[i]);

    }

    int break_point = 9898;






    return 0ULL;
}
