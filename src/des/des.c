#include "des.h"
#include <stdio.h>
#define DEBUG 0


unsigned long long mix_with_array(unsigned long long data,
                                    unsigned char mixer_array[],
                                        int mix_array_length,
                                            int input_size_bits,
                                                int output_size_bits)
{
    //still in progress.
    unsigned long long result = 0ULL;
    for(int i=0;i<input_size_bits;i++)
    {
        int shifter = mixer_array[i];
        unsigned long long bit = BIT(data, (input_size_bits - shifter));
        result |= (bit << (output_size_bits - i - 1));
    }
    return result;
}

unsigned long long mix_with_reverse_ip_array(unsigned long long val)
{
    unsigned long long result = 0ULL;
    for(int i=0;i<64;i++)
    {
        int shifter = reverse_ip[i];
        unsigned long long bit = BIT(val, (64 - shifter));
        result |= (bit << (64 - i - 1));
    }
    return result;
}

unsigned int mix_with_p_table(unsigned int sbox_out)
{
    unsigned int mixed = 0u;
    for(int i=0; i<32; i++)
    {
        unsigned int bit = BIT(sbox_out, (32-(p[i])));
        mixed |= (bit << ( 32 - i - 1));
    }
    return mixed;
}


unsigned long long f_function(unsigned int RVal, unsigned long long KVal)
{

    // make RVal 48 bit.
    unsigned long long RVal_new = 0ULL;
    for(int i=0;i<48; i++)
    {
        int shifter = e_bit_selection_table[i];
        unsigned long long bit = BIT(RVal, ( 32 - shifter ) );
        #ifdef DEBUG
            printf("bit %llu : %x\n", bit, i);
        #endif // DEBUG
        RVal_new |= ( bit << ( 48 -i - 1) );
        int abcd = 9;
    }

    unsigned long long xor_result = RVal_new ^ KVal;
    int i = 0;
    unsigned int out = 0;
    while(i<8)
    {
        unsigned int B_n = B(xor_result, ++i);
        // calculate S box.
        int row = 0, column = 0;  // 0x20 = 100000, //0x01 = 000001
        row |= B_n & 1;
        row |= (((B_n & 0x20) >> 5 ) << 1 );
        column |= ((B_n >> 1) & 0xF);
        printf("row : %d, column : %d\n", row, column);
        // get number at SN[row][column]
        unsigned int sbox_out = S_ARRAYS[i-1][row][column];
        printf("sbox_out[%d] : %d\n", i, sbox_out);
        out |= (sbox_out << 4 * (8 - i));
    }

    // mix with P table.

    unsigned int f_result = mix_with_p_table(out);

    return f_result;
}


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


unsigned long long mix_message_with_ip2(unsigned long long message)
{
    unsigned long long mixed_message = 0ULL;
    for(int i=0;i<64;i++)
    {
        unsigned long long bit = BIT(message, 64 - ip[i] );
        #ifdef DEBUG
            printf("bit %llu : %x\n", bit, i);
        #endif // DEBUG
            mixed_message |= ( bit << ( 64 - i - 1 ) );
    }
    return mixed_message;

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

void generate_sub_keys_from_original_key(unsigned long long original_key, unsigned long long sub_keys[])
{
    unsigned long long mixed_key = mix_original_key(original_key);  // OK.
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


        sub_keys[i] = mix_with_pc2(cn_dn);
        printf("input : %16llx, output : %16llx\n", cn_dn, sub_keys[i]);

    }
}

unsigned long long
Encrypt(unsigned long long data,
                            unsigned long long key)
{
    unsigned long long K_values[16] = {0};
    generate_sub_keys_from_original_key(key, K_values);
    unsigned long long mixed_msg = mix_message_with_ip2(data);


    unsigned long long L_n[17]={0}
                , R_n[17] = {0};
    L_n[0] = RIGHT(mixed_msg), R_n[0] = LEFT(mixed_msg);

    //Ln = Rn-1
    //Rn = Ln-1 + f(Rn-1, Kn)
    for(int i=1;i<=16;i++)
    {
        L_n[i] = R_n[i - 1];
        R_n[i] = L_n[i-1] ^ f_function(R_n[i-1], K_values[i-1]);
    }

    unsigned long long tar = (R_n[16] << 32) | L_n[16];

    unsigned long long encrypted_message = mix_with_reverse_ip_array(tar);


    return encrypted_message;
}
