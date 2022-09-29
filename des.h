#ifndef DES_H_INCLUDED
#define DES_H_INCLUDED


#define SHIFTLEFT( x , n ) ~( ~( x ) << ( n ) )   // x : 00110011, n : 3 --> SHIFTLEFT(x,n) = 10011
#define RIGHT( x )    ( ( x >> 32 ) & ( 0xFFFFFFFF ))
#define LEFT( x )     ( ( x ) & ( 0xFFFFFFFF ) )
#define BIT( x , y)   ( ( x >> y) & 1 )


static unsigned char ip[64] = { 58, 50, 42, 34, 26, 18, 10, 2,//Init. Permutation
                                60, 52, 44, 36, 28, 20, 12, 4,
                                62, 54, 46, 38, 30, 22, 14, 6,
                                64, 56, 48, 40, 32, 24, 16, 8,
                                57, 49, 41, 33, 25, 17, 9, 1,
                                59, 51, 43, 35, 27, 19, 11, 3,
                                61, 53, 45, 37, 29, 21, 13, 5,
                                63, 55, 47, 39, 31, 23, 15, 7
                                };

static unsigned char iip[64] = { 40, 8, 48, 16, 56, 24, 64, 32,//Inv. Permutation
                                 39, 7, 47, 15, 55, 23, 63, 31,
                                 38, 6, 46, 14, 54, 22, 62, 30,
                                 37, 5, 45, 13, 53, 21, 61, 29,
                                 36, 4, 44, 12, 52, 20, 60, 28,
                                 35, 3, 43, 11, 51, 19, 59, 27,
                                 34, 2, 42, 10, 50, 18, 58, 26,
                                 33, 1, 41, 9, 49, 17, 57, 25
                                 };


//PC1
static unsigned char pc1[56] = { 57, 49, 41, 33, 25, 17, 9,
                                1, 58, 50, 42, 34, 26, 18,
                                10, 2, 59, 51, 43, 35, 27,
                                19, 11, 3, 60, 52, 44, 36,
                                63, 55, 47, 39, 31, 23, 15,
                                7, 62, 54, 46, 38, 30, 22,
                                14, 6, 61, 53, 45, 37, 29,
                                21, 13, 5, 28, 20, 12, 4};

//PC2
static unsigned char pc2[48] = { 14, 17, 11, 24, 1, 5,
                                3, 28, 15, 6, 21, 10,
                                23, 19, 12, 4, 26, 8,
                                16, 7, 27, 20, 13, 2,
                                41, 52, 31, 37, 47, 55,
                                30, 40, 51, 45, 33, 48,
                                44, 49, 39, 56, 34, 53,
                                46, 42, 50, 36, 29, 32};


unsigned long long Encrypt(unsigned long long data, unsigned long long key);
unsigned long long mix_original_key(unsigned long long original_key);
unsigned long long mix_with_pc2(unsigned long long cn_dn);


#endif // DES_H_INCLUDED
